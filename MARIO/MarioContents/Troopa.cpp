#include "Troopa.h"
#include "Mario.h"

ATurtle::ATurtle()
{
}

ATurtle::~ATurtle()
{
}

void ATurtle::BeginPlay()
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

void ATurtle::Tick(float _DeltaTime)
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
					&& Collision.GetPosition().X + 32.0f >= MyTransform.GetPosition().X - 32.0f
					&& Collision.GetPosition().X - 32.0f <= MyTransform.GetPosition().X + 32.0f
				)
			{
				StateChange(EMonsterState::Dead);
			}
		}

		if (EMonsterState::Dead == State)
		{
			if
				(
					Collision.GetPosition().X + 32.0f >= MyTransform.GetPosition().X - 32.0f
					&& Collision.GetPosition().X - 32.0f <= MyTransform.GetPosition().X + 32.0f
				)
			{
				StateChange(EMonsterState::Shoot);
				return;
			}
		}
	}

	StateUpdate(_DeltaTime);
}

void ATurtle::StateChange(EMonsterState _State)
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
		case EMonsterState::Wake:
			WakeStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void ATurtle::StateUpdate(float _DeltaTime)
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

void ATurtle::DirCheck()
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

void ATurtle::AnimationCheck(EActorDir _Dir)
{
	if (_Dir != DirState)
	{
		DirState = _Dir;
		std::string Name = GetAnimationName(CurAnimationName);
		Renderer->ChangeAnimation(Name, true, Renderer->GetCurAnimationFrame(), Renderer->GetCurAnimationTime());
	}
}

std::string ATurtle::GetAnimationName(std::string _Name)
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

void ATurtle::MoveStart()
{
	DeadValue = false;
	DirCheck();
	Renderer->ChangeAnimation(GetAnimationName("Troopa_Move"));
}

void ATurtle::DeadStart()
{
	DeadValue = true;
	Renderer->ChangeAnimation("TroopaHide");
}

void ATurtle::ShootStart()
{

}

void ATurtle::WakeStart()
{
	DeadValue = false;
	Renderer->ChangeAnimation("TroopaWake");
}

void ATurtle::Move(float _DeltaTime)
{
}

void ATurtle::Dead(float _DeltaTime)
{
}

void ATurtle::Shoot(float _DeltaTime)
{
}

void ATurtle::Wake(float _DeltaTime)
{
}
