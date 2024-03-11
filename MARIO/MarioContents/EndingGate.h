#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class AEndingGate : public AActor
{
public:
	// constrcuter destructer
	AEndingGate(); // ����Ʈ ������
	~AEndingGate(); // ����Ʈ �Ҹ���

	// delete Function
	AEndingGate(const AEndingGate& _Other) = delete; // ����Ʈ ���� ������
	AEndingGate(AEndingGate&& _Other) noexcept = delete; 
	AEndingGate& operator=(const AEndingGate& _Other) = delete; // ����Ʈ ���� ������
	AEndingGate& operator=(AEndingGate&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UCollision* Collision = nullptr;

	float ChangeLevelTime = 1.0f;
	float CurChangeLevelTime = 0.0f;
};

