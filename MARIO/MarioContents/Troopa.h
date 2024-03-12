#pragma once
#include "Monster.h"
#include "ContentsHelper.h"

class ATroopa : public AMonster
{
public:
	ATroopa();
	~ATroopa();

	ATroopa(const ATroopa& _Other) = delete;
	ATroopa(ATroopa&& _Other) noexcept = delete;
	ATroopa& operator=(const ATroopa& _Other) = delete;
	ATroopa& operator=(ATroopa&& _Other) noexcept = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateChange(EMonsterState _State) override;
	void StateUpdate(float _DeltaTime) override;

	bool AnimationCheck(bool _IsDirChange);
	std::string GetAnimationName(std::string _Name);

	void MoveStart() override;
	void HeadHitStart() override;
	void WakeStart();
	void ShootStart();

	void Move(float _DeltaTime) override;
	void HeadHit(float _DeltaTime) override;
	void Wake(float _DeltaTime);
	void Shoot(float _DeltaTime);

private:
	UCollision* HideLeftCollision = nullptr;
	UCollision* HideRightCollision = nullptr;

	bool IsShoot = false;

	float ShootSpeed = 400.0f;

	float HideTime = 3.0f;
	float CurHideTime = 0.0f;

	float WakeTime = 2.0f;
	float CurWakeTime = 0.0f;

	float CurNoCollisionTime = 0.0f;
	float NoCollisionTime = 0.2f;
};

