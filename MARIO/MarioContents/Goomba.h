#pragma once
#include "Monster.h"
#include "ContentsHelper.h"

class AGoomba : public AMonster
{
public:
	AGoomba();
	~AGoomba();

	AGoomba(const AGoomba& _Other) = delete;
	AGoomba(AGoomba&& _Other) noexcept = delete;
	AGoomba& operator=(const AGoomba& _Other) = delete;
	AGoomba& operator=(AGoomba&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateChange(EMonsterState _State) override;
	void StateUpdate(float _DelatTime) override;

	void MoveStart() override;
	void HeadHitStart() override;
	void SpinDeadStart() override;

	void Move(float _DeltaTime) override;
	void HeadHit(float _DeltaTime) override;

private:
	float DestroyTime = 1.0f;
};

