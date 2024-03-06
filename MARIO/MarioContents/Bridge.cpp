#include "Bridge.h"

ABridge::ABridge()
{
}

ABridge::~ABridge()
{
}

void ABridge::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(ERenderOrder::Brick);
	Renderer->SetImage("Bridge.png");
	Renderer->SetTransform({ {0, 0}, {64, 64} });

	TopCollision = CreateCollision(ECollisionOrder::Step);
	TopCollision->SetColType(ECollisionType::Rect);
	TopCollision->SetTransform({ {0, -23}, {65, 20} });
}

void ABridge::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

}
