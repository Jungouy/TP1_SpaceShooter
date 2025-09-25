// Fill out your copyright notice in the Description page of Project Settings.


#include "GrosKaillou.h"

#include "Exhortation.h"
#include "SuperProjectile.h"
#include "UsineAKaillou.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

UPROPERTY(VisibleAnywhere)
UFloatingPawnMovement* PawnMovement;

// Sets default values
AGrosKaillou::AGrosKaillou()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxCollision;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(BoxCollision);

	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("MovementComponent0"));
	MovementComponent->UpdatedComponent = BoxCollision;
	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovement"));
	PawnMovement->UpdatedComponent = RootComponent;
	PawnMovement->MaxSpeed = 600.f;
	PawnMovement->bConstrainToPlane = true;
	PawnMovement->SetPlaneConstraintNormal(FVector(1,0,0));
}

// Called when the game starts or when spawned
void AGrosKaillou::BeginPlay()
{
	Super::BeginPlay();
	
		
	int32 RandomHP = FMath::RandRange(1, 3);
	SetHealth(RandomHP);
	FVector2D ViewportSize;
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
	}
	TargetLocation = FVector(0.f, FMath::RandRange(-ViewportSize.X-1000 , ViewportSize.X+1000), FMath::RandRange(-ViewportSize.Y-1000 , ViewportSize.Y+1000));

	TargetReachedRadiusSq = TargetReachedRadius * TargetReachedRadius;
	bHasReachedTarget = false;
}

// Called every frame
void AGrosKaillou::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector ToTarget = TargetLocation - GetActorLocation();
	ToTarget.X = 0.f; // reste sur plan YZ si nécessaire

	if (!ToTarget.IsNearlyZero())
	{
		FVector Direction = ToTarget.GetSafeNormal();

		// Vitesse souhaitée (ajuste)
		const float Speed = 300.f; // units / seconde
		FVector DeltaMove = Direction * Speed * DeltaTime;

		// sweep=true pour ne pas traverser la géo
		FHitResult Hit;
		AddActorWorldOffset(DeltaMove, true, &Hit);
		if (!bHasReachedTarget)
		{
			// calcule la distance au target (work en world space)
			const float DistSq = FVector::DistSquared(GetActorLocation(), TargetLocation);
			if (DistSq <= TargetReachedRadiusSq)
			{
				bHasReachedTarget = true;
				Destroy();
			}
		}
	}
}

void AGrosKaillou::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
    
	if (OtherActor && OtherActor != this){
		if  (OtherActor && OtherActor->IsA(ASuperProjectile::StaticClass())){
			Health--;
			if (Health <= 0){
				AUsineAKaillou::Score += 1;
				Destroy();
			}
			
		}else{
			if  (OtherActor && OtherActor->IsA(AExhortation::StaticClass())){
				Destroy();
			}
		}
	}
}

// Called to bind functionality to input
void AGrosKaillou::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
FVector AGrosKaillou::Seek(FVector Location)
{
	FVector vDesiredLocation = Location - GetActorLocation();

	vDesiredLocation.Normalize();
	vDesiredLocation *= MovementComponent->GetMaxSpeed();

	FVector vSteering = (vDesiredLocation - MovementComponent->Velocity);
	vSteering = vSteering.GetClampedToMaxSize(MovementComponent->GetMaxSpeed());

	return vSteering;
}
void AGrosKaillou::SetHealth(int32 NewHealth)
{
	Health = NewHealth;
	InitialHealth = NewHealth;
}
