#pragma once

#include "Engine.h"
#include "UObject/UObject.h"
#include "api/Debug.h"
#include "npp/result.h"

using namespace std;
using namespace npp;

namespace api {

  /// Actor api
  class Actor {
    public:

      /// Find an actor in the current world
      static void find(UObject *context);

      /// Find first actor component TComponent on the given context and return it.
      /// Usage:
      ///
      ///      api::Actor::get_component<UTestCmp2>(actor).then(
      ///        [&] (UTestCmp2 *v) { api::Debug::trace(this, "Found self! %ld", v); },
      ///        [&] (int32 err) { api::Debug::trace(this, "No such record on target"); }
      ///      );
      ///
      template<typename TComponent> static Result<TComponent *,int32> get_component(AActor *actor) {
        UActorComponent* component = actor->GetComponentByClass(TComponent::StaticClass());
        TComponent *rtn = Cast<TComponent, UActorComponent>(component);
        return rtn ? Ok<TComponent *,int32>(rtn) : Err<TComponent *,int32>(0);
      }
  };
}
