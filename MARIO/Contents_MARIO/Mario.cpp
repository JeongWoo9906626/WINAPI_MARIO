#include "Mario.h"

#include <EnginePlatform\EngineInput.h>
#include <EngineBase\EngineDebug.h>

#include "ContentsHelper.h"
#include "BackGround.h"

AMario::AMario()
{
}

AMario::~AMario()
{
}

void AMario::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(RenderOrder::Player);
	Renderer->SetImage("Mario_Right.png");
	Renderer->SetTransform({ {0,0}, {256, 256} });

	Renderer->CreateAnimation("Idle_Right", "Mario_Right.png", 0, 0, 0.1f, true);
	Renderer->CreateAnimation("Move_Right", "Mario_Right.png", 1, 3, 0.1f, true);
	Renderer->CreateAnimation("Jump_Right", "Mario_Right.png", 5, 5, 0.1f, true);

	Renderer->CreateAnimation("Idle_Left", "Mario_Left.png", 0, 0, 0.1f, true);
	Renderer->CreateAnimation("Move_Left", "Mario_Left.png", 1, 3, 0.1f, true);
	Renderer->CreateAnimation("Jump_Left", "Mario_Left.png", 5, 5, 0.1f, true);

	StateChange(EPlayState::Idle);
}

void AMario::GravityCheck(float _DeltaTime)
{
	Color8Bit Color = UContentsHelper::MapColImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color != Color8Bit(255, 0, 255, 0))
	{
		AddActorLocation(FVector::Down * _DeltaTime * Gravity);
	}
}

void AMario::DirCheck()
{
	EActorDir Dir = DirState;
	if (EngineInput::IsPress(VK_LEFT))
	{
		Dir = EActorDir::Left;
	}
	if (EngineInput::IsPress(VK_RIGHT))
	{
		Dir = EActorDir::Right;
	}

	if (Dir != DirState)
	{
		DirState = Dir;
		std::string Name = GetAnimationName(CurAnimationName);
		Renderer->ChangeAnimation(Name);
	}
}

std::string AMario::GetAnimationName(std::string _Name)
{
	std::string DirName = "";

	switch (DirState)
	{
	case EActorDir::Left:
		DirName = "_Left";
		break;
	case EActorDir::Right:
		DirName = "_Right";
		break;
	default:
		break;
	}

	CurAnimationName = _Name;

	return _Name + DirName;
}

void AMario::IdleStart()
{
	Renderer->ChangeAnimation(GetAnimationName("Idle"));
	DirCheck();
}

void AMario::MoveStart()
{
	Renderer->ChangeAnimation(GetAnimationName("Move"));
	DirCheck();
}

void AMario::JumpStart()
{
	Renderer->ChangeAnimation(GetAnimationName("Jump"));
	DirCheck();
}

void AMario::StateChange(EPlayState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EPlayState::Idle:
			IdleStart();
			break;
		case EPlayState::Move:
			MoveStart();
			break;
		case EPlayState::Jump:
			JumpStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void AMario::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EPlayState::CameraFreeMove:
		CameraFreeMove(_DeltaTime);
		break;
	case EPlayState::FreeMove:
		FreeMove(_DeltaTime);
		break;
	case EPlayState::Idle:
		Idle(_DeltaTime);
		break;
	case EPlayState::Move:
		Move(_DeltaTime);
		break;
	case EPlayState::Jump:
		Jump(_DeltaTime);
		break;
	default:
		break;
	}
}

void AMario::CameraFreeMove(float _DeltaTime)
{
	if (EngineInput::IsPress(VK_LEFT))
	{
		GetWorld()->AddCameraPos(FVector::Left * _DeltaTime * FreeMoveSpeed);
		// AddActorLocation(FVector::Left * _DeltaTime * 500.0f);
	}

	if (EngineInput::IsPress(VK_RIGHT))
	{
		GetWorld()->AddCameraPos(FVector::Right * _DeltaTime * FreeMoveSpeed);
	}

	if (EngineInput::IsPress(VK_UP))
	{
		GetWorld()->AddCameraPos(FVector::Up * _DeltaTime * FreeMoveSpeed);
		// AddActorLocation(FVector::Up * _DeltaTime * 500.0f);
	}

	if (EngineInput::IsPress(VK_DOWN))
	{
		GetWorld()->AddCameraPos(FVector::Down * _DeltaTime * FreeMoveSpeed);
		// AddActorLocation(FVector::Down * _DeltaTime * 500.0f);
	}

	if (EngineInput::IsDown('2'))
	{
		StateChange(EPlayState::Idle);
	}
}

