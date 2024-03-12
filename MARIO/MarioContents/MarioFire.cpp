#include "MarioFire.h"

AMarioFire::AMarioFire()
{
}

AMarioFire::~AMarioFire()
{
}

void AMarioFire::BeginPlay()
{
	AActor::BeginPlay();

	FireRenderer = CreateImageRenderer(ERenderOrder::Fire);
	FireRenderer->SetImage("Fire.png");
	FireRenderer->SetTransform({ { 0, 0 }, { 128, 128 } });
	FireRenderer->CreateAnimation("FireShot", "Fire.png", 0, 3, 0.1f, true);
	FireRenderer->CreateAnimation("FireBomb", "FireBomb.png", 0, 2, 0.1f, false);

	BombRenderer = CreateImageRenderer(ERenderOrder::Fire);
	BombRenderer->SetImage("FireBomb.png");
	BombRenderer->SetTransform({ { 0, 0 }, { 256, 256 } });
	BombRenderer->CreateAnimation("FireBomb", "FireBomb.png", 0, 2, 0.1f, false);
	BombRenderer->ActiveOff();

	Collision = CreateCollision(ECollisionOrder::Fire);
	Collision->SetColType(ECollisionType::CirCle);
	Collision->SetTransform({ {0, -10}, {20, 20} });

	UContentsHelper::MarioFireCount++;
	FireRenderer->ChangeAnimation("FireShot");
}

void AMarioFire::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	
	if (true == IsDestroy)
	{
		DestroyStart(_DeltaTime);
	}
	else
	{
		MoveUpdate(_DeltaTime);
	}
}

void AMarioFire::MoveUpdate(float _DeltaTime)
{
	CheckWindowPosition();

	float UnitDir = 0.0f;
	float CheckPos = 0.0f;
	switch (Dir)
	{
	case EActorDir::Left:
	{
		UnitDir = -1.0f;
		CheckPos = -5.0f;
		break;
	}
	case EActorDir::Right:
	{
		UnitDir = 1.0f;
		CheckPos = 5.0f;
		break;
	}
	default:
		break;
	}

	Color8Bit Color = UContentsHelper::MapColImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY() - 5, Color8Bit::MagentaA);
	if (Color == Color8Bit(255, 0, 255, 0))
	{
		CurJumpPower = JumpPower;
	}

	Color8Bit ColorX = UContentsHelper::MapColImage->GetColor(GetActorLocation().iX() + CheckPos, GetActorLocation().iY() - 10, Color8Bit::MagentaA);
	if (ColorX == Color8Bit(255, 0, 255, 0))
	{
		SetIsDestroy(true);
	}

	CurJumpPower += GravityAcc * _DeltaTime;
	AddActorLocation({ UnitDir * MoveSpeed * _DeltaTime , CurJumpPower * _DeltaTime });
}

void AMarioFire::SetDir(EActorDir _Dir)
{
	Dir = _Dir;
}

void AMarioFire::SetIsDestroy(bool _IsDestroy)
{
	IsDestroy = _IsDestroy;
}

void AMarioFire::DestroyStart(float _DeltaTime)
{
	FireRenderer->ActiveOff();
	BombRenderer->ActiveOn();

	if (CurDestroyTime >= DestroyTime)
	{
		UContentsHelper::MarioFireCount--;
		Destroy();
	}
	else
	{
		CurDestroyTime += _DeltaTime;
		CurJumpPower = 0.0f;
		MoveSpeed = 0.0f;
	}
}

void AMarioFire::CheckWindowPosition()
{
	FVector CurPosition = GetActorLocation();
	FVector CameraPos = GetWorld()->GetCameraPos();
	if (CameraPos.X >= CurPosition.X)
	{
		UContentsHelper::MarioFireCount--;
		Destroy();
	}
}