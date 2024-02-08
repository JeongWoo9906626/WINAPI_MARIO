#include "TestLevel.h"
#include <EnginePlatform\EngineInput.h>
#include <EnginePlatform\EngineWindow.h>
#include <EngineCore\EngineCore.h>

UTestLevel::UTestLevel()
{
}

UTestLevel::~UTestLevel()
{
}

void UTestLevel::BeginPlay()
{
	ULevel::BeginPlay();
}

void UTestLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (UEngineInput::IsDown('A'))
	{
		GEngine->MainWindow.SetClearColor({ 0,0,0,0 });
	}

}

void UTestLevel::LevelStart(ULevel* _Level)
{
	// 여기서 리소스를 로드하고
	// 액터도 여기서 만들고
	int a = 0;
}
void UTestLevel::LevelEnd(ULevel* _Level)
{
	// 리소스도 날려요.
	// 액터를 삭제한다.
	int a = 0;
}