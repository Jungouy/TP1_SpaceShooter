// Fill out your copyright notice in the Description page of Project Settings.


#include "UsineAKaillou.h"

#include "GrosKaillou.h"
#include "GameFramework/PawnMovementComponent.h"


int AUsineAKaillou::Score = 0;
// Sets default values
AUsineAKaillou::AUsineAKaillou()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
}

// Called when the game starts or when spawned
void AUsineAKaillou::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AUsineAKaillou::SpawnKaillou, SpawnInterval, true, 0.5f);

	Score = 0;
	

	
}

// Called every frame
void AUsineAKaillou::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float MyDelay = 3;
	
}



void AUsineAKaillou::SpawnKaillou()
{
	
    if (!GrosKaillouBlueprint) return;

    FVector SpawnLocation;
    FVector2D ViewportSize;
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
	}
    
    
    int32 Edge = FMath::RandRange(0, 3); // 0: Haut, 1: Droite, 2: Bas, 3: Gauche

    switch (Edge)
    {
    case 0: // Haut
       SpawnLocation.X = 0;
       SpawnLocation.Y = FMath::RandRange(-ViewportSize.X / 2.f, ViewportSize.X / 2.f);
       SpawnLocation.Z = ViewportSize.Y / 2.f + 1000.f;
       break;
    case 1: // Droite
       SpawnLocation.X = 0;
       SpawnLocation.Y = ViewportSize.X / 2.f + 1400.f;
       SpawnLocation.Z = FMath::RandRange(-ViewportSize.Y / 2.f, ViewportSize.Y / 2.f);
       break;
    case 2: // Bas
       SpawnLocation.X = 0;
       SpawnLocation.Y = FMath::RandRange(-ViewportSize.X / 2.f, ViewportSize.X / 2.f);
       SpawnLocation.Z = -ViewportSize.Y / 2.f - 1000.f;
       break;
    case 3: // Gauche
       SpawnLocation.X = 0;
       SpawnLocation.Y = -ViewportSize.X / 2.f - 1400.f;
       SpawnLocation.Z = FMath::RandRange(-ViewportSize.Y / 2.f, ViewportSize.Y / 2.f);
       break;
    }
    
    
    FRotator SpawnRotation = GetActorRotation();
	
	
    FActorSpawnParameters SpawnParams;
    GetWorld()->SpawnActor<AGrosKaillou>(GrosKaillouBlueprint, SpawnLocation, SpawnRotation, SpawnParams);
	
}
int AUsineAKaillou::GetScore() const
{
	return Score;
}



