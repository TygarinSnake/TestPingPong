#include "Game/Actors/BallActor.h"

#include "Components/SphereComponent.h"

#include "Game/Components/BaseMovementComponent.h"
#include "Game/Interfaces/Movable.h"

DEFINE_LOG_CATEGORY_STATIC(LogBallActor, All, All);

ABallActor::ABallActor()
{
    Direction = FVector::Zero();
    MoveSpeed = 2000.f;
    PrimaryActorTick.bCanEverTick = true;

    MovementComponent = CreateDefaultSubobject<UBaseMovementComponent>(TEXT("MovementComponent"));
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

    check(MovementComponent);
    check(CollisionComponent);

    CollisionComponent->InitSphereRadius(50.0f);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

    RootComponent = CollisionComponent;

    CollisionComponent->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
}

void ABallActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (!OtherActor || OtherActor == this)
    {
        return;
    }

    Direction = ReflectionVector(Direction, Hit);
    UE_LOG(LogBallActor, Display, TEXT("Reflected direction: %s"), *Direction.ToString());
}

FORCEINLINE FVector ABallActor::ReflectionVector(const FVector& CurrentDirection, const FHitResult& Hit)
{
    const FVector& SurfaceNormal = Hit.Normal;
    FVector ReflectedVelocity = FMath::GetReflectionVector(CurrentDirection, SurfaceNormal);
    return ReflectedVelocity;
}

void ABallActor::BeginPlay()
{
    Super::BeginPlay();

    check(MovementComponent);
    MovementComponent->SetMaxSpeed(MoveSpeed);
}

FORCEINLINE void ABallActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    check(MovementComponent);
    MovementComponent->AddInputVector(Direction);
}

FORCEINLINE FVector ABallActor::GetDirectionMovement() const
{
    return Direction;
}

FORCEINLINE void ABallActor::SetDirectionMovement(FVector VectorDirection)
{
    Direction = VectorDirection;
}
