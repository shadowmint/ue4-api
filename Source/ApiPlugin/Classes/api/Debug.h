#pragma once

#include "Engine.h"
#include "UObject/UObject.h"
#include "npp/result.h"

namespace api {

  /// Debugging helper
  class Debug {
    public:
      static void trace(UObject *context, FString value);
      static npp::Result<int32, int32> test(int32 value);
  };
}
