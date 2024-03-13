#include "ScoreUI.h"

ScoreUI::ScoreUI()
{
}

ScoreUI::~ScoreUI()
{
}

void ScoreUI::SetScore(int _Score)
{
	Score = _Score;
}

void ScoreUI::BeginPlay()
{
	AActor::BeginPlay();

	ScoreRenderer = CreateImageRenderer(ERenderOrder::UI);
	ScoreRenderer->SetImage("Score.png");
	ScoreRenderer->SetTransform({ { 0, -80 }, { 512, 512 } });

	ScoreRenderer->CreateAnimation("100", "Score.png", 0, 0, 0.1f, true);
	ScoreRenderer->CreateAnimation("200", "Score.png", 1, 1, 0.1f, true);
	ScoreRenderer->CreateAnimation("1000", "Score.png", 4, 4, 0.1f, true);

	Destroy(1.0f);
}

void ScoreUI::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	ScorePrint(_DeltaTime);
}

void ScoreUI::ScorePrintStart(int _Score)
{
	std::string ScoreString = std::to_string(Score);
	ScoreRenderer->ChangeAnimation(ScoreString);
}

void ScoreUI::ScorePrint(float _DeltaTime)
{
	ScorePrintStart(Score);
	AddActorLocation(FVector::Up * 100.0f * _DeltaTime);
}
