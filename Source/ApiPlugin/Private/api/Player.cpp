#include "ApiPluginPrivatePCH.h"
#include "api/Player.h"
#include "api/World.h"
#include "api/Camera.h"
#include "npp/iterator.h"

namespace api {
  namespace tests {
    namespace player {

      /// Get the current HUD, if any, from the local player
      void test_get_ui(UObject *context) {
        auto player = api::Player::Local(context).Or(NULL);
        auto hud = api::Player::UI(player).Then([] (AHUD *hud) {
          // ...
        });
      }

      void test_find_players(UObject *context) {
        api::Player::All(context).Each([] (APlayerController *a) {
          // ...
        });
      }

      void test_find_local_players(UObject *context) {
        api::Player::Locals(context).Each([] (APlayerController *a) {
          // ...
        });
      }

      void test_find_local_player(UObject *context) {
        APlayerController *player = api::Player::Local(context).Or(NULL);
      }

      void test_set_camera(UObject *context) {
        APlayerController *player = api::Player::Local(context).Or(NULL);
        AActor *camera = api::Camera::All(context).First().Or(NULL);
        api::Player::SetCamera(player, camera);
      }

      void test_get_pawn_for_player(UObject *context) {
        api::Player::Local(context).Then([] (APlayerController *player) {
          APawn *game_object = api::Player::Pawn(player);
        });
      }
    }
  }
}
