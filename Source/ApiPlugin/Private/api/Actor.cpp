#include "ApiPluginPrivatePCH.h"
#include "test/TestApiCmp.h"
#include "test/TestApiActor.h"
#include "api/Actor.h"

namespace api {
  namespace tests {
    namespace world {

      /// Project a vector relative to the actor in the XY plane
      void test_project_from_actor_in_plane(AActor *actor) {
        auto vec = Actor::VectorFrom(actor, FVector2D(1.7, 2.3), FVector(1.0, 0.0, 0.0), FVector(0.0, 1.0, 0.0));
      }
      /// Find first actor that owns a ULightComponent
      void test_find_actor_component_by_type(AActor *context) {
        UTestApiCmp *result = api::Actor::Component<UTestApiCmp>(context).Or(NULL);
        // ...
      }

      /// Iterate over all components of type T that an actor owns
      void test_find_actor_components_by_type(AActor *context) {
        api::Actor::Components<UTestApiCmp>(context).Each([] (UTestApiCmp *u) {
          // ...
        });
      }

      /// Add an instance of component to an actor
      void test_add_component_to_actor(AActor *context) {
        UTestApiCmp *instance = api::Actor::AddComponent<UTestApiCmp>(context);
      }

      /// Remove an instance of a component from an actor
      void test_remove_component_from_actor(AActor *context) {
        UTestApiCmp *instance = api::Actor::AddComponent<UTestApiCmp>(context);
        api::Actor::RemoveComponent(context, instance);
      }

      /// Remove all instances of a component from an actor
      void test_remove_component_from_actor_by_type(AActor *context) {
        api::Actor::AddComponent<UTestApiCmp>(context);
        api::Actor::AddComponent<UTestApiCmp>(context);
        api::Actor::AddComponent<UTestApiCmp>(context);
        api::Actor::RemoveComponents<UTestApiCmp>(context);
      }

      /// Create a new instance of an actor from a known class type
      void test_create_actor(UObject *context) {
        ATestApiActor *actor = api::Actor::Create<ATestApiActor>(context).Or(NULL);
      }

      /// Create a new instance of an actor from a known class type
      void test_create_actor_from_blueprint(UObject *context, UBlueprintGeneratedClass *factory) {
        // UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Things")
        // UBlueprintGeneratedClass *factory; // <-- Get BP reference here in editor
        AActor *actor = api::Actor::Create(context, factory).Or(NULL);
      }

      /// Destroy an actor from a concrete instance
      void test_destroy_actor(UObject *context) {
        ATestApiActor *actor = api::Actor::Create<ATestApiActor>(context).Or(NULL);
        api::Actor::Destroy(actor);
      }

      /// Move an actor
      void test_move_actor(UObject *context) {
        ATestApiActor *actor = api::Actor::Create<ATestApiActor>(context).Or(NULL);
        api::Actor::Move(actor, FVector(1.0, 5.0, 1.0));
        api::Actor::Move(actor, 1.0, 5.0, 1.0);
      }

      /// Find actor pos
      void test_actor_position(UObject *context) {
        ATestApiActor *actor = api::Actor::Create<ATestApiActor>(context).Or(NULL);
        FVector pos = api::Actor::Position(actor);
      }
    }
  }
}
