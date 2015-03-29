#pragma once

#include "Engine.h"
#include "UObject/UObject.h"
#include "npp/result.h"
#include <memory>
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

namespace api {

  /// Debugging helper
  class Debug {
    public:
      static npp::Result<int32, int32> test(int32 value);

      /// Convert an FString into a const char *
      /// Usage: Debug::as_str(*actor->GetName());
      inline static char *as_str(FString value) {
        return TCHAR_TO_ANSI(*value);
      }

      /// Trace a debug message
      /// Usage: Debug::trace(this, FString::Printf(TEXT("%s"), TEXT("Hello World")));
      static void trace(UObject *context, FString value);

      /// Trace a debug message dynamically
      /// Usage: Debug::trace(this, "%s", "Hello World");
      /// Usage: Debug::trace(context, "Found an actor: %s", Debug::as_str(ActorItr->GetName()));
      template<typename ... Args> static void trace(UObject *context, const string& format, Args ... args) {
        size_t size = 1 + snprintf(nullptr, 0, format.c_str(), args ...);
        unique_ptr<char[]> buf(new char[size]);
        snprintf(buf.get(), size, format.c_str(), args ...);
        auto compiled = string(buf.get(), buf.get() + size);
        Debug::trace(context, FString(&compiled[0]));
      }
  };
}
