// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SamplePawn.generated.h"

UCLASS()
class SAMPLEACTORDEMO_API ASamplePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASamplePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly , Category = "Components")
	class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UFloatingPawnMovement* FloatingPawnMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCameraComponent* CameraComponent;

	//Input functions
	void MoveForward(float Value);
	void MoveRight(float Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
