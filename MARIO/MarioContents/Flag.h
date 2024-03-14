#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class AFlag : public AActor
{
public:
	AFlag();
	~AFlag();

	AFlag(const AFlag& _Other) = delete;
	AFlag(AFlag&& _Other) noexcept = delete;
	AFlag& operator=(const AFlag& _Other) = delete;
	AFlag& operator=(AFlag&& _Other) noexcept = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void FlagDown(float _DeltaTime);

private:
	UImageRenderer* Renderer = nullptr;
	UCollision* FlagCollision = nullptr;

	float DownSpeed = 300.0f;
	float DownRange = 500.0f;
	float CurDownY = 0.0f;
	bool IsFlagCollision = false;
};

