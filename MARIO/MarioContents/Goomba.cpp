#include "Goomba.h"

AGoomba::AGoomba()
{
}

AGoomba::~AGoomba()
{
}

void AGoomba::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(RenderOrder::Monster);
	Renderer->SetImage("Goomba.png");
	Renderer->SetTransform({ { 0, 0 }, { 256, 256 } });

	Renderer->CreateAnimation("GoombaDie", "Goomba.png", 2, 2, true, 0.1f);
	Renderer->CreateAnimation("GoombaMove", "Goomba.png", 0, 1, true, 0.2f);
	
	StateChange(EMonsterState::Move);
}

void AGoomba::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	
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
	DeadValue = false;
	Renderer->ChangeAnimation("GoombaMove");
}

void AGoomba::DeadStart()
{
	DeadValue = true;
	Renderer->ChangeAnimation("GoombaDead");
}

void AGoomba::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EMonsterState::Move:
		Move(_DeltaTime);
		break;
	case EMonsterState::Dead:
		Dead(_DeltaTime);
		break;
	default:
		break;
	}
}

void AGoomba::Move(float _DeltaTime)
{
	FVector ForwardVector = { 1.0f, 0.0f, 0.0f, 0.0f };
	AddActorLocation(ForwardVector * MoveSpeed * _DeltaTime);
}

void AGoomba::Dead(float _DeltaTime)
{
	if (true == DeadValue)
	{
		Destroy(_DeltaTime);
	}
}

