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
	// ���⼭ ���ҽ��� �ε��ϰ�
	// ���͵� ���⼭ �����
	int a = 0;
}
void UTestLevel::LevelEnd(ULevel* _Level)
{
	// ���ҽ��� ������.
	// ���͸� �����Ѵ�.
	int a = 0;
}