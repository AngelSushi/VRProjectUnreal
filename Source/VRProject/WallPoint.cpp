#include "WallPoint.h"
#include "Components/BillboardComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "WPSubSystem.h"

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

	if (!PC) {
		return;
	}

	if (bHasSpawnedWall) {
		return;
	}

	FVector PlayerToPoint = PC->K2_GetActorLocation() - (GetActorLocation()  + GetActorForwardVector() * 100.f);
	FVector Forward = GetActorForwardVector();

	float angle = FVector::DotProduct(PlayerToPoint, Forward);


	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::FromInt(angle));

	if (angle > 0) {
		UWPSubSystem::SpawnWall(GetWorld(),Wall,GetActorLocation(),GetActorRotation());
		bHasSpawnedWall = true;
	}


}



