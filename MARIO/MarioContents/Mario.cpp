#include "Mario.h"

#include <EnginePlatform\EngineInput.h>
#include <EngineBase\EngineDebug.h>
#include <EngineCore/EngineDebug.h>

#include "ContentsHelper.h"
#include "HiddenGate.h"
#include "MarioFire.h"

AMario* AMario::MainPlayer = nullptr;

AMario::AMario()
{
}

AMario::~AMario()
{
}

void AMario::BeginPlay()
{
	AActor::BeginPlay();

	AMario::MainPlayer = this;

	{
		Renderer = CreateImageRenderer(ERenderOrder::Player);
		Renderer->SetImage("Mario_Right.png");
		Renderer->SetTransform({ { 0, 0 }, { 256, 256 } });
	}

	{
		Renderer->CreateAnimation("Idle_Small_Right", "Mario_Right.png", 0, 0, 0.1f, true);
		Renderer->CreateAnimation("Move_Small_Right", "Mario_Right.png", 1, 3, 0.1f, true);
		Renderer->CreateAnimation("MoveFast_Small_Right", "Mario_Right.png", 1, 3, 0.05f, true);
		Renderer->CreateAnimation("Reverse_Small_Right", "Mario_Right.png", 4, 4, 0.1f, true);
		Renderer->CreateAnimation("Jump_Small_Right", "Mario_Right.png", 5, 5, 0.1f, true);

		Renderer->CreateAnimation("Idle_Big_Right", "Mario_Right.png", 9, 9, 0.1f, true);
		Renderer->CreateAnimation("Move_Big_Right", "Mario_Right.png", 10, 12, 0.1f, true);
		Renderer->CreateAnimation("MoveFast_Big_Right", "Mario_Right.png", 10, 12, 0.05f, true);
		Renderer->CreateAnimation("Reverse_Big_Right", "Mario_Right.png", 13, 13, 0.1f, true);
		Renderer->CreateAnimation("Jump_Big_Right", "Mario_Right.png", 14, 14, 0.1f, true);
		Renderer->CreateAnimation("Crouch_Big_Right", "Mario_Right.png", 15, 15, 0.1f, true);

		Renderer->CreateAnimation("Idle_Fire_Right", "Mario_Right.png", 20, 20, 0.1f, true);
		Renderer->CreateAnimation("Move_Fire_Right", "Mario_Right.png", 21, 23, 0.1f, true);
		Renderer->CreateAnimation("MoveFast_Fire_Right", "Mario_Right.png", 21, 23, 0.05f, true);
		Renderer->CreateAnimation("Reverse_Fire_Right", "Mario_Right.png", 24, 24, 0.1f, true);
		Renderer->CreateAnimation("Jump_Fire_Right", "Mario_Right.png", 25, 25, 0.1f, true);
		Renderer->CreateAnimation("Crouch_Fire_Right", "Mario_Right.png", 26, 26, 0.1f, true);

		Renderer->CreateAnimation("Idle_Small_Left", "Mario_Left.png", 0, 0, 0.1f, true);
		Renderer->CreateAnimation("Move_Small_Left", "Mario_Left.png", 1, 3, 0.1f, true);
		Renderer->CreateAnimation("MoveFast_Small_Left", "Mario_Left.png", 1, 3, 0.05f, true);
		Renderer->CreateAnimation("Reverse_Small_Left", "Mario_Left.png", 4, 4, 0.1f, true);
		Renderer->CreateAnimation("Jump_Small_Left", "Mario_Left.png", 5, 5, 0.1f, true);

		Renderer->CreateAnimation("Idle_Big_Left", "Mario_Left.png", 9, 9, 0.1f, true);
		Renderer->CreateAnimation("Move_Big_Left", "Mario_Left.png", 10, 12, 0.1f, true);
		Renderer->CreateAnimation("MoveFast_Big_Left", "Mario_Left.png", 10, 12, 0.05f, true);
		Renderer->CreateAnimation("Reverse_Big_Left", "Mario_Left.png", 13, 13, 0.1f, true);
		Renderer->CreateAnimation("Jump_Big_Left", "Mario_Left.png", 14, 14, 0.1f, true);
		Renderer->CreateAnimation("Crouch_Big_Left", "Mario_Left.png", 15, 15, 0.1f, true);

		Renderer->CreateAnimation("Idle_Fire_Left", "Mario_Left.png", 20, 20, 0.1f, true);
		Renderer->CreateAnimation("Move_Fire_Left", "Mario_Left.png", 21, 23, 0.1f, true);
		Renderer->CreateAnimation("MoveFast_Fire_Left", "Mario_Left.png", 21, 23, 0.05f, true);
		Renderer->CreateAnimation("Reverse_Fire_Left", "Mario_Left.png", 24, 24, 0.1f, true);
		Renderer->CreateAnimation("Jump_Fire_Left", "Mario_Left.png", 25, 25, 0.1f, true);
		Renderer->CreateAnimation("Crouch_Fire_Left", "Mario_Left.png", 26, 26, 0.1f, true);

		Renderer->CreateAnimation("Die", "Mario_Left.png", 6, 6, 0.1f, true);

		Renderer->CreateAnimation("Down_Small", "Mario_Right.png", 7, 8, 0.1f, true);
		Renderer->CreateAnimation("DownWait_Small", "Mario_Right.png", 8, 8, 0.1f, true);
		Renderer->CreateAnimation("DownReverse_Small", "Mario_Left.png", 8, 8, 0.1f, true);

		Renderer->CreateAnimation("Down_Big", "Mario_Right.png", 16, 17, 0.1f, true);
		Renderer->CreateAnimation("DownWait_Big", "Mario_Right.png", 17, 17, 0.1f, true);
		Renderer->CreateAnimation("DownReverse_Big", "Mario_Left.png", 17, 17, 0.1f, true);

		Renderer->CreateAnimation("Down_Fire", "Mario_Right.png", 27, 28, 0.1f, true);
		Renderer->CreateAnimation("DownWait_Fire", "Mario_Right.png", 28, 28, 0.1f, true);
		Renderer->CreateAnimation("DownReverse_Fire", "Mario_Left.png", 28, 28, 0.1f, true);

		Renderer->CreateAnimation("GrowUp_Right", "Mario_Right.png", { 0, 19, 18, 19, 18 }, 0.1f, false);
		Renderer->CreateAnimation("GrowUp_Left", "Mario_Left.png", { 0, 19, 18, 19, 18 }, 0.1f, false);

		Renderer->CreateAnimation("GrowDown_Right", "Mario_Right.png", { 18, 19, 18, 19, 0 }, 0.1f, false);
		Renderer->CreateAnimation("GrowDown_Left", "Mario_Left.png", { 18, 19, 18, 19, 0 }, 0.1f, false);

		Renderer->CreateAnimation("ChangeRed_Right", "Mario_Right.png", { 33, 32, 33, 32, 33 }, 0.1f, false);
		Renderer->CreateAnimation("ChangeRed_Left", "Mario_Left.png", { 33, 32, 33, 32, 33 }, 0.1f, false);

		Renderer->CreateAnimation("FireShoot_Left", "Mario_Left.png", 31, 31, 0.1f, false);
		Renderer->CreateAnimation("FireShoot_Right", "Mario_Right.png", 31, 31, 0.1f, false);
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
	CurMaxSpeed = MaxMoveSpeed;
	CurJumpPower = MoveJumpPower;
	CurGravityAcc = GravityAcc;
	CurBreakSpeed = BreakSpeed;
	SizeState = EMarioSizeState::Small;
	StateChange(EPlayState::Idle);
}

void AMario::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	FVector PlayerPos = GetActorLocation();
	UEngineDebug::DebugTextPrint("X : " + std::to_string(PlayerPos.X) + ", Y : " + std::to_string(PlayerPos.Y), 30.0f);
	UEngineDebug::DebugTextPrint("\nDeltaTime : " + std::to_string(_DeltaTime), 30.0f);

	// 디버그 관련 기능들 
	{
		if (true == UEngineInput::IsDown('4'))
		{
			UContentsHelper::Time = 1300;
			UContentsHelper::SubStage = 4;
			UContentsHelper::MapName = "FinalStage";
			GEngine->ChangeLevel("Loading");
			return;
		}

		if (true == UEngineInput::IsDown('3'))
		{
			UContentsHelper::Time = 1400;
			UContentsHelper::SubStage = 1;
			UContentsHelper::MapName = "FirstStage";
			GEngine->ChangeLevel("Loading");
			return;
		}

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

		if (true == UEngineInput::IsDown('S') && UContentsHelper::MSizeState != EMarioSizeState::Small)
		{
			SizeState = EMarioSizeState::Small;
			StateChange(EPlayState::GrowDown);
			return;
		}

		if (true == UEngineInput::IsDown('B') && UContentsHelper::MSizeState != EMarioSizeState::Big)
		{
			SizeState = EMarioSizeState::Big;
			StateChange(EPlayState::GrowUp);
			return;
		}

		if (true == UEngineInput::IsDown('F') && UContentsHelper::MSizeState != EMarioSizeState::Red)
		{
			SizeState = EMarioSizeState::Red;
			StateChange(EPlayState::ChangeRed);
			return;
		}

		if (true == UEngineInput::IsDown('E'))
		{
			if (UContentsHelper::MapName._Equal("FinalStage"))
			{
				float XPos = 7700.0f;
				float YPos = 0.0f;

				FVector ChangePos = { XPos, YPos, 0.0f, 0.0f };
				GetWorld()->SetCameraPos(ChangePos);

				FVector SpawnPos = { 7945.0f, 641.0f, 0.0f, 0.0f };
				SetActorLocation(SpawnPos);
			}
			if (UContentsHelper::MapName._Equal("FirstStage"))
			{
				float XPos = 12460.0f;
				float YPos = 0.0f;

				FVector ChangePos = { XPos, YPos, 0.0f, 0.0f };
				GetWorld()->SetCameraPos(ChangePos);

				FVector SpawnPos = { 12900.0f, 833.0f, 0.0f, 0.0f };
				SetActorLocation(SpawnPos);
			}
		}

		if (true == UEngineInput::IsDown('K'))
		{
			IsInvincibility = !IsInvincibility;
		}
	}

	if (true == UEngineInput::IsDown('X'))
	{
		CurMaxSpeed = MaxRunSpeed;
		CurJumpPower = RunJumpPower;
		CurBreakSpeed = RunBreakSpeed;
		if (EMarioSizeState::Red == SizeState && UContentsHelper::MarioFireCount < 2)
		{
			AMarioFire* MarioFire = GetWorld()->SpawnActor<AMarioFire>(ERenderOrder::Fire);
			MarioFire->SetActorLocation({ GetActorLocation().X, GetActorLocation().Y - 80 });
			MarioFire->SetDir(DirState);
		}
	}
	if (true == UEngineInput::IsFree('X'))
	{
		if (MoveVector.X <= 410.0f)
		{
			CurMaxSpeed = MaxMoveSpeed;
			CurJumpPower = MoveJumpPower;
			CurBreakSpeed = RunBreakSpeed;
		}
		else
		{
			if (MoveVector.X > 0.0f)
			{
				MoveVector.X -= CurBreakSpeed * _DeltaTime;
			}
			else
			{
				MoveVector.X += CurBreakSpeed * _DeltaTime;
			}
		}
	}

	if (true == IsChange)
	{
		if (CurNoCollisionTime > NoCollisionTime)
		{
			CurNoCollisionTime = 0.0f;
			Renderer->SetAlpha(1.0f);
			BodyCollision->ActiveOn();
			BottomCollision->ActiveOn();
			HeadCollision->ActiveOn();
			IsChange = false;
		}
		CurNoCollisionTime += _DeltaTime;
	}

	// 마리오 콜리전 체크
	{
		// 비밀 장소로 이동하는 게이트 충돌처리
		std::vector<UCollision*> HiddenGateInResult;
		if (true == BottomCollision->CollisionCheck(ECollisionOrder::Gate, HiddenGateInResult))
		{
			AHiddenGate* HiddenGate = (AHiddenGate*)HiddenGateInResult[0]->GetOwner();
			EGateState GateState = HiddenGate->GetGateState();
			if (GateState == EGateState::In && true == UEngineInput::IsDown(VK_DOWN))
			{
				BottomCollision->ActiveOff();
				StateChange(EPlayState::HiddenStageEnter);
				return;
			}
		}

		// 비밀 장소에서 나가는 게이트 충돌 처리
		std::vector<UCollision*> HiddenGateOutResult;
		if (true == BodyCollision->CollisionCheck(ECollisionOrder::Gate, HiddenGateOutResult))
		{
			AHiddenGate* HiddenGate = (AHiddenGate*)HiddenGateOutResult[0]->GetOwner();
			EGateState GateState = HiddenGate->GetGateState();
			if (GateState == EGateState::Out && true == UEngineInput::IsDown(VK_RIGHT))
			{
				BottomCollision->ActiveOn();
				StateChange(EPlayState::HiddenStageOut);
				return;
			}
		}

		// 블록 윗부분과 충돌처리
		std::vector<UCollision*> BoxTopResult;
		if (true == BottomCollision->CollisionCheck(ECollisionOrder::BoxTop, BoxTopResult))
		{
			GravityVector = FVector::Zero;
			JumpVector = FVector::Zero;

			FVector MarioBottomCollisionPos = BottomCollision->GetActorBaseTransform().GetPosition();
			FVector MarioBottomCollisionScale = BottomCollision->GetActorBaseTransform().GetScale();

			FVector BoxCollisionPos = BoxTopResult[0]->GetActorBaseTransform().GetPosition();
			FVector BoxCollisionScale = BoxTopResult[0]->GetActorBaseTransform().GetScale();

			SetActorLocation({ MarioBottomCollisionPos.X, BoxCollisionPos.Y - 3.0f });

			IsCollision = true;
		}
		else
		{
			IsCollision = false;
		}
	}

	DieCheck();
	StateUpdate(_DeltaTime);
}

