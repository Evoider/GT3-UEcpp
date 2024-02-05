// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"

// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>("ObstacleMesh");
	ObstacleMesh->SetCollisionProfileName("BlockAllDynamic");
	ObstacleMesh->SetSimulatePhysics(false);
	ObstacleMesh->SetNotifyRigidBodyCollision(true);
	
	RootComponent = ObstacleMesh;
	
}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();

	ObstacleMesh->OnComponentHit.AddDynamic(this, &AObstacle::OnComponentHit);
}

void AObstacle::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor == GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		OnTrigger(OtherActor);
	}
	else return;
}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

