#include "UI.h"

#include <EnginePlatform\EngineInput.h>
#include <EngineBase\EngineDebug.h>

#include "ContentsHelper.h"

AUI::AUI()
{
}

AUI::~AUI()
{
}

void AUI::BeginPlay()
{
	AActor::BeginPlay();

	ScoreRenderer = CreateImageRenderer(ERenderOrder::UI);
	ScoreRenderer->SetImage("UIBar.png");

	FVector UIScale = ScoreRenderer->GetImage()->GetScale();

	ScoreRenderer->SetTransform({ { 296,-136 }, { 1024, 108 } });
	ScoreRenderer->CameraEffectOff();

	CoinImage = CreateImageRenderer(ERenderOrder::UI);
	CoinImage->SetImage("UICoin.png");
	CoinImage->SetTransform({ { 165 ,-95 }, { 128,128 } });
	CoinImage->CameraEffectOff();

	for (int i = 0; i < 2; i++)
	{
		Coins[i] = CreateImageRenderer(ERenderOrder::UI);
		Coins[i]->SetImage("0.png");
		Coins[i]->SetTransform({ { 230 + (i * 35), -95}, {20, 20} });
		Coins[i]->CameraEffectOff();
	}

	for (int i = 0; i < 6; i++)
	{
		ScoreArray[i] = CreateImageRenderer(ERenderOrder::UI);
		ScoreArray[i]->SetImage("0.png");
		ScoreArray[i]->SetTransform({ { -110 + (i * 35), -95}, {20, 20} });
		ScoreArray[i]->CameraEffectOff();
	}

	for (int i = 0; i < 3; i++)
	{
		TimeArray[i] = CreateImageRenderer(ERenderOrder::UI);
		TimeArray[i]->SetImage("0.png");
		TimeArray[i]->SetTransform({ { 640 + (i * 35), -95 }, { 20, 20 } });
		TimeArray[i]->CameraEffectOff();
	}

	MainStageImage = CreateImageRenderer(ERenderOrder::UI);
	MainStageImage->SetImage("0.png");
	MainStageImage->SetTransform({ {430, -95}, {20, 20} });
	MainStageImage->CameraEffectOff();

	SubStageImage = CreateImageRenderer(ERenderOrder::UI);
	SubStageImage->SetImage("0.png");
	SubStageImage->SetTransform({ {485, -95}, {20, 20} });
	SubStageImage->CameraEffectOff();

	CoinImage->CreateAnimation("Idle", "UICoin.png", 0, 5, 0.2f, true);
	CoinImage->ChangeAnimation("Idle");
}

void AUI::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	CoinsUpdate();
	ScoreUpdate();
	TimeUpdate();
	StageUIUpdate();
}

void AUI::CoinsUpdate()
{
	std::string Count = std::to_string(UContentsHelper::CoinCount);
	std::string NumberImage;
	for (int i = 0; i < 2; ++i) 
	{
		NumberImage = Count.substr(i + 1, 1) + ".png";
		Coins[i]->SetImage(NumberImage);
	}
}

void AUI::ScoreUpdate()
{
	std::string Count = std::to_string(UContentsHelper::Score);
	std::string NumberImage;
	for (int i = 0; i < 6; ++i) 
	{
		NumberImage = Count.substr(i + 1, 1) + ".png";
		ScoreArray[i]->SetImage(NumberImage);
	}
}

void AUI::TimeUpdate()
{
	std::string Count = std::to_string(UContentsHelper::Time);
	std::string NumberImage;
	for (int i = 0; i < 3; ++i) 
	{
		NumberImage = Count.substr(i + 1, 1) + ".png";
		TimeArray[i]->SetImage(NumberImage);
	}
}

void AUI::StageUIUpdate()
{
	std::string MainStageNum = std::to_string(UContentsHelper::MainStage);
	std::string SubStageNum = std::to_string(UContentsHelper::SubStage);

	MainStageImage->SetImage(MainStageNum + ".png");
	SubStageImage->SetImage(SubStageNum + ".png");
}