void AMario::StateChange(EPlayState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EPlayState::FreeMove:
			FreeMoveStart();
			break;
		case EPlayState::Idle:
			IdleStart();
			break;
		case EPlayState::Move:
			MoveStart();
			break;
		case EPlayState::Jump:
			JumpStart();
			break;
		case EPlayState::Crouch:
			CrouchStart();
			break;
		case EPlayState::CrouchMove:
			CrouchMoveStart();
			break;
		case EPlayState::Reverse:
			ReverseStart();
			break;
		case EPlayState::Kill:
			KillStart();
			break;
		case EPlayState::Die:
			DieStart();
			break;
		case EPlayState::GrowUp:
			GrowUpStart();
			break;
		case EPlayState::GrowDown:
			GrowDownStart();
			break;
		case EPlayState::ChangeRed:
			ChangeRedStart();
			break;
		case EPlayState::HiddenStageEnter:
			HiddenStageEnterStart();
			break;
		case EPlayState::HiddenStageOut:
			HiddenStageOutStart();
			break;
		case EPlayState::HiddenStageOutUp:
			HiddenStageOutUpStart();
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
		case EPlayState::BossFinish:
			BossFinishStart();
			break;
		case EPlayState::BossFinishWalk:
			BossFinishWalkStart();
			break;
		case EPlayState::Ending:
			EndingStart();
			break;
		}
	}

	State = _State;
}

