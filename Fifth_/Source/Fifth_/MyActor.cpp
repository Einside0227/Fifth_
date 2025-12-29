// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActor.h"
#include "Engine/Engine.h" //Gengine 및 디버깅 메시지 관련 헤더

// Sets default values
AMyActor::AMyActor() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay() {
	Super::BeginPlay();

	SetActorLocation(FVector(0, 50, 0)); // 액터 (0,50,0) 위치로 이동

	for (int32 i = 0; i < 10; ++i) { // 10회
		Turn(); // 회전
		Move(); // 이동
		Event(); // 이벤트
	}

	if (GEngine) { // 출력 (총 이동거리, 총 이벤트 발생횟수)
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT("Total Distance : %.2f | Total Event Count : %d"), MoveDistance, EventCount));
	}

}
void AMyActor::Move() {
	// 랜덤값 생성
	int32 MoveX = FMath::RandRange(1, 100); //X값
	int32 MoveY = FMath::RandRange(1, 100); //Y값
	int32 MoveZ = FMath::RandRange(1, 100); //Z값

	const FVector Current = GetActorLocation(); // 액터 위치
	const FVector NewLocation = FVector(Current.X + MoveX, Current.Y + MoveY, Current.Z + MoveZ); // 현재 위치값 + 랜덤 위치값 = 새 위치값

	SetActorLocation(NewLocation); // 새 위치로 액터 이동

	MoveCount++; // 이동 횟수 증가
	const float StepDistance = distance(Current, NewLocation); // 한번 이동할 때의 이동거리
	MoveDistance += StepDistance; // 총 이동거리

	if (GEngine) { // 출력 (이동 횟수, 현재 위치)
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString::Printf(TEXT("[Step %d] %s"), MoveCount, *NewLocation.ToString()));
	}
}

void AMyActor::Turn() {
	// 랜덤값 생성
	int32 PitchDelta = FMath::RandRange(1, 100); //X축값
	int32 YawDelta = FMath::RandRange(1, 100); //Y축값
	int32 RollDelta = FMath::RandRange(1, 100); //Z축값

	const FRotator NewRotation = GetActorRotation() + FRotator(PitchDelta, YawDelta, RollDelta); // 현재 회전값 + 랜덤 회전값 = 새 회전값
	SetActorRotation(NewRotation); // 액터 회전
}

void AMyActor::Event() {
	const int32 Roll = FMath::RandRange(1, 100); // 랜덤값 생성
	const bool bEvent = (Roll <= 50); // 50% 확률

	if (bEvent) {
		EventCount++; // 이벤트 발생 횟수 증가

		if (GEngine) { // 출력 (이벤트 발생)
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("[Step %d] Event Triggered!"), MoveCount));
		}
	}
	else {
		if (GEngine) { // 출력 (이벤트 발생X)
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
void AMyActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}