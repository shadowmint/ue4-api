#pragma once

#include "Components/ActorComponent.h"
#include "TestApiCmp.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class APIPLUGIN_API UTestApiCmp : public UActorComponent
{
  GENERATED_BODY()

public:

  // Sets default values for this component's properties
  UTestApiCmp();

  // Called when the game starts
  virtual void InitializeComponent() override;

  // Called every frame
  virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
};
