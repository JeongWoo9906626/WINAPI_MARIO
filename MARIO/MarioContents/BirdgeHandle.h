#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class ABirdgeHandle : public AActor
{
public:
	ABirdgeHandle();
	~ABirdgeHandle();

	ABirdgeHandle(const ABirdgeHandle& _Other) = delete;
	ABirdgeHandle(ABirdgeHandle&& _Other) noexcept = delete;
	ABirdgeHandle& operator=(const ABirdgeHandle& _Other) = delete;
	ABirdgeHandle& operator=(ABirdgeHandle&& _Other) noexcept = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UCollision* Collision = nullptr;

};

