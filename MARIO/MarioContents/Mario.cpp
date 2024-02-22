#include "Mario.h"

#include <EnginePlatform\EngineInput.h>
#include <EngineBase\EngineDebug.h>

#include "ContentsHelper.h"
#include "Goomba.h"
#include "Troopa.h"
#include "Plant.h"

AMario::AMario()
{
}

AMario::~AMario()
{
}

void AMario::BeginPlay()
{
	AActor::BeginPlay();

	{
		Renderer = CreateImageRenderer(ERenderOrder::Player);
		Renderer->SetImage("Mario_Right.png");
		Renderer->SetTransform({ { 0, 0 }, { 256, 256 } });
	}

	{
		Renderer->CreateAnimation("Idle_Right", "Mario_Right.png", 0, 0, 0.1f, true);
		Renderer->CreateAnimation("Move_Right", "Mario_Right.png", 1, 3, 0.1f, true);
		Renderer->CreateAnimation("Reverse_Right", "Mario_Right.png", 4, 4, 0.1f, true);
		Renderer->CreateAnimation("Jump_Right", "Mario_Right.png", 5, 5, 0.1f, true);
	
		Renderer->CreateAnimation("Idle_Left", "Mario_Left.png", 0, 0, 0.1f, true);
		Renderer->CreateAnimation("Move_Left", "Mario_Left.png", 1, 3, 0.1f, true);
		Renderer->CreateAnimation("Reverse_Left", "Mario_Left.png", 4, 4, 0.1f, true);
		Renderer->CreateAnimation("Jump_Left", "Mario_Left.png", 5, 5, 0.1f, true);

		Renderer->CreateAnimation("Die", "Mario_Left.png", 6, 6, 0.1f, true);
	}

	{
		BodyCollision = CreateCollision(ECollisionOrder::Player);
		BodyCollision->SetColType(ECollisionType::Rect);
		BodyCollision->SetPosition({ 0, -35 });
		BodyCollision->SetScale({ 50, 65 });
	}

	StateChange(EPlayState::Idle);
}

void AMario::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	//std::vector<UCollision*> Result;
	//if (true == BodyCollision->CollisionCheck(ECollisionOrder::Monster, Result))
	//{
	//	for (size_t i = 0; i < Result.size(); i++)
	//	{
	//		UCollision* MonsterCollision = Result[i];
	//		FTransform MonsterTransform = MonsterCollision->GetActorBaseTransform();
	//		FTransform MyTransform = BodyCollision->GetActorBaseTransform();

	//		int a = 0;

	//		// ������ �Ӹ� y��ǥ > �������� �ٴ� y��ǥ
	//		/*if 
	//			(
	//				   MonsterTransform.GetPosition().Y - 32.0f < MyTransform.GetPosition().Y + 32.0f 
	//				&& MonsterTransform.GetPosition().Y > MyTransform.GetPosition().Y + 32.0f
	//			)
	//		{
	//			StateChange(EPlayState::Kill);
	//			return;
	//		}
	//		else
	//		{
	//			StateChange(EPlayState::Die);
	//			return;
	//		}*/
	//	}
	//}

	StateUpdate(_DeltaTime);
}

void AMario::DirCheck()
{
	EActorDir Dir = DirState;

	if (UEngineInput::IsPress(VK_LEFT) && UEngineInput::IsPress(VK_RIGHT))
	{
		AnimationCheck(Dir);
		return;
	}

	if (UEngineInput::IsPress(VK_LEFT))
	{
		Dir = EActorDir::Left;
		AnimationCheck(Dir);
		return;
	}
	if (UEngineInput::IsPress(VK_RIGHT))
	{
		Dir = EActorDir::Right;
		AnimationCheck(Dir);
		return;
	}
}

