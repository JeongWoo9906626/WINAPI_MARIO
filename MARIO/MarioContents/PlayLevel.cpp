#include "PlayLevel.h"
#include "BackGround.h"
#include "ContentsHelper.h"
#include "Mario.h"
#include "Goomba.h"
#include "Troopa.h"
#include "Plant.h"
#include "Flag.h"
#include "Brick.h"
#include "BreakBrick.h"
#include "ItemBox.h"
#include "Gate.h"

UPlayLevel::UPlayLevel()
{
}

UPlayLevel::~UPlayLevel()
{
}

void UPlayLevel::BeginPlay()
{
	ULevel::BeginPlay();

	ABackGround* BackGroundMap = SpawnActor<ABackGround>(ERenderOrder::Map);
	BackGroundMap->SetMapImage("Stage01.png");
	BackGroundMap->SetCollisionMapImage("Stage01_Col.png");
	BackGroundMap->SwitchDebug();

	AFlag* Flag = SpawnActor<AFlag>(ERenderOrder::Map);
	//Flag->SetActorLocation({ 705, 700 });
	Flag->SetActorLocation({ 12705, 700 });

	AMario* Mario = SpawnActor<AMario>(ERenderOrder::Player);
	Mario->SetName("Player");
	Mario->SetActorLocation({ 200, 500 });

	AGoomba* Goomba = SpawnActor<AGoomba>(ERenderOrder::Monster);
	Goomba->SetName("OpenWorldGoomba1");
	Goomba->SetActorLocation({ 750, 600 });
	AGoomba* Goomba2 = SpawnActor<AGoomba>(ERenderOrder::Monster);
	Goomba2->SetName("OpenWorldGoomba2");
	Goomba2->SetActorLocation({ 1260, 600 });

	ATroopa* Turtle = SpawnActor<ATroopa>(ERenderOrder::Monster);
	Turtle->SetName("OpenWorldTroopa");
	Turtle->SetActorLocation({ 1600, 700 });
	ATroopa* Turtle2 = SpawnActor<ATroopa>(ERenderOrder::Monster);
	Turtle2->SetName("OpenWorldTroopa2");
	Turtle2->SetActorLocation({ 1000, 700 });

	APlant* Plant = SpawnActor<APlant>(ERenderOrder::Plant);
	Plant->SetName("Plant");
	// 710 MaxTop 
	// 800 MaxBottom
	Plant->SetActorLocation({ 1855, 800 });

	ABrick* OWBrick;
	OWBrick = SpawnActor<ABrick>(ERenderOrder::Brick);
	OWBrick->SetName("Brick1");
	OWBrick->SetActorLocation({ 800, 640 });
	
	ABrick* OWBrick1;
	OWBrick1 = SpawnActor<ABrick>(ERenderOrder::Brick);
	OWBrick1->SetName("Brick2");
	OWBrick1->SetActorLocation({ 861, 640 });
	
	ABrick* OWBrick2;
	OWBrick2 = SpawnActor<ABrick>(ERenderOrder::Brick);
	OWBrick2->SetName("Brick3");
	OWBrick2->SetActorLocation({ 922, 640 });
	
	ABrick* OWBrick3;
	OWBrick3 = SpawnActor<ABrick>(ERenderOrder::Brick);
	OWBrick3->SetName("Brick4");
	OWBrick3->SetActorLocation({ 983, 640 });

	AGate* Gate = SpawnActor<AGate>(ERenderOrder::Gate);
	Gate->SetName("Gate1");
	Gate->SetActorLocation({ 13140, 800 });

	ABreakBrick* OWBreakBrick;
	OWBreakBrick = SpawnActor<ABreakBrick>(ERenderOrder::Brick);
	OWBreakBrick->SetName("Brick1");
	OWBreakBrick->SetActorLocation({ 700, 640 });

	AItemBox* ItemBrick;
	ItemBrick = SpawnActor<AItemBox>(ERenderOrder::Brick);
	ItemBrick->SetName("Item1");
	ItemBrick->SetActorLocation({ 800, 640 });

	AItemBox* ItemBrick1;
	ItemBrick1 = SpawnActor<AItemBox>(ERenderOrder::Brick);
	ItemBrick1->SetName("Item1");
	ItemBrick1->SetActorLocation({ 1044, 640 });
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
