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
	Run,
	Reverse,
	Jump,
};

enum class EMArioSizeState
{
	Small,
	Big,
	Red,
	Star
};

// Ό³Έν :
class UContentsHelper
{
public:
	static class AMario* MainPlayer;
	static UWindowImage* MapColImage;

protected:

private:
	// constrcuter destructer
	UContentsHelper();
	~UContentsHelper();
};

