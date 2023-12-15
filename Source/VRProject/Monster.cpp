#include "Monster.h"

#include "MovingWall.h"
#include "VRCharacter.h"
#include "WPSubSystem.h"
#include "Camera/CameraComponent.h"
#include "Components/SplineComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

AMonster::AMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	RootComponent = SkeletalMesh;

	PendingSightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sight"));
	PendingSightMesh->SetupAttachment(SkeletalMesh, FName("Head_Socket"));

	// TraceTarget = CreateDefaultSubobject<USceneComponent>(TEXT("TraceTarget"));
	// TraceTarget->SetupAttachment(SkeletalMesh);
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
	bIsRotating = true;
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Spline"), FoundActors);

	AActor* Spline = FoundActors[0];
	SplineComp = Spline->GetComponentByClass<USplineComponent>();
}

void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Distance += DeltaTime;
	//
	// if (Distance > SplineComp->GetSplineLength())
	// {
	// 	Distance = 0;
	// }

	UWorld* World = GetWorld();
	check(World);
	
	// if (SplineComp) {
	// 	// Obtenez la position de la sphère le long du spline
	// 	FVector SphereLocation = SplineComp->GetLocationAtDistanceAlongSpline(DeltaTime, ESplineCoordinateSpace::World);
	//
	// 	// Obtenez la position actuelle du géant
	// 	FVector SightLocation = GetActorLocation();
	//
	// 	// Calculer la direction entre le géant et la sphère
	// 	FVector DirectionToSphere = (SphereLocation - SightLocation).GetSafeNormal();
	//
	// 	// Calculer la rotation à partir de la direction
	// 	FRotator RotationToSphere = FRotationMatrix::MakeFromX(DirectionToSphere).Rotator();
	//
	//
	// 	// Appliquer la rotation au Sight Component
	// 	PendingSightMesh->SetWorldRotation(RotationToSphere);
	// }
	

	FVector Start = PendingSightMesh->GetComponentLocation();
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
				FVector WorldRight = FVector(0,1,0);
				
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

