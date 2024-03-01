#pragma once
#include <EngineBase\EngineMath.h>
#include <EngineCore\EngineCore.h>
#include <EngineCore\ImageRenderer.h>

enum ERenderOrder
{
	Plant,
	Map,
	UI,
	Gate,
	Coin,
	Monster,
	Brick,
	Item,
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
	Gate,
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
	Change,
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

enum class EItemState
{
	Spawn,
	Move,
	CollisionMove,
	Eat,
	None,
};

// Ό³Έν :
class UContentsHelper
{
public:
	static class AMario* MainPlayer;
	static UWindowImage* MapColImage;
	
	static int CoinCount;
	static int Score;
	static int Time;
	static int MainStage;
	static int SubStage;
protected:

private:
	// constrcuter destructer
	UContentsHelper();
	~UContentsHelper();
};

