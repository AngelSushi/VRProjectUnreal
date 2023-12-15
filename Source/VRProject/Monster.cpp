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
#include "Engine/CollisionProfile.h"


	
AMonster::AMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(GetRootComponent());

	SightRoot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SightRoot"));
	SightRoot->SetupAttachment(SkeletalMesh, FName("Head_Socket"));

	Sight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sight"));
	Sight->SetupAttachment(SightRoot);

	WayPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Waypoint"));
	WayPoint->SetupAttachment(GetRootComponent());
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

// void AMonster::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);
//
// 	UWorld* World = GetWorld();
// 	check(World);
//
// 	FVector Start = SightRoot->GetComponentLocation();
// 	FVector End = Start + SightRoot->GetForwardVector() * RayCastDistance;
//
// 	FCollisionQueryParams QueryParams;
// 	QueryParams.AddIgnoredActor(this);
// 	TArray<AActor*> ActorsToIgnore;
//
// 	TArray<FHitResult> HitResults;
// 	
// 	ETraceTypeQuery MyTraceType = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Pawn);
// 	bool bHit = UKismetSystemLibrary::SphereTraceMulti(this, Start, End, RayCastRadius, , false, ActorsToIgnore,EDrawDebugTrace::ForDuration, HitResults, true);
// 	if (bHit)
// 	{
// 		for(int i = 0; i < HitResults.Num(); i++)
// 		{
// 			if (AVRCharacter* VRCharacter = Cast<AVRCharacter>(HitResults[i].GetActor()))
// 			{
// 				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Player hit by Trace"));
// 				FHitResult PlayerTraceResult = VRCharacter->SphereTrace();
// 				if (Cast<AMonster>(PlayerTraceResult.GetActor()))
// 				{
// 					// arrêter l'animation
// 					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Monster hit by Trace"));
// 				}
// 				else
// 				{
// 					FVector CamPos = VRCharacter->Camera->GetComponentLocation();
// 					FVector CamForward = VRCharacter->Camera->GetForwardVector();
// 				
// 					FVector WorldForward = FVector(1,0,0);
// 					FVector WorldRight = FVector(0,1,0);
// 				
// 					float DotWForward = FVector::DotProduct(CamForward, WorldForward);
// 					float DotWRight = FVector::DotProduct(CamForward, WorldRight);
//
// 					FVector WallSpawnPos;
//
// 					if (abs(DotWForward) > abs(DotWRight))
// 					{
// 						if (DotWForward > 0)
// 						{
// 							WallSpawnPos = CamPos + WorldForward * WallSpawnDistance;
// 						}
// 						else
// 						{
// 							WallSpawnPos = CamPos - WorldForward * WallSpawnDistance;
// 						}
// 					}
// 					else
// 					{
// 						if (DotWRight > 0)
// 						{
// 							WallSpawnPos = CamPos + WorldRight * WallSpawnDistance;
// 						}
// 						else
// 						{
// 							WallSpawnPos = CamPos - WorldRight * WallSpawnDistance;
// 						}
// 					}
// 					FRotator WallSpawnRot = UKismetMathLibrary::FindLookAtRotation(WallSpawnPos, CamPos);
//
// 					UWPSubSystem::SpawnWall(GetWorld(), AMovingWall::StaticClass(), WallSpawnPos, WallSpawnRot);
// 				}
// 			}
// 		}
// 	}
// }

void AMonster::SpawnWall(FVector WallSpawnPos, FRotator WallSpawnRot)
{
	UWPSubSystem::SpawnWall(GetWorld(), AMovingWall::StaticClass(), WallSpawnPos, WallSpawnRot);
}