void AMario::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EPlayState::FreeMove:
		FreeMove(_DeltaTime);
		break;
	case EPlayState::CameraFreeMove:
		CameraFreeMove(_DeltaTime);
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
	case EPlayState::Crouch:
		Crouch(_DeltaTime);
		break;
	case EPlayState::CrouchMove:
		CrouchMove(_DeltaTime);
		break;
	case EPlayState::Reverse:
		Reverse(_DeltaTime);
		break;
	case EPlayState::Kill:
		Kill(_DeltaTime);
		break;
	case EPlayState::Die:
		Die(_DeltaTime);
		break;
	case EPlayState::GrowUp:
		GrowUp(_DeltaTime);
		break;
	case EPlayState::GrowDown:
		GrowDown(_DeltaTime);
		break;
	case EPlayState::ChangeRed:
		ChangeRed(_DeltaTime);
		break;
	case EPlayState::HiddenStageEnter:
		HiddenStageEnter(_DeltaTime);
		break;
	case EPlayState::HiddenStageOut:
		HiddenStageOut(_DeltaTime);
		break;
	case EPlayState::HiddenStageOutUp:
		HiddenStageOutUp(_DeltaTime);
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
	case EPlayState::BossFinish:
		BossFinish(_DeltaTime);
		break;
	case EPlayState::BossFinishWalk:
		BossFinishWalk(_DeltaTime);
		break;
	}
}

