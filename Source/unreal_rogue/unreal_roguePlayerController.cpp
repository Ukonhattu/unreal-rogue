// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "unreal_roguePlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "unreal_rogueCharacter.h"
#include "Engine/World.h"

Aunreal_roguePlayerController::Aunreal_roguePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void Aunreal_roguePlayerController::MoveForwad(float amount)
{
	if (Aunreal_rogueCharacter* MyPawn = Cast<Aunreal_rogueCharacter>(GetPawn())) {
		MyPawn->AddMovementInput(FVector(1.0f, 0.0f, 0.0f), amount);
	}
}

void Aunreal_roguePlayerController::MoveRight(float amount)
{
	if (Aunreal_rogueCharacter* MyPawn = Cast<Aunreal_rogueCharacter>(GetPawn())) {
		MyPawn->AddMovementInput(FVector(0.0f, 1.0f, 0.0f), amount);
	}
}

void Aunreal_roguePlayerController::RotateToMouse()
{
	if (Aunreal_rogueCharacter* MyPawn = Cast<Aunreal_rogueCharacter>(GetPawn())) {

		if (MyPawn->GetCursorToWorld()) {
			FVector Direction =  MyPawn->GetCursorToWorld()->GetComponentLocation() - MyPawn->GetActorLocation();
			Direction = FVector(Direction.X, Direction.Y, 0);
			MyPawn->SetActorRotation(FQuat::FindBetween(FVector::ForwardVector, Direction));
		}

	}

}

void Aunreal_roguePlayerController::FireWeapon()
{
	if (Aunreal_rogueCharacter* MyPawn = Cast<Aunreal_rogueCharacter>(GetPawn())) {
		MyPawn->FireWeapon();
	}
}


void Aunreal_roguePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	RotateToMouse();

	/* keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}*/
}

void Aunreal_roguePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();
	/*
	InputComponent->BindAction("SetDestination", IE_Pressed, this, &Aunreal_roguePlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &Aunreal_roguePlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &Aunreal_roguePlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &Aunreal_roguePlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &Aunreal_roguePlayerController::OnResetVR);
	*/

	// wasd movement

	InputComponent->BindAxis("MoveForward", this, &Aunreal_roguePlayerController::MoveForwad);
	InputComponent->BindAxis("MoveRight", this, &Aunreal_roguePlayerController::MoveRight);

	// Fire weapon
	InputComponent->BindAction("Fire", IE_Pressed, this, &Aunreal_roguePlayerController::FireWeapon);
}

void Aunreal_roguePlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void Aunreal_roguePlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (Aunreal_rogueCharacter* MyPawn = Cast<Aunreal_rogueCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);


		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void Aunreal_roguePlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void Aunreal_roguePlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void Aunreal_roguePlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void Aunreal_roguePlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}
