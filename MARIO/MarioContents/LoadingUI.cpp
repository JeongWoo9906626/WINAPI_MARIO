#include "LoadingUI.h"

ALoadingUI::ALoadingUI()
{
}

ALoadingUI::~ALoadingUI()
{
}

void ALoadingUI::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(ERenderOrder::Loading);
	Renderer->SetImage("Loading.png");
	Renderer->SetTransform({ {0, 0}, {GEngine->MainWindow.GetWindowScale()} });
	Renderer->CameraEffectOff();

	MainStageRenderer = CreateImageRenderer(ERenderOrder::Loading);
	MainStageRenderer->SetImage(CheckMainStage());
	MainStageRenderer->SetTransform({ { 45, -147 }, { 30, 30 } });
	MainStageRenderer->CameraEffectOff();
	
	SubStageRenderer = CreateImageRenderer(ERenderOrder::Loading);
	SubStageRenderer->SetImage(CheckSubStage());
	SubStageRenderer->SetTransform({ { 115, -147 }, { 30, 30 } });
	SubStageRenderer->CameraEffectOff();
	
	MarioLifeRenderer = CreateImageRenderer(ERenderOrder::Loading);
	MarioLifeRenderer->SetImage(CheckMarioLife());
	MarioLifeRenderer->SetTransform({ { 75, -15 }, { 30, 30 } });
	MarioLifeRenderer->CameraEffectOff();

	TimeHideRenderer = CreateImageRenderer(ERenderOrder::Cheat);
	TimeHideRenderer->SetImage("UIBlackBox.png");
	TimeHideRenderer->SetTransform({ { 365, -365 }, { 100, 40 } });
	TimeHideRenderer->CameraEffectOff();
}
void ALoadingUI::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	MainStageUpdate();
	SubStageUpdate();
	MarioLifeUpdate();
}

void ALoadingUI::MainStageUpdate()
{
	MainStageRenderer->SetImage(CheckMainStage());
}

void ALoadingUI::SubStageUpdate()
{
	SubStageRenderer->SetImage(CheckSubStage());
}

void ALoadingUI::MarioLifeUpdate()
{
	MarioLifeRenderer->SetImage(CheckMarioLife());
}

std::string ALoadingUI::CheckMainStage()
{
	std::string MainStageString = "";
	switch (UContentsHelper::MainStage)
	{
	case 1:
		MainStageString = "1.png";
		break;
	case 2:
		MainStageString = "2.png";
		break;
	case 3:
		MainStageString = "3.png";
		break;
	case 4:
		MainStageString = "4.png";
		break;
	}
	return MainStageString;
}

std::string ALoadingUI::CheckSubStage()
{
	std::string SubStageString = "";
	switch (UContentsHelper::SubStage)
	{
	case 1:
		SubStageString = "1.png";
		break;
	case 2:
		SubStageString = "2.png";
		break;
	case 3:
		SubStageString = "3.png";
		break;
	case 4:
		SubStageString = "4.png";
		break;
	}
	return SubStageString;
}

std::string ALoadingUI::CheckMarioLife()
{
	std::string MarioLife = "";
	switch (UContentsHelper::MarioLife)
	{
	case 0:
		MarioLife = "0.png";
		break;
	case 1:
		MarioLife = "1.png";
		break;
	case 2:
		MarioLife = "2.png";
		break;
	case 3:
		MarioLife = "3.png";
		break;
	}
	return MarioLife;
}