void AMario::DirCheck()
{
	if (true == UEngineInput::IsFree(VK_RIGHT) && true == UEngineInput::IsFree(VK_LEFT))
	{
		DirState;
		return;
	}
	if (true == UEngineInput::IsPress(VK_RIGHT) && true == UEngineInput::IsPress(VK_LEFT))
	{
		return;
	}
	if (
		true == UEngineInput::IsPress(VK_RIGHT) && true == UEngineInput::IsUp(VK_LEFT) ||
		true == UEngineInput::IsPress(VK_RIGHT) && true == UEngineInput::IsFree(VK_LEFT)
		)
	{
		DirState = EActorDir::Right;
		return;
	}
	if (
		true == UEngineInput::IsPress(VK_LEFT) && true == UEngineInput::IsUp(VK_RIGHT) ||
		true == UEngineInput::IsPress(VK_LEFT) && true == UEngineInput::IsFree(VK_RIGHT)
		)
	{
		DirState = EActorDir::Left;
		return;
	}
}

std::string AMario::GetAnimationName(std::string _Name)
{
	std::string SizeName = "";
	std::string AnimationDir = "";

	switch (SizeState)
	{
	case EMarioSizeState::Small:
		SizeName = "_Small";
		break;
	case EMarioSizeState::Big:
		SizeName = "_Big";
		break;
	case EMarioSizeState::Red:
		SizeName = "_Fire";
		break;
	case EMarioSizeState::Star:
		break;
	}

	if (EPlayState::Reverse == State)
	{
		switch (DirState)
		{
		case EActorDir::Left:
			AnimationDir = "_Right";
			break;
		case EActorDir::Right:
			AnimationDir = "_Left";
			break;
		}
	}
	else
	{
		switch (DirState)
		{
		case EActorDir::Left:
			AnimationDir = "_Left";
			break;
		case EActorDir::Right:
			AnimationDir = "_Right";
			break;
		}
	}

	return _Name + SizeName + AnimationDir;
}

void AMario::FreeMoveStart()
{
	BodyCollision->ActiveOff();
	BottomCollision->ActiveOff();
	HeadCollision->ActiveOff();
	Renderer->SetAlpha(0.5f);
}

void AMario::IdleStart()
{
	if (false == IsChange && false == IsInvincibility)
	{
		BodyCollision->ActiveOn();
		Renderer->SetAlpha(1.0f);
	}

	DirCheck();
	MoveVector = FVector::Zero;
	SizeState = UContentsHelper::MSizeState;

	switch (SizeState)
	{
	case EMarioSizeState::Small:
	{
		BodyCollision->SetPosition({ 0, -35 });
		BodyCollision->SetScale({ 50, 64 });
		HeadCollision->SetPosition({ 0, -62 });
		BottomCollision->SetPosition({ 0, -5 });
		BottomCollision->SetScale({ 10, 10 });
		break;
	}
	case EMarioSizeState::Big:
	case EMarioSizeState::Red:
	{
		BodyCollision->SetPosition({ 0, -70 });
		BodyCollision->SetScale({ 50, 130 });
		HeadCollision->SetPosition({ 0, -130 });
		BottomCollision->SetPosition({ 0, -5 });
		BottomCollision->SetScale({ 10, 10 });
		break;
	}
	}

	if (true == IsDown && false == IsMove)
	{
		StateChange(EPlayState::Crouch);
		return;
	}
	Renderer->ChangeAnimation(GetAnimationName("Idle"));
}

void AMario::MoveStart()
{
	DirCheck();
	Renderer->ChangeAnimation(GetAnimationName("Move"));
}

void AMario::JumpStart()
{
	IsGround = false;
	JumpForce = CurJumpPower;
	DirCheck();
	AddActorLocation(FVector::Up * 5);
	JumpVector = FVector::Up * JumpForce;
	if (true == IsDown)
	{
		Renderer->ChangeAnimation(GetAnimationName("Crouch"));
	}
	else
	{
		Renderer->ChangeAnimation(GetAnimationName("Jump"));
	}
}

void AMario::CrouchStart()
{
	DirCheck();
	BodyCollision->SetPosition({ 0, -45 });
	BodyCollision->SetScale({ 50, 80 });
	HeadCollision->SetPosition({ 0, -82 });
	Renderer->ChangeAnimation(GetAnimationName("Crouch"));
}

void AMario::CrouchMoveStart()
{
	DirCheck();
	Renderer->ChangeAnimation(GetAnimationName("Crouch"));
}

void AMario::ReverseStart()
{
	DirCheck();
	Renderer->ChangeAnimation(GetAnimationName("Reverse"));
}

void AMario::KillStart()
{
	DirCheck();
	GravityVector = FVector::Zero;
	JumpForce = KillJumpPower;
	JumpVector = FVector::Up * JumpForce;
	Renderer->ChangeAnimation(GetAnimationName("Jump"));
}

void AMario::DieStart()
{
	GetWorld()->SetTimeScale(ERenderOrder::Monster, 0.0f);
	GetWorld()->SetTimeScale(ERenderOrder::UI, 0.0f);

	UContentsHelper::MSizeState = SizeState;
	UContentsHelper::MarioLife--;
	JumpVector = FVector::Up * DieJumpPower;;
	BodyCollision->ActiveOff();
	HeadCollision->ActiveOff();
	BottomCollision->ActiveOff();
	Renderer->ChangeAnimation("Die");
}

void AMario::GrowUpStart()
{
	GetWorld()->SetOtherTimeScale(ERenderOrder::Player, 0.0f);
	UContentsHelper::MSizeState = SizeState;
	DirCheck();
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

	Renderer->ChangeAnimation("GrowUp" + DirName);
}

