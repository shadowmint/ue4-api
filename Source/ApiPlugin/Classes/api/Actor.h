#pragma once

#include "Engine.h"
#include "UObject/UObject.h"
#include "api/Debug.h"

using namespace std;

namespace api {

  /// Actor api
  class Actor {
    public:

      /// Find an actor in the current world
      static void find(UObject *context);

      /// Find an actor by component type
      /// Usage: ...
      template<typename T> static void find_components(UObject *context) {
        /*for (TActorIterator<T> ActorItr(context->GetWorld()); ActorItr; ++ActorItr) {
          Debug::trace(context, "Found an typed actor: %s", Debug::as_str(ActorItr->GetName()));
        }*/
        for (TActorIterator<AActor> ActorItr(context->GetWorld()); ActorItr; ++ActorItr )
        {
          Debug::trace(context, "Found an actor: %ld - %s", (long) ActorItr, Debug::as_str(*ActorItr->GetName()));
          //ClientMessage(ActorItr->GetName());
        }

        for (TObjectIterator<T> Itr; Itr; ++Itr ) {
          Debug::trace(context, "Found an instance of the given component");
          Debug::trace(context, Itr->GetDesc());
          auto actor = Cast<AActor>(Itr->GetOwner());
          Debug::trace(context, "Component owner: %s", Debug::as_str(*actor->GetName()));
          //Debug::trace(context, "Found a component: %s", Debug::as_str(actor->GetName()));
        }
      }
  };
}
