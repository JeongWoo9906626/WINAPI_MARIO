#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class AHiddenGate : public AActor
{
public:
	AHiddenGate();
	~AHiddenGate();

	AHiddenGate(const AHiddenGate& _Other) = delete;
	AHiddenGate(AHiddenGate&& _Other) noexcept = delete;
	AHiddenGate& operator=(const AHiddenGate& _Other) = delete;
	AHiddenGate& operator=(AHiddenGate&& _Other) noexcept = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Renderer = nullptr;
	UCollision* BodyCollision = nullptr;

	float ChangeLevelTime = 1.0f;
	float CurChangeLevelTime = 0.0f;
};

