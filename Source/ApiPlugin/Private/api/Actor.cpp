#include "ApiPluginPrivatePCH.h"
#include "api/Actor.h"
#include "api/Debug.h"

using namespace npp;
using namespace api;

void Actor::find(UObject *context) {

  UWorld *world = context->GetWorld();
  Debug::trace(context, "Found world: %ld", (long) world);

  for (FConstPawnIterator Iterator = world->GetPawnIterator(); Iterator; ++Iterator) {
    APawn* Pawn = *Iterator;
    if (IsValid(Pawn)) {
      Debug::trace(context, "Found a pawn...");
    }
  }

  for (FConstControllerIterator It = world->GetControllerIterator(); It; ++It) {
    Debug::trace(context, "Found a controller!");
  }

  for (TActorIterator<AActor> ActorItr(world); ActorItr; ++ActorItr )
	{
    FString name = ActorItr->GetName();
    Debug::trace(context, "Found an actor: %s", Debug::as_str(name));
		//ClientMessage(ActorItr->GetName());
  }

  Debug::trace(context, "Completed query");
}
