#pragma once

#include "API.h"
#include "World.h"
#include "Camera.h"

using namespace api;

namespace api {

  /// Player api
  /// see Player.cpp for usage.
  class Player {
    public:

      /// Return an iterator of all player controllers
      static npp::Iterator<UObject*, APlayerController*> All(UObject *context) {
        return npp::iter<UObject, APlayerController*>(context, [] (UObject *context, std::function< bool(APlayerController *value) > handler) {
          World::Actors<APlayerController>(context).iter(context, [&] (AActor *actor) {
            APlayerController *controller = Cast<APlayerController>(actor);
            if (controller != NULL) {
              return handler(controller);
            }
            return true;
          });
        });
      }

      /// Return an iterator of all the local controllers
      /// NB. Local, as in, only when IsLocalPlayerController() is true.
      static npp::Iterator<UObject*, APlayerController*> Locals(UObject *context) {
        return npp::iter<UObject, APlayerController*>(context, [] (UObject *context, std::function< bool(APlayerController *value) > handler) {
          World::Actors<APlayerController>(context).iter(context, [&] (AActor *actor) {
            APlayerController *controller = Cast<APlayerController>(actor);
            if (controller != NULL) {
              if (controller->IsLocalPlayerController()) {
                return handler(controller);
              }
            }
            return true;
          });
        });
      }

      /// Return the first local player
      /// NB. Local, as in, only when IsLocalPlayerController() is true.
      static npp::Option<APlayerController*> Local(UObject *context) {
        return Locals(context).First();
      }

      /// Set the camera for the given context
      static void SetCamera(APlayerController *player, AActor *camera) {
        if (player != NULL) {
          if (Camera::IsValid(camera)) {
            player->SetViewTarget(camera);
          }
        }
      }

      /// Get the camera for the given context
      static npp::Option<AActor*> Camera(APlayerController *player) {
        if (player != NULL) {
          auto cam = player->GetViewTarget();
          if (Camera::IsValid(cam)) {
            return npp::Some<AActor*>(cam);
          }
        }
        return npp::None<AActor*>();
      }

      /// Get the actor which is the pawn (ie. game world object) for this player
      static APawn *Pawn(AController *player) {
        APawn *rtn = player->GetCharacter();
        if (!rtn) {
          rtn = player->GetPawn();
        }
        return rtn;
      }

      /// Return the current UI interface for the player
      static npp::Option<AHUD*> UI(APlayerController *player) {
        if (player) {
          AHUD *rtn = player->GetHUD();
          if (rtn)
            return npp::Some<AHUD*>(rtn);
        }
        return npp::None<AHUD*>();
      }
  };
}