void AMario::FreeMove(float _DeltaTime)
{
	FVector MovePos;

	if (EngineInput::IsPress(VK_LEFT))
	{
		MovePos += FVector::Left * _DeltaTime * FreeMoveSpeed;
	}

	if (EngineInput::IsPress(VK_RIGHT))
	{
		MovePos += FVector::Right * _DeltaTime * FreeMoveSpeed;
	}

	if (EngineInput::IsPress(VK_UP))
	{
		MovePos += FVector::Up * _DeltaTime * FreeMoveSpeed;
	}

	if (EngineInput::IsPress(VK_DOWN))
	{
		MovePos += FVector::Down * _DeltaTime * FreeMoveSpeed;
	}

	AddActorLocation(MovePos);
	GetWorld()->AddCameraPos(MovePos);

	if (EngineInput::IsDown('1'))
	{
		StateChange(EPlayState::Idle);
	}
}

void AMario::Idle(float _DeltaTime)
{
	if (true == EngineInput::IsDown('1'))
	{
		StateChange(EPlayState::FreeMove);
		return;
	}

	if (true == EngineInput::IsDown('2'))
	{
		StateChange(EPlayState::CameraFreeMove);
		return;
	}

	

	if (
		true == EngineInput::IsPress(VK_LEFT) ||
		true == EngineInput::IsPress(VK_RIGHT)
		)
	{
		StateChange(EPlayState::Move);
		return;
	}

	if (
		true == EngineInput::IsDown(VK_SPACE)
		)
	{
		/*if (true == EngineInput::IsPress(VK_SPACE))
		{

		}*/
		StateChange(EPlayState::Jump);
		return;
	}
	GravityCheck(_DeltaTime);
}
void AMario::Jump(float _DeltaTime)
{
	DirCheck();
	FVector MovePos = FVector::Up * _DeltaTime * /*JumpSpeed*/500.0f;
	AddActorLocation(MovePos);

	if (true == EngineInput::IsFree(VK_SPACE))
	{
		StateChange(EPlayState::Idle);
		return;
	}
}
void AMario::Move(float _DeltaTime)
{
	DirCheck();
	GravityCheck(_DeltaTime);

	if (true == EngineInput::IsFree(VK_LEFT) && EngineInput::IsFree(VK_RIGHT))
	{
		StateChange(EPlayState::Idle);
		return;
	}

	if (true == EngineInput::IsPress(VK_LSHIFT))
	{
		MoveSpeed = 1000.0f;
	}

	if (true == EngineInput::IsFree(VK_LSHIFT))
	{
		MoveSpeed = 300.0f;
	}

	if (true == EngineInput::IsDown(VK_SPACE))
	{
		StateChange(EPlayState::Jump);
		return;
	}

	FVector MovePos = FVector::Zero;
	if (EngineInput::IsPress(VK_LEFT))
	{
		MovePos += FVector::Left * _DeltaTime * MoveSpeed;
	}

	if (EngineInput::IsPress(VK_RIGHT))
	{
		MovePos += FVector::Right * _DeltaTime * MoveSpeed;
	}

	FVector CheckPos = GetActorLocation();
	switch (DirState)
	{
	case EActorDir::Left:
		CheckPos.X -= 30;
		break;
	case EActorDir::Right:
		CheckPos.X += 30;
		break;
	default:
		break;
	}
	CheckPos.Y -= 30;
	Color8Bit Color = UContentsHelper::MapColImage->GetColor(CheckPos.iX(), CheckPos.iY(), Color8Bit::MagentaA);
	if (Color != Color8Bit(255, 0, 255, 0))
	{
		// 현재 카메라의 위치(맵에서의 위치)
		FVector CamerPos = GetWorld()->GetCameraPos();
		// 화면이 랜더링 되고 있는 곳에서 왼쪽으로 갈 수 없게 하는 것
		if (CamerPos.X >= CheckPos.X)
		{
			return;
		}
		
		AddActorLocation(MovePos);
		
		FVector NextCamerPos = CamerPos + MovePos;
		// 0보다 작은 곳까지 이동 안하게 하는 것
		if (0 >= NextCamerPos.X)
		{
			return;
		}
		// 화면이 맵의 마지막 부분까지 출력했으면 더 이상 카메라 이동 안하게 하는 것
		if (/*백그라운드 이미지의 X 크기*/13504.0f <= (CamerPos.X + GEngine->MainWindow.GetWindowScale().X))
		{
			return;
		}
		// 화면 이동이 캐릭터가 중간에 오면 이동하는 것
		if (GEngine->MainWindow.GetWindowScale().Half2D().X + CamerPos.X <= GetActorLocation().X)
		{
			GetWorld()->AddCameraPos(MovePos);
		}
	}
}


void AMario::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	
	if (EngineInput::IsAnyKeyDown())
	{
		int a = 0;
	}

	if (EngineInput::IsAnyKeyUp())
	{
		int a = 0;
	}

	StateUpdate(_DeltaTime);
}
