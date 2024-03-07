#include "KoopaFire.h"
#include "Mario.h"

AKoopaFire::AKoopaFire()
{
}

AKoopaFire::~AKoopaFire()
{
}

void AKoopaFire::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(ERenderOrder::Fire);
	Renderer->SetImage("Koopa_Left.png");
	Renderer->SetTransform({ {0, 0}, {512, 512} });

	Renderer->CreateAnimation("KoopaFire", "Koopa_Left.png", 6, 7, 0.1f, true);
	Renderer->ChangeAnimation("KoopaFire");

	Collision = CreateCollision(ECollisionOrder::Goomba);
	Collision->SetColType(ECollisionType::Rect);
	Collision->SetTransform({ {0, -20}, {90, 35} });
}

void AKoopaFire::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> MarioResult;
	if (true == Collision->CollisionCheck(ECollisionOrder::Player, MarioResult))
	{
		UCollision* MarioCollision = MarioResult[0];
		AMario* Mario = (AMario*)MarioCollision->GetOwner();

		if (Mario->SizeState != EMarioSizeState::Small)
		{
			Mario->SizeState = EMarioSizeState::Small;
			Mario->StateChange(EPlayState::GrowDown);
			return;
		}
		else
		{
			UContentsHelper::MarioDie = true;
			Mario->StateChange(EPlayState::Die);
			return;
		}
	}

	if (true == CheckWindowPosition())
	{
		Destroy();
		return;
	}
	else
	{
		AddActorLocation(FVector::Left * 100.0f * _DeltaTime);
	}
}

bool AKoopaFire::CheckWindowPosition()
{
	FVector CurPosition = GetActorLocation();
	FVector CameraPos = GetWorld()->GetCameraPos();
	if (CameraPos.X >= CurPosition.X)
	{
		return true;
	}
}