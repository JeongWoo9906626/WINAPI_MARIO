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

	if (UEngineInput::IsAnykeyPress())
	{
		UContentsHelper::Time = 1400;
		UContentsHelper::SubStage = 1;
		UContentsHelper::MapName = "FirstStage";
		UContentsHelper::MarioLife = 3;
		UContentsHelper::Score = 1000000;
		GEngine->ChangeLevel("Loading");
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
