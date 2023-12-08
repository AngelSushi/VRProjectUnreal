#include "MovingWall.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PlayerController.h"


AMovingWall::AMovingWall()
{
	PrimaryActorTick.bCanEverTick = true;

	Detection = CreateDefaultSubobject<USceneComponent>(TEXT("Detection"));
	Detection->SetupAttachment(Mesh);

}

void AMovingWall::BeginPlay()
{
	Super::BeginPlay();
	bLastChangeWallDirection = true;
	
}

void AMovingWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

		FVector newPosition = GetActorForwardVector() * Speed * DeltaTime;
		SetActorLocation(GetActorLocation() + newPosition);

		APlayerController* PController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		if (!PController || !PController->GetPawn()) {
			return;
		}

		if (CheckIfPlayerIsInWall(PController)) {
			// Kill Player
		}

		 bChangeWallDirection = true;

		 UWorld* World = GetWorld();
		 check(World);

		 FVector Start = PController->K2_GetActorLocation();
		 FVector End = Start + PController->GetPawn()->GetActorForwardVector() * MaxDistanceToWall;

		 FCollisionQueryParams QueryParams;


		 FHitResult HitResult;

		 bool bHit = World->LineTraceSingleByChannel(HitResult, Start, End,ECollisionChannel::ECC_Visibility, QueryParams);

		 if (bHit) {
			 if (AWall* Wall = Cast<AWall>(HitResult.GetActor())) {
				 GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Hit Wall"));
				
				 GLog->Log(HitResult.GetActor()->GetName());
				 bChangeWallDirection = false;
			 }
		 }


		 if (bChangeWallDirection  && !bLastChangeWallDirection) {
			 GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Yellow, TEXT("Change Wall"));
			 
		 }

		 bLastChangeWallDirection = bChangeWallDirection;
	
}

void AMovingWall::DestroyWall() {}

bool AMovingWall::CheckIfPlayerIsInWall(APlayerController* PController) {
	FVector PlayerToWall = PController->K2_GetActorLocation() - Detection->GetComponentLocation();
	FVector Forward = GetActorForwardVector();

	float angle = FVector::DotProduct(PlayerToWall, Forward);

	return angle < 0;
}


