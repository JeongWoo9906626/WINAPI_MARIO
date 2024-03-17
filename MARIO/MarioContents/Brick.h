#pragma once

#include "ContentsHelper.h"
#include "BrickBase.h"

class ABrick : public ABrickBase
{
public:
	ABrick();
	~ABrick();

	ABrick(const ABrick& _Other) = delete;
	ABrick(ABrick&& _Other) noexcept = delete;
	ABrick& operator=(const ABrick& _Other) = delete;
	ABrick& operator=(ABrick&& _Other) noexcept = delete;

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
	int HitCount = 5;

};

