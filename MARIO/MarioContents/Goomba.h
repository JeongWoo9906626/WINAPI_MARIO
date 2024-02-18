#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class AGoomba : public AActor
{
public:
	AGoomba();
	~AGoomba();

	AGoomba(const AGoomba& _Other) = delete;
	AGoomba(AGoomba&& _Other) noexcept = delete;
	AGoomba& operator=(const AGoomba& _Other) = delete;
	AGoomba& operator=(AGoomba&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Renderer = nullptr;
	UCollision* BodyCollision = nullptr;

	bool DeadValue = false;
};

