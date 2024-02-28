#include "Coin.h"
#include "Brick.h"

ACoin::ACoin()
{
}

ACoin::~ACoin()
{
}

void ACoin::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(ERenderOrder::Coin);
	Renderer->SetImage("Coin.png");
	Renderer->SetTransform({ { 0, 0 }, { 64 * 1.5f, 64 * 1.5f } });

	Renderer->CreateAnimation("CoinSpawn", "Coin.png", 0, 3, 0.05f, true);
}

void ACoin::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void ACoin::StateChange(ECoinState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ECoinState::CoinSpawn:
			CoinSpawnStart();
			break;
		case ECoinState::CoinDestroy:
			CoinDestroyStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void ACoin::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ECoinState::CoinSpawn:
		CoinSpawn(_DeltaTime);
		break;
	case ECoinState::CoinDestroy:
		CoinDestroy(_DeltaTime);
		break;
	default:
		break;
	}
}

void ACoin::CoinSpawnStart()
{
	AddActorLocation({ 0.0f, -60.0f });
	Renderer->ChangeAnimation("CoinSpawn");
}

void ACoin::CoinDestroyStart()
{
	Renderer->SetActive(false);
}

void ACoin::CoinSpawn(float _DeltaTime)
{
	if (CurUpTime < MoveTime)
	{
		AddActorLocation(FVector::Up * MoveUpSpeed * _DeltaTime);
		CurUpTime += _DeltaTime;
	}
	else if (CurDownTime < MoveTime)
	{
		AddActorLocation(FVector::Down * MoveUpSpeed * _DeltaTime);
		CurDownTime += _DeltaTime;
	}
	else
	{
		StateChange(ECoinState::CoinDestroy);
		return;
	}
}

void ACoin::CoinDestroy(float _DeltaTime)
{
	Destroy();
}
