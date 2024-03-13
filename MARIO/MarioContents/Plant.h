#pragma once
#include "Monster.h"
#include "ContentsHelper.h"

class APlant : public AMonster
{
public:
	APlant();
	~APlant();

	APlant(const APlant& _Other) = delete;
	APlant(APlant&& _Other) noexcept = delete;
	APlant& operator=(const APlant& _Other) = delete;
	APlant& operator=(APlant&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateChange(EMonsterState _State) override;
	void StateUpdate(float _DeltaTime) override;

	void MoveStart() override;
	void WaitStart();
	void SpinDeadStart() override;

	void Move(float _DeltaTime) override;
	void Wait(float _DeltaTime);
	void SpinDead(float _DeltaTime) override;

private:
	FVector DirVector = FVector::Up;

	bool IsUp = true;

	float MoveSpeed = 50.0f;
	float MaxMoveY = 90.0f;
	float CurMoveY = 0.0f;

	float CurTime = 0.0f;
	float WaitTime = 2.0f;

	float DestroyTime = 0.5f;
	float CurDestoryTime = 0.0f;
};

