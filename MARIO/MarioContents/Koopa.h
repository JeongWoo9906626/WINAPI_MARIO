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

	void StateChange(EKoopaState _State);
	void StateUpdate(float _DeltaTime);

	void DirCheck();

	void WalkStart();
	void JumpStart();
	void DeadStart();

	void Walk(float _DeltaTime);
	void Dead(float _DeltaTime);
	void Jump(float _DeltaTime);

	std::string GetAnimationName();

private:
	UImageRenderer* Renderer = nullptr;
	UCollision* Collision = nullptr;

	EKoopaState State = EKoopaState::None;
	EActorDir DirState = EActorDir::Left;

	float JumpSpeed = 300.0f;
	float GravitySpeed = 600.0f;
	float WalkSpeed = 100.0f;

	float JumpTime = 3.0f;
	float CurJumpTime = 0.0f;

	int Dir = -1;

	FVector JumpVector = FVector::Zero;
};