void AMario::AnimationCheck(EActorDir _Dir)
{
	if (_Dir != DirState)
	{
		DirState = _Dir;
		std::string Name = GetAnimationName(CurAnimationName);
		Renderer->ChangeAnimation(Name, true, Renderer->GetCurAnimationFrame(), Renderer->GetCurAnimationTime());
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

std::string AMario::GetReverseAnimationName(std::string _Name)
{
	std::string DirName = "";

	switch (DirState)
	{
	case EActorDir::Left:
		DirName = "_Right";
		break;
	case EActorDir::Right:
		DirName = "_Left";
		break;
	default:
		break;
	}

	CurAnimationName = _Name;

	return _Name + DirName;
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
		case EPlayState::Run:
			RunStart();
			break;
		case EPlayState::Jump:
			JumpStart();
			break;
		case EPlayState::Reverse:
			ReverseStart();
			break;
		case EPlayState::Die:
			DieStart();
			break;
		case EPlayState::Kill:
			KillStart();
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
	case EPlayState::Run:
		Run(_DeltaTime);
		break;
	case EPlayState::Jump:
		Jump(_DeltaTime);
		break;
	case EPlayState::Reverse:
		Reverse(_DeltaTime);
		break;
	case EPlayState::Die:
		Die(_DeltaTime);
		break;
	case EPlayState::Kill:
		Kill(_DeltaTime);
		break;
	default:
		break;
	}
}

void AMario::CameraFreeMove(float _DeltaTime)
{
	if (UEngineInput::IsPress(VK_LEFT))
	{
		GetWorld()->AddCameraPos(FVector::Left * _DeltaTime * 500.0f);
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		GetWorld()->AddCameraPos(FVector::Right * _DeltaTime * 500.0f);
	}

	if (UEngineInput::IsPress(VK_UP))
	{
		GetWorld()->AddCameraPos(FVector::Up * _DeltaTime * 500.0f);
	}

	if (UEngineInput::IsPress(VK_DOWN))
	{
		GetWorld()->AddCameraPos(FVector::Down * _DeltaTime * 500.0f);
	}

	if (UEngineInput::IsDown('2'))
	{
		StateChange(EPlayState::Idle);
	}
}

void AMario::FreeMove(float _DeltaTime)
{
	FVector CameraMovePos;
	if (UEngineInput::IsPress(VK_LEFT))
	{
		CameraMovePos += FVector::Left * _DeltaTime * FreeMoveSpeed;
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		CameraMovePos += FVector::Right * _DeltaTime * FreeMoveSpeed;
	}

	if (UEngineInput::IsPress(VK_UP))
	{
		CameraMovePos += FVector::Up * _DeltaTime * FreeMoveSpeed;
	}

	if (UEngineInput::IsPress(VK_DOWN))
	{
		CameraMovePos += FVector::Down * _DeltaTime * FreeMoveSpeed;
	}

	AddActorLocation(CameraMovePos);
	GetWorld()->AddCameraPos(CameraMovePos);

	if (UEngineInput::IsDown('1'))
	{
		StateChange(EPlayState::Idle);
	}
}

void AMario::IdleStart()
{
	DirCheck();
	Renderer->ChangeAnimation(GetAnimationName("Idle"));
}

void AMario::RunStart()
{
	DirCheck();
	Renderer->ChangeAnimation(GetAnimationName("Move"));
}

void AMario::JumpStart()
{
	DirCheck();
	JumpVector = JumpPower;
	Renderer->ChangeAnimation(GetAnimationName("Jump"));
}

void AMario::ReverseStart()
{
	Renderer->ChangeAnimation(GetReverseAnimationName("Reverse"));
}

void AMario::DieStart()
{
	JumpVector = DieJumpVector;
	BodyCollision->ActiveOff();
	Renderer->ChangeAnimation("Die");
}

void AMario::KillStart()
{
	DirCheck();
	GravityVector = FVector::Zero;
	JumpVector = DieJumpVector;
	Renderer->ChangeAnimation(GetAnimationName("Jump"));
}

void AMario::Idle(float _DeltaTime)
{
	if (true == UEngineInput::IsDown('1'))
	{
		StateChange(EPlayState::FreeMove);
		return;
	}

	if (true == UEngineInput::IsDown('2'))
	{
		StateChange(EPlayState::CameraFreeMove);
		return;
	}

	if (true == UEngineInput::IsPress(VK_LEFT) && true == UEngineInput::IsPress(VK_RIGHT))
	{
		return;
	}

	if (true == UEngineInput::IsPress(VK_LEFT) || true == UEngineInput::IsPress(VK_RIGHT))
	{
		StateChange(EPlayState::Run);
		return;
	}

	if (true == UEngineInput::IsDown(VK_SPACE))
	{
		StateChange(EPlayState::Jump);
		return;
	}

	MoveUpdate(_DeltaTime);
}

void AMario::Run(float _DeltaTime)
{
	if (true == UEngineInput::IsDown(VK_SPACE))
	{
		StateChange(EPlayState::Jump);
		return;
	}

	if (true == UEngineInput::IsFree(VK_LEFT) && true == UEngineInput::IsFree(VK_RIGHT))
	{
		if (abs(RunVector.X) <= 5.0f)
		{
			RunVector.X = 0.0f;
			StateChange(EPlayState::Idle);
			return;
		}
		else
		{
			MoveUpdate(_DeltaTime);
			return;
		}
	}

	if (true == UEngineInput::IsPress(VK_LEFT) && true == UEngineInput::IsPress(VK_RIGHT))
	{
		if (abs(RunVector.X) <= 10.0f)
		{
			RunVector.X = 0.0f;
			StateChange(EPlayState::Idle);
			return;
		}
		else
		{
			FVector BreakDirState = FVector::Zero;
			switch (DirState)
			{
			case EActorDir::Left:
				BreakDirState = FVector::Right;
				break;
			case EActorDir::Right:
				BreakDirState = FVector::Left;
				break;
			default:
				break;
			}
			SubtractVector(BreakDirState * _DeltaTime);
			MoveUpdate(_DeltaTime);
			return;
		}
	}

	if (true == UEngineInput::IsPress(VK_LSHIFT))
	{
		MaxRunSpeed = ShiftRunSpeed;
		JumpPower = RunJumpPower;
	}
	if (true == UEngineInput::IsFree(VK_LSHIFT))
	{
		MaxRunSpeed = NoramlRunSpeed;
		JumpPower = NoramlJumpPower;
	}

	if (true == UEngineInput::IsPress(VK_LEFT))
	{
		if (RunVector.X > 0.0f)
		{
			StateChange(EPlayState::Reverse);
			return;
		}

		AddVector(FVector::Left * _DeltaTime);
		MoveUpdate(_DeltaTime);

		return;
	}

	if (true == UEngineInput::IsPress(VK_RIGHT))
	{
		if (RunVector.X < 0.0f)
		{
			StateChange(EPlayState::Reverse);
			return;
		}

		AddVector(FVector::Right * _DeltaTime);
		MoveUpdate(_DeltaTime);

		return;
	}
}

void AMario::Jump(float _DeltaTime)
{
	if (UEngineInput::IsPress(VK_LEFT))
	{
		AddVector(FVector::Left * _DeltaTime);
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		AddVector(FVector::Right * _DeltaTime);
	}

	MoveUpdate(_DeltaTime);

	Color8Bit Color = UContentsHelper::MapColImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		JumpVector = FVector::Zero;
		StateChange(EPlayState::Idle);
		return;
	}
}

