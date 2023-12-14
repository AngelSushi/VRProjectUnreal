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

	CheckForDeath();

	if (!bCheckHasChangedDirection) {
		//StartForward = PController->GetPawn()->GetActorForwardVector();
		//bCheckHasChangedDirection = true;
		//GetWorld()->GetTimerManager().SetTimer(LocationTimer,this,&AMovingWall::CheckChangeLocation,1.f,false);
	}

	// Récupérer quand le joueur change de position, récupérer la direction et l'endroit ou on a changer de direction 

	
}

void AMovingWall::CheckChangeLocation() {
	GetWorld()->GetTimerManager().ClearTimer(LocationTimer);

	float dot = FVector::DotProduct(StartForward, PController->GetPawn()->GetActorForwardVector());
	float angle = FMath::Acos(dot);

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::FromInt(angle));

	if (FMath::Abs(angle) >= 80 && FMath::Abs(angle) <= 100) { // The player is going to the right or the left side
		// Get si c droite ou gauche
		

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Change Direction"));
		// Enregistrer la position + la direction pour faire changer le moving wall


	}
	// L'angle entre l'ancien forward et le nouveau est situé entre 80 et 100

	bCheckHasChangedDirection = false;
}

void AMovingWall::CheckForDeath() {
	FVector PlayerToWall = PController->K2_GetActorLocation() - Detection->GetComponentLocation();
	FVector Forward = GetActorForwardVector();

	float angle = FVector::DotProduct(PlayerToWall, Forward);

	if (angle < 0 && lastAngle >= 0) {
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
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





