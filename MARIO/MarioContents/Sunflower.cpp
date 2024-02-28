#include "Sunflower.h"
#include "Mario.h"

ASunflower::ASunflower()
{
}

ASunflower::~ASunflower()
{
}

void ASunflower::BeginPlay()
{
	AActor::BeginPlay();

	{
		Renderer = CreateImageRenderer(ERenderOrder::Monster);
		Renderer->SetImage("MarioItem.png");
		Renderer->SetTransform({ { 0, 0 }, { 64 * 1.7f, 64 * 1.7f } });
	}

	{
		BodyCollision = CreateCollision(ECollisionOrder::Goomba);
		BodyCollision->SetColType(ECollisionType::Rect);
		BodyCollision->SetPosition({ 0, -30 });
		BodyCollision->SetScale({ 55, 55 });
	}

	{
		BottomCollision = CreateCollision(ECollisionOrder::Goomba);
		BottomCollision->SetColType(ECollisionType::Rect);
		BottomCollision->SetPosition({ 0, 10 });
		BottomCollision->SetScale({ 30, 3 });
	}

	StateChange(EItemState::Spawn);
}

void ASunflower::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> MarioResult;
	if (true == BodyCollision->CollisionCheck(ECollisionOrder::Player, MarioResult))
	{
		UCollision* MarioPosition = MarioResult[0];
		AMario* Player = (AMario*)MarioPosition->GetOwner();

		Player->SizeState = EMarioSizeState::Big;
		StateChange(EItemState::Eat);
		return;
	}

	std::vector<UCollision*> BoxTopResult;
	if (true == BottomCollision->CollisionCheck(ECollisionOrder::BoxTop, BoxTopResult))
	{
		for (UCollision* BoxPosition : BoxTopResult)
		{
			IsBoxCollision = true;
		}
	}
	else
	{
		IsBoxCollision = false;
	}

	StateUpdate(_DeltaTime);
}

void ASunflower::StateChange(EItemState _State)
{
}

void ASunflower::StateUpdate(float _DeltaTime)
{
}

void ASunflower::SpawnStart()
{
}

void ASunflower::EatStart()
{
}

void ASunflower::Spawn(float _DeltaTime)
{
}
