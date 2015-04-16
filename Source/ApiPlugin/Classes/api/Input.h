#pragma once

#include "API.h"
#include "Camera.h"
#include "Actor.h"
#include "Debug.h"

using namespace api;

namespace api {

  /// User input api
  /// see Input.cpp for usage.
  class Input {
    public:

      /// Get the mouse position for a specific player
      /// Default to cursor id 0 for this query
      static void Cursor(APlayerController *player, float *x, float *y) {
        bool down;
        Input::Cursor(player, 0, x, y, &down);
      }

      /// Get the mouse position & downness for a specific player
      /// Default to cursor id 0 for this query
      static void Cursor(APlayerController *player, float *x, float *y, bool *down) {
        Input::Cursor(player, 0, x, y, down);
      }

      /// Get the mouse position for a specific player
      /// Default to cursor id 0 for this query
      static FVector2D Cursor(APlayerController *player) {
        bool down;
        float x, y;
        Input::Cursor(player, 0, &x, &y, &down);
        return FVector2D(x, y);
      }

      /// Get the mouse position for a specific player
      static void Cursor(APlayerController *player, int32 id, float *x, float *y, bool *down) {
        if (player) {
          if (!player->GetMousePosition(*x, *y)) {
            ETouchIndex::Type type;
            switch (id) {
              case 0:
                type = ETouchIndex::Touch1;
              case 1:
                type = ETouchIndex::Touch2;
              case 2:
                type = ETouchIndex::Touch3;
              case 3:
                type = ETouchIndex::Touch4;
              case 4:
                type = ETouchIndex::Touch5;
              case 5:
                type = ETouchIndex::Touch6;
              case 6:
                type = ETouchIndex::Touch7;
              case 7:
                type = ETouchIndex::Touch8;
              case 8:
                type = ETouchIndex::Touch9;
              case 9:
                type = ETouchIndex::Touch10;
              default:
                type = ETouchIndex::Touch10;
            }
            player->GetInputTouchState(type, *x, *y, *down);
          }
          else {
            FKey key;
            switch (id) {
              case 0:
                key = EKeys::LeftMouseButton;
              case 1:
                key = EKeys::RightMouseButton;
              case 2:
                key = EKeys::MiddleMouseButton;
              case 3:
                key = EKeys::ThumbMouseButton;
              case 4:
                key = EKeys::ThumbMouseButton2;
              default:
                key = EKeys::LeftMouseButton;
            }
            *down = player->IsInputKeyDown(key);
          }
        }
      }

      /// Return a 2D offset from the target actor to the current cursor position.
      /// To project this into a 3D vector on a plane, see Actor::Project
      static FVector2D CursorFromActor(APlayerController *player, AActor *target) {
        auto player_loc = Actor::Position(target);
        auto player_pos = Camera::WorldToScreen(player, player_loc);

        // If the user has configured a resolution quality we need to multiply
        // the pixels by the resolution quality to arrive at the true position in
        // the viewport, as the rendered image will be stretched to fill whatever
        // size the viewport is at.
        Scalability::FQualityLevels ScalabilityQuality = Scalability::GetQualityLevels();
        float QualityScale = ( ScalabilityQuality.ResolutionQuality / 100.0f );
        player_pos = player_pos / QualityScale;

        auto mouse_pos = Input::Cursor(player);
        auto rtn = mouse_pos - player_pos;
        rtn.Y = -rtn.Y; // Swap into y = up mode
        return rtn;
      }
  };
}
