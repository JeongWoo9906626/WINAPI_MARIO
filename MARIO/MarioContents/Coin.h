#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class ABrick;
class ACoin : public AActor
{
	friend ABrick;

public:
	ACoin();
	~ACoin();

	ACoin(const ACoin& _Other) = delete;
	ACoin(ACoin&& _Other) noexcept = delete;
	ACoin& operator=(const ACoin& _Other) = delete;
	ACoin& operator=(ACoin&& _Other) noexcept = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateChange(ECoinState _State);
	void StateUpdate(float _DeltaTime);
	
	void CoinSpawnStart();
	void CoinDestroyStart();

	void CoinSpawn(float _DeltaTime);
	void CoinDestroy(float _DeltaTime);
private:
	UImageRenderer* Renderer = nullptr;

	ECoinState State = ECoinState::None;

	float MoveTime = 0.5f;
	float CurUpTime = 0.0f;
	float CurDownTime = 0.0f;

	float MoveUpSpeed = 200.0f;
};

