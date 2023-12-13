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


protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
