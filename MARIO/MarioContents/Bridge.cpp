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

}

void ABridge::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

}
