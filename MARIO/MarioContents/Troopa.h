#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class ATurtle : public AActor
{
public:
	ATurtle();
	~ATurtle();

	ATurtle(const ATurtle& _Other) = delete;
	ATurtle(ATurtle&& _Other) noexcept = delete;
	ATurtle& operator=(const ATurtle& _Other) = delete;
	ATurtle& operator=(ATurtle&& _Other) noexcept = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateChange(EMonsterState _State);
	void StateUpdate(float _DeltaTime);

	void DirCheck();
	void AnimationCheck(EActorDir _Dir);

	std::string GetAnimationName(std::string _Name);

	void MoveStart();
	void DeadStart();
	void ShootStart();
	void WakeStart();

	void Move(float _DeltaTime);
	void Dead(float _DeltaTime);
	void Shoot(float _DeltaTime);
	void Wake(float _DeltaTime);

private:
	UImageRenderer* Renderer = nullptr;
	UCollision* BodyCollision = nullptr;

	EMonsterState State = EMonsterState::None;
	EActorDir DirState = EActorDir::Left;

	std::string CurAnimationName = "";

	bool DeadValue = false;

	float MoveSpeed = 100.0f;
	float GravitySpeed = 500.0f;
	float DirUnitVector = -1.0f;
};

