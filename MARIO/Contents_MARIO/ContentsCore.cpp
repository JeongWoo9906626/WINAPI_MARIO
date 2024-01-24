#include "ContentsCore.h"
#include "TitleLevel.h"
#include "PlayLevel.h"

ContentsCore::ContentsCore()
	: EngineCore()
{
}

ContentsCore::~ContentsCore()
{
}

// ���ӽ���
void ContentsCore::BeginPlay()
{
	CreateLevel<UTitleLevel>("Title");
	CreateLevel<UPlayLevel>("PlayLevel");

	ChangeLevel("PlayLevel");
}

void ContentsCore::Tick(float _DeltaTime)
{
}

void ContentsCore::End()
{
}