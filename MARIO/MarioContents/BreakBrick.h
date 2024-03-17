#pragma once
#include "BrickBase.h"
#include "ContentsHelper.h"

class ABreakBrick : public ABrickBase
{
public:
	ABreakBrick();
	~ABreakBrick();

	ABreakBrick(const ABreakBrick& _Other) = delete;
	ABreakBrick(ABreakBrick&& _Other) noexcept = delete;
	ABreakBrick& operator=(const ABreakBrick& _Other) = delete;
	ABreakBrick& operator=(ABreakBrick&& _Other) noexcept = delete;
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
	void Break(float _DeltaTime) override;

private:

};