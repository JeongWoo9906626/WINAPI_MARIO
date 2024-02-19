#pragma once
#include <EngineBase\EngineMath.h>
#include <EngineCore\EngineCore.h>
#include <EngineCore\ImageRenderer.h>

enum ERenderOrder
{
	Map,
	Monster,
	Player
};

enum class ECollisionOrder
{
	Player,
	Monster,
	Box,
	Step,
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

enum class EMonsterState
{
	Move,
	Dead,
	None
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

