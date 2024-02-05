#include "StartStage.h"

#include "StartMap.h"
#include "EngineCore\EngineCore.h"

UStartStage::UStartStage()
{
}

UStartStage::~UStartStage()
{
}

void UStartStage::BeginPlay()
{
	ULevel::BeginPlay();

	{
		// Start Map
		ATestTitleLogo* Logo = SpawnActor<ATestTitleLogo>();
	}


}
void UStartStage::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (EngineInput::IsDown('P'))
	{
		GEngine->ChangeLevel("Play");
	}

}
void UStartStage::LevelStart(ULevel* _Level)
{
	int a = 0;
}
void UStartStage::LevelEnd(ULevel* _Level)
{
	int a = 0;
}