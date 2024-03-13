#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class AMonster;
class AGoomba;
class ATroopa;
class APlant;
class AFlag;
class ABrick;
class ABreakBrick;
class AItemBox;
class AGate;
class AMushroom;
class ASunflower;
class AKoopa;
class ASpinFire;
class AKoopaFire;
class ABirdgeHandle;
class AEndingGate;
// Ό³Έν :
class AMario : public AActor
{
	friend AMonster;
	friend AGoomba;
	friend ATroopa;
	friend APlant;
	friend AFlag;
	friend ABrick;
	friend AGate;
	friend ABreakBrick;
	friend AItemBox;
	friend AMushroom;
	friend ASunflower;
	friend AKoopa;
	friend ASpinFire;
	friend AKoopaFire;
	friend ABirdgeHandle;
	friend AEndingGate;

public:
	//static AMario* GetMainPlayer();
	static AMario* MainPlayer;

	// constrcuter destructer
	AMario();
	~AMario();

	// delete Function
	AMario(const AMario& _Other) = delete;
	AMario(AMario&& _Other) noexcept = delete;
	AMario& operator=(const AMario& _Other) = delete;
	AMario& operator=(AMario&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateChange(EPlayState _State);
	void StateUpdate(float _DeltaTime);

	void DirCheck();
	std::string GetAnimationName(std::string _Name);

	void FreeMoveStart();
	void IdleStart();
	void MoveStart();
	void JumpStart();
	void CrouchStart();
	void CrouchMoveStart();
	void ReverseStart();
	void KillStart();
	void DieStart();
	void GrowUpStart();
	void GrowDownStart();
	void ChangeRedStart();
	void HiddenStageEnterStart();
	void HiddenStageOutStart();
	void HiddenStageOutUpStart();
	void FinishMoveStart();
	void FinishReverseStart();
	void FinishWalkStart();
	void BossFinishStart();
	void BossFinishWalkStart();
	void EndingStart();

	void CameraFreeMove(float _DeltaTime);
	void FreeMove(float _DeltaTime);
	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);
	void Jump(float _DeltaTime);
	void Crouch(float _DeltaTime);
	void CrouchMove(float _DeltaTime);
	void Reverse(float _DeltaTime);
	void Kill(float _DeltaTime);
	void Die(float _DeltaTime);
	void GrowUp(float _DeltaTime);
	void GrowDown(float _DeltaTime);
	void ChangeRed(float _DeltaTime);
	void HiddenStageEnter(float _DeltaTime);
	void HiddenStageOut(float _DeltaTime);
	void HiddenStageOutUp(float _DeltaTime);
	void FinishMove(float _DeltaTime);
	void FinishReverse(float _DeltaTime);
	void FinishWalk(float _DeltaTime);
	void BossFinish(float _DeltaTime);
	void BossFinishWalk(float _DeltaTime);

private:
	UImageRenderer* Renderer = nullptr;
	UCollision* BodyCollision = nullptr;
	UCollision* HeadCollision = nullptr;
	UCollision* BottomCollision = nullptr;

	EPlayState State = EPlayState::None;
	EMarioSizeState SizeState = EMarioSizeState::Small;
	EActorDir DirState = EActorDir::Right;

	float FreeMoveSpeed = 1000.0f;

	bool IsHiddenStage = false;
	bool IsRun = false;
	bool IsChange = false;
	bool IsGround = false;
	bool IsDown = false;
	bool IsMove = true;
	bool IsCollision = false;
	bool IsStageEnd = false;
	bool IsInvincibility = false;

	FVector MoveVector = FVector::Zero;
	float MoveAcc = 400.0f;

	float CurMaxSpeed = 0.0f;
	float MaxMoveSpeed = 400.0f;
	float MaxRunSpeed = 800.0f;

	float CurBreakSpeed = 0.0f;
	float BreakSpeed = 600.0f;
	float RunBreakSpeed = 1000.0f;

	float FinsihWalkSpeed = 100.0f;
	float FinishDownSpeed = 300.0f;

	FVector GravityVector = FVector::Zero;
	float CurGravityAcc = 0.0f;
	float GravityAcc = 1500.f;

	FVector JumpVector = FVector::Zero;
	float JumpForce = 0.0f;
	float CurJumpPower = 0.0f;
	float MoveJumpPower = 880.0f;
	float RunJumpPower = 900.0f;
	float KillJumpPower = 500.0f;
	float DieJumpPower = 500.0f;

	FVector TotalForceVector = FVector::Zero;

	float CurDieTime = 0.0f;
	float DieTime = 1.0f;

	float ChangeTime = 0.5f;
	float CurChangeTime = 0.0f;

	float PortalTime = 2.0f;
	float CurPortalTime = 0.0f;

	float CurScreenChangeTime = 0.0f;
	float ScreenChangeTime = 1.0f;

	float DownTime = 1.0f;
	float CurDownTime = 0.0f;

	float CurNoCollisionTime = 0.0f;
	float NoCollisionTime = 2.0f;

	float CurBossFinishTime = 0.0f;
	float BossFinishTime = 4.0f;

	float FireSpawnTime = 0.1f;
	float CurFireSpawnTime = 0.0f;

	void MoveUpdate(float _DeltaTime);
	void GroundUp();
	void WallUp();
};

