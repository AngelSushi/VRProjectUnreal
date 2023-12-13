#pragma once

#include "CoreMinimal.h"
#include "Wall.h"
#include "GameFramework/Actor.h"
#include "MovingWall.generated.h"

class UBoxComponent;
class AWall;
class ACheckPoint;

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
	float LifeTimer;


	UPROPERTY(EditAnywhere)
	float MinDistanceWithPlayer;

	UPROPERTY() 
	FTimerHandle LifeTimerHandle;

	UFUNCTION()
	void DestroyWall();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void CheckForRotation();


private:

	TObjectPtr<class APlayerController> PController;

	float lastAngle;
};
