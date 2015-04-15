#include "ApiPluginPrivatePCH.h"
#include "test/TestApiCmp.h"
#include "test/TestApiActor.h"
#include "api/World.h"

using namespace api;

namespace api {
  namespace tests {
    namespace world {

      /// Find first actor that owns a component
      void test_find_actor_by_component_type(UObject *context) {
        AActor *result = World::Actor<UTestApiCmp>(context).Or(NULL);
        // ...
      }

      /// Iterate over all actors that own a component
      void test_find_actors_by_component_type(UObject *context) {
        World::Actors<UTestApiCmp>(context).Each([] (AActor *a) {
          // ...
        });
      }

      /// Find first actor that is a specific type
      void test_find_actor_by_type(UObject *context) {
        AActor *result = World::Actor<ATestApiActor>(context).Or(NULL);
        // ...
      }

      /// Iterate over all actors that are a specific type
      void test_find_actors_by_type(UObject *context) {
        World::Actors<ATestApiActor>(context).Each([] (AActor *a) {
          // ...
        });
      }
    }
  }
}
