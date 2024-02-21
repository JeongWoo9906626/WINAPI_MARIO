#include "Plant.h"

APlant::APlant()
{
}

APlant::~APlant()
{
}

void APlant::BeginPlay()
{
	AActor::BeginPlay();

	{
		Renderer = CreateImageRenderer(ERenderOrder::Monster);
		Renderer->SetImage("Plant.png");
		Renderer->SetTransform({ { 0, 0 }, { 256 * 3.0f, 256 * 3.0f } });
	}

	{
		Renderer->CreateAnimation("PlantIdle", "Plant.png", 0, 1, 0.2f, true);
	}

	{
		BodyCollision = CreateCollision(ECollisionOrder::Monster);
		BodyCollision->SetColType(ECollisionType::Rect);
		BodyCollision->SetPosition({ 0, -40 });
		BodyCollision->SetScale({ 40, 80 });
	}
	Renderer->ChangeAnimation("PlantIdle");

	StateChange(EPlantState::Move);
}

void APlant::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void APlant::StateChange(EPlantState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EPlantState::Move:
			MoveStart();
			break;
		case EPlantState::Stop:
			StopStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void APlant::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EPlantState::Move:
		Move(_DeltaTime);
		break;
	case EPlantState::Stop:
		Stop(_DeltaTime);
		break;
	default:
		break;
	}
}

void APlant::MoveStart()
{
	
}

void APlant::StopStart()
{
}

void APlant::Move(float _DeltaTime)
{
	//if (CurMoveY >= MaxMoveY)
	//{
	//	CurMoveY -= MoveSpeed * _DeltaTime;
	//	DirVector = FVector::Down;
	//}
	if (true == IsUp)
	{
		DirVector = FVector::Up;
		if (CurMoveY <= MaxMoveY && CurMoveY >= 0.0f)
		{
			CurMoveY += MoveSpeed * _DeltaTime;
		}
		else
		{
			CurMoveY = MaxMoveY;
			IsUp = false;
		}
	}
	else
	{
		DirVector = FVector::Down;
		if (CurMoveY <= MaxMoveY && CurMoveY >= 0.0f)
		{
			CurMoveY -= MoveSpeed * _DeltaTime;
		}
		else
		{
			CurMoveY = 0.0f;
			IsUp = true;
		}
	}

	AddActorLocation(DirVector * MoveSpeed * _DeltaTime);
}

void APlant::Stop(float _DeltaTime)
{
}
