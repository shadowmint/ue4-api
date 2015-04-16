#pragma once

#include "API.h"
#include <functional>

namespace api {

  /// Common typedefs
  typedef std::function< void(AActor *context, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) > OnOverlapHandler;

  /// A common delegate wrapper for all the UE4 functions.
  template<typename TContext, typename TCallback>
  class Event : public UObject {
    public:

      /// The context this callback should be invoked with
      TContext context;

      /// The actual type of this callback
      TCallback callback;

      /// Create a new instance
      Event(TContext context, TCallback callback) {
        this.context = context;
        this.callback = callback;
      }

      /// Handle OnOverlapCallbacks
      void OnOverlapCallback(AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
        callback(context, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
      }
  };
}
