#pragma once

#include "Components/ActorComponent.h"
#include "Marker.generated.h"

/// A marker class that lets items be uniquely identified by id.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class APIPLUGIN_API UMarker : public UActorComponent
{
  GENERATED_BODY()

public:

  // Sets default values for this component's properties
  UMarker();

  // Unique id for this marker
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  int32 id;
};
