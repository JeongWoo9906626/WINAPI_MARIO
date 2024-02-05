#include "MarioContentsCore.h"

#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include <EngineCore\EngineResourcesManager.h>

#include "TestTitleLevel.h"
#include "TestPlayLevel.h"

UMarioContentsCore::UMarioContentsCore()
{
}

UMarioContentsCore::~UMarioContentsCore()
{
}

void UMarioContentsCore::BeginPlay()
{
	MainWindow.SetWindowScale({ 256 * 4, 240 * 4 });
	MainWindow.SetWindowPosition({ 800, 0 });

	UEngineCore::BeginPlay();

	// D:\Project\GM\WIn\App
	UEngineDirectory NewDir;

	// D:\Project\GM\WIn
	NewDir.MoveParent();

	// D:\Project\GM\WIn\ContentsResources
	NewDir.Move("ContentsResources");

	std::list<UEngineFile> NewList = NewDir.AllFile({ ".png", ".bmp" }, true);

	// 엔진만의 규칙을 정할거냐.
	for (UEngineFile& File : NewList)
	{
		UEngineResourcesManager::GetInst().LoadImg(File.GetFullPath());
	}

	UEngineResourcesManager::GetInst().CuttingImage("TestPlayer_Right.png", 5, 8);
	UEngineResourcesManager::GetInst().LoadFolder(NewDir.AppendPath("PlayLevel\\TestFolderAnimation"));

	CreateLevel<UTestTitleLevel>("Title");
	CreateLevel<UTestPlayLevel>("Play");
	ChangeLevel("Play");
}

void UMarioContentsCore::Tick(float _DeltaTime)
{
	UEngineCore::Tick(_DeltaTime);
}
