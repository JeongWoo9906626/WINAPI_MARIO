#include "MarioCore.h"
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineFile.h>	
#include <EngineCore/EngineResourcesManager.h>
#include "TitleLevel.h"
#include "PlayLevel.h"

UMarioCore::UMarioCore() 
{
}

UMarioCore::~UMarioCore() 
{
}

void UMarioCore::BeginPlay()
{
	UEngineCore::BeginPlay();

	MainWindow.SetWindowScale({ 256 * 4, 240 * 4 });
	MainWindow.SetWindowPosition({ 0, 0 });

	UEngineDirectory NewDir;
	NewDir.MoveParent();
	NewDir.Move("ContentsResources");

	std::list<UEngineFile> NewList = NewDir.AllFile({ ".png", ".bmp" }, true);
	UEngineResourcesManager& ResoucreManager = UEngineResourcesManager::GetInst();

	for (UEngineFile& File : NewList)
	{
		ResoucreManager.LoadImg(File.GetFullPath());
	}

	ResoucreManager.CuttingImage("Mario_Right.png", 5, 8);
	ResoucreManager.CuttingImage("Mario_Left.png", 5, 8);
	ResoucreManager.CuttingImage("Goomba.png", 3, 1);

	// TODO
	// 생성할 모든 레벨 Core에서 생성
	CreateLevel<UTitleLevel>("Title");
	CreateLevel<UPlayLevel>("Play");

	// TODO
	// 처음 시작할 레벨 설정
	//ChangeLevel("Play");
	ChangeLevel("Title");
}

void UMarioCore::Tick(float _DeltaTime)
{
	UEngineCore::Tick(_DeltaTime);

	if (true == UEngineInput::IsDown(VK_F2))
	{
		GEngine->EngineDebugSwitch();
	}
}

void UMarioCore::End()
{
	UEngineCore::End();
}
