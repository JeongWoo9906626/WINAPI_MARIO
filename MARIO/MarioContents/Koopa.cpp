#include "Koopa.h"
#include "Mario.h"
#include "KoopaFire.h"

AKoopa::AKoopa()
{
}

AKoopa::~AKoopa()
{
}

void AKoopa::BeginPlay()
{
	AMonster::BeginPlay();

	Renderer = CreateImageRenderer(ERenderOrder::Monster);
	Renderer->SetImage("Koopa_Left.png");
	Renderer->SetTransform({ {0, 0}, {256 * 2.0f, 256 * 2.0f} });

	Renderer->CreateAnimation("Walk_Left", "Koopa_Left.png", 0, 1, 0.1f, true);
	Renderer->CreateAnimation("Die_Left", "Koopa_Left.png", 0, 1, 0.05f, true);
	Renderer->CreateAnimation("Fire_Left", "Koopa_Left.png", 2, 3, 0.1f, false);
	
	Renderer->CreateAnimation("Walk_Right", "Koopa_Right.png", 0, 1, 0.1f, true);
	Renderer->CreateAnimation("Die_Right", "Koopa_Right.png", 0, 1, 0.05f, true);
	Renderer->CreateAnimation("Fire_Right", "Koopa_Right.png", 2, 3, 0.1f, false);

	Collision = CreateCollision(ECollisionOrder::Monster);
	Collision->SetColType(ECollisionType::Rect);
	Collision->SetPosition({ -30, -70 });
	Collision->SetScale({ 140, 140 });

	BottomCollision = CreateCollision(ECollisionOrder::Monster);
	BottomCollision->SetColType(ECollisionType::Rect);
	BottomCollision->SetPosition({ 0, 0 });
	BottomCollision->SetScale({ 10, 10 });

	HitCount = 5;
	SpinDeadScore = 500;

	Renderer->ChangeAnimation(GetAnimationName("Walk"));
	StateChange(EMonsterState::Move);
}

