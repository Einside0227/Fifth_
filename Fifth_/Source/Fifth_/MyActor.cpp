// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Engine/Engine.h" //Gengine 및 디버깅 메시지 관련 헤더

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector(0, 50, 0)); // 액터 (0,50,0) 위치로 이동

	// 10회
	for (int32 i = 0; i < 10; ++i)
	{
		Turn();
		Move();
		Event();
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT("Total Distance : %.2f | Total Event Count : %d"), MoveDistance, EventCount));
	}

}
void AMyActor::Move() {
	const float MoveX = (float)FMath::RandRange(1, 100);
	const float MoveY = (float)FMath::RandRange(1, 100);
	const float MoveZ = (float)FMath::RandRange(1, 100);

	const FVector Current = GetActorLocation(); // 액터 위치
	const FVector NewLocation = FVector(Current.X + MoveX, Current.Y + MoveY, Current.Z + MoveZ); // 현재 위치값 + 랜덤 위치값 = 새 위치값

	SetActorLocation(NewLocation); // 액터 위치 이동

	MoveCount++; // 이동 횟수
	const float StepDistance = distance(Current, NewLocation);
	MoveDistance += StepDistance;
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString::Printf(TEXT("[Step %d] %s"), MoveCount,*NewLocation.ToString())); // 현재 위치 출력
	}
}

void AMyActor::Turn() {
	const float PitchDelta = (float)FMath::RandRange(1, 100);
	const float YawDelta = (float)FMath::RandRange(1, 100);
	const float RollDelta = (float)FMath::RandRange(1, 100);

	const FRotator NewRotation = GetActorRotation() + FRotator(PitchDelta, YawDelta, RollDelta); // 현재 회전값 + 랜덤 회전값 = 새 회전값
	SetActorRotation(NewRotation); // 액터 회전
}

void AMyActor::Event() {
	const int32 Roll = FMath::RandRange(1, 100); 
	const bool bEvent = (Roll <= 50); // 50% 확률

	if (bEvent) {
		EventCount++;

		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("[Step %d] Event Triggered!"), MoveCount));
		}
	}
	else {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("[Step %d] Event Not Triggered!"), MoveCount));
		}
	}
}

float AMyActor::distance(FVector first, FVector second) {
	float dx = first.X - second.X;
	float dy = first.Y - second.Y;
	return FMath::Sqrt(dx * dx + dy * dy);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

