#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckPoint.generated.h"

UCLASS()
class VRPROJECT_API ACheckPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	ACheckPoint();

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USceneComponent> Scene;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBillboardComponent> Billboard;
#endif 


	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	TObjectPtr<class AMovingWall> MovingWall;

	float lastAngle;
};
