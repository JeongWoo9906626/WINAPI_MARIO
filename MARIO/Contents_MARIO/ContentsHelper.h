#pragma once
#include <EngineBase\EngineMath.h>
#include <EngineCore\EngineCore.h>
#include <EngineCore\ImageRenderer.h>

enum RenderOrder
{
	Map,
	Monster,
	Player
};

class UContentsHelper
{
public:
	static UWindowImage* MapColImage;

private:
	// constrcuter destructer
	UContentsHelper();
	~UContentsHelper();
};

