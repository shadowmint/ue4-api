#include "ApiPluginPrivatePCH.h"
#include "api/Debug.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "api/Physics.h"

namespace api {
  namespace tests {
    namespace input {

      /// Set the absolute world velocity of an actor's root component
      void test_set_velocity(AActor *actor) {
        api::Physics::SetVelocity(actor, FVector(100.0, 0.0, 0.0));
      }
    }
  }
}
