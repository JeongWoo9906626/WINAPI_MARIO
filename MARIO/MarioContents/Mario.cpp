#include "Mario.h"

#include <EnginePlatform\EngineInput.h>
#include <EngineBase\EngineDebug.h>

#include "ContentsHelper.h"
#include "Goomba.h"
#include "Troopa.h"
#include "Plant.h"
#include "Flag.h"
#include "Brick.h"
#include "Gate.h"
#include "BreakBrick.h"

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
		Renderer->CreateAnimation("MoveFast_Right", "Mario_Right.png", 1, 3, 0.05f, true);
		Renderer->CreateAnimation("Reverse_Right", "Mario_Right.png", 4, 4, 0.1f, true);
		Renderer->CreateAnimation("Jump_Right", "Mario_Right.png", 5, 5, 0.1f, true);

		Renderer->CreateAnimation("Idle_Left", "Mario_Left.png", 0, 0, 0.1f, true);
		Renderer->CreateAnimation("Move_Left", "Mario_Left.png", 1, 3, 0.1f, true);
		Renderer->CreateAnimation("MoveFast_Left", "Mario_Left.png", 1, 3, 0.05f, true);
		Renderer->CreateAnimation("Reverse_Left", "Mario_Left.png", 4, 4, 0.1f, true);
		Renderer->CreateAnimation("Jump_Left", "Mario_Left.png", 5, 5, 0.1f, true);

		Renderer->CreateAnimation("Die", "Mario_Left.png", 6, 6, 0.1f, true);
		Renderer->CreateAnimation("Down", "Mario_Right.png", 7, 8, 0.1f, true);
		Renderer->CreateAnimation("DownReverse", "Mario_Left.png", 7, 7, 0.1f, true);
	}

	{
		BodyCollision = CreateCollision(ECollisionOrder::Player);
		BodyCollision->SetColType(ECollisionType::Rect);
		BodyCollision->SetPosition({ 0, -35 });
		BodyCollision->SetScale({ 50, 64 });
	}

	{
		HeadCollision = CreateCollision(ECollisionOrder::PlayerHead);
		HeadCollision->SetColType(ECollisionType::Rect);
		HeadCollision->SetPosition({ 0, -62 });
		HeadCollision->SetScale({ 10, 10 });
	}

	{
		BottomCollision = CreateCollision(ECollisionOrder::PlayerBottom);
		BottomCollision->SetColType(ECollisionType::Rect);
		BottomCollision->SetPosition({ 0, -5 });
		BottomCollision->SetScale({ 10, 10 });
	}

	CurDieTime = 0.0f;
	CurDownTime = 0.0f;
	StateChange(EPlayState::Idle);
}

void AMario::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> BoxTopResult;
	if (true == BottomCollision->CollisionCheck(ECollisionOrder::BoxTop, BoxTopResult))
	{
		for (UCollision* BoxPosition : BoxTopResult)
		{
			ABrick* Player = (ABrick*)BoxPosition->GetOwner();

			FTransform BoxCollision = BoxPosition->GetActorBaseTransform();
			FTransform MyTransform = BottomCollision->GetActorBaseTransform();

			GravityPower = FVector::Zero;
			JumpVector = FVector::Zero;
			if (false == IsCollision)
			{
				AddActorLocation(FVector::Up);
			}
			IsJump = false;
			IsCollision = true;
		}
	}
	else 
	{
		IsCollision = false;
	}


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
		case EPlayState::FinishMove:
			FinishMoveStart();
			break;
		case EPlayState::FinishReverse:
			FinishReverseStart();
			break;
		case EPlayState::FinishWalk:
			FinishWalkStart();
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
	case EPlayState::FinishMove:
		FinishMove(_DeltaTime);
		break;
	case EPlayState::FinishReverse:
		FinishReverse(_DeltaTime);
		break;
	case EPlayState::FinishWalk:
		FinishWalk(_DeltaTime);
		break;
	default:
		break;
	}
}

