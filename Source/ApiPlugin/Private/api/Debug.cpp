#include "ApiPluginPrivatePCH.h"
#include "api/Debug.h"
#include "Kismet/KismetSystemLibrary.h"
#include <stdio.h>

using namespace npp;
using namespace api;

void Debug::trace(UObject *context, FString value) {
  UKismetSystemLibrary::PrintString(context, value, true, true, FLinearColor(0.0,0.0,0.0));
}
