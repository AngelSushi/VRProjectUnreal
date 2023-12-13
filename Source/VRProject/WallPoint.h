#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WallPoint.generated.h"

UCLASS()
class VRPROJECT_API AWallPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	AWallPoint();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USceneComponent> Scene;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBillboardComponent> Billboard;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UArrowComponent> Arrow;
#endif 

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AWall> Wall;
private: 

	TObjectPtr<class APlayerController> PC;

	bool bHasSpawnedWall;

protected:
	virtual void BeginPlay() override;


public:
	virtual void Tick(float DeltaTime) override;
};
