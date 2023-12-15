#include "Wall.h"

AWall::AWall()
{
	PrimaryActorTick.bCanEverTick = true;
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Scene);


}

void AWall::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWall::Flash() {
	if (!bCanBeFlashed) {
		return;
	}

	Destroy();

}

