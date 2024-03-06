#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

// Ό³Έν :
class SpinFire : public AActor
{
public:
	// constrcuter destructer
	SpinFire();
	~SpinFire();

	// delete Function
	SpinFire(const SpinFire& _Other) = delete;
	SpinFire(SpinFire&& _Other) noexcept = delete;
	SpinFire& operator=(const SpinFire& _Other) = delete;
	SpinFire& operator=(SpinFire&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void FireSpin(float _DeltaTime);

private:
	UImageRenderer* Renderer = nullptr;
	UCollision* Collision = nullptr;

};

