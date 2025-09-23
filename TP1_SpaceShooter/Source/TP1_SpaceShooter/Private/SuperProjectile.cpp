#include "SuperProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"

ASuperProjectile::ASuperProjectile()
{
    PrimaryActorTick.bCanEverTick = false; // pas besoin de Tick normalement

    BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
    RootComponent = BoxCollision;
    BoxCollision->SetCollisionProfileName(TEXT("BlockAllDynamic")); // ou "Projectile" si tu as ce profile
    BoxCollision->SetNotifyRigidBodyCollision(true); // pour recevoir OnComponentHit

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMesh->SetupAttachment(BoxCollision);
    StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); // laisse la box gérer la collision

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->InitialSpeed = 1500.f;
    ProjectileMovement->MaxSpeed = 1500.f;
    ProjectileMovement->bRotationFollowsVelocity = false;
    ProjectileMovement->bShouldBounce = false;
    ProjectileMovement->ProjectileGravityScale = 0.f; // pas de gravité pour un shooter 2D

    // NOTE : on peut aussi définir une valeur par défaut InitialLifeSpan ici,
    // mais on préfère exposer LifeTime et appeler SetLifeSpan dans BeginPlay.
    // InitialLifeSpan = 3.0f;
}

void ASuperProjectile::BeginPlay()
{
    Super::BeginPlay();

    // Définit la durée de vie de l'acteur (sera détruit automatiquement après LifeTime secondes)
    if (LifeTime > 0.f)
    {
        SetLifeSpan(LifeTime);
    }

    // Hook OnHit pour détruire à l'impact
    if (BoxCollision)
    {
        BoxCollision->OnComponentHit.AddDynamic(this, &ASuperProjectile::OnHit);
    }

#if WITH_EDITOR
    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Projectile spawned"));
#endif
}

void ASuperProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ASuperProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
                             UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // ignore self-collisions / instigator si besoin
    if (OtherActor && OtherActor != this)
    {
        // Ici tu peux appliquer des dégâts, spawn des particules, etc.
        Destroy();
    }
}
