#include "Game/Actors/GateActor.h"

#include "Components/BoxComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogGateActor, All, All);

AGateActor::AGateActor()
{
    CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    check(CollisionComponent);

    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);
}

void AGateActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    UE_LOG(LogGateActor, Display, TEXT("Goal in %s"), *GateName);
    OnGoalEvent.Broadcast(GateName, OtherActor);
}

FORCEINLINE void AGateActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    OnGoalEvent.Clear();
}
