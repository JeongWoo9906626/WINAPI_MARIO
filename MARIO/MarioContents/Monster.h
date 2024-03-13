#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"
#include "ScoreUI.h"

class AMonster : public AActor
{
public:
	AMonster();
	~AMonster();

	AMonster(const AMonster& _Other) = delete;
	AMonster(AMonster&& _Other) noexcept = delete;
	AMonster& operator=(const AMonster& _Other) = delete;
	AMonster& operator=(AMonster&& _Other) noexcept = delete;

	virtual void StateChange(EMonsterState _State);
	virtual void StateUpdate(float _DeltaTime);

	void WindowCheck();

	virtual void MoveStart();
	virtual void SpinDeadStart();
	virtual void HeadHitStart();

	virtual void Move(float _DeltaTime);
	virtual void SpinDead(float _DeltaTime);
	virtual void HeadHit(float _DeltaTime);

	void GravityMove(float _DeltaTime);

	void SetHitCount(int _HitCount);
	void ChangeDir();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	ScoreUI* Score = nullptr;

	UImageRenderer* Renderer = nullptr;
	UCollision* Collision = nullptr;
	UCollision* HeadCollision = nullptr;
	UCollision* BottomCollision = nullptr;
	EActorDir DirState = EActorDir::Left;
	
	EMonsterState State = EMonsterState::None;

	bool IsWake = false;
	bool IsWindowOut = false;
	bool IsBoxCollision = false;
	bool IsDirChange = false;

	int HitCount = 1;

	float GravityAcc = 500.0f;
	float MoveSpeed = 100.0f;

private:

};

