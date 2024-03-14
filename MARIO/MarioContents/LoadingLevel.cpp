#include "LoadingLevel.h"

#include "LoadingUI.h"
#include "UI.h"

ULoadingLevel::ULoadingLevel()
{
}

ULoadingLevel::~ULoadingLevel()
{
}

void ULoadingLevel::BeginPlay()
{
	ULevel::BeginPlay();
	ALoadingUI* Loading = SpawnActor<ALoadingUI>(ERenderOrder::Loading);
	Loading->SetActorLocation({ GEngine->MainWindow.GetWindowScale().ihX(), GEngine->MainWindow.GetWindowScale().ihY() });

	AUI* UI = SpawnActor<AUI>(ERenderOrder::UI);
	UI->SetActorLocation({ 200, 200 });
}

void ULoadingLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
	
}

void ULoadingLevel::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
}

void ULoadingLevel::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);
}
