#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LoadArea.generated.h"

UCLASS()
class VRPROJECT_API ALoadArea : public AActor
{
	GENERATED_BODY()
	
public:	
	ALoadArea();

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBoxComponent> Box;

	UPROPERTY(EditAnywhere)
	FName AreaLevelStreamingName;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
