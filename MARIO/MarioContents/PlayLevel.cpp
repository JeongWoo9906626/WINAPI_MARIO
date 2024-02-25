#include "PlayLevel.h"
#include "BackGround.h"
#include "ContentsHelper.h"
#include "Mario.h"
#include "Goomba.h"
#include "Troopa.h"
#include "Plant.h"
#include "Flag.h"

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
	
		//AGoomba* Goomba = SpawnActor<AGoomba>(ERenderOrder::Monster);
		//Goomba->SetName("OpenWorldGoomba1");
		//Goomba->SetActorLocation({ 1200, 600 });
		//AGoomba* Goomba2 = SpawnActor<AGoomba>(ERenderOrder::Monster);
		//Goomba2->SetName("OpenWorldGoomba2");
		//Goomba2->SetActorLocation({ 1260, 600 });

		//ATroopa* Turtle = SpawnActor<ATroopa>(ERenderOrder::Monster);
		//Turtle->SetName("OpenWorldTroopa");
		//Turtle->SetActorLocation({ 1600, 700 });
		//ATroopa* Turtle2 = SpawnActor<ATroopa>(ERenderOrder::Monster);
		//Turtle2->SetName("OpenWorldTroopa2");
		//Turtle2->SetActorLocation({ 1000, 700 });

		//APlant* Plant = SpawnActor<APlant>(ERenderOrder::Plant);
		//Plant->SetName("Plant");
		//// 710 MaxTop 
		//// 800 MaxBottom
		//Plant->SetActorLocation({ 1855, 800 });
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
