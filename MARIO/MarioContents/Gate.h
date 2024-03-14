#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class AGate : public AActor
{
public:
	AGate();
	~AGate();

	AGate(const AGate& _Other) = delete;
	AGate(AGate&& _Other) noexcept = delete;
	AGate& operator=(const AGate& _Other) = delete;
	AGate& operator=(AGate&& _Other) noexcept = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void TimeToScore(float _DeltaTime);
	void StageChange();

private:
	UCollision* Collision = nullptr;


	float Time = 0.0f;
	float ChangeLevelTime = 1.0f;
	float CurChangeLevelTime = 0.0f;

};

