#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class ALoadingUI : public AActor
{
public:
	ALoadingUI();
	~ALoadingUI();

	ALoadingUI(const ALoadingUI& _Other) = delete;
	ALoadingUI(ALoadingUI&& _Other) noexcept = delete;
	ALoadingUI& operator=(const ALoadingUI& _Other) = delete;
	ALoadingUI& operator=(ALoadingUI&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void MainStageUpdate();
	void SubStageUpdate();
	void MarioLifeUpdate();

	std::string CheckMainStage();
	std::string CheckSubStage();
	std::string CheckMarioLife();

private:
	UImageRenderer* Renderer = nullptr;
	UImageRenderer* MainStageRenderer = nullptr;
	UImageRenderer* SubStageRenderer = nullptr;
	UImageRenderer* MarioLifeRenderer = nullptr;
	UImageRenderer* TimeHideRenderer = nullptr;
};

