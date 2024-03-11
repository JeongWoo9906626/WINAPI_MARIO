#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class AEndingGate : public AActor
{
public:
	// constrcuter destructer
	AEndingGate(); // 디폴트 생성자
	~AEndingGate(); // 디폴트 소멸자

	// delete Function
	AEndingGate(const AEndingGate& _Other) = delete; // 디폴트 복사 생성자
	AEndingGate(AEndingGate&& _Other) noexcept = delete; 
	AEndingGate& operator=(const AEndingGate& _Other) = delete; // 디폴트 대입 연산자
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

