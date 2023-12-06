#include "MovingWall.h"

AMovingWall::AMovingWall()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = Mesh;
}

void AMovingWall::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMovingWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector newPosition = GetActorForwardVector() * speed * DeltaTime;

	SetActorLocation(GetActorLocation() + newPosition);
}

