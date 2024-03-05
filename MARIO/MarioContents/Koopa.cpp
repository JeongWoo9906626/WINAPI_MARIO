#include "Koopa.h"
#include "Mario.h"

AKoopa::AKoopa()
{
}

AKoopa::~AKoopa()
{
}

void AKoopa::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(ERenderOrder::Monster);
	Renderer->SetImage("Koopa_Left.png");
	Renderer->SetTransform({ {0, 0}, {256 * 2.0f, 256 * 2.0f} });

	Renderer->CreateAnimation("Walk_Left", "Koopa_Left.png", 0, 3, 0.1f, true);
	Renderer->CreateAnimation("Walk_Right", "Koopa_Right.png", 0, 3, 0.1f, true);

	Collision = CreateCollision(ECollisionOrder::Goomba);
	Collision->SetColType(ECollisionType::Rect);
	Collision->SetPosition({ -30, -70 });
	Collision->SetScale({ 140, 140 });

	Renderer->ChangeAnimation("Walk_Left");

	StateChange(EKoopaState::Walk);
}

void AKoopa::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void AKoopa::StateChange(EKoopaState _State)
{
	switch (_State)
	{
	case EKoopaState::Walk:
		WalkStart();
		break;
	case EKoopaState::Jump:
		JumpStart();
		break;
	case EKoopaState::Dead:
		DeadStart();
		break;
	default:
		break;
	}

	State = _State;
}

void AKoopa::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EKoopaState::Walk:
		Walk(_DeltaTime);
		break;
	case EKoopaState::Jump:
		Jump(_DeltaTime);
		break;
	case EKoopaState::Dead:
		Dead(_DeltaTime);
		break;
	default:
		break;
	}
}

void AKoopa::DirCheck()
{
	FVector MarioPos = AMario::MainPlayer->GetActorLocation();
	FVector MyPos = GetActorLocation();
	
	EActorDir Curdir = DirState;

	if (MarioPos.X > MyPos.X)
	{
		DirState = EActorDir::Right;
	}
	else
	{
		DirState = EActorDir::Left;
	}

	if (Curdir != DirState)
	{
		Renderer->ChangeAnimation(GetAnimationName());
	}
}

void AKoopa::WalkStart()
{
	DirCheck();
	Renderer->ChangeAnimation(GetAnimationName());
}

void AKoopa::JumpStart()
{
	JumpVector.Y += JumpSpeed;
}

void AKoopa::DeadStart()
{
}

void AKoopa::Walk(float _DeltaTime)
{
	DirCheck();

	switch (DirState)
	{
	case EActorDir::Left:
		Dir = -1;
		break;
	case EActorDir::Right:
		Dir = 1;
		break;
	}

	AddActorLocation({ Dir * WalkSpeed * _DeltaTime, 0.0f });
}

void AKoopa::Dead(float _DeltaTime)
{
}

void AKoopa::Jump(float _DeltaTime)
{
}

std::string AKoopa::GetAnimationName()
{
	std::string AnimationName = "";
	switch (DirState)
	{
	case EActorDir::Left:
		AnimationName = "Walk_Left";
		break;
	case EActorDir::Right:
		AnimationName = "Walk_Right";
		break;
	}

	return AnimationName;
}

