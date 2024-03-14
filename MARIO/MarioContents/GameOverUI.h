#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class AGameOverUI : public AActor
{
public:
	AGameOverUI();
	~AGameOverUI();

	AGameOverUI(const AGameOverUI& _Other) = delete;
	AGameOverUI(AGameOverUI&& _Other) noexcept = delete;
	AGameOverUI& operator=(const AGameOverUI& _Other) = delete;
	AGameOverUI& operator=(AGameOverUI&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Renderer = nullptr;

};

