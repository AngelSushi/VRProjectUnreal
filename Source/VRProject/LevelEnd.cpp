#include "LevelEnd.h"	
#include "Engine/PostProcessVolume.h"
#include "Kismet/GameplayStatics.h"

ALevelEnd::ALevelEnd()
{
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;

	TeleportPosition = CreateDefaultSubobject<USceneComponent>(TEXT("TeleportPosition"));
	TeleportPosition->SetupAttachment(Scene);

}

void ALevelEnd::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(GameTimerHandle,this, &ALevelEnd::EndGame, GameTimer, false);

	StartValue = 0.f;
	EndValue = 1.f;
	
}

void ALevelEnd::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsEnding) {
		FPostProcessVolumeProperties Volume = PP_Volume->GetProperties();
		if (Volume.bIsUnbound)
		{
			FPostProcessSettings* VolumeSettings = (FPostProcessSettings*)Volume.Settings;
			VolumeSettings->FilmBlackClip = FMath::Lerp(StartValue,EndValue,TimeElapsed / BlackClipTimer);

			if (VolumeSettings->FilmBlackClip >= 1.f) {
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Arrive To End"));
				
				bIsEnding = false;

				APlayerController* PController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

				if (!PController || !PController->GetPawn()) {
					return;
				}

				PController->GetPawn()->SetActorLocation(TeleportPosition->GetComponentLocation());

				TimeElapsed = 0.f;
				StartValue = 1.f;
				EndValue = 0.f;
				bIsEnding = true;
			}
			else if (VolumeSettings->FilmBlackClip <= 0.f && StartValue == 1.f) {
				bIsEnding = false;
				TimeElapsed = 0.f;
				StartValue = 0.f;
				EndValue = 1.f;
			}
		}

		TimeElapsed += DeltaTime;
	}

}

void ALevelEnd::EndGame() {
	GetWorld()->GetTimerManager().ClearTimer(GameTimerHandle);

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Start Anim"));
	bIsEnding = true;
}

