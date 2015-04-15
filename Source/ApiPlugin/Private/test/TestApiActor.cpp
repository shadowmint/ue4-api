#include "ApiPluginPrivatePCH.h"
#include "TestApiActor.h"

ATestApiActor::ATestApiActor() {
	PrimaryActorTick.bCanEverTick = true;
}

void ATestApiActor::BeginPlay() {
	Super::BeginPlay();
}

void ATestApiActor::Tick( float DeltaTime ) {
	Super::Tick( DeltaTime );
}
