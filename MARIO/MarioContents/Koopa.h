#pragma once
#include "Monster.h"
#include "ContentsHelper.h"

class AKoopa : public AMonster
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

	void StateChange(EMonsterState _State) override;
	void StateUpdate(float _DeltaTime);

	void MoveStart() override;
	void SpinDeadStart() override;
	void FireStart();
	void JumpStart();

	bool CheckMarioPos();
	void MoveDirChange();

	void Move(float _DeltaTime) override;
	void Fire(float _DeltaTime);
	void Jump(float _DeltaTime);

	void MoveUpdate(float _DeltaTime);

	std::string GetAnimationName(std::string _Name);

private:
	float JumpSpeed = 0.0f;
	float WalkSpeed = 100.0f;

	float FirstKoopaPosX = 8862.0f;
	float LastKoopaPosX = 8562.0f;

	float TotalMoveRange = 300.0f;
	
	float Dir = -1.0f;

	float JumpTime = 1.0f;
	float CurJumpTime = 0.0f;
	float FireTime = 3.5f;
	float CurFireTime = 0.0f;
	float CurChangeTime = 0.0f;
	float ChangeTime = 0.3f;

	float CurWalkTime = 0.0f;
	float WalkTime = 2.0f;

	bool IsCollision = false;
	bool IsJump = true;
	bool IsMarioDie = false;
	bool FirstShot = false;
	bool IsRendererChange = false;

	EActorDir MarioToKoopa = EActorDir::Left;

	FVector JumpVector = FVector::Zero;
};