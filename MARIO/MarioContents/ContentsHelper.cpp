#include "ContentsHelper.h"
#include "Mario.h"

UWindowImage* UContentsHelper::MapColImage = nullptr;
EMarioSizeState UContentsHelper::MSizeState = EMarioSizeState::Small;
std::string UContentsHelper::MapName = "";

int UContentsHelper::MarioLife = 3;
int UContentsHelper::CoinCount = 100;
int UContentsHelper::Score = 1000000;
int UContentsHelper::HighScore = 1000000;
int UContentsHelper::Time = 1400;
int UContentsHelper::MainStage = 1;
int UContentsHelper::SubStage = 1;
int UContentsHelper::MarioFireCount = 0;

bool UContentsHelper::IsFlagDown = false;
bool UContentsHelper::KoopaDie = false;
bool UContentsHelper::KoopaWake = false;
bool UContentsHelper::KoopaIsFire = false;
bool UContentsHelper::MarioDie = false;
bool UContentsHelper::IsBridgeHandleCollision = false;
bool UContentsHelper::IsBossStage = false;
bool UContentsHelper::IsStageSoundOff = false;
bool UContentsHelper::IsUnderStage = false;

FVector UContentsHelper::PortalPos1 = { 3708.0f, 578.0f, 0.0f, 0.0f };
FVector UContentsHelper::HiddenStageSpawnPos = { 3218.0f, 1262.0f, 0.0f, 0.0f };
FVector UContentsHelper::HiddenStageOutSpawnPos = { 10492.0f, 803.0f, 0.0f, 0.0f };

float UContentsHelper::HiddenStageCameraPosX = 3064.0f;
float UContentsHelper::HiddenStageOutCameraPosX = 10260.0f;

UContentsHelper::UContentsHelper()
{
}

UContentsHelper::~UContentsHelper()
{
}

