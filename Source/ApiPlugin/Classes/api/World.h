#pragma once

#include "Engine.h"
#include "UObject/UObject.h"
#include "api/Debug.h"

using namespace std;

namespace api {

  /// Actor api
  class World {
    public:

      /// Find a list of components in the world matching the given type T
      /// Usage: 
      template<typename T> static void find_components(UObject *context) {
        for (TObjectIterator<T> Itr; Itr; ++Itr ) {
          Debug::trace(context, "Found an instance of the given component");
          auto actor = Cast<AActor>(Itr->GetOwner());
          Debug::trace(context, "Component owner: %s", Debug::as_str(actor->GetName()));
          //Debug::trace(context, "Found a component: %s", Debug::as_str(actor->GetName()));
        }
      }
  };
}
