// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Exhortation.h"

#include "SuperProjectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AExhortation::AExhortation()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxCollision;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(BoxCollision);

	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("MovementComponent0"));
	MovementComponent->UpdatedComponent = BoxCollision;
}

// Called when the game starts or when spawned
void AExhortation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExhortation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector Pos = GetActorLocation();
	Pos.Z = FMath::Clamp(Pos.Z, ZMin, ZMax);
	Pos.Y = FMath::Clamp(Pos.Y, YMin, YMax);
	SetActorLocation(Pos);
}

// Called to bind functionality to input
void AExhortation::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent)
	PlayerInputComponent->BindAxis(TEXT("MoveUpDownZ"), this, &AExhortation::MoveUpDown);
	PlayerInputComponent->BindAxis(TEXT("MoveRightLeftY"), this, &AExhortation::MoveRightLeft);
	PlayerInputComponent->BindAction(TEXT("Fire!"), IE_Pressed, this, &AExhortation::Fire);
}

void AExhortation::MoveUpDown(float Value)
{
	if (MovementComponent  && FMath::Abs(Value) > KINDA_SMALL_NUMBER)
	{
		AddMovementInput(GetActorUpVector(), Value);
	}
}

void AExhortation::MoveRightLeft(float Value)
{
	if (MovementComponent && FMath::Abs(Value) > KINDA_SMALL_NUMBER)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}
void AExhortation::Fire()
{
	if (!ProjectileBlueprint) return;

	FVector SpawnLocation = GetActorLocation();
	SpawnLocation.Z += 100.0f;
	FRotator SpawnRotation = GetActorRotation(); // ou FRotator::ZeroRotator si tu veux

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.Instigator = GetInstigator();

	ASuperProjectile* Proj = GetWorld()->SpawnActor<ASuperProjectile>(ProjectileBlueprint, SpawnLocation, SpawnRotation, Params);
	if (Proj && Proj->ProjectileMovement)
	{
		// Direction vers "avant" selon ta logique (ex: vers +Z local du pawn)
		FVector Dir = FVector::UpVector; // world Up (0,0,1) si c'est vers le haut de ton écran
		// Ou utiliser la rotation de ton pawn pour diriger le projectile :
		// FVector Dir = GetActorRotation().RotateVector(FVector(0.f, 0.f, 1.f));

		Dir.X = 0.f;
		Dir = Dir.GetSafeNormal();

		Proj->ProjectileMovement->Velocity = Dir * Proj->ProjectileMovement->InitialSpeed;
	}
}

