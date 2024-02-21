#include "Troopa.h"
#include "Mario.h"

ATroopa::ATroopa()
{
}

ATroopa::~ATroopa()
{
}

void ATroopa::BeginPlay()
{
	AActor::BeginPlay();

	{
		Renderer = CreateImageRenderer(ERenderOrder::Monster);
		Renderer->SetImage("OpenWorldTroopa_Left.png");
		Renderer->SetTransform({ {0, 0}, {128 * 1.3f, 128 * 1.3f} });
	}

	{
		Renderer->CreateAnimation("Troopa_Move_Left", "OpenWorldTroopa_Left.png", 0, 1, 0.1f, true);
		Renderer->CreateAnimation("Troopa_Move_Right", "OpenWorldTroopa_Right.png", 0, 1, 0.1f, true);

		Renderer->CreateAnimation("TroopaWake", "OpenWorldTroopa_Left.png", 5, 5, 0.1f, true);
		Renderer->CreateAnimation("TroopaHide", "OpenWorldTroopa_Left.png", 4, 4, 0.1f, true);
	}

	{
		BodyCollision = CreateCollision(ECollisionOrder::Monster);
		BodyCollision->SetColType(ECollisionType::Rect);
		BodyCollision->SetPosition({ 0, -30 });
		BodyCollision->SetScale({ 50, 50 });
	}

	StateChange(EMonsterState::Move);
}

void ATroopa::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> Result;
	if (true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		UCollision* MarioPosition = Result[0];
		AMario* Player = (AMario*)MarioPosition->GetOwner();

		FTransform Collision = MarioPosition->GetActorBaseTransform();

		FTransform MyTransform = BodyCollision->GetActorBaseTransform();

		if (EMonsterState::Move == State)
		{
			if
				(
					Collision.GetPosition().Y + 32.0f >= MyTransform.GetPosition().Y - 32.0f
					&& Collision.GetPosition().Y + 32.0f < MyTransform.GetPosition().Y
				)
			{
				Player->StateChange(EPlayState::Kill);
				StateChange(EMonsterState::Dead);
				return;
			}
		}

		if (EMonsterState::Dead == State)
		{
			if 
				(
					Collision.GetPosition().X > MyTransform.GetPosition().X - 32.0f
					&& Collision.GetPosition().X < MyTransform.GetPosition().X
				)
			{
				ShootState = EMonsterShootDir::Left;
				
			}
			else if 
				(
					Collision.GetPosition().X > MyTransform.GetPosition().X
					&& Collision.GetPosition().X < MyTransform.GetPosition().X + 32.0f
				)
			{
				ShootState = EMonsterShootDir::Right;
			}

			StateChange(EMonsterState::Shoot);
			return;
		}
	}

	StateUpdate(_DeltaTime);
}

void ATroopa::StateChange(EMonsterState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EMonsterState::Move:
			MoveStart();
			break;
		case EMonsterState::Dead:
			DeadStart();
			break;
		case EMonsterState::Shoot:
			ShootStart();
			break;
		/*case EMonsterState::Wake:
			WakeStart();
			break;*/
		default:
			break;
		}
	}

	State = _State;
}

void ATroopa::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EMonsterState::Move:
		Move(_DeltaTime);
		break;
	case EMonsterState::Dead:
		Dead(_DeltaTime);
		break;
	case EMonsterState::Shoot:
		Shoot(_DeltaTime);
		break;
	case EMonsterState::Wake:
		Wake(_DeltaTime);
		break;
	default:
		break;
	}

}

void ATroopa::AnimationCheck(EActorDir _Dir)
{
	if (_Dir != DirState)
	{
		DirState = _Dir;
		std::string Name = GetAnimationName(CurAnimationName);
		Renderer->ChangeAnimation(Name, true, Renderer->GetCurAnimationFrame(), Renderer->GetCurAnimationTime());
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
	default:
		break;
	}

	CurAnimationName = _Name;

	return _Name + DirName;
}

