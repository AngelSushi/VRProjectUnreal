#include "Camera.h"
#include "FlashLight.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/KismetRenderingLibrary.h"

ACamera::ACamera()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UMeshComponent>(TEXT("Mesh"));

	RootComponent = Mesh;
}

void ACamera::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACamera::Flash(FVector Position, FRotator Rotation) {
	AFlashLight* FlashLight = Cast<AFlashLight>(GetWorld()->SpawnActor(AFlashLight::StaticClass(), &Position, &Rotation));
	FlashLight->FlashSpeed = FlashSpeed;
	FlashLight->FlashDuration = FlashDuration;
}
