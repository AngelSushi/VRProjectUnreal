#include "Wall.h"

AWall::AWall()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;


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


}

