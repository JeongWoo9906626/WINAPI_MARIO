#pragma once
#include <EngineCore/Actor.h>	
#include "ContentsHelper.h"

class AFloatingBox : public AActor
{
public:
	AFloatingBox();
	~AFloatingBox();

	AFloatingBox(const AFloatingBox& _Other) = delete;
	AFloatingBox(AFloatingBox&& _Other) noexcept = delete;
	AFloatingBox& operator=(const AFloatingBox& _Other) = delete;
	AFloatingBox& operator=(AFloatingBox&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Float(float _DeltaTime);
	void ChangeDir();

private:
	UImageRenderer* Renderer = nullptr;
	UCollision* TopCollision = nullptr;
	UCollision* BottomCollision = nullptr;
	UCollision* LeftCollision = nullptr;
	UCollision* RightCollision = nullptr;

	EActorDir DirState = EActorDir::Left;
	
	float MoveRange = -200.0f;
	float CurMoveX = 0.0f;
	float DirVector = -1.0f;
	float FloatSpeed = 100.0f;
};

