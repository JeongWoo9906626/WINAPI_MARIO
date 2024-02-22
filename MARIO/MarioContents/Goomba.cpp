#include "Goomba.h"
#include "Mario.h"

AGoomba::AGoomba()
{
}

AGoomba::~AGoomba()
{
}

void AGoomba::BeginPlay()
{
	AActor::BeginPlay();

	{
		Renderer = CreateImageRenderer(ERenderOrder::Monster);
		Renderer->SetImage("OpenWorldGoomba.png");
		Renderer->SetTransform({ { 0, 0 }, { 256 * 1.3f, 256 * 1.3f } });
	}

	{
		Renderer->CreateAnimation("GoombaDie", "OpenWorldGoomba.png", 2, 2, 0.1f, true);
		Renderer->CreateAnimation("GoombaMove", "OpenWorldGoomba.png", 0, 1, 0.2f, true);
	}

	{
		BodyCollision = CreateCollision(ECollisionOrder::Monster);
		BodyCollision->SetColType(ECollisionType::Rect);
		BodyCollision->SetPosition({ 0, -30 });
		BodyCollision->SetScale({ 40, 40 });
	}

	StateChange(EMonsterState::Move);
}

void AGoomba::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	
	std::vector<UCollision*> Result;
	if (true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		UCollision* MarioPosition = Result[0];
		AMario* Player = (AMario*)MarioPosition->GetOwner();

		FTransform Collision = MarioPosition->GetActorBaseTransform();

		FTransform MyTransform = BodyCollision->GetActorBaseTransform();

		if (Collision.GetPosition().Y + 32.0f < MyTransform.GetPosition().Y)
		{
			Player->StateChange(EPlayState::Kill);
			StateChange(EMonsterState::Dead);
			return;
		}
		else
		{
			Player->StateChange(EPlayState::Die);
			return;
		}
	}

	StateUpdate(_DeltaTime);
}

void AGoomba::StateChange(EMonsterState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EMonsterState::Move:
			MoveStart();
			break;
		case EMonsterState::Dead:
			DeadStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void AGoomba::MoveStart()
{
	DestroyValue = false;
	Renderer->ChangeAnimation("GoombaMove");
}

void AGoomba::DeadStart()
{
	DestroyValue = true;
	Renderer->ChangeAnimation("GoombaDie");
	BodyCollision->ActiveOff();
	Destroy(0.5f);
}

void AGoomba::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EMonsterState::Move:
		Move(_DeltaTime);
		break;
	default:
		break;
	}
}

void AGoomba::Move(float _DeltaTime)
{
	FVector ForwardVector = { 1.0f, 0.0f, 0.0f, 0.0f };
	GravityMove(_DeltaTime);

	FVector CheckPos = GetActorLocation();
	switch (DirState)
	{
	case EActorDir::Left:
		CheckPos.X -= 32.0f;
		break;
	case EActorDir::Right: 
		CheckPos.X += 32.0f;
		break;
	default:
		break;
	}
	CheckPos.Y -= 32.0f;

	Color8Bit Color = UContentsHelper::MapColImage->GetColor(CheckPos.iX(), CheckPos.iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		ChangeDir(DirState);
	}

	if (EActorDir::Left == DirState)
	{
		DirUnitVector = -1.0f;
	}
	else
	{
		DirUnitVector = 1.0f;
	}

	CheckWindowPosition();

	if (true == DestroyValue)
	{
		Destroy();
	}
	
	AddActorLocation(ForwardVector * DirUnitVector * MoveSpeed * _DeltaTime);
}

void AGoomba::GravityMove(float _DeltaTime)
{
	FVector GravityVector = { 0.0f, 1.0f, 0.0f, 0.0f };
	Color8Bit Color = UContentsHelper::MapColImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		GravityVector = FVector::Zero;
	}
	else
	{
		AddActorLocation(GravityVector * GravitySpeed * _DeltaTime);
	}
}

void AGoomba::ChangeDir(EActorDir _State)
{
	if (EActorDir::Left == DirState)
	{
		DirState = EActorDir::Right;
	}
	else
	{
		DirState = EActorDir::Left;
	}
}

void AGoomba::CheckWindowPosition()
{
	FVector CurPosition = GetActorLocation();
	FVector CameraPos = GetWorld()->GetCameraPos();
	if (CameraPos.X >= CurPosition.X)
	{
		DestroyValue = true;
	}
}