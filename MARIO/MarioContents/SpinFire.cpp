#include "SpinFire.h"

SpinFire::SpinFire() 
{
}

SpinFire::~SpinFire() 
{
}

void SpinFire::BeginPlay()
{
	AActor::BeginPlay();
}

void SpinFire::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	FireSpin(_DeltaTime);
}

void SpinFire::FireSpin(float _DeltaTime)
{
}

