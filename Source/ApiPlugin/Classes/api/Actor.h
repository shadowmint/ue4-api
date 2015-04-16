#pragma once

#include "API.h"

using namespace api;

namespace api {

  /// Actor api
  /// see Actor.cpp for usage
  class Actor {
    public:

      /// Return an Option for a new instance of T
      /// NB. This can only fail if T is NULL, eg. blueprint binding not set
      template<typename T>
      static npp::Option<T *> Create(UObject *context) {
        auto world = context->GetWorld();
        T *actor = world->SpawnActor<T>();
        if (actor)
          return npp::Some<T*>(actor);
        return npp::None<T*>();
      }

      /// Return an Option for a new instance of T
      /// NB. This can only fail if T is NULL, eg. blueprint binding not set
      static npp::Option<AActor *> Create(UObject *context, UClass *T) {
        auto world = context->GetWorld();
        AActor *actor = world->SpawnActor(T);
        if (actor)
          return npp::Some<AActor*>(actor);
        return npp::None<AActor*>();
      }

      /// Destroy the actor instance given
      static void Destroy(AActor *target) {
        auto world = target->GetWorld();
        world->DestroyActor(target);
      }

      /// Return an iterator of component T objects that belong to the given actor
      template<typename T>
      static npp::Iterator<AActor*, T*> Components(AActor *context) {
        return npp::iter<AActor, T*>(context, [&] (AActor *actor, std::function< bool(T *value) > handler) {
          if (actor != NULL) {
            TArray<UActorComponent*> items = actor->GetComponentsByClass(T::StaticClass());
            for (auto query = items.CreateIterator(); query; ++query) {
              UActorComponent *cmp = *query;
              if (cmp->IsA(T::StaticClass())) {
                T *ref = Cast<T>(cmp);
                if (!handler(ref)) {
                  break;
                }
              }
            }
          }
        });
      }

      /// Return first component T that belongs to the given actor
      template<typename T>
      static npp::Option<T*> Component(AActor *context) {
        return Actor::Components<T>(context).First();
      }

      /// Add a new instance of component T to the actor context
      template<typename T>
      static T *AddComponent(AActor *context) {
        T* rtn = NewObject<T>(context);
        context->AddOwnedComponent(rtn);
        return rtn;
      }

      /// Remove all components of type T from the context
      template<typename T>
      static void RemoveComponents(AActor *context) {
        Actor::Components<T>(context).Each([&] (T *instance) {
          Actor::RemoveComponent(context, instance);
        });
      }

      /// Remove a specific component from the actor
      template<typename T>
      static void RemoveComponent(AActor *context, T* instance) {
        if (instance->IsA(UActorComponent::StaticClass())) {
          UActorComponent *cmp = Cast<UActorComponent>(instance);
          context->RemoveOwnedComponent(cmp);
        }
      }

      /// Move an actor to the given coordinates
      static void Move(AActor *context, FVector target) {
        context->SetActorLocation(target);
      }

      /// Move an actor to the given coordinates
      static void Move(AActor *context, float x, float y, float z) {
        Actor::Move(context, FVector(x, y, z));
      }

      /// Return the current position of the actor
      static FVector Position(AActor *context) {
        return context->GetActorLocation();
      }

      /// Project the given 2D vector into a 3D vector from the actor position
      /// The new vector will be in the 3D plane specified by the combination of
      /// the actors current position and the two offset vectors x and y.
      /// ie. To project in the X,Y place you would use:
      /// Project(actor, src, FVector(1, 0, 0), FVector(0, 1, 0));
      static FVector VectorFrom(AActor *actor, FVector2D vec, FVector x, FVector y) {
        auto vx = x * vec.X / x.Size();
        auto vy = y * vec.Y / y.Size();
        return vx + vy;
      }

      /// Project the given 2D vector into a 3D vector from the actor position
      /// As per VectorFrom, but the result is a unit vector instead.
      static FVector UnitVectorFrom(AActor *actor, FVector2D vec, FVector x, FVector y) {
        auto rtn = VectorFrom(actor, vec, x, y);
        auto size = rtn.Size();
        if (size > 0) {
          return rtn / size;
        }
        return rtn;
      }
  };
}
