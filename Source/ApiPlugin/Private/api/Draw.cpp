#include "ApiPluginPrivatePCH.h"
#include "api/Draw.h"
#include "api/Input.h"
#include "api/Player.h"
#include "api/Debug.h"

namespace api {
  namespace tests {
    namespace input {

      /// Draw a specific texture on the hud, eg. for a cursor
      void test_draw_texture_on_hud(APlayerController *player, UTexture *texture) {
        auto ui = api::Player::UI(player).Or(NULL);
        if (ui) {
          float x, y;
          api::Input::Cursor(player, &x, &y);
          api::Draw::Texture(ui, texture, x, y);
        }
      }
    }
  }
}
