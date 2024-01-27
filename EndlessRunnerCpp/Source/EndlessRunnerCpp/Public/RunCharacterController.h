// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RunCharacterController.generated.h"

struct FInputActionValue;
/**
 * 
 */
UCLASS()
class ENDLESSRUNNERCPP_API ARunCharacterController : public APlayerController
{
	GENERATED_BODY()
protected:
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "Player")
	class ARunCharacter* RunCharacter;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Player")
	bool bCanMove = true;
	
protected:
	virtual void BeginPlay() override;
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void SetupInputComponent() override;
};
