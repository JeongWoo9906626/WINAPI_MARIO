#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

// 설명 :
class AMario : public AActor
{
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

	void CameraFreeMove(float _DeltaTime);
	void FreeMove(float _DeltaTime);

	void Idle(float _DeltaTime);
	void Run(float _DeltaTime);
	void Jump(float _DeltaTime);
	void Reverse(float _DeltaTime);

	void ReverseDir();
	

	EPlayState State = EPlayState::None;
	EActorDir DirState = EActorDir::Right;
	std::string CurAnimationName = "None";

private:
	UImageRenderer* Renderer = nullptr;

	float AnimationTime = 0.0f;
	int AnimationFrame = 0;

	float AlphaTime = 0.0f;
	bool Dir = false;

	float FreeMoveSpeed = 1000.0f;

	//float BreakSpeed = 100.0f;

	FVector RunAcc = FVector::Right * 500.0f;
	FVector RunVector = FVector::Zero;
	
	float MaxRunSpeed = 400.0f;
	float NoramlRunSpeed = 400.0f;
	float ShiftRunSpeed = 700.0f;

	float CurBreakSpeed = 200.0f;

	void AddVector(const FVector& _DirDelta);
	void SubtractVector(const FVector& _DirDelta);

	FVector GravityAcc = FVector::Down * 2000.0f;
	FVector GravityVector = FVector::Zero;

	FVector JumpPower = FVector::Up * 700.0f;
	FVector NoramlJumpPower = FVector::Up * 700.0f;
	FVector RunJumpPower = FVector::Up * 1000.0f;

	FVector JumpVector = FVector::Zero;

	FVector TotalForceVector = FVector::Zero;

	// 움직임 벡터 업데이트
	void RunVectorUpdate(float _DeltaTime);
	void JumpVectorUpdate(float _DeltaTime);
	void GravityVectorUpdate(float _DeltaTime);

	// 모든 이동 벡터 더하기
	void MoveVectorUpdate(float _DeltaTime);

	// 실제 움직임(카메라 및 마리오)
	void Move(float _DeltaTime);

	// 이동 업데이트 (종합 관리)
	void MoveUpdate(float _DeltaTime);
};

