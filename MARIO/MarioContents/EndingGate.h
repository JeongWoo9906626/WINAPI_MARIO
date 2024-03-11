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
	UImageRenderer* Text = nullptr;
	UImageRenderer* UIBox = nullptr;

	UCollision* Collision = nullptr;

	bool IsEndingMessage = false;
	float CurTime = 0.0f;
	float Time = 1.0f;
};

