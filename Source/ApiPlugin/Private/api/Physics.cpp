#include "ApiPluginPrivatePCH.h"
#include "api/Debug.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "api/Physics.h"
#include "api/Events.h"

namespace api {
  namespace tests {
    namespace input {

      /// Bind a delegate to be invoked when a collision occurs
      /*void test_bind_a_collision_callback(AActor *actor) {
        auto handler = new Event(actor, [] (AActor *context, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
          // ...
        });
        api::Physics::BindOnOverlap(actor, handler);
      }*/

      /// Set the absolute world velocity of an actor's root component
      void test_set_velocity(AActor *actor) {
        api::Physics::SetVelocity(actor, FVector(100.0, 0.0, 0.0));
      }
    }
  }
}
