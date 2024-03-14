#include "GameOverLevel.h"

#include <EngineCore/EngineCore.h>

#include "TitleLevel.h"
#include "GameOverUI.h"
#include "UI.h"

GameOverLevel::GameOverLevel()
{
}

GameOverLevel::~GameOverLevel()
{
}

void GameOverLevel::BeginPlay()
{
	ULevel::BeginPlay();

	AGameOverUI* GameOver = SpawnActor<AGameOverUI>(ERenderOrder::Loading);
	GameOver->SetActorLocation({ GEngine->MainWindow.GetWindowScale().ihX(), GEngine->MainWindow.GetWindowScale().ihY() });

	AUI* UI = SpawnActor<AUI>(ERenderOrder::UI);
	UI->SetActorLocation({ 200, 200 });
}

void GameOverLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (CurChangeTime >= ChangeTime)
	{
		CurChangeTime = 0.0f;
		GEngine->CreateLevel<UTitleLevel>("Title");
		GEngine->ChangeLevel("Title");
	}
	else
	{
		CurChangeTime += _DeltaTime;
	}
}

void GameOverLevel::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
}

void GameOverLevel::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);
}
