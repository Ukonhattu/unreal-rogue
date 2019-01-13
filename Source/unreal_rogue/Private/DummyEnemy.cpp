// Fill out your copyright notice in the Description page of Project Settings.

#include "DummyEnemy.h"

// Sets default values
ADummyEnemy::ADummyEnemy() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	CollisionComponent->BodyInstance.SetCollisionProfileName("Enemy");

	RootComponent = CollisionComponent;

}

// Called when the game starts or when spawned
void ADummyEnemy::BeginPlay() {
	Super::BeginPlay();

}

// Called every frame
void ADummyEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

