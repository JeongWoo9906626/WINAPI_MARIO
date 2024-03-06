#include "SpinFire.h"

ASpinFire::ASpinFire() 
{
}

ASpinFire::~ASpinFire() 
{
}

void ASpinFire::SetSpinDir(EActorDir _Dir)
{
	Dir = _Dir;
}

void ASpinFire::BeginPlay()
{
	AActor::BeginPlay();

	for (int i = 0; i < 6; i++)
	{
		Renderer[i] = CreateImageRenderer(ERenderOrder::Monster);
		Renderer[i]->SetImage("Fire.png");
		Renderer[i]->CreateAnimation("Spin", "Fire.png", 0, 3, 0.1f, true);
		Renderer[i]->SetTransform({ { 32.0f * i, 0.0f }, { 256.0f, 256.0f } });
		Renderer[i]->ChangeAnimation("Spin");
	}

	/*for (int i = 0; i < 6; i++)
	{
		Collision[i] = CreateCollision(ECollisionOrder::Goomba);
		Collision[i]->SetColType(ECollisionType::CirCle);

	}*/
}

void ASpinFire::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	FireSpin(_DeltaTime);
}

void ASpinFire::FireSpin(float _DeltaTime)
{
}

