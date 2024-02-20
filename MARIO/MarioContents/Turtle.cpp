#include "Turtle.h"

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
		Renderer->SetImage("OpenWorldTroopa.png");
		Renderer->SetTransform({ {0, 0}, {256 * 1.5f, 256 * 1.3f} });
	}

	{
		Renderer->CreateAnimation("TurtleMove", "Turtle.png", 0, 0, 0.1f, true);
		Renderer->CreateAnimation("TurtleStop", "Turtle.png", 0, 0, 0.1f, true);
		Renderer->CreateAnimation("TurtleWake", "Turtle.png", 0, 0, 0.1f, true);
	}

	{
		BodyCollision = CreateCollision(ECollisionOrder::Monster);
		BodyCollision->SetColType(ECollisionType::Rect);
		BodyCollision->SetPosition({ 0, 0 });
		BodyCollision->SetScale({ 100, 100 });
	}
}

void ATurtle::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
