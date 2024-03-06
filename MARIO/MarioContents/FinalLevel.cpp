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
#include "BirdgeHandle.h"
#include "Bridge.h"
#include "Koopa.h"

UFinalLevel::UFinalLevel()
{
}

UFinalLevel::~UFinalLevel()
{
}

void UFinalLevel::BeginPlay()
{
	ULevel::BeginPlay();

	UContentsHelper::Time = 1300;
	UContentsHelper::SubStage = 4;
	UContentsHelper::MapName = "FinalStage";

	ABackGround* BackGroundMap = SpawnActor<ABackGround>(ERenderOrder::Map);
	BackGroundMap->SetMapImage("Stage04.png");
	BackGroundMap->SetCollisionMapImage("Stage04_Col.png");
	BackGroundMap->SwitchDebug();

	AUI* UI = SpawnActor<AUI>(ERenderOrder::UI);
	UI->SetActorLocation({ 200, 200 });

	AMario* Mario = SpawnActor<AMario>(ERenderOrder::Player);
	Mario->SetName("Player");
	Mario->SetActorLocation({ 100, 700 });

	ABirdgeHandle* BirdgeHandle = SpawnActor<ABirdgeHandle>(ERenderOrder::Brick);
	BirdgeHandle->SetName("Handle");
	BirdgeHandle->SetActorLocation({ 9050, 540 });

	AKoopa* Koopa = SpawnActor<AKoopa>(ERenderOrder::Monster);
	Koopa->SetActorLocation({ 8862, 600 });

	// Bridge
	{
		ABridge* Bridge1 = SpawnActor<ABridge>(ERenderOrder::Brick);
		Bridge1->SetActorLocation({ 8222, 672 });

		ABridge* Bridge2 = SpawnActor<ABridge>(ERenderOrder::Brick);
		Bridge2->SetActorLocation({ 8286, 672 });

		ABridge* Bridge3 = SpawnActor<ABridge>(ERenderOrder::Brick);
		Bridge3->SetActorLocation({ 8350, 672 });

		ABridge* Bridge4 = SpawnActor<ABridge>(ERenderOrder::Brick);
		Bridge4->SetActorLocation({ 8414, 672 });

		ABridge* Bridge5 = SpawnActor<ABridge>(ERenderOrder::Brick);
		Bridge5->SetActorLocation({ 8478, 672 });

		ABridge* Bridge6 = SpawnActor<ABridge>(ERenderOrder::Brick);
		Bridge6->SetActorLocation({ 8542, 672 });

		ABridge* Bridge7 = SpawnActor<ABridge>(ERenderOrder::Brick);
		Bridge7->SetActorLocation({ 8606, 672 });

		ABridge* Bridge8 = SpawnActor<ABridge>(ERenderOrder::Brick);
		Bridge8->SetActorLocation({ 8670, 672 });

		ABridge* Bridge9 = SpawnActor<ABridge>(ERenderOrder::Brick);
		Bridge9->SetActorLocation({ 8734, 672 });

		ABridge* Bridge10 = SpawnActor<ABridge>(ERenderOrder::Brick);
		Bridge10->SetActorLocation({ 8798, 672 });

		ABridge* Bridge11 = SpawnActor<ABridge>(ERenderOrder::Brick);
		Bridge11->SetActorLocation({ 8862, 672 });

		ABridge* Bridge12 = SpawnActor<ABridge>(ERenderOrder::Brick);
		Bridge12->SetActorLocation({ 8926, 672 });

		ABridge* Bridge13 = SpawnActor<ABridge>(ERenderOrder::Brick);
		Bridge13->SetActorLocation({ 8990, 672 });
	}
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
