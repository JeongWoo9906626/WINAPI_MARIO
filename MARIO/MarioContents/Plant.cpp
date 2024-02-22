#include "Plant.h"
#include "Mario.h"

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
		// TODO : �Ĺ��� ���������� �ڿ��� ���;���
		//		: ������ ���� �׷� RenderOrder ������ ��
		Renderer = CreateImageRenderer(ERenderOrder::Monster);
		Renderer->SetImage("Plant.png");
		Renderer->SetTransform({ { 0, 0 }, { 256 * 3.0f, 256 * 3.0f } });
	}

	{
		Renderer->CreateAnimation("PlantIdle", "Plant.png", 0, 1, 0.2f, true);
	}

	{
		BodyCollision = CreateCollision(ECollisionOrder::Goomba);
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

	std::vector<UCollision*> Result;
	if (true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		UCollision* MarioPosition = Result[0];
		AMario* Player = (AMario*)MarioPosition->GetOwner();
		Player->StateChange(EPlayState::Die);
		return;
	}

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
		case EPlantState::Wait:
			WaitStart();
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
	case EPlantState::Wait:
		Wait(_DeltaTime);
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
	CurMoveY = 0.0f;
}

void APlant::WaitStart()
{
	CurTime = 0.0f;
}

void APlant::StopStart()
{
}

void APlant::Move(float _DeltaTime)
{
	if (true == IsUp)
	{
		DirVector = FVector::Up;
	}
	else
	{
		DirVector = FVector::Down;
	}

	if (CurMoveY <= MaxMoveY && CurMoveY >= 0.0f)
	{
		CurMoveY += MoveSpeed * _DeltaTime;
	}
	else
	{
		StateChange(EPlantState::Wait);
		return;
	}

	AddActorLocation(DirVector * MoveSpeed * _DeltaTime);
}

void APlant::Wait(float _DeltaTime)
{
	if (CurTime >= WaitTime)
	{
		IsUp = !IsUp;
		StateChange(EPlantState::Move);
		return;
	}
	CurTime += _DeltaTime;
}

void APlant::Stop(float _DeltaTime)
{
}
