#pragma once
#include <EngineBase\EngineMath.h>
#include <EngineCore\EngineCore.h>
#include <EngineCore\ImageRenderer.h>
//#include "Mario.h"

enum ERenderOrder
{
	Map,
	Plant,
	Gate,
	Coin,
	Monster,
	Brick,
	Item,
	Flag,
	Player,
	BreakOne,
	Fire,
	Pipe,
	Loading,
	UI,
	Cheat,
};

enum class ECollisionOrder
{
	Player,
	PlayerHead,
	PlayerBottom,
	Monster,
	MonsterHead,
	MonsterBottom,
	Goomba,
	Troopa,
	Item,
	Box,
	BoxTop,
	Gate,
	BlockGate,
	Flag,
	Step,
	HiddenCoin,
	Fire,
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
	FreeMove,
	CameraFreeMove,
	Idle,
	Move,
	Jump,
	Crouch,
	CrouchMove,
	Reverse,
	Kill,
	Die,
	GrowUp,
	GrowDown,
	ChangeRed,
	HiddenStageEnter,
	HiddenStageOut,
	HiddenStageOutUp,
	FinishMove,
	FinishReverse,
	FinishWalk,
	BossFinish,
	BossFinishWalk,
	Ending,
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

enum class EKoopaState
{
	Idle,
	Walk,
	Jump,
	Dead,
	None,
};

enum class EMonsterState
{
	Move,
	Wait,
	Jump,
	SpinDead,
	Dead,
	HeadHit,
	Shoot,
	Fire,
	Wake,
	None
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

enum class EGateState
{
	In,
	Out,
	None,
};

// Ό³Έν :
class UContentsHelper
{
public:
	static UWindowImage* MapColImage;

	static enum EMarioSizeState MSizeState;

	static int MarioLife;
	static int CoinCount;
	static int Score;
	static int HighScore;
	static int Time;
	static int MainStage;
	static int SubStage;

	static std::string MapName;

	static bool IsFlagDown;
	static bool KoopaDie;
	static bool KoopaWake;
	static bool KoopaIsFire;
	static bool MarioDie;
	static bool IsBridgeHandleCollision;
	static bool IsBossStage;

	static FVector PortalPos1;
	static float HiddenStageCameraPosX;
	static float HiddenStageOutCameraPosX;
	static FVector HiddenStageSpawnPos;
	static FVector HiddenStageOutSpawnPos;
	static int MarioFireCount;

protected:

private:
	// constrcuter destructer
	UContentsHelper();
	~UContentsHelper();
};

