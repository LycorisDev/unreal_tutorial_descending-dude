// Fill out your copyright notice in the Description page of Project Settings.

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

	/*
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	float MovedDistance = 0;
	*/

	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector PlatformVelocity = FVector(100, 0, 0);
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxDistance = 100;

	FVector StartLocation;
};
