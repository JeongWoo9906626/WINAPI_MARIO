#include "BirdgeHandle.h"
#include "Bridge.h"
#include "Mario.h"
#include "MarioFire.h"
#include "KoopaFire.h"

ABirdgeHandle::ABirdgeHandle()
{
}

ABirdgeHandle::~ABirdgeHandle()
{
}

void ABirdgeHandle::AddBridge(ABridge* _Bridge)
{
	BridgeList.push_front(_Bridge);
}

void ABirdgeHandle::BeginPlay()
{
	AActor::BeginPlay();

	Collision = CreateCollision(ECollisionOrder::Box);
	Collision->SetColType(ECollisionType::Rect);
	Collision->SetTransform({ { 50, -50 }, { 60, 70 } });

	BlockCollision = CreateCollision(ECollisionOrder::BlockGate);
	BlockCollision->SetColType(ECollisionType::Rect);
	BlockCollision->SetTransform({ { 15, -180 }, { 20, 370 } });

	Renderer = CreateImageRenderer(ERenderOrder::Gate);
	Renderer->SetImage("Axe.png");
	Renderer->SetTransform({ { 0, 0 }, { 170, 180 } });
}

void ABirdgeHandle::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> MarioResult;
	if (true == Collision->CollisionCheck(ECollisionOrder::Player, MarioResult) || true == Collision->CollisionCheck(ECollisionOrder::PlayerBottom, MarioResult))
	{
		IsCollision = true;
		UContentsHelper::KoopaDie = true;
		Renderer->ActiveOff();
		Collision->ActiveOff();

		UCollision* MarioCollision = MarioResult[0];
		AMario* Mario = static_cast<AMario*>(MarioCollision->GetOwner());
		Mario->StateChange(EPlayState::BossFinish);
		return;
	}

	if (IsCollision == true)
	{
		UContentsHelper::IsBridgeHandleCollision = true;
		DestroyBridge(_DeltaTime);
	}
}

void ABirdgeHandle::DestroyBridge(float _DeltaTime)
{
	if (Count >= 13)
	{
		IsCollision = false;
		Destroy();
		return;
	}

	if (CurDestroyTime >= DestroyTime)
	{
		++Count;
		CurDestroyTime = 0.0f;
		BridgeList.front()->Destroy();
		BridgeList.pop_front();
	}
	else 
	{
		CurDestroyTime += _DeltaTime;
	}
}
