#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlashLight.generated.h"

UCLASS()
class VRPROJECT_API AFlashLight : public AActor
{
	GENERATED_BODY()
	
public:	
	AFlashLight();

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UPointLightComponent> Light;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
