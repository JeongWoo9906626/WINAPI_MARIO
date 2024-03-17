#pragma once
#include <EngineCore/Actor.h>
#include <EnginePlatform/EngineSound.h>

#include "ContentsHelper.h"

class ABrickBase : public AActor
{
public:
	ABrickBase();
	~ABrickBase();

	ABrickBase(const ABrickBase& _Other) = delete;
	ABrickBase(ABrickBase&& _Other) noexcept = delete;
	ABrickBase& operator=(const ABrickBase& _Other) = delete;
	ABrickBase& operator=(ABrickBase&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	virtual void StateChange(EBoxState _State);
	virtual void StateUpdate(float _DeltaTime);

	virtual void IdleStart();
	virtual void HitStart();
	virtual void BreakStart();

	virtual void Idle(float _DeltaTime);
	virtual void Hit(float _DeltaTime);
	virtual void Break(float _DeltaTime);

private:
	UEngineSoundPlayer SoundPlayer;
	UImageRenderer* Renderer = nullptr;

	UCollision* TopCollision = nullptr;
	UCollision* BottomCollision = nullptr;
	UCollision* LeftCollision = nullptr;
	UCollision* RightCollision = nullptr;

	EBoxState State = EBoxState::None;
	EMarioSizeState MarioState = EMarioSizeState::None;

	int HitCount = 10;
	bool IsBreak = false;
	float MaxHitUpSize = 30.0f;
	float HitUpSpeed = 300.0f;
	FVector FirstPos = FVector::Zero;
	FVector MoveUpPos = FVector::Zero;
	FVector MoveDownPos = FVector::Zero;
};

