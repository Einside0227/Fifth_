// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class FIFTH__API AMyActor : public AActor
{
	GENERATED_BODY()

private:
	int32 MoveCount = 0;
	int32 EventCount = 0;
	float MoveDistance = 0.f; // 총 이동 거리

	void Move(); // 이동
	void Turn(); // 회전
	void Event(); // 이벤트

	float distance(FVector first, FVector second);

public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
