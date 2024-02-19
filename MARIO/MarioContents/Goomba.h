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
	void GravityMove(float _DeltaTime);

	void ChangeDir(EActorDir _State);
	void CheckWindowPosition();

private:
	UImageRenderer* Renderer = nullptr;
	UCollision* BodyCollision = nullptr;

	EMonsterState State = EMonsterState::None;
	EActorDir DirState = EActorDir::Left;

	bool DeadValue = false;

	float MoveSpeed = 300.0f;
	float GravitySpeed = 500.0f;
	float DirUnitVector = -1.0f;
};

