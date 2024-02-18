#include "Goomba.h"

AGoomba::AGoomba()
{
}

AGoomba::~AGoomba()
{
}

void AGoomba::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(RenderOrder::Monster);
	Renderer->SetImage("Goomba.png");
	Renderer->SetTransform({ { 0, 0 }, { 256, 256 } });

	Renderer->CreateAnimation("GoombaDie", "Goomba.png", 2, 2, true, 0.1f);
	Renderer->CreateAnimation("GoombaMove", "Goomba.png", 0, 1, true, 0.2f);
	
	int a = 0;

	Renderer->ChangeAnimation("GoombaMove");
}

void AGoomba::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	//Renderer->ChangeAnimation("GoombaDie", true);
}
