// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RunCharacter.generated.h"

 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeath, ARunCharacter*, DeadActor);
UCLASS()
class ENDLESSRUNNERCPP_API ARunCharacter : public ACharacter
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

public:
	// Sets default values for this character's properties
	ARunCharacter();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	bool bIsDead = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	class ARunCharacterController* RunCharacterController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	UParticleSystem* DeathParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	USoundBase* DeathSound;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Player")
	virtual void Die();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetCamera() const { return Camera; }

	UPROPERTY(BlueprintAssignable, Category = "Player")
	FOnDeath OnDeath;
};
