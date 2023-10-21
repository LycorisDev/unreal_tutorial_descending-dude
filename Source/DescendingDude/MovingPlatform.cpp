// Mofumofu Studios © All Rights Reserved

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

	//FString Str = "Hello world";
	//UE_LOG(LogTemp, Display, TEXT("Max distance: %.2f"), MaxDistance);
	//UE_LOG(LogTemp, Warning, TEXT("%s message is %s"), *GetName(), *Str);
	//UE_LOG(LogTemp, Error, TEXT("Console log message"));
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation() + PlatformVelocity * DeltaTime;
	FHitResult Hit;
	SetActorLocation(CurrentLocation, true, &Hit);

	if (ShouldPlatformReturn(CurrentLocation))
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

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

bool AMovingPlatform::ShouldPlatformReturn(FVector CurrentLocation) const
{
	float MovedDistance = FVector::Distance(StartLocation, CurrentLocation);
	return MovedDistance > MaxDistance;
}