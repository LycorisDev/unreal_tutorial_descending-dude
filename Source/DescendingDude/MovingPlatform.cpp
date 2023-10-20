// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation() + PlatformVelocity * DeltaTime;
	FHitResult Hit;
	SetActorLocation(CurrentLocation, true, &Hit);
	float MovedDistance = FVector::Distance(StartLocation, CurrentLocation);

	if (MovedDistance > MaxDistance)
	{
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation += MoveDirection * MaxDistance;
		PlatformVelocity = -PlatformVelocity;
	}

	// Fix collision with non-physics based character
	if (Hit.GetActor())
	{
		const double Distance = FVector::Dist(Hit.TraceStart, Hit.TraceEnd);
		const FVector Direction = PlatformVelocity.GetSafeNormal();
		const FVector Delta = Direction * Distance;
		Hit.GetActor()->AddActorWorldOffset(Delta);
		SetActorLocation(CurrentLocation);
	}
}
