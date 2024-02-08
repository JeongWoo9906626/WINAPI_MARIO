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

enum class EActorDir
{
	Left,
	Right,
};

enum class EPlayState
{
	None,
	CameraFreeMove,
	FreeMove,
	Idle,
	Move,
	MoveReverse,
	Jump,
};

enum class EMArioSizeState
{
	Small,
	Big,
	Red,
	Star
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

