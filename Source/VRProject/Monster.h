#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Monster.generated.h"

UCLASS()
class VRPROJECT_API AMonster : public AActor
{
	GENERATED_BODY()
	
public:	
	AMonster();

	UPROPERTY(EditAnywhere) 
	TObjectPtr<class UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> PendingSightMesh;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
