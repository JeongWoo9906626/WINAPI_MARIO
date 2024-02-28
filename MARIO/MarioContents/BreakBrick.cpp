#include "BreakBrick.h"
#include "Mario.h"

ABreakBrick::ABreakBrick()
{
}

ABreakBrick::~ABreakBrick()
{
}

void ABreakBrick::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(ERenderOrder::Brick);
	Renderer->SetImage("OpenWorldBrick.png");
	Renderer->SetTransform({ { 0, 0 }, { 256 * 3.8f, 256 * 3.8f } });

	Renderer->CreateAnimation("BrickIdle", "OpenWorldBrick.png", 0, 0, 0.1f, true);
	Renderer->CreateAnimation("BrickHit", "OpenWorldBrick.png", 0, 0, 0.1f, true);

	LeftTop = CreateImageRenderer(ERenderOrder::Brick);
	LeftTop->SetImage("OpenWorldBrokenBrick.png");
	LeftTop->SetTransform({ { -16, -44 }, { 32, 32} });

	LeftTop->CreateAnimation("BrokenBrickLeftTop", "OpenWorldBrokenBrick.png", 0, 0, 0.1f, true);

	LeftBottom = CreateImageRenderer(ERenderOrder::Brick);
	LeftBottom->SetImage("OpenWorldBrokenBrick.png");
	LeftBottom->SetTransform({ { -16, -12 }, { 32, 32 } });

	LeftBottom->CreateAnimation("BrokenBrickLeftBottom", "OpenWorldBrokenBrick.png", 2, 2, 0.1f, true);

	RightTop = CreateImageRenderer(ERenderOrder::Brick);
	RightTop->SetImage("OpenWorldBrokenBrick.png");
	RightTop->SetTransform({ { 16, -44 }, { 32, 32 } });

	RightTop->CreateAnimation("BrokenBrickRightTop", "OpenWorldBrokenBrick.png", 1, 1, 0.1f, true);

	RightBottom = CreateImageRenderer(ERenderOrder::Brick);
	RightBottom->SetImage("OpenWorldBrokenBrick.png");
	RightBottom->SetTransform({ { 16, -12 }, { 32, 32 } });

	RightBottom->CreateAnimation("BrokenBrickRightBottom", "OpenWorldBrokenBrick.png", 3, 3, 0.1f, true);
	 
	TopCollision = CreateCollision(ECollisionOrder::BoxTop);
	TopCollision->SetColType(ECollisionType::Rect);
	TopCollision->SetPosition({ 0, -55 });
	TopCollision->SetScale({ 62, 10 });

	BottomCollision = CreateCollision(ECollisionOrder::Box);
	BottomCollision->SetColType(ECollisionType::Rect);
	BottomCollision->SetPosition({ 0, -5 });
	BottomCollision->SetScale({ 50, 10 });

	LeftCollision = CreateCollision(ECollisionOrder::Box);
	LeftCollision->SetColType(ECollisionType::Rect);
	LeftCollision->SetPosition({ -26, -25 });
	LeftCollision->SetScale({ 10, 50 });

	RightCollision = CreateCollision(ECollisionOrder::Box);
	RightCollision->SetColType(ECollisionType::Rect);
	RightCollision->SetPosition({ +26, -25 });
	RightCollision->SetScale({ 10, 50 });

	StateChange(EBoxState::Idle);
}

void ABreakBrick::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> BottomResult;
	if (true == BottomCollision->CollisionCheck(ECollisionOrder::PlayerHead, BottomResult))
	{
		UCollision* MarioPosition = BottomResult[0];
		AMario* Player = (AMario*)MarioPosition->GetOwner();
		MarioState = Player->SizeState;

		if (EBoxState::Idle == State)
		{
			Player->JumpVector = FVector::Zero;
			Player->AddActorLocation(FVector::Down * 10);
  			StateChange(EBoxState::Hit);
			return;
		}
	}

	std::vector<UCollision*> LeftResult;
	if (true == LeftCollision->CollisionCheck(ECollisionOrder::Player, LeftResult))
	{
		UCollision* MarioPosition = LeftResult[0];
		AMario* Player = (AMario*)MarioPosition->GetOwner();

		Player->RunVector.X = 0.0f;
		return;
	}

	std::vector<UCollision*> RightResult;
	if (true == RightCollision->CollisionCheck(ECollisionOrder::Player, RightResult))
	{
		UCollision* MarioPosition = RightResult[0];
		AMario* Player = (AMario*)MarioPosition->GetOwner();

		Player->RunVector.X = 0.0f;
		return;
	}

	StateUpdate(_DeltaTime);
}

void ABreakBrick::StateChange(EBoxState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EBoxState::Idle:
			IdleStart();
			break;
		case EBoxState::Hit:
			HitStart();
			break;
		case EBoxState::Break:
			BreakStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void ABreakBrick::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EBoxState::Idle:
		Idle(_DeltaTime);
		break;
	case EBoxState::Hit:
		Hit(_DeltaTime);
		break;
	case EBoxState::Break:
		Break(_DeltaTime);
		break;
	default:
		break;
	}
}

void ABreakBrick::IdleStart()
{
	LeftTop->ActiveOff();
	LeftBottom->ActiveOff();
	RightTop->ActiveOff();
	RightBottom->ActiveOff();

	MoveUpPos = FVector::Zero;
	MoveDownPos = FVector::Zero;
	Renderer->ChangeAnimation("BrickIdle");
}

void ABreakBrick::HitStart()
{
	FirstPos = GetActorLocation();
	Renderer->ChangeAnimation("BrickHit");
}

void ABreakBrick::BreakStart()
{
	Renderer->ActiveOff();

	TopCollision->ActiveOff();
	BottomCollision->ActiveOff();
	LeftCollision->ActiveOff();
	RightCollision->ActiveOff();

	LeftTop->ActiveOn();
	LeftBottom->ActiveOn();
	RightTop->ActiveOn();
	RightBottom->ActiveOn();

	LeftTop->ChangeAnimation("BrokenBrickLeftTop");
	LeftBottom->ChangeAnimation("BrokenBrickLeftBottom");
	RightTop->ChangeAnimation("BrokenBrickRightTop");
	RightBottom->ChangeAnimation("BrokenBrickRightBottom");
}

void ABreakBrick::Idle(float _DeltaTime)
{
}

void ABreakBrick::Hit(float _DeltaTime)
{
	if (EMarioSizeState::Small != MarioState)
	{
		StateChange(EBoxState::Break);
		return;
	}

	if (abs(MoveUpPos.Y) >= MaxHitUpSize)
	{
		if (abs(MoveDownPos.Y) >= MaxHitUpSize)
		{
			SetActorLocation(FirstPos);
			StateChange(EBoxState::Idle);
			return;
		}
		else
		{
			MoveDownPos += FVector::Down * HitUpSpeed * _DeltaTime;
			AddActorLocation(FVector::Down * HitUpSpeed * _DeltaTime);
		}
	}
	else
	{
		MoveUpPos += FVector::Up * HitUpSpeed * _DeltaTime;
		AddActorLocation(FVector::Up * HitUpSpeed * _DeltaTime);
	}
}

void ABreakBrick::Break(float _DeltaTime)
{
	//Destroy();
}