void AMario::CameraFreeMove(float _DeltaTime)
{
	if (UEngineInput::IsPress(VK_LEFT))
	{
		GetWorld()->AddCameraPos(FVector::Left * _DeltaTime * 2000.0f);
	}

	if (UEngineInput::IsPress(VK_RIGHT))
	{
		GetWorld()->AddCameraPos(FVector::Right * _DeltaTime * 2000.0f);
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
	JumpVector += JumpPower;
	AddActorLocation(FVector::Up * 4);
	Renderer->ChangeAnimation(GetAnimationName("Jump"));
}

void AMario::ReverseStart()
{
	Renderer->ChangeAnimation(GetReverseAnimationName("Reverse"));
}

void AMario::DieStart()
{
	JumpVector = DieJumpPower;
	BodyCollision->ActiveOff();
	Renderer->ChangeAnimation("Die");
}

void AMario::KillStart()
{
	DirCheck();
	GravityPower = FVector::Zero;
	JumpVector = KillJumpPower;
	Renderer->ChangeAnimation(GetAnimationName("Jump"));
}

void AMario::FinishMoveStart()
{
	Renderer->ChangeAnimation("Down");
}

void AMario::FinishReverseStart()
{
	AddActorLocation(FVector::Right * 12.0f);
	Renderer->ChangeAnimation("DownReverse");
}

void AMario::FinishWalkStart()
{
	Renderer->ChangeAnimation("Move_Right");
}

void AMario::Idle(float _DeltaTime)
{
	MoveUpdate(_DeltaTime);
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

	if (true == UEngineInput::IsPress(VK_LSHIFT))
	{
		MaxRunSpeed = ShiftRunSpeed;
		CurBreakSpeed = ShiftBreakSpeed;
	}
	if (true == UEngineInput::IsFree(VK_LSHIFT))
	{
		MaxRunSpeed = NoramlRunSpeed;
		CurBreakSpeed = NormalBreakSpeed;
	}

	if (true == UEngineInput::IsPress(VK_LEFT) || true == UEngineInput::IsPress(VK_RIGHT))
	{
		StateChange(EPlayState::Run);
		GroundUp();
		return;
	}

	if (true == UEngineInput::IsDown(VK_SPACE) && false == IsJump)
	{
		StateChange(EPlayState::Jump);
		GroundUp();
		return;
	}
}

void AMario::Run(float _DeltaTime)
{
	GroundUp();
	if (true == UEngineInput::IsDown(VK_SPACE))
	{
		StateChange(EPlayState::Jump);
		GroundUp();
		return;
	}

	if (true == UEngineInput::IsFree(VK_LEFT) && true == UEngineInput::IsFree(VK_RIGHT))
	{
		if (abs(RunVector.X) <= 5.0f)
		{
			RunVector.X = 0.0f;
			StateChange(EPlayState::Idle);
			GroundUp();
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
		if (abs(RunVector.X) <= 5.0f)
		{
			RunVector.X = 0.0f;
			StateChange(EPlayState::Idle);
			GroundUp();
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
			SubtractRunVector(BreakDirState * _DeltaTime);
			MoveUpdate(_DeltaTime);
			return;
		}
	}

	if (true == UEngineInput::IsPress(VK_LSHIFT))
	{
		MaxRunSpeed = ShiftRunSpeed;
		CurBreakSpeed = ShiftBreakSpeed;
		Renderer->ChangeAnimation(GetAnimationName("MoveFast"));
	}
	if (true == UEngineInput::IsFree(VK_LSHIFT))
	{
		MaxRunSpeed = NoramlRunSpeed;
		CurBreakSpeed = NormalBreakSpeed;
		Renderer->ChangeAnimation(GetAnimationName("Move"));
	}

	if (true == UEngineInput::IsPress(VK_LEFT))
	{
		if (RunVector.X > 0.0f)
		{
			StateChange(EPlayState::Reverse);
			GroundUp();
			return;
		}

		AddRunVector(FVector::Left * _DeltaTime);
		MoveUpdate(_DeltaTime);
		return;
	}

	if (true == UEngineInput::IsPress(VK_RIGHT))
	{
		if (RunVector.X < 0.0f)
		{
			StateChange(EPlayState::Reverse);
			GroundUp();
			return;
		}

		AddRunVector(FVector::Right * _DeltaTime);
		MoveUpdate(_DeltaTime);
		return;
	}
}

void AMario::Jump(float _DeltaTime)
{
	IsJump = true;

	if (UEngineInput::IsPress(VK_LEFT))
	{
		AddRunVector(FVector::Left * _DeltaTime);
	}
	if (UEngineInput::IsPress(VK_RIGHT))
	{
		AddRunVector(FVector::Right * _DeltaTime);
	}

	if (UEngineInput::IsUp(VK_SPACE))
	{
		JumpVector = FVector::Zero;
	}

	MoveUpdate(_DeltaTime);

	FVector Location = GetActorLocation();

	Color8Bit Color = UContentsHelper::MapColImage->GetColor(Location.iX(), Location.iY(), Color8Bit::MagentaA);

	if (Color == Color8Bit(255, 0, 255, 0))
	{
		JumpVector = FVector::Zero;
		GravityPower = FVector::Zero;

		if (RunVector.X > 0.0f)
		{
			if (true == UEngineInput::IsPress(VK_LEFT))
			{
				StateChange(EPlayState::Reverse);
				GroundUp();
				return;
			}
		}

		if (RunVector.X < 0.0f)
		{
			if (true == UEngineInput::IsPress(VK_RIGHT))
			{
				StateChange(EPlayState::Reverse);
				GroundUp();
				return;
			}
		}
	}

	if (JumpVector.Y == 0.0f && GravityPower.Y == 0.0f)
	{
		StateChange(EPlayState::Idle);
		GroundUp();
		return;
	}


}

void AMario::Reverse(float _DeltaTime)
{
	if (true == UEngineInput::IsDown(VK_SPACE))
	{
		StateChange(EPlayState::Jump);
		GroundUp();
		return;
	}

	if (DirState == EActorDir::Left)
	{
		if (true == UEngineInput::IsDown(VK_LEFT))
		{
			StateChange(EPlayState::Run);
			GroundUp();
			return;
		}

		if (true == UEngineInput::IsPress(VK_RIGHT))
		{
			SubtractRunVector(FVector::Right * _DeltaTime);
		}

		if (0.0f <= RunVector.X)
		{
			RunVector.X = 0.0f;
			ReverseDir();
			StateChange(EPlayState::Idle);
			GroundUp();
			return;
		}
	}

	if (DirState == EActorDir::Right)
	{
		if (true == UEngineInput::IsDown(VK_RIGHT))
		{
			StateChange(EPlayState::Run);
			GroundUp();
			return;
		}

		if (true == UEngineInput::IsPress(VK_LEFT))
		{
			SubtractRunVector(FVector::Left * _DeltaTime);
		}

		if (0.0f >= RunVector.X)
		{
			RunVector.X = 0.0f;
			ReverseDir();
			StateChange(EPlayState::Idle);
			GroundUp();
			return;
		}
	}

	MoveUpdate(_DeltaTime);
}

void AMario::Die(float _DeltaTime)
{
	if (CurDieTime >= DieTime)
	{
		AddActorLocation(JumpVector * (_DeltaTime));
		JumpVector += GravityAcc * _DeltaTime;
	}
	else
	{
		CurDieTime += _DeltaTime;
	}
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
		GroundUp();
		return;
	}
}

void AMario::FinishMove(float _DeltaTime)
{
	Color8Bit Color = UContentsHelper::MapColImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		StateChange(EPlayState::FinishReverse);
		return;
	}
	else
	{
		AddActorLocation(FVector::Down * FinishDownSpeed * _DeltaTime);
	}
}

