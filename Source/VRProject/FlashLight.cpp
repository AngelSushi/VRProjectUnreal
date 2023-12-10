#include "FlashLight.h"
#include "Components/PointLightComponent.h"

AFlashLight::AFlashLight()
{
	PrimaryActorTick.bCanEverTick = true;

	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	RootComponent = Light;

	Light->Intensity = 18500.f;
	Light->AttenuationRadius = 280.f;
}

void AFlashLight::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFlashLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

