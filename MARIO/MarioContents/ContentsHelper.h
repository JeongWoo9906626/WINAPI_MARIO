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
	Coin,
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
	BoxTop,
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

enum class EMarioSizeState
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
	CollisionMove,
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

enum class ECoinState
{
	CoinSpawn,
	CoinDestroy,
	None,
};

// ���� :
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

