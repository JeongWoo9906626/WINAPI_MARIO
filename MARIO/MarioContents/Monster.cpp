#include "Monster.h"
#include "MarioFire.h"
#include "Mario.h"

AMonster::AMonster()
{
}

AMonster::~AMonster()
{
}

void AMonster::SetHitCount(int _HitCount)
{
	HitCount = _HitCount;
}

void AMonster::BeginPlay()
{
	AActor::BeginPlay();
}

void AMonster::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (true == IsWindowOut)
	{
		Destroy();
	}

	std::vector<UCollision*> BoxTopResult;
	if (true == BottomCollision->CollisionCheck(ECollisionOrder::BoxTop, BoxTopResult))
	{
		IsBoxCollision = true;
	}
	else
	{
		IsBoxCollision = false;
	}

	std::vector<UCollision*> MarioFireResult;
	if (true == Collision->CollisionCheck(ECollisionOrder::Fire, MarioFireResult))
	{
		UCollision* MarioFireCollision = MarioFireResult[0];
		AMarioFire* MarioFire = static_cast<AMarioFire*>(MarioFireCollision->GetOwner());
		MarioFire->SetIsDestroy(true);
		HitCount--;

		if (0 == HitCount)
		{
			StateChange(EMonsterState::SpinDead);
			return;
		}
	}

	std::vector<UCollision*> MarioKillResult;
	if (true == HeadCollision->CollisionCheck(ECollisionOrder::Player, MarioKillResult))
	{
		UCollision* MarioCollision = MarioKillResult[0];
		AMario* Mario = static_cast<AMario*>(MarioCollision->GetOwner());
		Mario->StateChange(EPlayState::Kill);
		StateChange(EMonsterState::HeadHit);
		return;
	}

	std::vector<UCollision*> TroopaResult;
	if (true == Collision->CollisionCheck(ECollisionOrder::Troopa, TroopaResult))
	{
		StateChange(EMonsterState::SpinDead);
		return;
	}

	std::vector<UCollision*> MarioResult;
	if (true == Collision->CollisionCheck(ECollisionOrder::Player, MarioResult))
	{
		UCollision* MarioCollision = MarioResult[0];
		AMario* Mario = static_cast<AMario*>(MarioCollision->GetOwner());

		if (Mario->SizeState != EMarioSizeState::Small)
		{
			Mario->SizeState = EMarioSizeState::Small;
			Mario->StateChange(EPlayState::GrowDown);
			return;
		}
		else
		{
			Mario->StateChange(EPlayState::Die);
			return;
		}
	}

	std::vector<UCollision*> MonsterResult;
	if (true == Collision->CollisionCheck(ECollisionOrder::Monster, MonsterResult))
	{
		UCollision* MonsterCollision = MonsterResult[0];
		AMonster* Monster = static_cast<AMonster*>(MonsterCollision->GetOwner());

		if (Monster->DirState == EActorDir::Left)
		{
			Monster->ChangeDir();
			Monster->AddActorLocation(FVector::Right);
			ChangeDir();
			AddActorLocation(FVector::Left);
		}
		else
		{
			Monster->ChangeDir();
			Monster->AddActorLocation(FVector::Left);
			ChangeDir();
			AddActorLocation(FVector::Right);
		}
		return;
	}

	WindowCheck();
	StateUpdate(_DeltaTime);
}

void AMonster::StateChange(EMonsterState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EMonsterState::Move:
			MoveStart();
			break;
		case EMonsterState::SpinDead:
			SpinDeadStart();
			break;
		case EMonsterState::HeadHit:
			HeadHitStart();
			break;
		}
	}
	State = _State;
}

void AMonster::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EMonsterState::Move:
		Move(_DeltaTime);
		break;
	case EMonsterState::SpinDead:
		SpinDead(_DeltaTime);
		break;
	case EMonsterState::HeadHit:
		HeadHit(_DeltaTime);
		break;
	}
}

void AMonster::ChangeDir()
{
	IsDirChange = true;
	if (EActorDir::Left == DirState)
	{
		DirState = EActorDir::Right;
	}
	else
	{
		DirState = EActorDir::Left;
	}
}

void AMonster::WindowCheck()
{
	FVector CurPosition = GetActorLocation();
	FVector CameraPos = GetWorld()->GetCameraPos();
	if (CameraPos.X >= CurPosition.X)
	{
		IsWindowOut = true;
	}
}

void AMonster::MoveStart()
{
	Collision->ActiveOn();
	HeadCollision->ActiveOn();
}

void AMonster::SpinDeadStart()
{
	Collision->ActiveOff();
	HeadCollision->ActiveOff();
	BottomCollision->ActiveOff();

	UContentsHelper::Score += KillScore;
}

void AMonster::HeadHitStart()
{
	Collision->ActiveOff();
	HeadCollision->ActiveOff();

	UContentsHelper::Score += KillScore;
}

void AMonster::Move(float _DeltaTime)
{
	if (false == IsBoxCollision)
	{
		GravityMove(_DeltaTime);
	}

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
		ChangeDir();
	}

	float UnitDir = 0.0f;
	switch (DirState)
	{
	case EActorDir::Left:
		UnitDir = -1.0f;
		break;
	case EActorDir::Right:
		UnitDir = 1.0f;
		break;
	}

	AddActorLocation({ UnitDir * MoveSpeed * _DeltaTime, 0.0f });
}

void AMonster::SpinDead(float _DeltaTime)
{

}

void AMonster::HeadHit(float _DeltaTime)
{

}

void AMonster::GravityMove(float _DeltaTime)
{
	Color8Bit Color = UContentsHelper::MapColImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		GravityAcc = 0.0f;
	}
	else
	{
		AddActorLocation(FVector::Down * GravityAcc * _DeltaTime);
	}
}