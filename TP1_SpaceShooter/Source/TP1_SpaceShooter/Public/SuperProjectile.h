#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SuperProjectile.generated.h"

class UProjectileMovementComponent;
class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class TP1_SPACESHOOTER_API ASuperProjectile : public AActor
{
	GENERATED_BODY()
    
public:
	ASuperProjectile();

	// Collision mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh;

	// Projectile movement
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* ProjectileMovement;

	// Durée de vie en secondes (editable dans l'inspecteur)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectile")
	float LifeTime = 3.0f;

protected:
	virtual void BeginPlay() override;

	// Optionnel : appelé quand on tape un obstacle
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
			   UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	virtual void Tick(float DeltaTime) override;
};
