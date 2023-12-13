#pragma once

#include "CoreMinimal.h"
#include "Flashable.h"
#include "GameFramework/Actor.h"
#include "Wall.generated.h"

UCLASS()
class VRPROJECT_API AWall : public AActor,public IFlashable
{
	GENERATED_BODY()
	
public:	
	AWall();

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USceneComponent> Scene;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere)
	bool bCanBeFlashed;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void Flash() override;

};
