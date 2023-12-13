#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LockPoint.generated.h"

UCLASS()
class VRPROJECT_API ALockPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	ALockPoint();

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USceneComponent> Scene;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBillboardComponent> Billboard;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UArrowComponent> Arrow;

#endif

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	TObjectPtr<class APlayerController> PController;
	TObjectPtr<class AMovingWall> MovingWall;

	float lastAngle;
};
