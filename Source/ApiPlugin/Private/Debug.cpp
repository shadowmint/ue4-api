#include "ApiPluginPrivatePCH.h"
#include "api/Debug.h"
#include "Kismet/KismetSystemLibrary.h"

using namespace npp;
using namespace api;

void Debug::trace(UObject *context, FString value) {
  UKismetSystemLibrary::PrintString(context, value, true, true, FLinearColor(0.0,0.0,0.0));
}

const char *Debug::as_str(FString value) {
  return (const char *) TCHAR_TO_ANSI(*value);
}

Result<int32, int32> Debug::test(int32 value) {
  return Ok<int32, int32>(100);
}
