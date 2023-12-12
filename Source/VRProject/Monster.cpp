#include "Monster.h"
#include "Kismet/KismetSystemLibrary.h"

AMonster::AMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	PendingSightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sight"));
	PendingSightMesh->SetupAttachment(Mesh);

	Sight = CreateDefaultSubobject<USceneComponent>(TEXT("SightPosition"));
	Sight->SetupAttachment(Mesh);
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
	bIsRotating = true;
}

void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsRotating) {
		PendingSightMesh->AddWorldRotation(FRotator(0.f, 50.f * DeltaTime, 0.f));
	}

	UWorld* World = GetWorld();
	check(World);

	FVector Start = Sight->GetComponentLocation();
	FVector End = Start + PendingSightMesh->GetForwardVector() * 1000.f;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	FHitResult HitResult;
	bool bHit = World->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, QueryParams);
	if (bHit)
	{
		
	}


}

