#include "BreakBrick.h"
#include "Mario.h"
#include "BreakOne.h"

ABreakBrick::ABreakBrick()
{
}

ABreakBrick::~ABreakBrick()
{
	ABreakOne* LeftTop = GetWorld()->SpawnActor<ABreakOne>(ERenderOrder::BreakOne);
	LeftTop->SetActorLocation(GetActorLocation() + (FVector::Up * 40.0f) + (FVector::Left * 20.0f));
	LeftTop->SetName("Left");

	ABreakOne* LeftBottom = GetWorld()->SpawnActor<ABreakOne>(ERenderOrder::BreakOne);
	LeftBottom->SetActorLocation(GetActorLocation()/* + (FVector::Down * 20.0f)*/ + (FVector::Left * 20.0f));
	LeftBottom->SetName("Left");

	ABreakOne* RightTop = GetWorld()->SpawnActor<ABreakOne>(ERenderOrder::BreakOne);
	RightTop->SetActorLocation(GetActorLocation() + (FVector::Up * 40.0f) + (FVector::Right * 20.0f));
	RightTop->SetName("Right");
	
	ABreakOne* RightBottom = GetWorld()->SpawnActor<ABreakOne>(ERenderOrder::BreakOne);
	RightBottom->SetActorLocation(GetActorLocation()/* + (FVector::Down * 20.0f)*/ + (FVector::Right * 20.0f));
	RightBottom->SetName("Right");
}

void ABreakBrick::BeginPlay()
{
	ABrickBase::BeginPlay();

	Renderer = CreateImageRenderer(ERenderOrder::Brick);
	Renderer->SetImage("OpenWorldBrick.png");
	Renderer->SetTransform({ { 0, 0 }, { 256, 256 } });

	Renderer->CreateAnimation("BrickIdle", "OpenWorldBrick.png", 0, 0, 0.1f, true);
	Renderer->CreateAnimation("BrickHit", "OpenWorldBrick.png", 0, 0, 0.1f, true);

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

void ABreakBrick::Tick(float _DeltaTime)
{
	ABrickBase::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void ABreakBrick::StateChange(EBoxState _State)
{
	ABrickBase::StateChange(_State);
}

void ABreakBrick::StateUpdate(float _DeltaTime)
{
	ABrickBase::StateUpdate(_DeltaTime);
}

void ABreakBrick::IdleStart()
{
	ABrickBase::IdleStart();

	Renderer->ChangeAnimation("BrickIdle");
}

void ABreakBrick::HitStart()
{
	ABrickBase::HitStart();

	Renderer->ChangeAnimation("BrickHit");
}

void ABreakBrick::BreakStart()
{
	ABrickBase::BreakStart();

	SoundPlayer = UEngineSound::SoundPlay("BrickBreak.wav");
	Renderer->ActiveOff();

	TopCollision->ActiveOff();
	BottomCollision->ActiveOff();
	LeftCollision->ActiveOff();
	RightCollision->ActiveOff();
}

void ABreakBrick::Idle(float _DeltaTime)
{
	ABrickBase::Idle(_DeltaTime);
}

void ABreakBrick::Hit(float _DeltaTime)
{
	ABrickBase::Hit(_DeltaTime);

	if (EMarioSizeState::Small != MarioSizeState)
	{
		StateChange(EBoxState::Break);
		return;
	}
}

void ABreakBrick::Break(float _DeltaTime)
{
	ABrickBase::Break(_DeltaTime);

	Destroy();
}