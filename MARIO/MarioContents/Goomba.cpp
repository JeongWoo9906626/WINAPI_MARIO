#include "Goomba.h"
#include "Mario.h"
#include "Troopa.h"
#include "MarioFire.h"

AGoomba::AGoomba()
{
}

AGoomba::~AGoomba()
{
}

void AGoomba::BeginPlay()
{
	AMonster::BeginPlay();

	{
		Renderer = CreateImageRenderer(ERenderOrder::Monster);
		Renderer->SetImage("OpenWorldGoomba.png");
		Renderer->SetTransform({ { 0, 0 }, { 256 * 1.3f, 256 * 1.3f } });
	}

	{
		Renderer->CreateAnimation("GoombaDie", "OpenWorldGoomba.png", 2, 2, 0.1f, true);
		Renderer->CreateAnimation("GoombaMove", "OpenWorldGoomba.png", 0, 1, 0.2f, true);
	}

	{
		Collision = CreateCollision(ECollisionOrder::Monster);
		Collision->SetColType(ECollisionType::Rect);
		Collision->SetPosition({ 0, -20 });
		Collision->SetScale({ 40, 30 });
	}

	{
		HeadCollision = CreateCollision(ECollisionOrder::MonsterHead);
		HeadCollision->SetColType(ECollisionType::Rect);
		HeadCollision->SetPosition({ 0, -50 });
		HeadCollision->SetScale({ 30, 10 });
	}

	{
		BottomCollision = CreateCollision(ECollisionOrder::MonsterBottom);
		BottomCollision->SetColType(ECollisionType::Rect);
		BottomCollision->SetPosition({ 0, 0 });
		BottomCollision->SetScale({ 30, 10 });
	}


	StateChange(EMonsterState::Move);
}

void AGoomba::Tick(float _DeltaTime)
{
	AMonster::Tick(_DeltaTime);
	
	StateUpdate(_DeltaTime);
}

void AGoomba::StateChange(EMonsterState _State)
{
	AMonster::StateChange(_State);
}

void AGoomba::StateUpdate(float _DeltaTime)
{
	AMonster::StateUpdate(_DeltaTime);
}

void AGoomba::MoveStart()
{
	AMonster::MoveStart();
	Renderer->ChangeAnimation("GoombaMove");
}

void AGoomba::HeadHitStart()
{
	AMonster::HeadHitStart();
	Renderer->ChangeAnimation("GoombaDie");
}

void AGoomba::Move(float _DeltaTime)
{
	AMonster::Move(_DeltaTime);
}

void AGoomba::HeadHit(float _DeltaTime)
{
	AMonster::HeadHit(_DeltaTime);

	Destroy(DestroyTime);
}
