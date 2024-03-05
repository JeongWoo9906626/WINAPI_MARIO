#include "FinalLevel.h"
#include "BackGround.h"
#include "ContentsHelper.h"
#include "Mario.h"
#include "Plant.h"
#include "Flag.h"
#include "Brick.h"
#include "BreakBrick.h"
#include "ItemBox.h"
#include "UI.h"

UFinalLevel::UFinalLevel()
{
}

UFinalLevel::~UFinalLevel()
{
}

void UFinalLevel::BeginPlay()
{
	ULevel::BeginPlay();

	ABackGround* BackGroundMap = SpawnActor<ABackGround>(ERenderOrder::Map);
	BackGroundMap->SetMapImage("Stage04.png");
	BackGroundMap->SetCollisionMapImage("Stage04_Col.png");
	BackGroundMap->SwitchDebug();

	AUI* UI = SpawnActor<AUI>(ERenderOrder::UI);
	UI->SetActorLocation({ 200, 200 });

	AMario* Mario = SpawnActor<AMario>(ERenderOrder::Player);
	Mario->SetName("Player");
	Mario->SetActorLocation({ 200, 500 });
}

void UFinalLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}

void UFinalLevel::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
	int a = 0;
}

void UFinalLevel::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);
}
