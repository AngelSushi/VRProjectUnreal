#include "LockPoint.h"
#include "Components/BillboardComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MovingWall.h"
#include "Kismet/KismetSystemLibrary.h"

ALockPoint::ALockPoint()
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

void ALockPoint::BeginPlay()
{
	Super::BeginPlay();

	PController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	MovingWall = Cast<AMovingWall>(UGameplayStatics::GetActorOfClass(GetWorld(), AMovingWall::StaticClass()));
}

void ALockPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PController || !PController->GetPawn()) {
		return;
	}

	if (!MovingWall) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Wall is Empty"));
		MovingWall = Cast<AMovingWall>(UGameplayStatics::GetActorOfClass(GetWorld(), AMovingWall::StaticClass()));
		return;
	}

	FVector WallToCPoint = PController->GetPawn()->GetActorLocation() - GetActorLocation();
	FVector Forward = GetActorForwardVector();

	float angle = FVector::DotProduct(WallToCPoint, Forward);

	if (angle > 0) { // The Player is in the soft lock area 
		// Verifier si le mur le poursuit
		
		float distance = FVector::Distance(PController->GetPawn()->GetActorLocation(),MovingWall->GetActorLocation());
	
		if (distance < MovingWall->MinDistanceWithPlayer) {
			MovingWall->DestroyWall();
			MovingWall = nullptr;
		}
		
	}

	
	lastAngle = angle;
}

