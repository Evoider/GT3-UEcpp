// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Obstacle.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ATile::ATile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	AttachPoint = CreateDefaultSubobject<UArrowComponent>("AttachPoint");
	AttachPoint->SetupAttachment(RootComponent);

	ExitTrigger = CreateDefaultSubobject<UBoxComponent>("ExitTrigger");
	ExitTrigger->SetupAttachment(AttachPoint);
	ExitTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATile::OnOverlapBegin);

	ObstacleSpawnArea = CreateDefaultSubobject<UBoxComponent>("ObstacleSpawnArea");
	ObstacleSpawnArea->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	SpawnObstacle();
}

void ATile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                           int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		OnExitTile.Broadcast(this);
	}
	else return;
}

void ATile::SpawnObstacle()
{
	FVector BoxExtent = ObstacleSpawnArea->GetScaledBoxExtent();
	FVector BoxOrigin = ObstacleSpawnArea->GetRelativeLocation();

	FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(BoxOrigin, BoxExtent);
	FRotator SpawnRotation = UKismetMathLibrary::RandomRotator();

	UChildActorComponent* Obstacle = NewObject<UChildActorComponent>(this, UChildActorComponent::StaticClass(),
	                                                                 FName("Obstacle"));
	Obstacle->RegisterComponent();
	Obstacle->AttachToComponent(ObstacleSpawnArea, FAttachmentTransformRules::KeepRelativeTransform);
	Obstacle->SetRelativeLocation(SpawnLocation);
	Obstacle->SetRelativeRotation(SpawnRotation);
	int32 ObstacleIndex = FMath::RandRange(0, Obstacles.Num() - 1);
	if (Obstacles.IsValidIndex(ObstacleIndex)
		&& Obstacles[ObstacleIndex] != nullptr)
	{
		Obstacle->SetChildActorClass(Obstacles[ObstacleIndex]);
		Obstacle->CreateChildActor();
		UE_LOG(LogTemp,Warning,TEXT("Spawned Obstacle %d"),ObstacleIndex);
	}
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UArrowComponent* ATile::GetAttachPoint()
{
	return AttachPoint;
}
