#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class AKoopa : public AActor
{
public:
	AKoopa();
	~AKoopa();

	AKoopa(const AKoopa& _Other) = delete;
	AKoopa(AKoopa&& _Other) noexcept = delete;
	AKoopa& operator=(const AKoopa& _Other) = delete;
	AKoopa& operator=(AKoopa&& _Other) noexcept = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void DirCheck();
	void Walk(float _DeltaTime);

	std::string GetAnimationName();

private:
	UImageRenderer* Renderer = nullptr;
	UCollision* Collision = nullptr;
	UCollision* BottomCollision = nullptr;

	EKoopaState State = EKoopaState::None;
	EActorDir DirState = EActorDir::Left;

	float JumpSpeed = 0.0f;
	float GravitySpeed = 150.0f;
	float WalkSpeed = 100.0f;

	float JumpTime = 2.0f;
	float CurJumpTime = 0.0f;

	int Dir = -1;

	bool IsCollision = false;
	bool IsJump = true;
	bool IsMarioDie = false;

	FVector JumpVector = FVector::Zero;
};

