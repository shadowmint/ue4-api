#pragma once

#include "API.h"
#include "Marker.h"
#include "World.h"
#include "Actor.h"
#include "Kismet/KismetMathLibrary.h"

using namespace api;

namespace api {

  /// Camera api
  /// see Camera.cpp for usage.
  class Camera {
    public:

      /// Return an iterator of all the cameras
      static npp::Iterator<UObject *, AActor *> All(UObject *context) {
        return World::Actors<UCameraComponent>(context);
      }

      /// Find a camera in the scene, by the marker on it.
      /// To use, assign a UMarker to a Camera instance.
      static npp::Option<AActor *> Marked(UObject *context, int marker) {
        npp::Option<AActor*> rtn = npp::None<AActor*>();
        Camera::All(context).Each([&] (AActor *a) {
          auto query = Actor::Components<UMarker>(a);
          Actor::Components<UMarker>(a).Each([&] (UMarker *u) {
            if (u->id == marker) {
              rtn = npp::Some<AActor*>(a);
            }
          });
        });
        return rtn;
      }

      /// Check if an arbitrary AActor is a valid camera
      static bool IsValid(AActor *camera) {
        return (camera != NULL) && World::Actors<UCameraComponent>(camera).Any();
      }

      /// Look at a specific actor
      static void LookAt(AActor *camera, AActor *target) {
        auto from = camera->K2_GetActorLocation();
        auto to = target->K2_GetActorLocation();
        auto rotator = UKismetMathLibrary::FindLookAtRotation(from, to);
        camera->SetActorRotation(rotator);
      }

      /// Get the viewport size in pixels for a specific local player
      /// dx and dy are returned in top-left floating point values.
      static void Viewport(APlayerController *player, float *dx, float *dy) {
        int32 dx32, dy32;
        player->GetViewportSize(dx32, dy32);
        *dx = (float) dx32;
        *dy = (float) dy32;
      }

      /// Project a world point onto a 2D viewport coordinate
      /// The values are top-left floating point pixel values
      static FVector2D WorldToScreen(APlayerController *player, FVector pos) {
        if (player) {
          auto rtn = FVector2D(0, 0);
          player->ProjectWorldLocationToScreen(pos, rtn);
          return rtn;
        }
        return FVector2D(0, 0);
      }
  };
}