void ATroopa::MoveStart()
{
	DeadValue = false;
	Renderer->ChangeAnimation(GetAnimationName("Troopa_Move"));
}

void ATroopa::DeadStart()
{
	DeadValue = true;
	BodyCollision->ActiveOff();
	Renderer->ChangeAnimation("TroopaHide");
}

void ATroopa::ShootStart()
{
	switch (ShootState)
	{
	case EMonsterShootDir::Left:
		DirState = EActorDir::Right;
		break;
	case EMonsterShootDir::Right:
		DirState = EActorDir::Left;
		break;
	default:
		break;
	}
}

void ATroopa::WakeStart()
{
	DeadValue = false;
	BodyCollision->SetPosition({ 0, -30 });
	BodyCollision->SetScale({ 50, 50 });
	Renderer->ChangeAnimation("TroopaWake");
}

void ATroopa::GravityMove(float _DeltaTime)
{
	FVector GravityVector = { 0.0f, 1.0f, 0.0f, 0.0f };
	Color8Bit Color = UContentsHelper::MapColImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		GravityVector = FVector::Zero;
	}
	else
	{
		AddActorLocation(GravityVector * GravitySpeed * _DeltaTime);
	}
}

void ATroopa::Move(float _DeltaTime)
{
	FVector ForwardVector = { 1.0f, 0.0f, 0.0f, 0.0f };
	GravityMove(_DeltaTime);

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
		ChangeDir(DirState);
		Renderer->ChangeAnimation(GetAnimationName("Troopa_Move"));
	}

	if (EActorDir::Left == DirState)
	{
		DirUnitVector = -1.0f;
	}
	else
	{
		DirUnitVector = 1.0f;
	}

	CheckWindowPosition();

	if (true == DestoryValue)
	{
		Destroy();
	}

	AddActorLocation(ForwardVector * DirUnitVector * MoveSpeed * _DeltaTime);
}

void ATroopa::Dead(float _DeltaTime)
{
	BodyCollision->ActiveOn();
	BodyCollision->SetPosition({ 0, -10 });
	BodyCollision->SetScale({ 50, 30 });
	if (WakeUpTime <= CurTime)
	{
		CurTime = 0.0f;
		StateChange(EMonsterState::Wake);
		return;
	}
	if (true == DeadValue)
	{
		CurTime += _DeltaTime;
	}
}

void ATroopa::Shoot(float _DeltaTime)
{
	FVector ForwardVector = { 1.0f, 0.0f, 0.0f, 0.0f };

	GravityMove(_DeltaTime);

	FVector CheckPos = GetActorLocation();
	switch (DirState)
	{
	case EActorDir::Left:
	{
		CheckPos.X -= 32.0f;
		break;
	}
	case EActorDir::Right:
	{
		CheckPos.X += 32.0f;
		break;
	}
	default:
		break;
	}
	CheckPos.Y -= 32.0f;

	Color8Bit Color = UContentsHelper::MapColImage->GetColor(CheckPos.iX(), CheckPos.iY(), Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		ChangeDir(DirState);
	}

	if (EActorDir::Left == DirState)
	{
		DirUnitVector = -1.0f;
	}
	else
	{
		DirUnitVector = 1.0f;
	}

	CheckWindowPosition();

	if (true == DestoryValue)
	{
		Destroy();
	}

	AddActorLocation(ForwardVector * DirUnitVector * ShootSpeed * _DeltaTime);
}

void ATroopa::Wake(float _DeltaTime)
{
	StateChange(EMonsterState::Move);
	return;
}

void ATroopa::ChangeDir(EActorDir _State)
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

void ATroopa::CheckWindowPosition()
{
	FVector CurPosition = GetActorLocation();
	FVector CameraPos = GetWorld()->GetCameraPos();
	if (CameraPos.X >= CurPosition.X)
	{
		DestoryValue = true;
	}
}