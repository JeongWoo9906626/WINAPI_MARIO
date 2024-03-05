#include "BirdgeHandle.h"

ABirdgeHandle::ABirdgeHandle()
{
}

ABirdgeHandle::~ABirdgeHandle()
{
}

void ABirdgeHandle::BeginPlay()
{
	AActor::BeginPlay();

	Collision = CreateCollision(ECollisionOrder::Box);
	Collision->SetColType(ECollisionType::Rect);
	Collision->SetTransform({ { 0,0 }, { 50, 50 } });
}

void ABirdgeHandle::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> MarioResult;
	if (true == Collision->CollisionCheck(ECollisionOrder::Player, MarioResult))
	{
		// TODO : �ٸ� �μ����� �����
		int a = 0;
	}

}