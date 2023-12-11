#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera.generated.h"

UCLASS()
class VRPROJECT_API ACamera : public AActor
{
	GENERATED_BODY()
	
public:	
	ACamera();

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UMeshComponent> Mesh;

	UPROPERTY(EditAnywhere)
	float FlashSpeed;

	UPROPERTY(EditAnywhere)
	float FlashDuration;

	UFUNCTION(BlueprintCallable)
	void Flash(FVector Position,FRotator Rotation);



protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};