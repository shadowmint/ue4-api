#pragma once

#include "API.h"
#include "npp/format.h"
#include <memory>
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;
using namespace api;

/// Cast an FString to char * for debugging purposes
#define AS_CSTR(value) api::Debug::AsStr(value).c_str()

namespace api {

  /// Debugging helper
  /// see Debug.cpp for usage
  class Debug {
    public:

      /// Internal unsafe buffer cache
      static string _debug;

      /// Convert an FString into a const char *
      /// Nb. Don't call this directly. Use AS_CSTR(value)
      static string AsStr(FString value) {
        string rtn("");
        for (auto i = 0; i < value.Len(); ++i) {
          rtn += (char) value[i];
        }
        return rtn;
      }

      /// Convert a FVector into a const char *
      /// Nb. Don't call this directly. Use AS_CSTR(value)
      static string AsStr(FVector value) {
        return npp::Format("<FVector: %f %f %f>", value.X, value.Y, value.Z);
      }

      /// Convert a FVector2D into a const char *
      /// Nb. Don't call this directly. Use AS_CSTR(value)
      static string AsStr(FVector2D value) {
        return npp::Format("<FVector2D: %f %f>", value.X, value.Y);
      }

      /// Trace a debug message
      static void Trace(UObject *context, FString value);

      /// Trace a debug message dynamically
      template<typename ... Args>
      static void Trace(UObject *context, const string& format, Args ... args) {
        size_t size = 1 + snprintf(nullptr, 0, format.c_str(), args ...);
        unique_ptr<char[]> buf(new char[size]);
        snprintf(buf.get(), size, format.c_str(), args ...);
        auto compiled = string(buf.get(), buf.get() + size);
        Debug::Trace(context, FString(&compiled[0]));
      }
  };
}
