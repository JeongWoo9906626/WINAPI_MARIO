#include "EndingGate.h"
#include "Mario.h"

AEndingGate::AEndingGate()
{
}

AEndingGate::~AEndingGate()
{
}

void AEndingGate::BeginPlay()
{
	AActor::BeginPlay();

	Text = CreateImageRenderer(ERenderOrder::UI);
	Text->SetImage("UIEndingText.png");
	Text->SetTransform({ { -50, -360 }, { 768, 320 } });

	UIBox = CreateImageRenderer(ERenderOrder::UI);
	UIBox->SetImage("UIBlackBox.png");
	UIBox->SetTransform({ { -50, -360 }, { 768, 320 } });


	Collision = CreateCollision(ECollisionOrder::Gate);
	Collision->SetColType(ECollisionType::Rect);
	Collision->SetTransform({ { 0, -30 }, { 65, 70 } });
}

void AEndingGate::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (true == IsEndingMessage)
	{
		if (CurTime >= Time) 
		{
			CurTime = 0.0f;
			FVector Pos = UIBox->GetTransform().GetPosition();
			FVector Scale = UIBox->GetTransform().GetScale();
			Pos.Y += 32.f;
			Scale.Y -= 64.f;
			UIBox->SetTransform({ Pos, Scale });

			if (0.0f > Scale.Y)
			{
				UContentsHelper::HighScore = UContentsHelper::Score;
				GEngine->ChangeLevel("GameOver");
				return;
			}

		}
		CurTime += _DeltaTime;
	}

	std::vector<UCollision*> Result;
	if (true == Collision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		UCollision* MarioPosition = Result[0];
		AMario* Player = (AMario*)MarioPosition->GetOwner();
		
		Player->StateChange(EPlayState::Ending);

		IsEndingMessage = true;
		Collision->Destroy();
	}
}
