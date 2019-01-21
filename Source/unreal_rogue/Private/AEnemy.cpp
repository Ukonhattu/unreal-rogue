// Fill out your copyright notice in the Description page of Project Settings.

#include "AEnemy.h"
#include "Engine/GameEngine.h"

// Sets default values
AEnemy::AEnemy() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Health = 10.f;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void AEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

// This is the actor damage handler.   
float AEnemy::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) {
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("apragadapra"));
	}
	// Call the base class - this will tell us how much damage to apply  
	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (Health > 0.f) {
		Health -= ActualDamage;
		// If the damage depletes our health set our lifespan to zero - which will destroy the actor  
		if (Health <= 0.f) {
			SetLifeSpan(0.001f);
		}
	}
	return ActualDamage;
}
