#include "StartStage.h"

#include "StartMapLogo.h"
#include <EngineCore\EngineCore.h>

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
		AStartMapLogo* Logo = SpawnActor<AStartMapLogo>();
	}


}
void UStartStage::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (UEngineInput::IsDown('P'))
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