void AMario::GrowDownStart()
{
	GetWorld()->SetOtherTimeScale(ERenderOrder::Player, 0.0f);
	UContentsHelper::MSizeState = SizeState;
	DirCheck();
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
	Renderer->SetAlpha(0.5f);

	BodyCollision->ActiveOff();
	Renderer->ChangeAnimation("GrowDown" + DirName);
}

void AMario::ChangeRedStart()
{
	UContentsHelper::MSizeState = SizeState;
	GetWorld()->SetOtherTimeScale(ERenderOrder::Player, 0.0f);
	DirCheck();
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

	Renderer->ChangeAnimation("ChangeRed" + DirName);
}

void AMario::HiddenStageEnterStart()
{
	IsHiddenStage = true;
	CurPortalTime = 0.0f;
	CurScreenChangeTime = 0.0f;
	MoveVector = FVector::Zero;

	Renderer->ChangeAnimation(GetAnimationName("Idle"));
	SetActorLocation(UContentsHelper::PortalPos1);
}

void AMario::HiddenStageOutStart()
{
	IsHiddenStage = false;
	CurPortalTime = 0.0f;
	CurScreenChangeTime = 0.0f;

	DirState = EActorDir::Right;
	Renderer->ChangeAnimation(GetAnimationName("Idle"));
}

void AMario::HiddenStageOutUpStart()
{
	CurPortalTime = 0.0f;
	CurScreenChangeTime = 0.0f;
}

void AMario::FinishMoveStart()
{
	BodyCollision->ActiveOff();
	std::string FinishMoveName = "";

	switch (SizeState)
	{
	case EMarioSizeState::Small:
		FinishMoveName = "_Small";
		break;
	case EMarioSizeState::Big:
		FinishMoveName = "_Big";
		break;
	case EMarioSizeState::Red:
		FinishMoveName = "_Fire";
		break;
	case EMarioSizeState::Star:
		break;
	}
	Renderer->ChangeAnimation("Down" + FinishMoveName);
	SetActorLocation({ 12675.0f, GetActorLocation().Y });
}

void AMario::FinishReverseStart()
{
	AddActorLocation(FVector::Right * 62.0f);

	std::string FinishMoveName = "";

	switch (SizeState)
	{
	case EMarioSizeState::Small:
		FinishMoveName = "_Small";
		break;
	case EMarioSizeState::Big:
		FinishMoveName = "_Big";
		break;
	case EMarioSizeState::Red:
		FinishMoveName = "_Fire";
		break;
	case EMarioSizeState::Star:
		break;
	}

	Renderer->ChangeAnimation("DownReverse" + FinishMoveName);
}

void AMario::FinishWalkStart()
{
	BodyCollision->ActiveOn();
	std::string FinishMoveName = "";

	switch (SizeState)
	{
	case EMarioSizeState::Small:
		FinishMoveName = "_Small";
		break;
	case EMarioSizeState::Big:
		FinishMoveName = "_Big";
		break;
	case EMarioSizeState::Red:
		FinishMoveName = "_Fire";
		break;
	case EMarioSizeState::Star:
		break;
	}

	Renderer->ChangeAnimation("Move" + FinishMoveName + "_Right");
}

void AMario::BossFinishStart()
{
	DirState = EActorDir::Left;
	BodyCollision->SetActive(false);
	Renderer->ChangeAnimation(GetAnimationName("Idle"));
}

void AMario::BossFinishWalkStart()
{
	DirState = EActorDir::Right;
	BodyCollision->SetActive(true);
	Renderer->ChangeAnimation(GetAnimationName("Move"));
	UContentsHelper::IsBossStage = false;
}

