#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class AKoopaFire : public AActor
{
public:
	AKoopaFire();
	~AKoopaFire();

	AKoopaFire(const AKoopaFire& _Other) = delete;
	AKoopaFire(AKoopaFire&& _Other) noexcept = delete;
	AKoopaFire& operator=(const AKoopaFire& _Other) = delete;
	AKoopaFire& operator=(AKoopaFire&& _Other) noexcept = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Renderer = nullptr;
	UCollision* Collision = nullptr;

};

