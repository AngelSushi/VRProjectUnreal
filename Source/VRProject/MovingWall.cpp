#include "MovingWall.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PlayerController.h"
#include "CheckPoint.h"
#include "Kismet/KismetMathLibrary.h"

AMovingWall::AMovingWall()
{
	PrimaryActorTick.bCanEverTick = true;

	Detection = CreateDefaultSubobject<USceneComponent>(TEXT("Detection"));
	Detection->SetupAttachment(Mesh);

}

void AMovingWall::BeginPlay()
{
	Super::BeginPlay();
	PController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	GetWorld()->GetTimerManager().SetTimer(LifeTimerHandle,this,&AMovingWall::DestroyWall, LifeTimer,false);
	
	lastAngle = -1; // Set to -1 to Disable first tick condition enter 
}

void AMovingWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector newPosition = GetActorForwardVector() * Speed * DeltaTime;
	SetActorLocation(GetActorLocation() + newPosition);

	if (!PController || !PController->GetPawn()) {
		return;
	}

	FVector PlayerToWall = PController->K2_GetActorLocation() - Detection->GetComponentLocation();
	FVector Forward = GetActorForwardVector();

	float angle = FVector::DotProduct(PlayerToWall, Forward);

	if (angle < 0 && lastAngle >= 0) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Kill Player"));
	}

	lastAngle = angle;
}


void AMovingWall::CheckForRotation() {
	if (!PController || !PController->GetPawn()) {
		return;
	}

	FRotator LookAt = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PController->GetPawn()->GetActorLocation());
	SetActorRotation(FRotator(0,LookAt.Yaw,0));
}

void AMovingWall::DestroyWall() {
	GetWorld()->GetTimerManager().ClearTimer(LifeTimerHandle);
	Destroy();
}