void AMario::EndingStart()
{
	DirState = EActorDir::Right;
	MoveVector = FVector::Zero;
	Renderer->ChangeAnimation(GetAnimationName("Idle"));
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

void AMario::Idle(float _DeltaTime)
{
	if (true == IsInvincibility && false == IsChange)
	{
		BodyCollision->ActiveOff();
		Renderer->SetAlpha(0.5f);
	}
	else if (false == IsInvincibility && false == IsChange)
	{
		BodyCollision->ActiveOn();
		Renderer->SetAlpha(1.0f);
	}

	GroundUp();
	MoveUpdate(_DeltaTime);

	if (EMarioSizeState::Small != SizeState && true == UEngineInput::IsPress(VK_DOWN) && false == IsDown && true == IsGround)
	{
		IsDown = true;
		IsMove = false;
		StateChange(EPlayState::Crouch);
		return;
	}

	if ((true == UEngineInput::IsUp(VK_DOWN) || true == UEngineInput::IsFree(VK_DOWN)))
	{
		IsDown = false;
		Renderer->ChangeAnimation(GetAnimationName("Idle"));
	}

	if (true == UEngineInput::IsPress(VK_RIGHT) && true == UEngineInput::IsPress(VK_LEFT))
	{
		MoveVector = FVector::Zero;
		return;
	}

	if (true == UEngineInput::IsDown(VK_SPACE) && GravityVector.Y == 0.0f)
	{
		StateChange(EPlayState::Jump);
		return;
	}

	if ((true == UEngineInput::IsPress(VK_RIGHT) || true == UEngineInput::IsPress(VK_LEFT)) && false == IsDown)
	{
		StateChange(EPlayState::Move);
		return;
	}
}

void AMario::Move(float _DeltaTime)
{
	GroundUp();

	if (abs(MoveVector.X) > 410.0f)
	{
		Renderer->ChangeAnimation(GetAnimationName("MoveFast"));
	}
	else
	{
		Renderer->ChangeAnimation(GetAnimationName("Move"));
	}

	if (EMarioSizeState::Small != SizeState && abs(MoveVector.X) > 10.0f && true == UEngineInput::IsDown(VK_DOWN))
	{
		StateChange(EPlayState::CrouchMove);
		return;
	}

	if (true == UEngineInput::IsDown(VK_SPACE) && GravityVector.Y == 0.0f)
	{
		StateChange(EPlayState::Jump);
		return;
	}

	if (
		(true == UEngineInput::IsFree(VK_RIGHT) && true == UEngineInput::IsFree(VK_LEFT)) ||
		(true == UEngineInput::IsPress(VK_RIGHT) && true == UEngineInput::IsPress(VK_LEFT))
		)
	{
		FVector MoveDirVector = FVector::Zero;
		switch (DirState)
		{
		case EActorDir::Left:
			MoveDirVector = FVector::Right;
			break;
		case EActorDir::Right:
			MoveDirVector = FVector::Left;
			break;
		}

		if (abs(MoveVector.X) > 5.0f)
		{
			MoveVector += MoveDirVector * CurBreakSpeed * _DeltaTime;
			MoveUpdate(_DeltaTime);
			return;
		}
		else
		{
			MoveVector = FVector::Zero;
			StateChange(EPlayState::Idle);
			return;
		}
	}

	if (true == UEngineInput::IsPress(VK_RIGHT))
	{
		if (MoveVector.X < -30.0f)
		{
			StateChange(EPlayState::Reverse);
			return;
		}

		if (MoveVector.X <= CurMaxSpeed)
		{
			MoveVector += FVector::Right * MoveAcc * _DeltaTime;
		}
		else
		{
			MoveVector.X = CurMaxSpeed;
		}
	}

	if (true == UEngineInput::IsPress(VK_LEFT))
	{
		if (MoveVector.X > 30.0f)
		{
			StateChange(EPlayState::Reverse);
			return;
		}

		if (MoveVector.X >= -CurMaxSpeed)
		{
			MoveVector += FVector::Left * MoveAcc * _DeltaTime;
		}
		else
		{
			MoveVector.X = -CurMaxSpeed;
		}
	}

	MoveUpdate(_DeltaTime);
}

void AMario::Jump(float _DeltaTime)
{
	MoveUpdate(_DeltaTime);

	if (JumpVector.Y == 0.0f && GravityVector.Y == 0.0f)
	{
		if (MoveVector.X == 0.0f)
		{
			if (true == IsDown)
			{
				StateChange(EPlayState::Crouch);
				return;
			}
			StateChange(EPlayState::Idle);
			return;
		}
		else
		{
			if (false == IsDown)
			{
				if (true == UEngineInput::IsFree(VK_RIGHT) && DirState == EActorDir::Left && MoveVector.X > 0.0f)
				{
					StateChange(EPlayState::Reverse);
					return;
				}
				if (true == UEngineInput::IsFree(VK_LEFT) && DirState == EActorDir::Right && MoveVector.X < 0.0f)
				{
					StateChange(EPlayState::Reverse);
					return;
				}
				StateChange(EPlayState::Move);
				return;
			}
		}
	}

	if (false == IsDown && true == UEngineInput::IsPress(VK_RIGHT))
	{
		if (MoveVector.X <= CurMaxSpeed)
		{
			MoveVector += FVector::Right * MoveAcc * 0.5f * _DeltaTime;
		}
		else
		{
			MoveVector.X = CurMaxSpeed;
		}
	}

	if (false == IsDown && true == UEngineInput::IsPress(VK_LEFT))
	{
		if (MoveVector.X >= -CurMaxSpeed)
		{
			MoveVector += FVector::Left * MoveAcc * 0.5f * _DeltaTime;
		}
		else
		{
			MoveVector.X = CurMaxSpeed;
		}
	}

	if (UEngineInput::IsUp(VK_SPACE))
	{
		JumpVector = FVector::Zero;
		GravityVector.Y *= 0.5f;
	}
}

void AMario::Crouch(float _DeltaTime)
{
	if (true == UEngineInput::IsUp(VK_DOWN))
	{
		IsDown = false;
		StateChange(EPlayState::Idle);
		return;
	}

	if (true == UEngineInput::IsDown(VK_SPACE) && GravityVector.Y == 0.0f)
	{
		IsMove = false;
		StateChange(EPlayState::Jump);
		return;
	}

	if (
		true == UEngineInput::IsPress(VK_RIGHT) && true == UEngineInput::IsUp(VK_LEFT) ||
		true == UEngineInput::IsPress(VK_RIGHT) && true == UEngineInput::IsFree(VK_LEFT)
		)
	{
		IsMove = true;
		StateChange(EPlayState::Idle);
		return;
	}
	if (
		true == UEngineInput::IsPress(VK_LEFT) && true == UEngineInput::IsUp(VK_RIGHT) ||
		true == UEngineInput::IsPress(VK_LEFT) && true == UEngineInput::IsFree(VK_RIGHT)
		)
	{
		IsMove = true;
		StateChange(EPlayState::Idle);
		return;
	}
}

void AMario::CrouchMove(float _DeltaTime)
{
	if (true == UEngineInput::IsUp(VK_DOWN))
	{
		StateChange(EPlayState::Move);
		return;
	}

	if (
		(true == UEngineInput::IsFree(VK_RIGHT) && true == UEngineInput::IsFree(VK_LEFT)) ||
		(true == UEngineInput::IsPress(VK_RIGHT) && true == UEngineInput::IsPress(VK_LEFT))
		)
	{
		FVector MoveDirVector = FVector::Zero;
		switch (DirState)
		{
		case EActorDir::Left:
			MoveDirVector = FVector::Right;
			break;
		case EActorDir::Right:
			MoveDirVector = FVector::Left;
			break;
		}

		if (abs(MoveVector.X) > 5.0f)
		{
			MoveVector += MoveDirVector * CurBreakSpeed * _DeltaTime;
			MoveUpdate(_DeltaTime);
			return;
		}
		else
		{
			MoveVector = FVector::Zero;
			StateChange(EPlayState::Crouch);
			return;
		}
	}
}

void AMario::Reverse(float _DeltaTime)
{
	FVector MoveDirVector = FVector::Zero;

	if (true == UEngineInput::IsDown(VK_SPACE) && GravityVector.Y == 0.0f)
	{
		StateChange(EPlayState::Jump);
		return;
	}

	switch (DirState)
	{
	case EActorDir::Left:
	{
		MoveDirVector = FVector::Left;
		if (true == UEngineInput::IsPress(VK_RIGHT))
		{
			StateChange(EPlayState::Move);
			return;
		}
		break;
	}
	case EActorDir::Right:
	{
		MoveDirVector = FVector::Right;
		if (true == UEngineInput::IsPress(VK_LEFT))
		{
			StateChange(EPlayState::Move);
			return;
		}
		break;
	}
	}

	if (abs(MoveVector.X) < 5.0f)
	{
		MoveVector.X = 0.0f;
		StateChange(EPlayState::Idle);
		return;
	}
	else
	{
		MoveVector += MoveDirVector * CurBreakSpeed * _DeltaTime;
	}

	MoveUpdate(_DeltaTime);
}

void AMario::Kill(float _DeltaTime)
{
	MoveUpdate(_DeltaTime);
	State = EPlayState::Jump;
	return;
}

void AMario::Die(float _DeltaTime)
{
	AddActorLocation(JumpVector * (_DeltaTime));
	JumpVector += FVector::Down * CurGravityAcc * _DeltaTime;

	Color8Bit DieColor = UContentsHelper::MapColImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::YellowA);
	if (Color8Bit(255, 255, 0, 0) == DieColor)
	{
		if (0 == UContentsHelper::MarioLife)
		{
			UContentsHelper::MapName = "GameOver";
			UContentsHelper::HighScore = UContentsHelper::Score;
			GEngine->ChangeLevel("Loading");
			return;
		}

		GEngine->ChangeLevel("Loading");
		return;
	}
}

