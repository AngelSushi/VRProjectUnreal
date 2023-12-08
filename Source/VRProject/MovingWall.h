#pragma once

#include "CoreMinimal.h"
#include "Wall.h"
#include "GameFramework/Actor.h"
#include "MovingWall.generated.h"

class UBoxComponent;
class AWall;

UCLASS()
class VRPROJECT_API AMovingWall : public AWall
{
	GENERATED_BODY()
	
public:	
	AMovingWall();

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USceneComponent> Detection;

	UPROPERTY(EditAnywhere)
	float Speed;

	UPROPERTY(EditAnywhere)
	float MaxDistanceToWall;

	UFUNCTION()
	void DestroyWall();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	bool bChangeWallDirection;
	bool bLastChangeWallDirection;

	bool CheckIfPlayerIsInWall(APlayerController*);
};
