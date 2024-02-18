#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class AGoomba : public AActor
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

	void StateChange(EMonsterState _State);

	void MoveStart();
	void DeadStart();

	void StateUpdate(float _DelatTime);

	void Move(float _DeltaTime);
	void Dead(float _DeltaTime);

private:
	UImageRenderer* Renderer = nullptr;
	UCollision* BodyCollision = nullptr;

	EMonsterState State = EMonsterState::None;

	bool DeadValue = false;
	float MoveSpeed = 100.0f;
};

