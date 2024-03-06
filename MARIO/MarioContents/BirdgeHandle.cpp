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

	Renderer = CreateImageRenderer(ERenderOrder::Item);
	Renderer->SetImage("Axe.png");
	Renderer->SetTransform({ { 0, 0 }, { 64, 64 } });
}

void ABirdgeHandle::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> MarioResult;
	if (true == Collision->CollisionCheck(ECollisionOrder::Player, MarioResult))
	{
		// TODO : 다리 부서지게 만들기
		Destroy();
	}

}
