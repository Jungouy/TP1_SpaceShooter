// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UsineAKaillou.generated.h"

UCLASS()
class TP1_SPACESHOOTER_API AUsineAKaillou : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AUsineAKaillou();
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere,Category = "BP")
	TSubclassOf<class AGrosKaillou> GrosKaillouBlueprint;

	FTimerHandle SpawnTimerHandle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnInterval = FMath::RandRange(0.5f, 2.0f);

	void SpawnKaillou();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float Force = 50000.f;
	

	static int Score;
	
	UFUNCTION(BlueprintCallable, Category = "Score")
	int GetScore() const;
};
