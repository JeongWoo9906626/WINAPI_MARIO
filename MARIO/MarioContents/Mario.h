#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class AGoomba;
class ATroopa;
class APlant;
class AFlag;
// ���� :
class AMario : public AActor
{
	friend AGoomba;
	friend ATroopa;
	friend APlant;
	friend AFlag;
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
	void DieAnimationStart(float _DeltaTime);

	void ReverseDir();
	

	EPlayState State = EPlayState::None;
	EActorDir DirState = EActorDir::Right;
	std::string CurAnimationName = "";

private:
	UImageRenderer* Renderer = nullptr;
	UCollision* BodyCollision = nullptr;

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

	float JumpUpSpeed = 4500.0f;
	float MaxJumpSpeed = 1500.0f;

	float DieTime = 1.0f;
	float CurDieTime = 0.0f;

	float DownTime = 1.0f;
	float CurDownTime = 0.0f;

	void AddRunVector(const FVector& _DirDelta);
	void SubtractRunVector(const FVector& _DirDelta);
	void AddJumpVector(const FVector& _DirDelta);

	FVector GravityAcc = FVector::Down * 3000.0f;
	FVector GravityPower = FVector::Zero;

	FVector DieJumpPower = FVector::Up * 700.0f;
	FVector JumpPower = FVector::Up * 500.0f;
	FVector KillJumpPower = FVector::Up * 500.0f;

	FVector JumpVector = FVector::Zero;

	FVector TotalForceVector = FVector::Zero;

	// ������ ���� ������Ʈ
	void RunVectorUpdate(float _DeltaTime);
	void JumpVectorUpdate(float _DeltaTime);
	void GravityVectorUpdate(float _DeltaTime);

	// ��� �̵� ���� ���ϱ�
	void MoveVectorUpdate(float _DeltaTime);

	// ���� ������(ī�޶� �� ������)
	void Move(float _DeltaTime);

	// �̵� ������Ʈ (���� ����)
	void MoveUpdate(float _DeltaTime);

	void GroundUp();
};

