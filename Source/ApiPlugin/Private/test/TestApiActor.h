#pragma once

#include "GameFramework/Actor.h"
#include "TestApiActor.generated.h"

UCLASS()
class APIPLUGIN_API ATestApiActor : public AActor
{
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  ATestApiActor();

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  // Called every frame
  virtual void Tick( float DeltaSeconds ) override;
};
