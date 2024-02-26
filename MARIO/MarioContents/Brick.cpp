#include "Brick.h"
#include "Mario.h"

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
	Renderer->SetTransform({ { 0, 0 }, { 256 * 4.0f, 256 * 4.0f } });

	Renderer->CreateAnimation("BrickIdle", "OpenWorldBrick.png", 0, 0, 0.1f, true);
	Renderer->CreateAnimation("BrickHit", "OpenWorldBrick.png", 0, 0, 0.1f, true);
	Renderer->CreateAnimation("Brickbreak", "OpenWorldBrick.png", 2, 2, 0.1f, true);
	Renderer->CreateAnimation("BrickBlock", "OpenWorldBrick.png", 3, 3, 0.1f, true);

	BodyCollision = CreateCollision(ECollisionOrder::Box);
	BodyCollision->SetColType(ECollisionType::Rect);
	BodyCollision->SetPosition({ 0, -30 });
	BodyCollision->SetScale({ 65, 70 });

	StateChange(EBoxState::Idle);
}

void ABrick::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> Result;
	if (true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		UCollision* MarioPosition = Result[0];
		AMario* Player = (AMario*)MarioPosition->GetOwner();

		FTransform MarioCollision = MarioPosition->GetActorBaseTransform();
		FTransform MyTransform = BodyCollision->GetActorBaseTransform();

		if (EBoxState::Idle == State)
		{
			if (MarioCollision.GetPosition().Y - 32.0f > MyTransform.GetPosition().Y + 32.0f)
			{
				Player->JumpVector = FVector::Zero;
				StateChange(EBoxState::Hit);
				return;
			}
		}
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
	Renderer->ChangeAnimation("BrickIdle");
}

void ABrick::HitStart()
{
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

	// 박스 위로 이동
	FVector HitUpPos = GetActorLocation();
	if (FirstPos.Y - HitUpPos.Y >= MaxHitUpSize)
	{
		--HitCount;
		SetActorLocation(FirstPos);
		StateChange(EBoxState::Idle);
		return;
	}
	else
	{
		AddActorLocation(FVector::Up * HitUpSpeed * _DeltaTime);
	}


}

void ABrick::Break(float _DeltaTime)
{
}

void ABrick::Block(float _DeltaTime)
{
}
