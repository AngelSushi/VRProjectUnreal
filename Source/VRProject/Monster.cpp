#include "Monster.h"

AMonster::AMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	PendingSightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sight"));
	PendingSightMesh->SetupAttachment(Mesh);
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PendingSightMesh->AddWorldRotation(FRotator(0.f,50.f * DeltaTime,0.f));

}

