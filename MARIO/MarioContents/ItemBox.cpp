#include "ItemBox.h"
#include "Mario.h"
#include "Mushroom.h"
#include "Sunflower.h"

AItemBox::AItemBox()
{
}

AItemBox::~AItemBox()
{
}

void AItemBox::BeginPlay()
{
	ABrickBase::BeginPlay();

	Renderer = CreateImageRenderer(ERenderOrder::Brick);
	Renderer->SetImage("OpenWorldBox.png");
	Renderer->SetTransform({ { 0, 0 }, { 256, 256 } });

	Renderer->CreateAnimation("BrickIdle", "OpenWorldBox.png", 0, 3, 0.2f, true);
	Renderer->CreateAnimation("BrickHit", "OpenWorldBox.png", 4, 4, 0.1f, true);
	Renderer->CreateAnimation("BrickBlock", "OpenWorldBox.png", 5, 5, 0.1f, true);

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

void AItemBox::Tick(float _DeltaTime)
{
	ABrickBase::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void AItemBox::StateChange(EBoxState _State)
{
	ABrickBase::StateChange(_State);
}

void AItemBox::StateUpdate(float _DeltaTime)
{
	ABrickBase::StateUpdate(_DeltaTime);
}

void AItemBox::IdleStart()
{
	ABrickBase::IdleStart();

	Renderer->ChangeAnimation("BrickIdle");
}

void AItemBox::HitStart()
{	
	ABrickBase::HitStart();

	Renderer->ChangeAnimation("BrickHit");
}

void AItemBox::BreakStart()
{
	ABrickBase::BreakStart();

	Renderer->ChangeAnimation("BrickBlock");
}

void AItemBox::Idle(float _DeltaTime)
{
	ABrickBase::Idle(_DeltaTime);
}

void AItemBox::Hit(float _DeltaTime)
{
	if (abs(MoveUpPos.Y) >= MaxHitUpSize)
	{
		if (abs(MoveDownPos.Y) >= MaxHitUpSize)
		{
			switch (MarioSizeState)
			{
			case EMarioSizeState::Small:
			{
				AMushroom* Mushroom = GetWorld()->SpawnActor<AMushroom>(ERenderOrder::Item);
				Mushroom->SetName("Mushroom");
				FVector BoxLocation = GetActorLocation();
				Mushroom->SetActorLocation({ BoxLocation.X, BoxLocation.Y - 15.0f });
				break;
			}
			case EMarioSizeState::Big:
			{
				ASunflower* Sunflower = GetWorld()->SpawnActor<ASunflower>(ERenderOrder::Item);
				Sunflower->SetName("Sunflower");
				FVector BoxLocation = GetActorLocation();
				Sunflower->SetActorLocation({ BoxLocation.X, BoxLocation.Y - 15.0f });
				break;
			}
			case EMarioSizeState::Red:
			{
				ASunflower* Sunflower = GetWorld()->SpawnActor<ASunflower>(ERenderOrder::Item);
				Sunflower->SetName("Sunflower");
				FVector BoxLocation = GetActorLocation();
				Sunflower->SetActorLocation({ BoxLocation.X, BoxLocation.Y - 15.0f });
				break;
			}
			case EMarioSizeState::Star:
				break;
			}

			SetActorLocation(FirstPos);
			StateChange(EBoxState::Block);
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