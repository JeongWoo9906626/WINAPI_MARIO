#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class AGoomba;
class ATroopa;
class APlant;
class AFlag;
class ABrick;
class AGate;
// 설명 :
class AMario : public AActor
{
	friend AGoomba;
	friend ATroopa;
	friend APlant;
	friend AFlag;
	friend ABrick;
	friend AGate;

private:
	//static AMario* MainPlayer;

public:
	//static AMario* GetMainPlayer();

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

	void DirCheck();
	void AnimationCheck(EActorDir _Dir);
	std::string GetAnimationName(std::string _Name);
	std::string GetReverseAnimationName(std::string _Name);

	void StateChange(EPlayState _State);
	void StateUpdate(float _DeltaTime);

	void IdleStart();
	void RunStart();
	void JumpStart();
	void ReverseStart();
	void DieStart();
	void KillStart();
	void FinishMoveStart();
	void FinishReverseStart();
	void FinishWalkStart();

	void CameraFreeMove(float _DeltaTime);
	void FreeMove(float _DeltaTime);

	void Idle(float _DeltaTime);
	void Run(float _DeltaTime);
	void Jump(float _DeltaTime);
	void Reverse(float _DeltaTime);
	void Die(float _DeltaTime);
	void Kill(float _DeltaTime);
	void FinishMove(float _DeltaTime);
	void FinishReverse(float _DeltaTime);
	void FinishWalk(float _DeltaTime);

	void ReverseDir();
	

	EPlayState State = EPlayState::None;
	EActorDir DirState = EActorDir::Right;
	std::string CurAnimationName = "";

private:
	UImageRenderer* Renderer = nullptr;
	UCollision* BodyCollision = nullptr;
	UCollision* HeadCollision = nullptr;
	UCollision* BottomCollision = nullptr;

	bool IsJump = false;
	bool IsGround = false;

	float AnimationTime = 0.0f;
	int AnimationFrame = 0;

	float AlphaTime = 0.0f;
	bool Dir = false;

	float FreeMoveSpeed = 1000.0f;

	FVector RunAcc = FVector::Right * 700.0f;
	FVector RunVector = FVector::Zero;
	
	float MaxRunSpeed = 400.0f;
	float NoramlRunSpeed = 400.0f;
	float ShiftRunSpeed = 700.0f;

	float FinishMoveSpeed = 100.0f;
	float FinishDownSpeed = 300.0f;

	float ShiftBreakSpeed = 1800.0f;
	float NormalBreakSpeed = 1000.0f;
	float CurBreakSpeed = 0.0f;

	float DieTime = 1.0f;
	float CurDieTime = 0.0f;

	float DownTime = 1.0f;
	float CurDownTime = 0.0f;

	void AddRunVector(const FVector& _DirDelta);
	void SubtractRunVector(const FVector& _DirDelta);

	FVector GravityAcc = FVector::Down * 1000.0f;
	FVector GravityPower = FVector::Zero;

	FVector JumpVector = FVector::Zero;
	FVector JumpPower = FVector::Up * 710.0f;

	FVector DieJumpPower = FVector::Up * 500.0f;
	FVector KillJumpPower = FVector::Up * 300.0f;

	FVector TotalForceVector = FVector::Zero;

	// 움직임 벡터 업데이트
	void RunVectorUpdate(float _DeltaTime);
	void GravityVectorUpdate(float _DeltaTime);

	// 모든 이동 벡터 더하기
	void MoveVectorUpdate(float _DeltaTime);

	// 실제 움직임(카메라 및 마리오)
	void Move(float _DeltaTime);

	// 이동 업데이트 (종합 관리)
	void MoveUpdate(float _DeltaTime);

	void GroundUp();
};

