// Mofumofu Studios � All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class DESCENDINGDUDE_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private: 
	/*
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	float MovedDistance = 0;
	*/

	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector PlatformVelocity = FVector(100, 0, 0);
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxDistance = 100;

	FVector StartLocation;

	UPROPERTY(EditAnywhere, Category="Rotation")
	FRotator RotationVelocity;

	void MovePlatform(float DeltaTime);
	void RotatePlatform(float DeltaTime);
	bool ShouldPlatformReturn(FVector CurrentLocation) const;
};
