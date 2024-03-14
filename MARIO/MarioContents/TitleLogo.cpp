#include "TitleLogo.h"
#include <EngineCore/EngineCore.h>
#include "ContentsHelper.h"
#include "UI.h"

ATitleLogo::ATitleLogo() 
{
}

ATitleLogo::~ATitleLogo() 
{
}

void ATitleLogo::BeginPlay()
{
	AActor::BeginPlay();

	UImageRenderer* Renderer = CreateImageRenderer();

	Renderer->SetImage(/*TODO 타이틀 로고 사진 이름*/"Mario_Title.png");
	
	FVector WindowScale = GEngine->MainWindow.GetWindowScale();
	Renderer->SetTransform({ WindowScale.Half2D(), WindowScale });

	TimeHideRenderer = CreateImageRenderer(ERenderOrder::Cheat);
	TimeHideRenderer->SetImage("UITitleBox.png");
	TimeHideRenderer->SetTransform({ { 870, 110 }, { 100, 35 } });
	TimeHideRenderer->CameraEffectOff();

	for (int i = 0; i < 6; i++)
	{
		HighScoreRenderer[i] = CreateImageRenderer(ERenderOrder::UI);
		HighScoreRenderer[i]->SetImage("0.png");
		HighScoreRenderer[i]->SetTransform({ { 555 + (i * 32), 748}, {25, 25}});
		HighScoreRenderer[i]->CameraEffectOff();
	}
}

void ATitleLogo::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	ScoreUpdate();
}

void ATitleLogo::ScoreUpdate()
{
	std::string Count = std::to_string(UContentsHelper::HighScore);
	std::string NumberImage;
	for (int i = 0; i < 6; ++i)
	{
		NumberImage = Count.substr(i + 1, 1) + ".png";
		HighScoreRenderer[i]->SetImage(NumberImage);
	}
}