#include "CheckPoint.h"
#include "Kismet/GameplayStatics.h"
#include "MovingWall.h"
#include "Components/BillboardComponent.h"
#include "Components/ArrowComponent.h"
#include "WPSubSystem.h"

ACheckPoint::ACheckPoint()
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

void ACheckPoint::BeginPlay() {
	Super::BeginPlay();

	MovingWall = Cast<AMovingWall>(UGameplayStatics::GetActorOfClass(GetWorld(), AMovingWall::StaticClass()));
	PController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACheckPoint::StaticClass(), CheckPoints);
}

void ACheckPoint::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (!PController || !PController->GetPawn()) {
		return;
	}

	if (!MovingWall) {
		MovingWall = Cast<AMovingWall>(UGameplayStatics::GetActorOfClass(GetWorld(), AMovingWall::StaticClass()));
		return;
	}

	if (!IsNearestCheckPoint()) {
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

bool ACheckPoint::IsNearestCheckPoint() {
	float MaxDistance = TNumericLimits<float>::Max();
	AActor* NearestCheckPoint = nullptr;

	for (AActor* checkpoint : CheckPoints) {

		float distance = FVector::Distance(PController->GetPawn()->GetActorLocation(), checkpoint->GetActorLocation());

		if (distance <= MaxDistance) {
			NearestCheckPoint = checkpoint;
			MaxDistance = distance;
		}
	}

	if (!NearestCheckPoint) {
		return false;
	}

	return NearestCheckPoint == this;
}




