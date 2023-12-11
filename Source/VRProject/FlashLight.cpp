#include "FlashLight.h"
#include "Components/PointLightComponent.h"

AFlashLight::AFlashLight()
{
	PrimaryActorTick.bCanEverTick = true;

	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	RootComponent = Light;

	Light->Intensity = 100000.f;
	Light->AttenuationRadius = 280.f;
}

void AFlashLight::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(LightHandle,this,&AFlashLight::EndFlash,FlashDuration,false);
	
}

void AFlashLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewPosition = GetActorLocation() * FlashSpeed * DeltaTime;
	SetActorLocation(GetActorLocation() + NewPosition);
}

void AFlashLight::EndFlash() {
	GetWorld()->GetTimerManager().ClearTimer(LightHandle);
	Destroy();
}

