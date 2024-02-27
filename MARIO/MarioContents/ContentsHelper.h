#pragma once
#include <EngineBase\EngineMath.h>
#include <EngineCore\EngineCore.h>
#include <EngineCore\ImageRenderer.h>

enum ERenderOrder
{
	Plant,
	Map,
	Gate,
	Brick,
	Monster,
	Player,
};

enum class ECollisionOrder
{
	Player,
	PlayerHead,
	PlayerBottom,
	Goomba,
	Troopa,
	Box,
	Flag,
	Step,
};

enum class EActorDir
{
	Left,
	Right,
};

enum class EMonsterShootDir
{
	Left,
	Right
};

enum class EPlayState
{
	CameraFreeMove,
	FreeMove,
	Idle,
	Run,
	Reverse,
	Jump,
	Die,
	Kill,
	FinishMove,
	FinishReverse,
	FinishWalk,
	None,
};

enum class EMArioSizeState
{
	Small,
	Big,
	Red,
	Star,
	None
};

enum class EMonsterState
{
	Move,
	Dead,
	Touch,
	Shoot,
	Wake,
	None
};

enum class EPlantState
{
	Move,
	Wait,
	Stop,
	None,
};

enum class EBoxState
{
	Idle,
	Hit,
	Break,
	Block,
	None,
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

