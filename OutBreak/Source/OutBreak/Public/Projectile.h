// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponComponent.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"


class USphereComponent;
class UProjectileMovementComponent;


UCLASS()
class OUTBREAK_API AProjectile : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile)
	UStaticMeshComponent* ProjectileMesh;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	float InitialSpeed = 5000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	float MaxSpeed = 5000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	float ProjectileLifeSpan = 3.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile)
	float Damage;
public:	
	AProjectile();


public:	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
 const FHitResult& Hit);
	
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	UFUNCTION(BlueprintCallable)
	void SetDamage(float Value);
};
