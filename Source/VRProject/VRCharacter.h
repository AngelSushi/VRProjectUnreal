#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "VRCharacter.generated.h"

UCLASS()
class VRPROJECT_API AVRCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AVRCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FHitResult SphereTrace();
	
	UCameraComponent* Camera;
};