void AMario::Reverse(float _DeltaTime)
{
	if (true == UEngineInput::IsDown(VK_SPACE))
	{
		StateChange(EPlayState::Jump);
		return;
	}

	if (DirState == EActorDir::Left)
	{
		if (true == UEngineInput::IsDown(VK_LEFT))
		{
			StateChange(EPlayState::Run);
			return;
		}

		if (true == UEngineInput::IsPress(VK_RIGHT))
		{
			SubtractVector(FVector::Right * _DeltaTime);
		}

		if (0.0f <= RunVector.X)
		{
			RunVector.X = 0.0f;
			ReverseDir();
			StateChange(EPlayState::Idle);
			return;
		}
	}

	if (DirState == EActorDir::Right)
	{
		if (true == UEngineInput::IsDown(VK_RIGHT))
		{
			StateChange(EPlayState::Run);
			return;
		}

		if (true == UEngineInput::IsPress(VK_LEFT))
		{
			SubtractVector(FVector::Left * _DeltaTime);
		}

		if (0.0f >= RunVector.X)
		{
			RunVector.X = 0.0f;
			ReverseDir();
			StateChange(EPlayState::Idle);
			return;
		}
	}
	MoveUpdate(_DeltaTime);
}

void AMario::Die(float _DeltaTime)
{
	AddActorLocation(JumpVector * _DeltaTime);
	JumpVector += GravityAcc * _DeltaTime;
}

