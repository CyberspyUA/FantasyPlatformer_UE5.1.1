// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
	FString PlatformName = GetName();
	UE_LOG(LogTemp, Display, TEXT("Platform spawned: %s"), *PlatformName);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Get current location of the actor
	FVector CurrentLocation = GetActorLocation();
	CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
	//Set the location
	SetActorLocation(CurrentLocation);
	//Send platform if it went too far
		//Check how it moved
	float PassedDistance = FVector::Distance(StartLocation, CurrentLocation);
		//Reverse direction of motion if gone too far
	if (PassedDistance > MaxDistancePassed)
	{
		float OverShoot = PassedDistance - MaxDistancePassed;
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MaxDistancePassed;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}

}

