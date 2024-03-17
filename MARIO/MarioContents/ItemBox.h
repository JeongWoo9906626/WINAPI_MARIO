#pragma once
#include "BrickBase.h"
#include "ContentsHelper.h"

class AItemBox : public ABrickBase
{
public:
	AItemBox();
	~AItemBox();

	AItemBox(const AItemBox& _Other) = delete;
	AItemBox(AItemBox&& _Other) noexcept = delete;
	AItemBox& operator=(const AItemBox& _Other) = delete;
	AItemBox& operator=(AItemBox&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateChange(EBoxState _State) override;
	void StateUpdate(float _DeltaTime) override;

	void IdleStart() override;
	void HitStart() override;
	void BreakStart() override;

	void Idle(float _DeltaTime) override;
	void Hit(float _DeltaTime) override;

private:

};

