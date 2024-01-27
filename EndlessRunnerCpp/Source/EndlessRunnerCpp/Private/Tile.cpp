// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"


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
	
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor == GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		OnExitTile.Broadcast();
	}
	else return;
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

