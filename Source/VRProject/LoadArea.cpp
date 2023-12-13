#include "LoadArea.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

ALoadArea::ALoadArea()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	Box->OnComponentBeginOverlap.AddDynamic(this,&ALoadArea::OnOverlapBegin);
	Box->OnComponentEndOverlap.AddDynamic(this, &ALoadArea::OnOverlapEnd);
}

void ALoadArea::BeginPlay()
{
	Super::BeginPlay();
}

void ALoadArea::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	APlayerController* PController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!PController || !PController->GetPawn()) {
		return;
	}

	if (OtherActor == PController->GetPawn()) {
		FLatentActionInfo Info;
		UGameplayStatics::LoadStreamLevel(this,AreaLevelStreamingName,true,true,Info);	
	}

}

void ALoadArea::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	APlayerController* PController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!PController || !PController->GetPawn()) {
		return;
	}

	if (OtherActor == PController->GetPawn()) {
		FLatentActionInfo Info;
		UGameplayStatics::UnloadStreamLevel(this, AreaLevelStreamingName,Info,false);
	}
}
