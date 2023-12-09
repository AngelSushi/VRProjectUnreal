#include "CheckPoint.h"
#include "Kismet/GameplayStatics.h"
#include "MovingWall.h"
#include "Components/BillboardComponent.h"

ACheckPoint::ACheckPoint()
{
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;

#if WITH_EDITOR
	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	Billboard->SetupAttachment(Scene);
#endif
}

void ACheckPoint::BeginPlay() {
	Super::BeginPlay();

	MovingWall = Cast<AMovingWall>(UGameplayStatics::GetActorOfClass(GetWorld(), AMovingWall::StaticClass()));
}

void ACheckPoint::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (!MovingWall) {
		return;
	}

	FVector WallToCPoint = MovingWall->GetActorLocation() - GetActorLocation();
	FVector Forward = GetActorForwardVector();

	float angle = FVector::DotProduct(WallToCPoint, Forward);

	if (angle >= 0 && lastAngle < 0) {
		MovingWall->CheckForRotation();
	}

	lastAngle = angle;
}





