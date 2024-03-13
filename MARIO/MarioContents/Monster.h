#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

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
	void SpinDeadStart();
	virtual void HeadHitStart();

	virtual void Move(float _DeltaTime);
	void SpinDead(float _DeltaTime);
	virtual void HeadHit(float _DeltaTime);

	void GravityMove(float _DeltaTime);

	void SetHitCount(int _HitCount);
	void ChangeDir();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


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
	int KillScore = 100;

	float GravityAcc = 500.0f;
	float MoveSpeed = 100.0f;

private:

};

