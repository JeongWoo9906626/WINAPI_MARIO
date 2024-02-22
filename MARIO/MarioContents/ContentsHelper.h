#pragma once
#include <EngineBase\EngineMath.h>
#include <EngineCore\EngineCore.h>
#include <EngineCore\ImageRenderer.h>

enum ERenderOrder
{
	Plant,
	Map,
	Monster,
	Player,
};

enum class ECollisionOrder
{
	Player,
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
	None,
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