void AMario::GrowUp(float _DeltaTime)
{
	if (CurChangeTime > ChangeTime)
	{
		GetWorld()->SetOtherTimeScale(ERenderOrder::Player, 1);
		JumpVector = FVector::Zero;
		GravityVector = FVector::Zero;
		CurChangeTime = 0.0f;
		StateChange(EPlayState::Idle);
		return;
	}
	CurChangeTime += _DeltaTime;
}

void AMario::GrowDown(float _DeltaTime)
{
	if (CurChangeTime > ChangeTime)
	{
		GetWorld()->SetOtherTimeScale(ERenderOrder::Player, 1);
		JumpVector = FVector::Zero;
		GravityVector = FVector::Zero;
		CurChangeTime = 0.0f;
		IsChange = true;
		StateChange(EPlayState::Idle);
		return;
	}
	CurChangeTime += _DeltaTime;
}

void AMario::ChangeRed(float _DeltaTime)
{
	if (CurChangeTime > ChangeTime)
	{
		GetWorld()->SetOtherTimeScale(ERenderOrder::Player, 1);
		JumpVector = FVector::Zero;
		GravityVector = FVector::Zero;
		CurChangeTime = 0.0f;
		StateChange(EPlayState::Idle);
		return;
	}
	CurChangeTime += _DeltaTime;
}

void AMario::HiddenStageEnter(float _DeltaTime)
{
	float DownSpeed = 0.0f;
	switch (SizeState)
	{
	case EMarioSizeState::Small:
		DownSpeed = 32.0f;
		break;
	case EMarioSizeState::Big:
	case EMarioSizeState::Red:
		DownSpeed = 63.0f;
		break;
	}
	if (CurPortalTime <= PortalTime)
	{
		AddActorLocation(FVector::Down * _DeltaTime * DownSpeed);
		CurPortalTime += _DeltaTime;
	}
	else
	{
		if (CurScreenChangeTime <= ScreenChangeTime)
		{
			CurScreenChangeTime += _DeltaTime;
		}
		else
		{
			float YPos = GEngine->MainWindow.GetWindowScale().Y;
			FVector ChangePos = { UContentsHelper::HiddenStageCameraPosX, YPos, 0.0f, 0.0f };
			GetWorld()->SetCameraPos(ChangePos);

			SetActorLocation(UContentsHelper::HiddenStageSpawnPos);
			StateChange(EPlayState::Idle);
			return;
		}
	}
}

void AMario::HiddenStageOut(float _DeltaTime)
{
	if (CurPortalTime <= PortalTime)
	{
		AddActorLocation(FVector::Right * _DeltaTime * 30.f);
		CurPortalTime += _DeltaTime;
	}
	else
	{
		if (CurScreenChangeTime <= ScreenChangeTime)
		{
			CurScreenChangeTime += _DeltaTime;
		}
		else
		{
			FVector ChangePos = { UContentsHelper::HiddenStageOutCameraPosX, 0.0f, 0.0f, 0.0f };
			GetWorld()->SetCameraPos(ChangePos);

			SetActorLocation(UContentsHelper::HiddenStageOutSpawnPos);
			StateChange(EPlayState::HiddenStageOutUp);
			return;
		}
	}
}

void AMario::HiddenStageOutUp(float _DeltaTime)
{
	if (CurPortalTime < PortalTime)
	{
		AddActorLocation(FVector::Up * _DeltaTime * 50.0f);
		CurPortalTime += _DeltaTime;
	}
	else
	{
		GroundUp();
		StateChange(EPlayState::Idle);
		return;
	}
}

