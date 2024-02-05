#include "PlayStage.h"

#include <EngineCore\EngineCore.h>

#include "Mario.h"
#include "BackGround.h"

UPlayStage::UPlayStage()
{
}

UPlayStage::~UPlayStage()
{
}

void UPlayStage::BeginPlay()
{
	ULevel::BeginPlay();

	ABackGround* Map = SpawnActor<ABackGround>();
	Map->SetMapImage("Stage01.png");
	Map->SetColMapImage("Stage01_Col.png");
	Map->SwitchDebug();


	AMario* Player = SpawnActor<AMario>();
	Player->SetActorLocation({ 200, 200 });
}

void UPlayStage::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}

void UPlayStage::LevelStart(ULevel* _Level)
{
	// 여기서 리소스를 로드하고
	// 액터도 여기서 만들고
	int a = 0;
}
void UPlayStage::LevelEnd(ULevel* _Level)
{
	// 리소스도 날려요.
	// 액터를 삭제한다.
	int a = 0;
}