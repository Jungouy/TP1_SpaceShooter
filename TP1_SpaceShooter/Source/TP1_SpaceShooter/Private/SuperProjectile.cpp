#include "SuperProjectile.h"

#include "GrosKaillou.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"

ASuperProjectile::ASuperProjectile()
{
    PrimaryActorTick.bCanEverTick = false; // pas besoin de Tick normalement

    BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
    RootComponent = BoxCollision;
    BoxCollision->SetCollisionProfileName(TEXT("BlockAllDynamic"));
    BoxCollision->SetNotifyRigidBodyCollision(true);

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMesh->SetupAttachment(BoxCollision);
    StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->InitialSpeed = 1500.f;
    ProjectileMovement->MaxSpeed = 1500.f;
    ProjectileMovement->bRotationFollowsVelocity = false;
    ProjectileMovement->bShouldBounce = false;
    ProjectileMovement->ProjectileGravityScale = 0.f;
}

void ASuperProjectile::BeginPlay()
{
    Super::BeginPlay();

    // Définit la durée de vie de l'acteur (sera détruit automatiquement après LifeTime secondes)
    if (LifeTime > 0.f)
    {
        SetLifeSpan(LifeTime);
    }
}

void ASuperProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ASuperProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    if (OtherActor && OtherActor != this)
            if  (OtherActor && OtherActor->IsA(AGrosKaillou::StaticClass()))
            {
                Destroy();
            }
}
