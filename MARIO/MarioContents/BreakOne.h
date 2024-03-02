#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class ABreakBrick;

class ABreakOne : public AActor
{
	friend ABreakBrick;

public:
	ABreakOne();
	~ABreakOne();

	ABreakOne(const ABreakOne& _Other) = delete;
	ABreakOne(ABreakOne&& _Other) noexcept = delete;
	ABreakOne& operator=(const ABreakOne& _Other) = delete;
	ABreakOne& operator=(ABreakOne&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetStartLocation(FVector _Position);
	void SetBoxImage(int _BoxPos);

private:
	UImageRenderer* Renderer = nullptr;

	FVector Position = FVector::Zero;

	int BoxPos = 0;

	float UpTime = 1.0f;
	float CurUpTime = 0.0f;
	float MoveTime = 3.0f;
	float CurMoveTime = 0.0f;
};

