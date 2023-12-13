#include "LevelEnd.h"

ALevelEnd::ALevelEnd()
{
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;

}

void ALevelEnd::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALevelEnd::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

