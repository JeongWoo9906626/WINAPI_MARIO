#include "MarioCore.h"
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineFile.h>	
#include <EngineCore/EngineResourcesManager.h>
#include "TitleLevel.h"
#include "PlayLevel.h"
#include "FinalLevel.h"

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

	ResoucreManager.CuttingImage("Mario_Right.png", 5, 7);
	ResoucreManager.CuttingImage("Mario_Left.png", 5, 7);
	
	ResoucreManager.CuttingImage("OpenWorldGoomba.png", 3, 1);
	ResoucreManager.CuttingImage("OpenWorldTroopa_Left.png", 5, 2);
	ResoucreManager.CuttingImage("OpenWorldTroopa_Right.png", 5, 2);
	ResoucreManager.CuttingImage("Plant.png", 2, 1);
	
	ResoucreManager.CuttingImage("OpenWorldBrick.png", 5, 1);
	ResoucreManager.CuttingImage("OpenWorldBrokenBrick.png", 2, 2);
	ResoucreManager.CuttingImage("OpenWorldBox.png", 6, 1);
	
	ResoucreManager.CuttingImage("Coin.png", 4, 1);
	ResoucreManager.CuttingImage("HiddenCoin.png", 3, 1);
	ResoucreManager.CuttingImage("MarioItem.png", 5, 2);

	ResoucreManager.CuttingImage("UICoin.png", 3, 1);

	// TODO
	// ������ ��� ���� Core���� ����
	CreateLevel<UTitleLevel>("Title");
	CreateLevel<UPlayLevel>("Play");
	//CreateLevel<UFinalLevel>("Final");

	// TODO
	// ó�� ������ ���� ����
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
