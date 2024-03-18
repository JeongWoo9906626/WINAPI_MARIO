#include "TitleLevel.h"

#include "ContentsHelper.h"
#include "TitleLogo.h"
#include "UI.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineCore.h>

UTitleLevel::UTitleLevel()
{
}

UTitleLevel::~UTitleLevel()
{
}

void UTitleLevel::BeginPlay()
{
	ULevel::BeginPlay();
	ATitleLogo* Logo = SpawnActor<ATitleLogo>(ERenderOrder::Map);

	AUI* UI = SpawnActor<AUI>(ERenderOrder::UI);
	UI->SetActorLocation({ 200, 200 });
}

void UTitleLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (true == UEngineInput::IsDown('4'))
	{
		UContentsHelper::CoinCount = 100;
		UContentsHelper::Time = 1300;
		UContentsHelper::SubStage = 4;
		UContentsHelper::KoopaWake = false;
		UContentsHelper::KoopaIsFire = false;
		UContentsHelper::KoopaDie = false;
		UContentsHelper::MarioLife = 3;
		UContentsHelper::MapName = "FinalStage";
		GEngine->ChangeLevel("Loading");
		return;
	}

	if (true == UEngineInput::IsDown('3'))
	{
		UContentsHelper::CoinCount = 100;
		UContentsHelper::Time = 1400;
		UContentsHelper::SubStage = 1;
		UContentsHelper::MarioLife = 3;
		UContentsHelper::MapName = "FirstStage";
		GEngine->ChangeLevel("Loading");
		return;
	}

	if (UEngineInput::IsAnykeyPress())
	{
		UContentsHelper::CoinCount = 100;
		UContentsHelper::Time = 1400;
		UContentsHelper::SubStage = 1;
		UContentsHelper::MapName = "FirstStage";
		UContentsHelper::MarioLife = 3;
		UContentsHelper::Score = 1000000;
		GEngine->ChangeLevel("Loading");
		return;
	}
}

void UTitleLevel::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
}

void UTitleLevel::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);
}
