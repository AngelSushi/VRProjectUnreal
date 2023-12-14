#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelEnd.generated.h"

UCLASS()
class VRPROJECT_API ALevelEnd : public AActor
{
	GENERATED_BODY()
	
public:	
	ALevelEnd();

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USceneComponent> Scene;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USceneComponent> TeleportPosition;

	UPROPERTY(EditAnywhere)
	float GameTimer;

	UPROPERTY(EditAnywhere)
	float BlackClipTimer;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class APostProcessVolume> PP_Volume;

	void EndGame();



protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle GameTimerHandle;
	bool bIsEnding;
	float TimeElapsed;

	float StartValue;
	float EndValue;
};
