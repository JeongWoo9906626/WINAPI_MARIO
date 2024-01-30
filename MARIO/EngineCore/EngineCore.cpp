#include "EngineCore.h"
#include <Windows.h>
#include "Level.h"
#include "EnginePlatform\EngineInput.h"


EngineCore* GEngine = nullptr;

EngineCore::EngineCore()
	: MainWindow()
{
}

EngineCore::~EngineCore()
{
}

void EngineCore::CoreTick()
{
	float DeltaTime = MainTimer.TimeCheck();

	if (1 <= Frame)
	{
		CurFrameTime += DeltaTime;

		if (CurFrameTime <= FrameTime)
		{
			return;
		}

		CurFrameTime -= FrameTime;
		DeltaTime = FrameTime;
	}

	EngineInput::KeyCheckTick(DeltaTime);

	if (nullptr == CurLevel)
	{
		MsgBoxAssert("������ ������ ������ �������� �ʾҽ��ϴ� ġ������ �����Դϴ�");
	}
	CurLevel->Tick(DeltaTime);
	CurLevel->LevelTick(DeltaTime);
	CurLevel->LevelRender(DeltaTime);
	CurLevel->LevelRelease(DeltaTime);
}

void EngineCore::EngineTick()
{
	GEngine->CoreTick();
}

void EngineCore::EngineEnd()
{
	for (std::pair<const std::string, ULevel*>& _Pair : GEngine->AllLevel)
	{
		if (nullptr == _Pair.second)
		{
			continue;
		}

		delete _Pair.second;
		_Pair.second = nullptr;
	}

	GEngine->AllLevel.clear();
}

void EngineCore::EngineStart(HINSTANCE _hInstance, EngineCore* _UserCore)
{
	EngineCore* Ptr = _UserCore;
	GEngine = Ptr;
	Ptr->MainTimer.TimeCheckStart();
	Ptr->CoreInit(_hInstance);
	Ptr->BeginPlay();
	UEngineWindow::WindowMessageLoop(EngineTick, EngineEnd);
}

void EngineCore::CoreInit(HINSTANCE _HINSTANCE)
{
	if (true == EngineInit)
	{
		return;
	}

	UEngineWindow::Init(_HINSTANCE);
	MainWindow.Open();

	this->AllLevel;

	EngineInit = true;
}

void EngineCore::BeginPlay()
{

}

void EngineCore::Tick(float _DeltaTime)
{

}

void EngineCore::End()
{

}

void EngineCore::ChangeLevel(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (false == AllLevel.contains(UpperName))
	{
		MsgBoxAssert(std::string(_Name) + "��� �������� �ʴ� ������ ü���� �Ϸ��� �߽��ϴ�");
	}

	CurLevel = AllLevel[UpperName];
}

void EngineCore::LevelInit(ULevel* _Level)
{
	_Level->BeginPlay();
}