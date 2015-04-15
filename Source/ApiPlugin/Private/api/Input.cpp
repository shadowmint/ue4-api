#include "ApiPluginPrivatePCH.h"
#include "api/Input.h"
#include "api/World.h"
#include "api/Camera.h"
#include "api/Actor.h"
#include "api/Player.h"
#include "npp/iterator.h"

namespace api {
  namespace tests {
    namespace input {

      /// Get current mouse cursor position in 2D on the viewport in pixels
      void test_get_mouse_position(APlayerController *player) {
        float x, y;
        api::Input::Cursor(player, &x, &y);
      }

      /// Get current mouse cursor position in 2D as a vector
      void test_get_mouse_position_as_vector(APlayerController *player) {
        auto vec = api::Input::Cursor(player);
      }

      /// Project the current mouse position onto the XY plane
      void test_project_mouse_to_relative_vector(APlayerController *player) {
        auto actor = api::Player::Pawn(player);
        auto vec2d = api::Input::CursorFromActor(player, actor);
        auto vec3d = api::Actor::VectorFrom(actor, vec2d, FVector(1.0, 0.0, 0.0), FVector(0.0, 1.0, 0.0));
      }
    }
  }
}