void AMario::FinishReverse(float _DeltaTime)
{
	if (DownTime <= CurDownTime)
	{
		StateChange(EPlayState::FinishWalk);
		return;
	}
	else
	{
		CurDownTime += _DeltaTime;
	}
}

void AMario::FinishWalk(float _DeltaTime)
{
	JumpVector = FVector::Zero;
	GroundUp();
	AddRunVector(FVector::Right * _DeltaTime);
	MoveUpdate(_DeltaTime);
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

void AMario::AddRunVector(const FVector& _DirDelta)
{
	RunVector += _DirDelta * RunAcc;
}

void AMario::SubtractRunVector(const FVector& _DirDelta)
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

	if (State == EPlayState::FinishWalk)
	{
		RunVector = RunVector.Normalize2DReturn() * FinishMoveSpeed;
	}

	float CamerPos = GetWorld()->GetCameraPos().X;

	if (CheckPos.X <= CamerPos)
	{
		RunVector = FVector::Zero;
	}
}

void AMario::GravityVectorUpdate(float _DeltaTime)
{
	if (!IsCollision) {
		GravityPower += GravityAcc * _DeltaTime;
	}
	Color8Bit Color = UContentsHelper::MapColImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		IsJump = false;
		GravityPower = FVector::Zero;
	}
}

void AMario::MoveVectorUpdate(float _DeltaTime)
{
	TotalForceVector = FVector::Zero;
	TotalForceVector = TotalForceVector + RunVector;
	TotalForceVector = TotalForceVector + GravityPower;
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
		NextMarioPos.X -= 32.0f;
	}
	if (EActorDir::Right == DirState)
	{
		NextMarioPos.X += 32.0f;
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

void AMario::GroundUp()
{
	while (true)
	{
		FVector Location = GetActorLocation();
		Location.Y -= 1.0f;
		Color8Bit Color = UContentsHelper::MapColImage->GetColor(Location.iX(), Location.iY(), Color8Bit::MagentaA);
		if (Color == Color8Bit(255, 0, 255, 0))
		{
			AddActorLocation(FVector::Up);
		}
		else
		{
			break;
		}
	}
}
