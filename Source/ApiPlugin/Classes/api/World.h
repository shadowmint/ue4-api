#pragma once

#include "API.h"

using namespace api;

namespace api {

  /// World  api
  /// see world.cpp for usage
  class World {
    public:

      /// Return an iterator of AActor objects that own a given component marker T
      /// @param T An Actor or ActorComponent type
      /// @param context The context to query on
      template<typename T>
      static npp::Iterator<UObject*, AActor*> Actors(UObject *context) {
        return npp::iter<UObject, AActor*>(context, [] (UObject *context, std::function< bool(AActor *value) > handler) {
          for (TObjectIterator<T> Itr; Itr; ++Itr ) {
            if (Itr->IsA(UActorComponent::StaticClass())) {
              UActorComponent* cmp = Cast<UActorComponent>(*Itr);
              AActor* actor = Cast<AActor>(Itr->GetOwner());
              if (actor != NULL) {
                if (!handler(actor)) {
                  break;
                }
              }
            }
            else if (Itr->IsA(AActor::StaticClass())) {
              auto actor = Cast<AActor>(*Itr);
              if (!handler(actor)) {
                break;
              }
            }
          }
        });
      }

      /// The first matching actor that owns a marker component of type T
      /// @param T An Actor or ActorComponent type
      /// @param context The context to query on
      template<typename T>
      static npp::Option<AActor*> Actor(UObject *context) {
        return World::Actors<T>(context).First();
      }
  };
}