void AMario::Kill(float _DeltaTime)
{
	MoveUpdate(_DeltaTime);
	State = EPlayState::Jump;
	Color8Bit Color = UContentsHelper::MapColImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		JumpVector = FVector::Zero;
		StateChange(EPlayState::Idle);
		return;
	}
}

void AMario::ReverseDir()
{
	if (EActorDir::Left == DirState)
	{
		DirState = EActorDir::Right;
	}
	else
	{
		DirState = EActorDir::Left;
	}
}

void AMario::AddVector(const FVector& _DirDelta)
{
	RunVector += _DirDelta * RunAcc;
}

void AMario::SubtractVector(const FVector& _DirDelta)
{
	RunVector += _DirDelta * CurBreakSpeed;
}

void AMario::RunVectorUpdate(float _DeltaTime)
{
	FVector CheckPos = GetActorLocation();
	switch (DirState)
	{
	case EActorDir::Left:
		CheckPos.X -= 32.0f;
		break;
	case EActorDir::Right:
		CheckPos.X += 32.0f;
		break;
	default:
		break;
	}
	CheckPos.Y -= 32.0f;

	Color8Bit Color = UContentsHelper::MapColImage->GetColor(CheckPos.iX(), CheckPos.iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		RunVector = FVector::Zero;
	}

	if (true == UEngineInput::IsFree(VK_LEFT) && true == UEngineInput::IsFree(VK_RIGHT))
	{
		if (0.001 <= RunVector.Size2D())
		{
			RunVector += (-RunVector.Normalize2DReturn()) * _DeltaTime * CurBreakSpeed * 5;
		}
		else
		{
			RunVector = FVector::Zero;
		}
	}

	if (MaxRunSpeed <= RunVector.Size2D())
	{
		RunVector = RunVector.Normalize2DReturn() * MaxRunSpeed;
	}

	float CamerPos = GetWorld()->GetCameraPos().X;

	if (CheckPos.X <= CamerPos)
	{
		RunVector = FVector::Zero;
	}
}

void AMario::JumpVectorUpdate(float _DeltaTime)
{
}

void AMario::GravityVectorUpdate(float _DeltaTime)
{
	GravityVector += GravityAcc * _DeltaTime;


	Color8Bit Color = UContentsHelper::MapColImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		GravityVector = FVector::Zero;
	}
}

void AMario::MoveVectorUpdate(float _DeltaTime)
{
	TotalForceVector = FVector::Zero;
	TotalForceVector = TotalForceVector + RunVector;
	TotalForceVector = TotalForceVector + GravityVector;
	TotalForceVector = TotalForceVector + JumpVector;
}

void AMario::Move(float _DeltaTime)
{
	FVector CurPos = GetActorLocation();
	FVector CurCameraPos = GetWorld()->GetCameraPos();
	FVector NextMarioPos = CurPos + (RunVector * _DeltaTime);
	float Center = GEngine->MainWindow.GetWindowScale().hX();
	float ScaleX = GEngine->MainWindow.GetWindowScale().X;
	if (CurCameraPos.X + Center < NextMarioPos.X && CurCameraPos.X + ScaleX <= UContentsHelper::MapColImage->GetScale().X)
	{
		GetWorld()->AddCameraPos(RunVector * _DeltaTime);
	}

	if (EActorDir::Left == DirState)
	{
		NextMarioPos.X -= 30;
	}
	if (EActorDir::Right == DirState)
	{
		NextMarioPos.X += 30;
	}

	if (CurCameraPos.X <= NextMarioPos.X)
	{
		AddActorLocation(TotalForceVector * _DeltaTime);
	}
}

void AMario::MoveUpdate(float _DeltaTime)
{
	GravityVectorUpdate(_DeltaTime);
	RunVectorUpdate(_DeltaTime);
	MoveVectorUpdate(_DeltaTime);
	Move(_DeltaTime);
}
