#include "Brick.h"
#include "Mario.h"
#include "Coin.h"

ABrick::ABrick()
{
}

ABrick::~ABrick()
{
}

void ABrick::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(ERenderOrder::Brick);
	Renderer->SetImage("OpenWorldBrick.png");
	Renderer->SetTransform({ { 0, 0 }, { 256 * 3.8f, 256 * 3.8f } });

	Renderer->CreateAnimation("BrickIdle", "OpenWorldBrick.png", 0, 0, 0.1f, true);
	Renderer->CreateAnimation("BrickHit", "OpenWorldBrick.png", 0, 0, 0.1f, true);
	Renderer->CreateAnimation("Brickbreak", "OpenWorldBrick.png", 2, 2, 0.1f, true);
	Renderer->CreateAnimation("BrickBlock", "OpenWorldBrick.png", 3, 3, 0.1f, true);

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

void ABrick::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> BottomResult;
	if (true == BottomCollision->CollisionCheck(ECollisionOrder::PlayerHead, BottomResult))
	{
		UCollision* MarioPosition = BottomResult[0];
		AMario* Player = (AMario*)MarioPosition->GetOwner();

		if (EBoxState::Idle == State)
		{
			Player->JumpVector = FVector::Zero;
			StateChange(EBoxState::Hit);
			return;
		}
		if (EBoxState::Block == State)
		{
			Player->JumpVector = FVector::Zero;
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

void ABrick::SetHitCount(int _HitCount)
{
	HitCount = _HitCount;
}

void ABrick::SetIsBreak(bool _IsBreak)
{
	IsBreak = _IsBreak;
}

void ABrick::StateChange(EBoxState _State)
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
		case EBoxState::Block:
			BlockStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}

void ABrick::StateUpdate(float _DeltaTime)
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
	case EBoxState::Block:
		Block(_DeltaTime);
		break;
	default:
		break;
	}
}

void ABrick::IdleStart()
{
	MoveUpPos = FVector::Zero;
	MoveDownPos = FVector::Zero;
	Renderer->ChangeAnimation("BrickIdle");
}

void ABrick::HitStart()
{
	ACoin* Coin = GetWorld()->SpawnActor<ACoin>(ERenderOrder::Coin);
	Coin->SetName("Coin");
	Coin->SetActorLocation(GetActorLocation());
	Coin->StateChange(ECoinState::CoinSpawn);

	FirstPos = GetActorLocation();
	Renderer->ChangeAnimation("BrickHit");
}

void ABrick::BreakStart()
{
	Renderer->ChangeAnimation("BrickBreak");
}

void ABrick::BlockStart()
{
	Renderer->ChangeAnimation("BrickBlock");
}

void ABrick::Idle(float _DeltaTime)
{
}

void ABrick::Hit(float _DeltaTime)
{
	if (true == IsBreak && (MarioState == EMArioSizeState::Big || MarioState == EMArioSizeState::Red))
	{
		StateChange(EBoxState::Break);
		return;
	}

	if (0 == HitCount && false == IsBreak)
	{
		StateChange(EBoxState::Block);
		return;
	}

	if (abs(MoveUpPos.Y) >= MaxHitUpSize)
	{
		if (abs(MoveDownPos.Y) >= MaxHitUpSize)
		{
			--HitCount;
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

void ABrick::Break(float _DeltaTime)
{
}

void ABrick::Block(float _DeltaTime)
{
}