void AKoopa::Tick(float _DeltaTime)
{
	AMonster::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void AKoopa::StateChange(EMonsterState _State)
{
	AMonster::StateChange(_State);

	switch (_State)
	{
	case EMonsterState::Dead:
		DeadStart();
		break;
	case EMonsterState::Fire:
		FireStart();
		break;
	case EMonsterState::Jump:
		JumpStart();
		break;
	}
	State = _State;
}

void AKoopa::StateUpdate(float _DeltaTime)
{
	AMonster::StateUpdate(_DeltaTime);

	switch (State)
	{
	case EMonsterState::Dead:
		Dead(_DeltaTime);
		break;
	case EMonsterState::Fire:
		Fire(_DeltaTime);
		break;
	case EMonsterState::Jump:
		Jump(_DeltaTime);
		break;
	}
}

void AKoopa::MoveStart()
{
	AMonster::MoveStart();

	CheckMarioPos();
	Renderer->ChangeAnimation(GetAnimationName("Walk"));
}

void AKoopa::SpinDeadStart()
{
	AMonster::SpinDeadStart();
}

void AKoopa::DeadStart()
{
	SoundPlayer = UEngineSound::SoundPlay("KoopaFall.mp3");
	Renderer->ChangeAnimation(GetAnimationName("Die"));
}

void AKoopa::FireStart()
{
	CheckMarioPos();
	Renderer->ChangeAnimation(GetAnimationName("Fire"));
}

void AKoopa::JumpStart()
{
	IsBoxCollision = false;
	AddActorLocation(FVector::Up * 10);
	CurJumpTime = 0.0f;
	JumpSpeed = -300.0f;
}

bool AKoopa::CheckMarioPos()
{
	FVector MarioPos = AMario::MainPlayer->GetActorLocation();
	FVector KoopaPos = GetActorLocation();
	std::string AnimationDirName = "";
	if (MarioPos.X < KoopaPos.X)
	{
		if (MarioToKoopa != EActorDir::Left)
		{
			MarioToKoopa = EActorDir::Left;
			return true;
		}
		return false;
	}
	else
	{
		if (MarioToKoopa != EActorDir::Right)
		{
			MarioToKoopa = EActorDir::Right;
			return true;
		}
		return false;
	}
}

void AKoopa::MoveDirChange()
{
	int RandomValue = rand() % 10 + 1;
	if (RandomValue > 5)
	{
		Dir = -1.0f;
	}
	else
	{
		Dir = 1.0f;
	}
}

void AKoopa::Move(float _DeltaTime)
{
	if (true == UContentsHelper::KoopaDie)
	{
		StateChange(EMonsterState::Dead);
		return;
	}

	bool IsDirChange = CheckMarioPos();
	if (true == IsDirChange)
	{
		Renderer->ChangeAnimation(GetAnimationName("Walk"));
	}

	if (true == UContentsHelper::KoopaIsFire && false == UContentsHelper::KoopaDie)
	{
		// 한번만 쏘는 것
		if (false == FirstShot)
		{
			float FirePos = 0.0f;
			FVector KoopaPos = GetActorLocation();

			int RandomValue = rand() % 10 + 1;
			if (RandomValue > 5)
			{
				FirePos = -10.0f;
			}
			else
			{
				FirePos = -100.0f;
			}

			AKoopaFire* KoopaFire = GetWorld()->SpawnActor<AKoopaFire>(ERenderOrder::Fire);
			KoopaFire->SetFireDir(EActorDir::Left);
			KoopaFire->SetActorLocation({ 6550.0f, KoopaPos.Y + FirePos });
			FirstShot = true;
		}

		if (CurFireTime >= FireTime)
		{
			StateChange(EMonsterState::Fire);
			return;
		}
		else
		{
			CurFireTime += _DeltaTime;
		}
	}

	// 쿠파 일정 시간 지나면 점프 및 이동
	if (true == UContentsHelper::KoopaWake && false == UContentsHelper::KoopaDie)
	{
		if (CurJumpTime >= JumpTime)
		{
			StateChange(EMonsterState::Jump);
			return;
			
		}
		if (true == IsBoxCollision)
		{
			CurJumpTime += _DeltaTime;
		}

		

		MoveUpdate(_DeltaTime);
	}
}

void AKoopa::Fire(float _DeltaTime)
{
	float FirePos = 0.0f;
	FVector KoopaPos = GetActorLocation();

	int RandomValue = rand() % 10 + 1;
	if (RandomValue > 5)
	{
		FirePos = -10.0f;
	}
	else
	{
		FirePos = -100.0f;
	}

	if (CurChangeTime >= ChangeTime)
	{
		AKoopaFire* KoopaFire = GetWorld()->SpawnActor<AKoopaFire>(ERenderOrder::Fire);
		KoopaFire->SetFireDir(MarioToKoopa);
		KoopaFire->SetActorLocation({ KoopaPos.X, KoopaPos.Y + FirePos });

		CurFireTime = 0.0f;
		CurChangeTime = 0.0f;
		StateChange(EMonsterState::Move);
		return;
	}
	else
	{
		CurChangeTime += _DeltaTime;
	}
}

void AKoopa::Jump(float _DeltaTime)
{
	MoveUpdate(_DeltaTime);
	if (CurFireTime >= FireTime)
	{
		StateChange(EMonsterState::Fire);
		return;
	}
	else
	{
		CurFireTime += _DeltaTime;
	}

	if (JumpSpeed == 0.0f)
	{
		StateChange(EMonsterState::Move);
		return;
	}
}

void AKoopa::Dead(float _DeltaTime)
{
	if (IsBoxCollision == false)
	{
		AddActorLocation(FVector::Down * GravityAcc * 0.5f * _DeltaTime);
	}
	Color8Bit DieColor = UContentsHelper::MapColImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::YellowA);
	if (DieColor == Color8Bit(255, 255, 0, 0))
	{
		Destroy();
	}
}

void AKoopa::MoveUpdate(float _DeltaTime)
{
	if (CurWalkTime >= WalkTime)
	{
		float KoopaPosX = GetActorLocation().X;
		MoveDirChange();
		KoopaPosX += Dir * 100;
		if (KoopaPosX > FirstKoopaPosX)
		{
			Dir = -1.0f;
		}
		if (KoopaPosX < LastKoopaPosX)
		{
			Dir = 1.0f;
		}
		CurWalkTime = 0.0f;
	}
	else
	{
		CurWalkTime += _DeltaTime;
	}

	if (true == IsBoxCollision)
	{
		JumpSpeed = 0.0f;
	}
	else
	{
		JumpSpeed += GravityAcc * _DeltaTime;
	}
	AddActorLocation({ Dir * WalkSpeed * _DeltaTime, JumpSpeed * _DeltaTime });
}

std::string AKoopa::GetAnimationName(std::string _Name)
{
	std::string AnimationName = "";

	switch (MarioToKoopa)
	{
	case EActorDir::Left:
		AnimationName = "_Left";
		break;
	case EActorDir::Right:
		AnimationName = "_Right";
		break;
	}

	return _Name + AnimationName;
}

