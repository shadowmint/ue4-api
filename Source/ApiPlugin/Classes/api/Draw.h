#pragma once

#include "API.h"

using namespace api;

namespace api {

  /// 2D drawing api
  /// see Draw.cpp for usage.
  class Draw {
    public:

      /// Draw an entire texture to the HUD
      /// NB. This wont do anything, unless you call it on a HUD redraw event
      /// The x,y are in top-left coordinate formats, in pixels.
      static void Texture(AHUD *context, UTexture *texture, float x, float y) {
        context->DrawTextureSimple(texture, x, y);
      }
  };
}
