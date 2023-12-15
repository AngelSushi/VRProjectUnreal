#include "WallPoint.h"
#include "Components/BillboardComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "WPSubSystem.h"
#include "Wall.h"

AWallPoint::AWallPoint()
{
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));

	RootComponent = Scene;

#if WITH_EDITOR
	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	Billboard->SetupAttachment(Scene);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Scene);
#endif
}

void AWallPoint::BeginPlay() {
	Super::BeginPlay();

	PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

void AWallPoint::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (!PC || !PC->GetPawn()) {
		return;
	}

	if (bHasSpawnedWall) {
		return;
	}

	FVector PlayerToPoint = PC->GetPawn()->GetActorLocation() - (GetActorLocation()  + GetActorForwardVector() * 100.f);
	FVector Forward = GetActorForwardVector();

	AActor* RightActor = nullptr;
	AActor* LeftActor = nullptr;

	float angle = FVector::DotProduct(PlayerToPoint, Forward);
	
	UWorld* World = GetWorld();
	check(World);

	FVector Start = GetActorLocation();
	FVector End = Start + GetActorRightVector() * 10000.f;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	FHitResult HitResult;
	bool bHit = World->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, QueryParams);
	
	if (bHit) {
		RightActor = HitResult.GetActor();
	}

	End = Start + GetActorRightVector() * -10000.f;

	bHit = World->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, QueryParams);

	if (bHit) {
		LeftActor = HitResult.GetActor();
	}

	float DistanceTolerance = 500.f;

	if (RightActor && LeftActor) {
		DistanceTolerance = FVector::Distance(RightActor->GetActorLocation(),LeftActor->GetActorLocation());
	}


	float Distance = FVector::Distance(PC->GetPawn()->GetActorLocation(),GetActorLocation());

	if (angle > 0 && Distance <= DistanceTolerance) {

		for (AWall* SWall : SpawningWalls) {
			SWall->SetActorLocation(FVector(SWall->GetActorLocation().X,SWall->GetActorLocation().Y,0.f));
		}
	}
}



