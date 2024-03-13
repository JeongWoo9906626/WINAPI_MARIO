#include "TitleLevel.h"
#include "TitleLogo.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineCore.h>
#include "BackGround.h"

UTitleLevel::UTitleLevel()
{
}

UTitleLevel::~UTitleLevel()
{
}

void UTitleLevel::BeginPlay()
{
	ULevel::BeginPlay();
	ATitleLogo* Logo = SpawnActor<ATitleLogo>();
}

void UTitleLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (UEngineInput::IsAnykeyPress())
	{
		GEngine->ChangeLevel("Play");
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
