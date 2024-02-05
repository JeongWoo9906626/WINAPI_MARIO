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
	// ���⼭ ���ҽ��� �ε��ϰ�
	// ���͵� ���⼭ �����
	int a = 0;
}
void UPlayStage::LevelEnd(ULevel* _Level)
{
	// ���ҽ��� ������.
	// ���͸� �����Ѵ�.
	int a = 0;
}