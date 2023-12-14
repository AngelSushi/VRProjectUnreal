#include "WPSubSystem.h"
#include "MovingWall.h"
#include "Kismet/GameplayStatics.h"
#include "CheckPoint.h"
#include "Math/NumericLimits.h"

void UWPSubSystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);
}

void UWPSubSystem::Deinitialize() {
	Super::Deinitialize();
}

void UWPSubSystem::SpawnWall(UWorld* World,TSubclassOf<class AWall> Wall,FVector SpawnPosition,FRotator Rotation) {
	World->SpawnActor(Wall, &SpawnPosition, &Rotation);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Spawn Wall"));
}

void UWPSubSystem::SpawnWall(UWorld* World, TSubclassOf<class AWall> Wall, FVector SpawnPosition, FRotator Rotation,FVector Scale) {
	AActor* WallInstance = World->SpawnActor(Wall, &SpawnPosition, &Rotation);
	WallInstance->SetActorScale3D(Scale);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Spawn Wall"));
}