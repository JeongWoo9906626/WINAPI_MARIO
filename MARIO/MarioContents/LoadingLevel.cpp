#include "LoadingLevel.h"

#include <EngineCore/EngineCore.h>

#include "TitleLevel.h"
#include "PlayLevel.h"
#include "FinalLevel.h"
#include "LoadingUI.h"
#include "GameOverLevel.h"
#include "UI.h"

ULoadingLevel::ULoadingLevel()
{
}

ULoadingLevel::~ULoadingLevel()
{
}

void ULoadingLevel::BeginPlay()
{
	ULevel::BeginPlay();

	ALoadingUI* Loading = SpawnActor<ALoadingUI>(ERenderOrder::Loading);
	Loading->SetActorLocation({ GEngine->MainWindow.GetWindowScale().ihX(), GEngine->MainWindow.GetWindowScale().ihY() });

	AUI* UI = SpawnActor<AUI>(ERenderOrder::UI);
	UI->SetActorLocation({ 200, 200 });
}

void ULoadingLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	CurLevelName = UContentsHelper::MapName;
	if (true == CurLevelName._Equal("GameOver"))
	{
		GEngine->CreateLevel<UGameOverLevel>(CurLevelName);
		GEngine->ChangeLevel(CurLevelName);
	}
	if (true == CurLevelName._Equal("Title"))
	{
		GEngine->CreateLevel<UTitleLevel>(CurLevelName);
		GEngine->ChangeLevel(CurLevelName);
	}

	if (CurChangeTime >= ChangeTime)
	{
		CurChangeTime = 0.0f;
		
		if (true == CurLevelName._Equal("FirstStage"))
		{
			GEngine->CreateLevel<UPlayLevel>(CurLevelName);
		}
		if (true == CurLevelName._Equal("FinalStage"))
		{
			GEngine->CreateLevel<UFinalLevel>(CurLevelName);
		}
		GEngine->ChangeLevel(CurLevelName);
	}
	else
	{
		CurChangeTime += _DeltaTime;
	}
}

void ULoadingLevel::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);

	GEngine->DestroyLevel(CurLevelName);
}

void ULoadingLevel::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);
}