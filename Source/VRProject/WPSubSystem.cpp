#include "WPSubSystem.h"
#include "MovingWall.h"

void UWPSubSystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);
}

void UWPSubSystem::Deinitialize() {
	Super::Deinitialize();
}

void UWPSubSystem::SpawnWall(UWorld* World,TSubclassOf<class AMovingWall> Wall,FVector SpawnPosition,FRotator Rotation) {
	World->SpawnActor(Wall, &SpawnPosition, &Rotation);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Spawn Wall"));
}