#pragma once

#include "API.h"
#include "Events.h"
#include "Components/PrimitiveComponent.h"

using namespace api;

namespace api {

  /// Physics api
  /// see Physics.cpp for usage.
  /// Notice these functions only work if the object has physics enabled,
  /// and have an attached scene component that can be modified.
  class Physics {
    public:

      /// Get the primitive component for an actor, if any.
      static npp::Option<UPrimitiveComponent*> Primitive(AActor *context) {
        auto root = Cast<UPrimitiveComponent>(context->K2_GetRootComponent());
        if (root) {
          auto body = root->GetBodyInstance();
          if (body && body->IsInstanceSimulatingPhysics())
            return npp::Some<UPrimitiveComponent*>(root);
        }
        return npp::None<UPrimitiveComponent*>();
      }

      /// Set the linear velocity of the given actor to the given vector.
      static void SetVelocity(AActor *context, FVector velocity) {
        Physics::Primitive(context).Then([&] (UPrimitiveComponent *mesh) {
          mesh->SetPhysicsLinearVelocity(velocity);
        });
      }

      /// Add a callback for an overlap start event
      static void BindOnOverlap(AActor *context, Event<AActor*, OnOverlapHandler> *handler) {
        Physics::Primitive(context).Then([&] (UPrimitiveComponent *c) {
          handler->context = context;
          auto ref = &Event<AActor*, OnOverlapHandler>::OnOverlapCallback;
          c->OnComponentBeginOverlap.AddDynamic(handler, ref);
        });
      }
  };
}
