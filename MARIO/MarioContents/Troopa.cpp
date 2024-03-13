#include "Troopa.h"
#include "Mario.h"
#include "MarioFire.h"
#include "Monster.h"

ATroopa::ATroopa()
{
}

ATroopa::~ATroopa()
{
}

void ATroopa::BeginPlay()
{
	AMonster::BeginPlay();

	Renderer = CreateImageRenderer(ERenderOrder::Monster);
	Renderer->SetImage("OpenWorldTroopa_Left.png");
	Renderer->SetTransform({ {0, 0}, {128 * 1.3f, 128 * 1.3f} });

	Renderer->CreateAnimation("Troopa_Move_Left", "OpenWorldTroopa_Left.png", 0, 1, 0.1f, true);
	Renderer->CreateAnimation("Troopa_Move_Right", "OpenWorldTroopa_Right.png", 0, 1, 0.1f, true);

	Renderer->CreateAnimation("TroopaWake", "OpenWorldTroopa_Left.png", 4, 5, 0.2f, true);
	Renderer->CreateAnimation("TroopaHide", "OpenWorldTroopa_Left.png", 4, 4, 0.1f, true);

	Collision = CreateCollision(ECollisionOrder::Monster);
	Collision->SetColType(ECollisionType::Rect);
	Collision->SetPosition({ 0, -30 });
	Collision->SetScale({ 50, 40 });

	HeadCollision = CreateCollision(ECollisionOrder::MonsterHead);
	HeadCollision->SetColType(ECollisionType::Rect);
	HeadCollision->SetPosition({ 0, -60 });
	HeadCollision->SetScale({ 30, 10 });

	BottomCollision = CreateCollision(ECollisionOrder::MonsterBottom);
	BottomCollision->SetColType(ECollisionType::Rect);
	BottomCollision->SetPosition({ 0, 0 });
	BottomCollision->SetScale({ 30, 10 });

	HideLeftCollision = CreateCollision(ECollisionOrder::Troopa);
	HideLeftCollision->SetColType(ECollisionType::Rect);
	HideLeftCollision->SetTransform({ { -15, -20 }, { 25, 30 } });

	HideRightCollision = CreateCollision(ECollisionOrder::Troopa);
	HideRightCollision->SetColType(ECollisionType::Rect);
	HideRightCollision->SetTransform({ { 15, -20 }, { 25, 30 } });

	StateChange(EMonsterState::Move);
}

