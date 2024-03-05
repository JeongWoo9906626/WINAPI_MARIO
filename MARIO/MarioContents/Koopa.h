#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class Koopa : public AActor
{
public:
	Koopa();
	~Koopa();

	Koopa(const Koopa& _Other) = delete;
	Koopa(Koopa&& _Other) noexcept = delete;
	Koopa& operator=(const Koopa& _Other) = delete;
	Koopa& operator=(Koopa&& _Other) noexcept = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
	UImageRenderer* Renderer = nullptr;
	UCollision* BodyCollision = nullptr;

	EMonsterState State = EMonsterState::None;
	EActorDir DirState = EActorDir::Left;
};

