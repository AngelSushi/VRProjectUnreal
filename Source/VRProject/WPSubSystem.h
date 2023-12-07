#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "WPSubSystem.generated.h"

class AMovingWall;

UCLASS()
class VRPROJECT_API UWPSubSystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public: 

	void Initialize(FSubsystemCollectionBase& Collection) override;

	void Deinitialize() override;

	static void SpawnWall(UWorld*,TSubclassOf<class AMovingWall>,FVector,FRotator);

private:
	static UClass* WallBPClass;
};
