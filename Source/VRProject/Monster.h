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
	TObjectPtr<USkeletalMeshComponent> SkeletalMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> PendingSightMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class USplineComponent> SplineComp;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float WallSpawnDistance;

	UPROPERTY(EditAnywhere)
	float RayCastRadius = 50.f;

	UPROPERTY(EditAnywhere)
	float RayCastDistance = 1000.f;

private:
	bool bIsRotating;

	float Distance = 0;
};
