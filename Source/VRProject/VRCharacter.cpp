#include "VRCharacter.h"

#include "Kismet/KismetSystemLibrary.h"


AVRCharacter::AVRCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
	Camera->SetupAttachment(RootComponent);
}

void AVRCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AVRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

FHitResult AVRCharacter::SphereTrace()
{
	FVector TraceStart = Camera->GetComponentLocation();
	FVector TraceEnd = TraceStart + Camera->GetForwardVector() * 1000.f;
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	TArray<AActor*> ActorsToIgnore;
	FHitResult HitResult;
	
	UKismetSystemLibrary::SphereTraceSingle(this, TraceStart, TraceEnd, 10.f, TraceTypeQuery1, false, ActorsToIgnore,EDrawDebugTrace::ForDuration, HitResult, true);
	return HitResult;
}


