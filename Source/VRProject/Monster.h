#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Monster.generated.h"

UCLASS()
class VRPROJECT_API AMonster : public AActor
{
	GENERATED_BODY()
	
public:	
	AMonster();

	UPROPERTY(EditAnywhere) 
	TObjectPtr<class USkeletalMeshComponent> SkeletalMesh;
	
	UPROPERTY(EditAnywhere) 
	TObjectPtr<class UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> PendingSightMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USceneComponent> Sight;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float WallSpawnDistance;

	UPROPERTY(EditAnywhere)
	float RayCastRadius;

	UPROPERTY(EditAnywhere)
	float RayCastDistance;

private:
	bool bIsRotating;
};
