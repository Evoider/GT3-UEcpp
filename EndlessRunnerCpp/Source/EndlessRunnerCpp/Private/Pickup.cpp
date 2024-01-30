// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

#include "RunCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"

// Sets default values
APickup::APickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene Component");
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	

	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere Component");
	SphereComponent->SetupAttachment(StaticMeshComponent);
	SphereComponent->SetSphereRadius(50.0f);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>("Rotating Movement Component");
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();

	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnOverlapBegin);
}

void APickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult)
{
	ARunCharacter* RunCharacter = Cast<ARunCharacter>(OtherActor);
	
	if (!RunCharacter)
		return;
	UE_LOG(LogTemp, Warning, TEXT("Overlap"));
	OnGet();
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
