#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class AMarioFire : public AActor
{
public:
	AMarioFire();
	~AMarioFire();

	AMarioFire(const AMarioFire& _Other) = delete;
	AMarioFire(AMarioFire&& _Other) noexcept = delete;
	AMarioFire& operator=(const AMarioFire& _Other) = delete;
	AMarioFire& operator=(AMarioFire&& _Other) noexcept = delete;

	void SetIsDestroy(bool _IsDestroy);
	void SetDir(EActorDir _Dir);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

	void MoveUpdate(float _DeltaTime);
	void DestroyStart(float _DeltaTime);
	void CheckWindowPosition();

private:
	UImageRenderer* FireRenderer = nullptr;
	UImageRenderer* BombRenderer = nullptr;
	UCollision* Collision = nullptr;

	EActorDir Dir = EActorDir::Right;

	bool IsDestroy = false;

	float CurDestroyTime = 0.0f;
	float DestroyTime = 0.3f;

	float MoveSpeed = 600.0f;
	float CurJumpPower = 0.0f;
	float JumpPower = -400.0f;
	float GravityAcc = 800.0f;

};

