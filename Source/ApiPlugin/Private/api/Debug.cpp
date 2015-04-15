#include "ApiPluginPrivatePCH.h"
#include "api/Debug.h"
#include "Kismet/KismetSystemLibrary.h"

using namespace api;

/// Notice that the stdout tracing isn't strictly required, but can be useful
/// to track invalid calls to Debug::Trace() causing engine crashes.
void Debug::Trace(UObject *context, FString value) {
  if (context != NULL) {
    printf("DEBUG: %s\n", AS_CSTR(value));
    UKismetSystemLibrary::PrintString(context, value, true, true, FLinearColor(0.0,0.0,0.0));
  }
  else {
    printf("DEBUG: Invalid call to Trace with NULL context value\n");
  }
}

namespace api {
  namespace tests {
    namespace debug {

      /// Print a raw string literal
      void test_trace_raw_string(UObject *context) {
        Debug::Trace(context, "Hello World");
      }

      /// Print a formatted string literal
      void test_trace_formatted_string(UObject *context) {
        Debug::Trace(context, "Hello World %d %s", 100, "Ok");
      }

      /// Print a formatted string literal from FString
      void test_trace_formatted_string(AActor *actor) {
        Debug::Trace(actor, "Hello %s", AS_CSTR(actor->GetName()));
      }
    }
  }
}
