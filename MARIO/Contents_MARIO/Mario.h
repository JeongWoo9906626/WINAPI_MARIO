#pragma once
#include <EngineCore\Actor.h>
#include "ContentsHelper.h"

class AMario : public AActor
{
public:
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

	void GravityCheck(float _DeltaTime);
	void DirCheck();

	void StateChange(EPlayState _State);
	void StateUpdate(float _DeltaTime);

	void CameraFreeMove(float _DeltaTime);
	void FreeMove(float _DeltaTime);
	
	void Idle(float _DeltaTime);
	void Jump(float _DeltaTime);
	void Move(float _DeltaTime);
	void MoveReverse(float _DeltaTime);

	void IdleStart();
	void MoveStart();
	void MoveReverseStart();
	void JumpStart();

	std::string GetAnimationName(std::string _Name);

	EPlayState State = EPlayState::None;
	EActorDir DirState = EActorDir::Right;
	EMArioSizeState MarioSzie = EMArioSizeState::Small;
	std::string CurAnimationName = "None";

private:
	UImageRenderer* Renderer = nullptr;
	float AnimationTime = 0.0f;
	int AnimationFrame = 0;

	float AlphaTime = 0.0f;
	bool Dir = false;

	float FreeMoveSpeed = 2000.0f;

	float Force = 500.0f;
	float Gravity = 500.0f;
	float MoveSpeed = 300.0f;
	float MaxSpeed = 1500.0f;
};

