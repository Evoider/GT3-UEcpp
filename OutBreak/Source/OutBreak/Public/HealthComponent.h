// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, int32, Health);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDamageTaken);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHeal);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OUTBREAK_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	bool bIsDead = false;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnDeath OnDeath;
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChanged OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnDamageTaken OnDamageTaken;
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHeal OnHeal;
	
public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeDamage(int32 Damage);

	UFUNCTION(BlueprintNativeEvent, Category = "Health")
	void Die();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void Heal(int32 HealAmount);

public:	
	UFUNCTION(BlueprintPure, Category = "Health")
	FORCEINLINE int32 GetHealth() const { return Health; }
	UFUNCTION(BlueprintPure, Category = "Health")
	FORCEINLINE int32 GetMaxHealth() const { return MaxHealth; }
		
};
