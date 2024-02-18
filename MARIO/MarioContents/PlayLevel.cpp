#include "PlayLevel.h"
#include "BackGround.h"
#include "ContentsHelper.h"
#include "Mario.h"
#include "Goomba.h"

UPlayLevel::UPlayLevel() 
{
}

UPlayLevel::~UPlayLevel() 
{
}

void UPlayLevel::BeginPlay()
{
	ULevel::BeginPlay();

	ABackGround* BackGroundMap = SpawnActor<ABackGround>(RenderOrder::Map);
	BackGroundMap->SetMapImage("Stage01.png");
	BackGroundMap->SetCollisionMapImage("Stage01_Col.png");
	BackGroundMap->SwitchDebug();

	AMario* Mario = SpawnActor<AMario>(RenderOrder::Player);
	Mario->SetName("Player");
	Mario->SetActorLocation({ 200, 200 });

	AGoomba* Goomba = SpawnActor<AGoomba>(RenderOrder::Monster);
	Goomba->SetName("Goomba1");
	Goomba->SetActorLocation({ 400, 200 });
}

void UPlayLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}

void UPlayLevel::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
}

void UPlayLevel::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);
}
