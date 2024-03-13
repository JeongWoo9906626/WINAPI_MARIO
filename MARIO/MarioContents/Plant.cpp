#include "Plant.h"
#include "Mario.h"
#include "MarioFire.h"
#include "ScoreUI.h"

APlant::APlant()
{
}

APlant::~APlant()
{
}

void APlant::BeginPlay()
{
	AMonster::BeginPlay();

	{
		// TODO : 식물이 파이프보다 뒤에서 나와야함
		//		: 파이프 따로 그려 RenderOrder 설정할 것
		Renderer = CreateImageRenderer(ERenderOrder::Monster);
		Renderer->SetImage("Plant.png");
		Renderer->SetTransform({ { 0, 0 }, { 256 * 3.0f, 256 * 3.0f } });
	}

	{
		Renderer->CreateAnimation("PlantIdle", "Plant.png", 0, 1, 0.2f, true);
	}

	{
		Collision = CreateCollision(ECollisionOrder::Goomba);
		Collision->SetColType(ECollisionType::Rect);
		Collision->SetPosition({ 0, -40 });
		Collision->SetScale({ 40, 80 });
	}
	Renderer->ChangeAnimation("PlantIdle");

	StateChange(EMonsterState::Move);
}

void APlant::Tick(float _DeltaTime)
{
	AMonster::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void APlant::StateChange(EMonsterState _State)
{
	AMonster::StateChange(_State);

	switch (_State)
	{
	case EMonsterState::Wait:
		WaitStart();
		break;
	case EMonsterState::Stop:
		StopStart();
		break;
	}

	State = _State;
}

void APlant::StateUpdate(float _DeltaTime)
{
	AMonster::StateUpdate(_DeltaTime);
	switch (State)
	{
	case EMonsterState::Wait:
		Wait(_DeltaTime);
		break;
	}
}

void APlant::MoveStart()
{
	AMonster::MoveStart();
	CurMoveY = 0.0f;
}

void APlant::WaitStart()
{
	CurTime = 0.0f;
}

void APlant::SpinDeadStart()
{
	AMonster::SpinDeadStart();

	Collision->ActiveOff();
	Renderer->SetAlpha(0.5f);
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
		StateChange(EMonsterState::Wait);
		return;
	}

	AddActorLocation(DirVector * MoveSpeed * _DeltaTime);
}

void APlant::Wait(float _DeltaTime)
{
	if (CurTime >= WaitTime)
	{
		IsUp = !IsUp;
		StateChange(EMonsterState::Move);
		return;
	}

	CurTime += _DeltaTime;
}

void APlant::SpinDead(float _DeltaTime)
{
	if (CurDestoryTime >= DestroyTime)
	{
		Destroy();
	}
	else
	{
		CurDestoryTime += _DeltaTime;
	}
}
