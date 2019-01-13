// Fill out your copyright notice in the Description page of Project Settings.

#include "RogueProjectile.h"
#include "Engine/GameEngine.h"

// Sets default values
ARogueProjectile::ARogueProjectile() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Use a sphere as a simple collision representation.
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	// Set the sphere's collision radius.
	CollisionComponent->InitSphereRadius(15.0f);
	CollisionComponent->SetSimulatePhysics(true);
	CollisionComponent->SetNotifyRigidBodyCollision(true);
	//CollisionComponent->BodyInstance.SetCollisionProfileName("PlayerProjectile"); <-- this was useless with overlay, probably here also
	CollisionComponent->OnComponentHit.AddDynamic(this, &ARogueProjectile::OnComponentHit);

	// Set the root component to be the collision component.
	RootComponent = CollisionComponent;

	// Separate collider required for overlay events
	TriggerComponent = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerComponent"));
	TriggerComponent->InitSphereRadius(15.0f);
	TriggerComponent->SetupAttachment(RootComponent);
	TriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &ARogueProjectile::OnOverlapBegin);
	

	// Use this component to drive this projectile's movement.
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;

}

// Called when the game starts or when spawned
void ARogueProjectile::BeginPlay() {
	Super::BeginPlay();

}

// Called every frame
void ARogueProjectile::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

// Function that initializes the projectile's velocity in the shoot direction.
void ARogueProjectile::FireInDirection(const FVector& ShootDirection) {
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}



void ARogueProjectile::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor && (OtherActor != this) && OtherComp) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Projectile destroyed"));
		}
		Destroy();
	}
}

void ARogueProjectile::OnComponentHit(class UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if (OtherActor && (OtherActor != this) && OtherComp) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("HIT"));
		}
		Destroy();
	}
}

