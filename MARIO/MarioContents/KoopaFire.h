#pragma once
#include <EngineCore/Actor.h>
#include <EnginePlatform/EngineSound.h>

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
	
	void SetFireDir(EActorDir _Dir);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CheckFireSound();

	float Speed = 400.0f;
	float PlaySoundRange = 300.0f;

	bool CheckWindowPosition();
	bool IsFirePlaySound = false;

private:
	UEngineSoundPlayer SoundPlayer;
	UImageRenderer* Renderer = nullptr;
	UCollision* Collision = nullptr;

	FVector MoveDirVector = FVector::Left;
};

