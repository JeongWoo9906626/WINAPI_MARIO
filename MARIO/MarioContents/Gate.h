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

private:
	UCollision* Collision = nullptr;

	float ChangeLevelTime = 1.0f;
	float CurChangeLevelTime = 0.0f;

};

