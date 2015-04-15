#include "ApiPluginPrivatePCH.h"
#include "TestApiCmp.h"
#include "Components/ActorComponent.h"

UTestApiCmp::UTestApiCmp() {
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UTestApiCmp::InitializeComponent() {
	Super::InitializeComponent();
}

void UTestApiCmp::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) {
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}
