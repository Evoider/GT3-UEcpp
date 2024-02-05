// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Zombie.generated.h"


UCLASS()
class OUTBREAK_API AZombie : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zombie")
	float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zombie")
	float AttackSpeed;
	
	class AHero* Hero;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
	class UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Zombie")
	float sightRange;

public:	
	AZombie();

	virtual void Tick(float DeltaTime) override;

	float GetSightRange() const { return sightRange; }
	float GetDamage() const { return Damage; }
	float GetAttackSpeed() const { return 1/AttackSpeed; }

	UFUNCTION(BlueprintCallable, Category = "Zombie")
	virtual void StartAttacking();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Zombie")
	void Attack();

	

};
