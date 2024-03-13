#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class ScoreUI : public AActor
{
public:
	ScoreUI();
	~ScoreUI();

	ScoreUI(const ScoreUI& _Other) = delete;
	ScoreUI(ScoreUI&& _Other) noexcept = delete;
	ScoreUI& operator=(const ScoreUI& _Other) = delete;
	ScoreUI& operator=(ScoreUI&& _Other) noexcept = delete;

	void SetScore(int _Score);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void ScorePrintStart();
	void ScorePrint(float _DeltaTime);

private:
	UImageRenderer* ScoreRenderer = nullptr;

	int Score = 0;
};

