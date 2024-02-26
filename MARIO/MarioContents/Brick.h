#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class ABrick : public AActor
{
public:
	ABrick();
	~ABrick();

	ABrick(const ABrick& _Other) = delete;
	ABrick(ABrick&& _Other) noexcept = delete;
	ABrick& operator=(const ABrick& _Other) = delete;
	ABrick& operator=(ABrick&& _Other) noexcept = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

