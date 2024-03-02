#include "BreakOne.h"

ABreakOne::ABreakOne()
{
}

ABreakOne::~ABreakOne()
{
}

void ABreakOne::BeginPlay()
{
   	AActor::BeginPlay();

	Renderer = CreateImageRenderer(ERenderOrder::Brick);
	Renderer->SetImage("OpenWorldBrokenBrick.png");
	Renderer->SetTransform({ {0,0}, {32, 32} });

	Renderer->CreateAnimation("Spin", "OpenWorldBrokenBrick.png", 0, 0, 0.1f, true);
	
	Renderer->ChangeAnimation("Spin");
}

void ABreakOne::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	int Move = 0;

	switch (BoxPos)
	{
	case 0:
	case 2:
		Move = -1;
		break;
	case 1:
	case 3:
		Move = 1;
		break;
	default:
		break;
	}
	
	if (CurUpTime >= UpTime)
	{
		FVector Up = FVector::Up * 200.0f * _DeltaTime;
		AddActorLocation(Up);
	}
	else
	{
		FVector Down = FVector::Down * 200.0f * _DeltaTime;
		AddActorLocation(Down);
	}

	if (CurMoveTime >= MoveTime)
	{
		FVector MoveX = { (200.0f * Move * _DeltaTime), 0.0f, 0.0f, 0.0f };
		AddActorLocation(MoveX);
	}
	else
	{
		Destroy();
	}
}

void ABreakOne::SetStartLocation(FVector _Position)
{
	Position = _Position;
}

void ABreakOne::SetBoxImage(int _BoxPos)
{
	BoxPos = _BoxPos;
}
