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
	
}

void AMovingWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector newPosition = GetActorForwardVector() * Speed * DeltaTime;
	SetActorLocation(GetActorLocation() + newPosition);

	if (!PController || !PController->GetPawn()) {
		return;
	}

	if (CheckIfPlayerIsInWall()) {
		// Kill Player
	}
}


void AMovingWall::CheckForRotation() {
	if (!PController || !PController->GetPawn()) {
		return;
	}

	UWorld* World = GetWorld();
	check(World);

	FVector Start = GetActorLocation();
	FVector End = Start + GetActorForwardVector() * 10000000000.f;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	FHitResult HitResult;
	bool bRotate = true;
	bool bHit = World->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_WorldDynamic, QueryParams);
	if (bHit)
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(HitResult.GetActor())) {
			//bRotate = false;
		}
	}


	if (bRotate) {
		FRotator LookAt = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PController->GetPawn()->GetActorLocation());
		SetActorRotation(FRotator(0,LookAt.Yaw,0));

		GetWorld()->GetTimerManager().ClearTimer(LifeTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(LifeTimerHandle, this, &AMovingWall::DestroyWall, LockTimer, false);
	}
}

void AMovingWall::DestroyWall() {
	Destroy();
}



bool AMovingWall::CheckIfPlayerIsInWall() {
	FVector PlayerToWall = PController->K2_GetActorLocation() - Detection->GetComponentLocation();
	FVector Forward = GetActorForwardVector();

	float angle = FVector::DotProduct(PlayerToWall, Forward);

	return angle < 0;
}


