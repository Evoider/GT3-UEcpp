// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Obstacle.h"
#include "Pickup.h"
#include "PickupComponent.h"
#include "Weapon.h"
#include "Zombie.h"
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

	CoinSpawnArea = CreateDefaultSubobject<UBoxComponent>("CoinSpawnArea");
	CoinSpawnArea->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	for(int32 i = 0; i < MaxNumberOfEnemy; i++)
		SpawnZombie();
	TrySpawnObstacle();
	TrySpawnPickup();
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

void ATile::TrySpawnObstacle()
{
	if (UKismetMathLibrary::RandomBoolWithWeight(0.6f))
		SpawnObstacle();
}

void ATile::TrySpawnPickup()
{
	if (UKismetMathLibrary::RandomBoolWithWeight(0.3f))
	{
		int32 NumberOfPickups = FMath::RandRange(1, MaxNumberOfPickups);
		for (int32 i = 0; i < NumberOfPickups; i++)
		{
			SpawnPickup();
		}
	}
}

void ATile::SpawnObstacle()
{
	if (Obstacles.Num() <= 0)
		return;

	const FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(
		ObstacleSpawnArea->GetRelativeLocation(),
		ObstacleSpawnArea->GetScaledBoxExtent()
	);

	const int32 RandomIndex = FMath::RandRange(0, Obstacles.Num() - 1);
	const TSubclassOf<AObstacle> RandomObstacleClass = Obstacles[RandomIndex];

	if (!RandomObstacleClass)
		return;

	UChildActorComponent* ChildActorComponent = NewObject<UChildActorComponent>(this, "Obstacle");

	ChildActorComponent->SetChildActorClass(RandomObstacleClass);
	ChildActorComponent->RegisterComponent();
	ChildActorComponent->SetRelativeTransform(UKismetMathLibrary::Conv_VectorToTransform(SpawnLocation));
	ChildActorComponent->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}


void ATile::SpawnPickup()
{
	if (Pickups.Num() <= 0)
		return;
	
	const FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(
		CoinSpawnArea->GetRelativeLocation(),
		CoinSpawnArea->GetScaledBoxExtent()
	);
	
	const int32 RandomIndex = FMath::RandRange(0, Pickups.Num() - 1);
	const TSubclassOf<AWeapon> RandomPickupClass = Pickups[RandomIndex];
	
	if (!RandomPickupClass)
		return;
	
	UChildActorComponent* ChildActorComponent = NewObject<UChildActorComponent>(this, "Pickup");
	ChildActorComponent->SetChildActorClass(RandomPickupClass);
	ChildActorComponent->RegisterComponent();
	ChildActorComponent->SetRelativeTransform(UKismetMathLibrary::Conv_VectorToTransform(SpawnLocation));
	ChildActorComponent->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	
}

void ATile::SpawnZombie()
{
	if(Zombies.Num() <= 0)
		return;

	const FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(
		ObstacleSpawnArea->GetRelativeLocation(),
		ObstacleSpawnArea->GetScaledBoxExtent()
	);

	const int32 RandomIndex = FMath::RandRange(0, Zombies.Num() - 1);
	const TSubclassOf<AZombie> RandomZombieClass = Zombies[RandomIndex];

	if (!RandomZombieClass)
		return;

	UChildActorComponent* ChildActorComponent = NewObject<UChildActorComponent>(this, "Zombie");

	ChildActorComponent->SetChildActorClass(RandomZombieClass);
	ChildActorComponent->RegisterComponent();
	ChildActorComponent->SetRelativeTransform(UKismetMathLibrary::Conv_VectorToTransform(SpawnLocation));
	ChildActorComponent->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	ChildActorComponent->SetRelativeRotation(FRotator(0, 180, 0));
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
