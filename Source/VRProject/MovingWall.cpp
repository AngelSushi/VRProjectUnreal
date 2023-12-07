#include "MovingWall.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

AMovingWall::AMovingWall()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Detection = CreateDefaultSubobject<USceneComponent>(TEXT("Detection"));
	Detection->SetupAttachment(Mesh);

}

void AMovingWall::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMovingWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsFollowingPlayer) {
		FVector newPosition = GetActorForwardVector() * speed * DeltaTime;
		SetActorLocation(GetActorLocation() + newPosition);

		APlayerController* PController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		FVector PlayerToWall = PController->K2_GetActorLocation() - Detection->GetComponentLocation();
		FVector Forward = GetActorForwardVector();

		float angle = FVector::DotProduct(PlayerToWall, Forward);

		 if(angle < 0) {
			 // Killed Player 
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("InBack"));
		}
	}
}

