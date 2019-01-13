// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "DummyEnemy.generated.h"

UCLASS()
class UNREAL_ROGUE_API ADummyEnemy : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADummyEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Collision component for the class
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionComponent;

};
