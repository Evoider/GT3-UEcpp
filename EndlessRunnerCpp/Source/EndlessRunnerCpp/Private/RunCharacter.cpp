// Fill out your copyright notice in the Description page of Project Settings.


#include "RunCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "RunCharacterController.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
ARunCharacter::ARunCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->SocketOffset = FVector(0.0f, 0.0f, 100.0f);
	SpringArm->bUsePawnControlRotation = true;
	

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	RunCharacterController = Cast<ARunCharacterController>(GetController());
	
}

void ARunCharacter::AddCoin()
{
	Coins++;
}

// Called when the game starts or when spawned
void ARunCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARunCharacter::Die()
{
	if (!bIsDead)
	{
		bIsDead = true;
		UE_LOG(LogTemp, Warning, TEXT("Dead"));
		USkeletalMeshComponent* MeshComp = GetMesh();
		MeshComp->SetSimulatePhysics(true);
		MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		MeshComp->AddImpulse(FVector(10000.0f, 0.0f, 50000.0f));

		UParticleSystemComponent* ParticleComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathParticle, GetActorLocation());
		ParticleComp->SetWorldScale3D(FVector(3.0f, 3.0f, 3.0f));

		UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
		
		OnDeath.Broadcast(this);
	}
	else if (bIsDead)
	{
		UE_LOG(LogTemp, Warning, TEXT("Already Dead"));
	}
}

// Called every frame
void ARunCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



