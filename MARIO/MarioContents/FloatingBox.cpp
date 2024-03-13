#include "FloatingBox.h"
#include "Mario.h"

AFloatingBox::AFloatingBox()
{
}

AFloatingBox::~AFloatingBox()
{
}

void AFloatingBox::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(ERenderOrder::Brick);
	Renderer->SetImage("FloatingBox.png");
	Renderer->SetTransform({ { 0, 0 }, { 128.0f * 2.0f, 128.0f * 1.4f } });

	TopCollision = CreateCollision(ECollisionOrder::BoxTop);
	TopCollision->SetColType(ECollisionType::Rect);
	TopCollision->SetTransform({ {0, -20}, { 130, 10 } });

	BottomCollision = CreateCollision(ECollisionOrder::Box);
	BottomCollision->SetColType(ECollisionType::Rect);
	BottomCollision->SetTransform({ {0, 0}, { 130, 10 } });

	LeftCollision = CreateCollision(ECollisionOrder::Box);
	LeftCollision->SetColType(ECollisionType::Rect);
	LeftCollision->SetTransform({ {-60, -10}, {10, 20} });

	RightCollision = CreateCollision(ECollisionOrder::Box);
	RightCollision->SetColType(ECollisionType::Rect);
	RightCollision->SetTransform({ {60, -10}, {10, 20} });
}

void AFloatingBox::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> TopResult;
	if (true == TopCollision->CollisionCheck(ECollisionOrder::PlayerBottom, TopResult))
	{
		IsTopCollision = true;
	}
	else
	{
		IsTopCollision = false;
	}

	std::vector<UCollision*> BottomResult;
	if (true == BottomCollision->CollisionCheck(ECollisionOrder::PlayerHead, BottomResult))
	{
		UCollision* MarioPosition = BottomResult[0];
		AMario* Player = (AMario*)MarioPosition->GetOwner();

		Player->JumpVector = FVector::Zero;
		return;
	}

	std::vector<UCollision*> LeftResult;
	if (true == LeftCollision->CollisionCheck(ECollisionOrder::Player, LeftResult))
	{
		UCollision* MarioPosition = LeftResult[0];
		AMario* Player = (AMario*)MarioPosition->GetOwner();

		Player->MoveVector.X = 0.0f;
		Player->AddActorLocation(FVector::Left);
		return;
	}

	std::vector<UCollision*> RightResult;
	if (true == RightCollision->CollisionCheck(ECollisionOrder::Player, RightResult))
	{
		UCollision* MarioPosition = RightResult[0];
		AMario* Player = (AMario*)MarioPosition->GetOwner();

		Player->MoveVector.X = 0.0f;
		Player->AddActorLocation(FVector::Right);
		return;
	}

	if (true == UContentsHelper::IsBridgeHandleCollision)
	{
		Destroy();
	}

	if (true == UContentsHelper::KoopaWake)
	{
		Float(_DeltaTime);
	}
}

void AFloatingBox::Float(float _DeltaTime)
{
	if (MoveRange > CurMoveX)
	{
		CurMoveX = MoveRange;
		ChangeDir();
	}

	if (CurMoveX > 0.0f)
	{
		CurMoveX = 0.0f;
		ChangeDir();
	}

	CurMoveX += DirVector * 100.f * _DeltaTime;
	float FloatMoveX = DirVector * 100.f * _DeltaTime;
	if (true == IsTopCollision)
	{
		AMario::MainPlayer->AddActorLocation({ FloatMoveX, 0.0f });
	}
	AddActorLocation({ FloatMoveX, 0.0f });
}

void AFloatingBox::ChangeDir()
{
	switch (DirState)
	{
	case EActorDir::Left:
	{
		DirState = EActorDir::Right;
		DirVector = 1.0f;
		break;
	}
	case EActorDir::Right:
	{
		DirState = EActorDir::Left;
		DirVector = -1.0f;
		break;
	}
	}
}


