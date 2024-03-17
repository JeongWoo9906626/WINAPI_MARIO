#pragma once
#include <EngineCore/Actor.h>
#include <EnginePlatform/EngineSound.h>

#include "ContentsHelper.h"

class ABrickBase;

class AMushroom : public AActor
{
	friend ABrickBase;

public:
	AMushroom();
	~AMushroom();

	AMushroom(const AMushroom& _Other) = delete;
	AMushroom(AMushroom&& _Other) noexcept = delete;
	AMushroom& operator=(const AMushroom& _Other) = delete;
	AMushroom& operator=(AMushroom&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateChange(EItemState _State);
	void StateUpdate(float _DeltaTime);

	void SpawnStart();
	void MoveStart();
	void JumpStart();
	void CollisionMoveStart();

	void Spawn(float _DeltaTime);
	void Move(float _DeltaTime);
	void Jump(float _DeltaTime);
	void CollisionMove(float _DeltaTime);
	void GravityMove(float _DeltaTime);

	void ChangeDir(EActorDir _State);
	void CheckWindowPosition();

private:
	UEngineSoundPlayer SoundPlayer;
	UImageRenderer* Renderer = nullptr;
	UCollision* BodyCollision = nullptr;
	UCollision* BottomCollision = nullptr;

	EMarioSizeState MarioSizeState = EMarioSizeState::None;
	EItemState State = EItemState::None;
	EActorDir DirState = EActorDir::Right;

	bool DestroyValue = false;
	bool IsBoxCollision = false;

	float SpawnUpSpeed = 100.0f;
	float MoveSpeed = 200.0f;
	float JumpPower = -50.0f;
	float CurJumpPower = 0.0f;
	float GravitySpeed = 500.0f;
	float DirUnitVector = -1.0f;
};

