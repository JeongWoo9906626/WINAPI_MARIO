#include "GameOverLevel.h"

#include <EngineCore/EngineCore.h>

#include "GameOverUI.h"
#include "UI.h"

UGameOverLevel::UGameOverLevel()
{
}

UGameOverLevel::~UGameOverLevel()
{
	SoundPlayer.Off();
}

void UGameOverLevel::BeginPlay()
{
	ULevel::BeginPlay();

	SoundPlayer = UEngineSound::SoundPlay("GameOver.wav");

	AGameOverUI* GameOver = SpawnActor<AGameOverUI>(ERenderOrder::Loading);
	GameOver->SetActorLocation({ GEngine->MainWindow.GetWindowScale().ihX(), GEngine->MainWindow.GetWindowScale().ihY() });

	AUI* UI = SpawnActor<AUI>(ERenderOrder::UI);
	UI->SetActorLocation({ 200, 200 });
}

void UGameOverLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (CurChangeTime >= ChangeTime)
	{
		CurChangeTime = 0.0f;
		UContentsHelper::Time = 1400;
		UContentsHelper::SubStage = 1;
		UContentsHelper::MapName = "Title";
		GEngine->ChangeLevel("Loading");
	}
	else
	{
		CurChangeTime += _DeltaTime;
	}
}

void UGameOverLevel::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
}

void UGameOverLevel::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);
}
