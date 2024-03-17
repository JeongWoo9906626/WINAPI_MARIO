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
	ABrickBase::BeginPlay();

	Renderer = CreateImageRenderer(ERenderOrder::Brick);
	Renderer->SetImage("OpenWorldBrick.png");
	Renderer->SetTransform({ { 0, 0 }, { 256, 256 } });

	Renderer->CreateAnimation("BrickIdle", "OpenWorldBrick.png", 0, 0, 0.1f, true);
	Renderer->CreateAnimation("BrickHit", "OpenWorldBrick.png", 0, 0, 0.1f, true);
	Renderer->CreateAnimation("Brickbreak", "OpenWorldBrick.png", 2, 2, 0.1f, true);
	Renderer->CreateAnimation("BrickBlock", "OpenWorldBrick.png", 3, 3, 0.1f, true);

	LeftCollision = CreateCollision(ECollisionOrder::Box);
	LeftCollision->SetColType(ECollisionType::Rect);
	LeftCollision->SetPosition({ -28, -28 });
	LeftCollision->SetScale({ 10, 55 });

	RightCollision = CreateCollision(ECollisionOrder::Box);
	RightCollision->SetColType(ECollisionType::Rect);
	RightCollision->SetPosition({ +28, -28 });
	RightCollision->SetScale({ 10, 55 });

	TopCollision = CreateCollision(ECollisionOrder::BoxTop);
	TopCollision->SetColType(ECollisionType::Rect);
	TopCollision->SetPosition({ 0, -60 });
	TopCollision->SetScale({ 64, 10 });

	BottomCollision = CreateCollision(ECollisionOrder::Box);
	BottomCollision->SetColType(ECollisionType::Rect);
	BottomCollision->SetPosition({ 0, -5 });
	BottomCollision->SetScale({ 60, 10 });


	StateChange(EBoxState::Idle);
}

void ABrick::Tick(float _DeltaTime)
{
	ABrickBase::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void ABrick::StateChange(EBoxState _State)
{
	ABrickBase::StateChange(_State);
}

void ABrick::StateUpdate(float _DeltaTime)
{
	ABrickBase::StateUpdate(_DeltaTime);
}

void ABrick::IdleStart()
{
	ABrickBase::IdleStart();

	Renderer->ChangeAnimation("BrickIdle");
}

void ABrick::HitStart()
{
	ABrickBase::HitStart();
	HitCount--;
	ACoin* Coin = GetWorld()->SpawnActor<ACoin>(ERenderOrder::Coin);
	Coin->SetName("Coin");
	Coin->SetActorLocation(GetActorLocation());
	Coin->StateChange(ECoinState::CoinSpawn);

	Renderer->ChangeAnimation("BrickHit");
}

void ABrick::BreakStart()
{
	ABrickBase::BreakStart();

	Renderer->ChangeAnimation("BrickBlock");
}

void ABrick::Idle(float _DeltaTime)
{
	ABrickBase::Idle(_DeltaTime);
}

void ABrick::Hit(float _DeltaTime)
{
	ABrickBase::Hit(_DeltaTime);

	if (0 == HitCount)
	{
		StateChange(EBoxState::Break);
		return;
	}
}
