// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Exhortation.generated.h"

UCLASS()
class TP1_SPACESHOOTER_API AExhortation : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AExhortation();
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollision;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPawnMovementComponent* MovementComponent;

	void MoveUpDown(float Value);
	void MoveRightLeft(float Value);
	void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float YMax = 1890.0f;
	float YMin = -1890.0f;
	float ZMax = 1060.0f;
	float ZMin = -1060.0f;

	UPROPERTY(EditAnywhere,Category = "BP")
	TSubclassOf<class ASuperProjectile> ProjectileBlueprint;
};
