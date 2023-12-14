#include "Monster.h"

#include "MovingWall.h"
#include "VRCharacter.h"
#include "WPSubSystem.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

AMonster::AMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	//Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//RootComponent = Mesh;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	RootComponent = SkeletalMesh;

	PendingSightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sight"));
	PendingSightMesh->SetupAttachment(SkeletalMesh);

	Sight = CreateDefaultSubobject<USceneComponent>(TEXT("SightPosition"));
	Sight->SetupAttachment(SkeletalMesh);	
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
	bIsRotating = true;
}

void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsRotating) {
		PendingSightMesh->AddWorldRotation(FRotator(0.f, 50.f * DeltaTime, 0.f));
	}

	UWorld* World = GetWorld();
	check(World);

	FVector Start = Sight->GetComponentLocation();
	FVector End = Start + PendingSightMesh->GetForwardVector() * RayCastDistance;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	TArray<AActor*> ActorsToIgnore;

	FHitResult HitResult;
	bool bHit = UKismetSystemLibrary::SphereTraceSingle(this, Start, End, RayCastRadius, TraceTypeQuery1, false, ActorsToIgnore,EDrawDebugTrace::ForDuration, HitResult, true);
	if (bHit)
	{
		if (AVRCharacter* VRCharacter = Cast<AVRCharacter>(HitResult.GetActor()))
		{
			FHitResult PlayerTraceResult = VRCharacter->SphereTrace();
			if (Cast<AMonster>(HitResult.GetActor()))
			{
				// arrêter l'animation
			}
			else
			{
				FVector CamPos = VRCharacter->Camera->GetComponentLocation();
				FVector CamForward = VRCharacter->Camera->GetForwardVector();
				
				FVector WorldForward = FVector(1,0,0);
				FVector WorldRight= FVector(0,1,0);
				
				float DotWForward = FVector::DotProduct(CamForward, WorldForward);
				float DotWRight = FVector::DotProduct(CamForward, WorldRight);

				FVector WallSpawnPos;

				if (abs(DotWForward) > abs(DotWRight))
				{
					if (DotWForward > 0)
					{
						WallSpawnPos = CamPos + WorldForward * WallSpawnDistance;
					}
					else
					{
						WallSpawnPos = CamPos - WorldForward * WallSpawnDistance;
					}
				}
				else
				{
					if (DotWRight > 0)
					{
						WallSpawnPos = CamPos + WorldRight * WallSpawnDistance;
					}
					else
					{
						WallSpawnPos = CamPos - WorldRight * WallSpawnDistance;
					}
				}
				FRotator WallSpawnRot = UKismetMathLibrary::FindLookAtRotation(WallSpawnPos, CamPos);

				UWPSubSystem::SpawnWall(GetWorld(), AMovingWall::StaticClass(), WallSpawnPos, WallSpawnRot);
			}
		}
	}


}

