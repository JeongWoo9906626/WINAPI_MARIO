#include "ContentsCore.h"
#include "TitleLevel.h"

ContentsCore::ContentsCore()
	: EngineCore()
{
}

ContentsCore::~ContentsCore()
{
}

// ���ӽ���
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