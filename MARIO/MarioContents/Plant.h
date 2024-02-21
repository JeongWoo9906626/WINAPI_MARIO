#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class APlant : public AActor
{
public:
	APlant();
	~APlant();

	APlant(const APlant& _Other) = delete;
	APlant(APlant&& _Other) noexcept = delete;
	APlant& operator=(const APlant& _Other) = delete;
	APlant& operator=(APlant&& _Other) noexcept = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Renderer = nullptr;
	UCollision* BodyCollision = nullptr;
};

