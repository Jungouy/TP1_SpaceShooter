// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GrosKaillou.generated.h"

UCLASS()
class TP1_SPACESHOOTER_API AGrosKaillou : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGrosKaillou();
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollision;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPawnMovementComponent* MovementComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 InitialHealth = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 Health = 2;

	UPROPERTY(EditAnywhere, Category="AI")
	float TargetReachedRadius = 100.f;

	float TargetReachedRadiusSq = 100.f * 100.f;

	bool bHasReachedTarget = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetHealth(int32);

	FVector Seek(FVector Location);
	
	FVector TargetLocation;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
};
