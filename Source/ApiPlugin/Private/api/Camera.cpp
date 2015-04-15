#include "ApiPluginPrivatePCH.h"
#include "api/Camera.h"
#include "api/Player.h"

using namespace api;

namespace api {
  namespace tests {
    namespace camera {

      /// Project a world coordinate to a screen position
      void test_get_screen_pos_of_world_object(APlayerController *player, AActor *target) {
        auto world_pos = Actor::Position(target);
        auto pos = Camera::WorldToScreen(player, world_pos);
      }

      /// Get the size in pixels of the viewport
      void test_get_viewport_size(APlayerController *player) {
        float dx, dy;
        Camera::Viewport(player, &dx, &dy);
      }

      /// Find all the camera objects that currently exist
      void test_find_cameras(UObject *context) {
        Camera::All(context).Each([] (AActor *a) {
          // ...
        });
      }

      /// Find the first camera object that exists
      void test_find_first_camera(UObject *context) {
        AActor *camera = Camera::All(context).First().Or(NULL);
      }

      /// Find the first camera with a Marker on it
      void test_find_camera_by_marker(UObject *context) {
        AActor *camera = Camera::Marked(context, 1).Or(NULL);
      }

      /// Set the camera for the player
      void test_set_camera(UObject *context) {
        APlayerController *player = Player::Local(context).Or(NULL);
        AActor *camera = Camera::All(context).First().Or(NULL);
        Camera::LookAt(camera, player);
      }
    }
  }
}