void AMario::FinishMove(float _DeltaTime)
{
	GroundUp();
	std::string FinishMoveName = "";
	switch (SizeState)
	{
	case EMarioSizeState::Small:
		FinishMoveName = "_Small";
		break;
	case EMarioSizeState::Big:
		FinishMoveName = "_Big";
		break;
	case EMarioSizeState::Red:
		FinishMoveName = "_Fire";
		break;
	case EMarioSizeState::Star:
		break;
	}
	Color8Bit Color = UContentsHelper::MapColImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		Renderer->ChangeAnimation("DownWait" + FinishMoveName);
		if (true == UContentsHelper::IsFlagDown)
		{
			StateChange(EPlayState::FinishReverse);
			return;
		}
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
	MoveUpdate(_DeltaTime);
	JumpVector = FVector::Zero;
	MoveVector = FVector::Right * FinsihWalkSpeed;
}

void AMario::BossFinish(float _DeltaTime)
{
	if (CurBossFinishTime >= BossFinishTime)
	{
		MoveVector.X = 0.0f;
		JumpVector.Y = 0.0f;
		GravityVector.Y = 0.0f;
		StateChange(EPlayState::BossFinishWalk);
		return;
	}
	else
	{
		CurBossFinishTime += _DeltaTime;
	}
}

void AMario::BossFinishWalk(float _DeltaTime)
{
	MoveVector = FVector::Right * 200.0f;
	MoveUpdate(_DeltaTime);
}

void AMario::MoveUpdate(float _DeltaTime)
{
	GroundUp();
	FVector MarioPos = GetActorLocation();
	Color8Bit ColorLeft = UContentsHelper::MapColImage->GetColor(MarioPos.iX() - 12, MarioPos.iY(), Color8Bit::MagentaA);
	Color8Bit ColorRight = UContentsHelper::MapColImage->GetColor(MarioPos.iX() + 12, MarioPos.iY(), Color8Bit::MagentaA);
	if (ColorLeft != Color8Bit::MagentaA && ColorRight != Color8Bit::MagentaA && false == IsCollision)
	{
		GravityVector += FVector::Down * GravityAcc * _DeltaTime;
	}
	else
	{
		IsGround = true;
		GravityVector = FVector::Zero;
		JumpVector = FVector::Zero;
	}

	FVector CurCameraPos = GetWorld()->GetCameraPos();
	FVector NextMarioPos = MarioPos + (MoveVector * _DeltaTime);
	float Center = GEngine->MainWindow.GetWindowScale().hX();
	float ScaleX = GEngine->MainWindow.GetWindowScale().X;
	if
		(
			false == IsHiddenStage &&
			CurCameraPos.X + Center < NextMarioPos.X &&
			CurCameraPos.X + ScaleX <= UContentsHelper::MapColImage->GetScale().X &&
			false == UContentsHelper::IsBossStage
			)
	{
		if (MoveVector.X > 0)
		{
			GetWorld()->AddCameraPos(MoveVector * _DeltaTime);
		}
	}
	if (CurCameraPos.X + 20.0f >= NextMarioPos.X)
	{
		MoveVector = FVector::Zero;
	}

	WallUp();

	TotalForceVector = MoveVector + JumpVector + GravityVector;
	AddActorLocation(TotalForceVector * _DeltaTime);
}

void AMario::DieCheck()
{
	Color8Bit DieColor = UContentsHelper::MapColImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::YellowA);
	if (Color8Bit(255, 255, 0, 0) == DieColor)
	{
		SizeState = EMarioSizeState::Small;
		StateChange(EPlayState::Die);
		return;
	}
}

void AMario::GroundUp()
{
	if (false == IsStageEnd)
	{
		while (true)
		{
			FVector Location = GetActorLocation();
			Location.Y -= 1.0f;
			Color8Bit ColorLeft = UContentsHelper::MapColImage->GetColor(Location.iX() - 12, Location.iY(), Color8Bit::MagentaA);
			Color8Bit ColorRight = UContentsHelper::MapColImage->GetColor(Location.iX() + 12, Location.iY(), Color8Bit::MagentaA);
			if (ColorLeft == Color8Bit(255, 0, 255, 0) || ColorRight == Color8Bit(255, 0, 255, 0))
			{
				AddActorLocation(FVector::Up);
			}
			else
			{
				break;
			}
		}
	}
}

void AMario::WallUp()
{
	FVector CheckPos = GetActorLocation();
	Color8Bit ColorBottomLeft = UContentsHelper::MapColImage->GetColor(CheckPos.iX() - 16, CheckPos.iY() - 5, Color8Bit::MagentaA);
	Color8Bit ColorTopLeft = UContentsHelper::MapColImage->GetColor(CheckPos.iX() - 16, CheckPos.iY() - 30, Color8Bit::MagentaA);
	Color8Bit ColorBottomRight = UContentsHelper::MapColImage->GetColor(CheckPos.iX() + 16, CheckPos.iY() - 5, Color8Bit::MagentaA);
	Color8Bit ColorTopRight = UContentsHelper::MapColImage->GetColor(CheckPos.iX() + 16, CheckPos.iY() - 30, Color8Bit::MagentaA);
	float CamerPos = GetWorld()->GetCameraPos().X;
	if (ColorBottomLeft == Color8Bit(255, 0, 255, 0) || ColorTopLeft == Color8Bit(255, 0, 255, 0))
	{
		AddActorLocation(FVector::Right);
		MoveVector = FVector::Zero;
	}
	else if (ColorBottomRight == Color8Bit(255, 0, 255, 0) || ColorTopRight == Color8Bit(255, 0, 255, 0))
	{
		AddActorLocation(FVector::Left);
		MoveVector = FVector::Zero;
	}
}

