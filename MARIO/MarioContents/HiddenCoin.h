#pragma once
#include <EngineCore/Actor.h>
#include <EnginePlatform/EngineSound.h>

#include "ContentsHelper.h"

class AHiddenCoin : public AActor
{
public:
	AHiddenCoin();
	~AHiddenCoin();

	AHiddenCoin(const AHiddenCoin& _Other) = delete;
	AHiddenCoin(AHiddenCoin&& _Other) noexcept = delete;
	AHiddenCoin& operator=(const AHiddenCoin& _Other) = delete;
	AHiddenCoin& operator=(AHiddenCoin&& _Other) noexcept = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);

private:
	UEngineSoundPlayer SoundPlayer;
	UImageRenderer* Renderer = nullptr;
	UCollision* Collision = nullptr;
};