void ATroopa::Tick(float _DeltaTime)
{
	AMonster::Tick(_DeltaTime);

	if (EMonsterState::Shoot == State)
	{
		std::vector<UCollision*> MarioResult;
		if (true == HideLeftCollision->CollisionCheck(ECollisionOrder::Player, MarioResult) || true == HideRightCollision->CollisionCheck(ECollisionOrder::Player, MarioResult))
		{
			UCollision* MarioCollision = MarioResult[0];
			AMario* Mario = static_cast<AMario*>(MarioCollision->GetOwner());

			if (Mario->SizeState != EMarioSizeState::Small)
			{
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
		if (true == HideLeftCollision->CollisionCheck(ECollisionOrder::Monster, MonsterResult) || true == HideRightCollision->CollisionCheck(ECollisionOrder::Player, MarioResult))
		{
			UCollision* MonsterCollision = MonsterResult[0];
			AMonster* Monster = static_cast<AMonster*>(MonsterCollision->GetOwner());

			Monster->StateChange(EMonsterState::SpinDead);
			return;
		}
	}

	if (EMonsterState::HeadHit == State || EMonsterState::Wake == State)
	{
		std::vector<UCollision*> MonsterLeftResult;
		if (true == HideLeftCollision->CollisionCheck(ECollisionOrder::Monster, MonsterLeftResult))
		{
			UCollision* MonsterCollision = MonsterLeftResult[0];
			AMonster* Monster = static_cast<AMonster*>(MonsterCollision->GetOwner());

			Monster->ChangeDir();
			Monster->AddActorLocation(FVector::Left);
			return;
		}

		std::vector<UCollision*> MonsterRightResult;
		if (true == HideRightCollision->CollisionCheck(ECollisionOrder::Monster, MonsterRightResult))
		{
			UCollision* MonsterCollision = MonsterRightResult[0];
			AMonster* Monster = static_cast<AMonster*>(MonsterCollision->GetOwner());

			Monster->ChangeDir();
			Monster->AddActorLocation(FVector::Right);
			return;
		}

		std::vector<UCollision*> ShootLeftResult;
		if (true == HideLeftCollision->CollisionCheck(ECollisionOrder::Player, ShootLeftResult))
		{
			IsShoot = true;
			DirState = EActorDir::Right;
			StateChange(EMonsterState::Shoot);
			return;
		}

		std::vector<UCollision*> ShootRightResult;
		if (true == HideRightCollision->CollisionCheck(ECollisionOrder::Player, ShootRightResult))
		{
			IsShoot = true;
			DirState = EActorDir::Left;
			StateChange(EMonsterState::Shoot);
			return;
		}
	}
	

	StateUpdate(_DeltaTime);
}

void ATroopa::StateChange(EMonsterState _State)
{
	AMonster::StateChange(_State);

	switch (_State)
	{
	case EMonsterState::Shoot:
		ShootStart();
		break;
	case EMonsterState::Wake:
		WakeStart();
		break;
	}

	State = _State;
}

void ATroopa::StateUpdate(float _DeltaTime)
{
	AMonster::StateUpdate(_DeltaTime);

	switch (State)
	{
	case EMonsterState::Shoot:
		Shoot(_DeltaTime);
		break;
	case EMonsterState::Wake:
		Wake(_DeltaTime);
		break;
	}
}

bool ATroopa::AnimationCheck(bool _IsDirChange)
{
	if (true == IsDirChange)
	{
		IsDirChange = false;
		return true;
	}
	else
	{
		return false;
	}
}

std::string ATroopa::GetAnimationName(std::string _Name)
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
	}

	return _Name + DirName;
}

void ATroopa::MoveStart()
{
	AMonster::MoveStart();
	HideLeftCollision->ActiveOff();
	HideRightCollision->ActiveOff();
	Renderer->ChangeAnimation(GetAnimationName("Troopa_Move"));
}

void ATroopa::HeadHitStart()
{
	AMonster::HeadHitStart();
	HideLeftCollision->ActiveOn();
	HideRightCollision->ActiveOn();
	Renderer->ChangeAnimation("TroopaHide");
	Score->SetScore(200);
}

void ATroopa::WakeStart()
{
	Renderer->ChangeAnimation("TroopaWake");
}

void ATroopa::ShootStart()
{
	MoveSpeed = ShootSpeed;
	HideLeftCollision->ActiveOff();
	HideRightCollision->ActiveOff();
	Renderer->ChangeAnimation("TroopaHide");

	Score = GetWorld()->SpawnActor<ScoreUI>(ERenderOrder::UI);
	FVector MonsterLocation = GetActorLocation();
	Score->SetActorLocation(MonsterLocation);
	Score->SetScore(400);
}

void ATroopa::Move(float _DeltaTime)
{
	AMonster::Move(_DeltaTime);

	if (true == AnimationCheck(IsDirChange))
	{
		Renderer->ChangeAnimation(GetAnimationName("Troopa_Move"));
	}
}

void ATroopa::HeadHit(float _DeltaTime)
{
	if (false == IsShoot)
	{
		if (CurHideTime >= HideTime)
		{
			CurHideTime = 0.0f;
			StateChange(EMonsterState::Wake);
			return;
		}
		CurHideTime += _DeltaTime;
	}
}

void ATroopa::Wake(float _DeltaTime)
{
	if (false == IsShoot)
	{
		if (CurWakeTime >= WakeTime)
		{
			CurWakeTime = 0.0f;
			StateChange(EMonsterState::Move);
			return;
		}
		CurWakeTime += _DeltaTime;
	}
}

void ATroopa::Shoot(float _DeltaTime)
{
	AMonster::Move(_DeltaTime);
	
	if (CurNoCollisionTime >= NoCollisionTime)
	{
		HideLeftCollision->ActiveOn();
		HideRightCollision->ActiveOn();
	}
	CurNoCollisionTime += _DeltaTime;
}
