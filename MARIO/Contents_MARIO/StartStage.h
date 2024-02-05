#pragma once
#include <EngineCore\Level.h>

// Ό³Έν :
class UStartStage : public ULevel
{
public:
	// constrcuter destructer
	UStartStage();
	~UStartStage();

	// delete Function
	UStartStage(const UStartStage& _Other) = delete;
	UStartStage(UStartStage&& _Other) noexcept = delete;
	UStartStage& operator=(const UStartStage& _Other) = delete;
	UStartStage& operator=(UStartStage&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _Level) override;
	void LevelEnd(ULevel* _Level) override;

private:

};
