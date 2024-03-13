#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class ABossGate : public AActor
{
public:
	ABossGate();
	~ABossGate();

	ABossGate(const ABossGate& _Other) = delete;
	ABossGate(ABossGate&& _Other) noexcept = delete;
	ABossGate& operator=(const ABossGate& _Other) = delete;
	ABossGate& operator=(ABossGate&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UCollision* Collision = nullptr;
};

