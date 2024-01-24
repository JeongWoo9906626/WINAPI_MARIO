#include "ContentsCore.h"
#include "TitleLevel.h"

ContentsCore::ContentsCore()
	: EngineCore()
{
}

ContentsCore::~ContentsCore()
{
}

// 게임시작
void ContentsCore::Start()
{
	CreateLevel<UTitleLevel>("Title");
}

void ContentsCore::Update()
{
}

void ContentsCore::End()
{
}