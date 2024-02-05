#pragma once
#include <EngineCore\Level.h>

// Ό³Έν :
class UPlayStage : public ULevel
{
public:
	// constrcuter destructer
	UPlayStage();
	~UPlayStage();

	// delete Function
	UPlayStage(const UPlayStage& _Other) = delete;
	UPlayStage(UPlayStage&& _Other) noexcept = delete;
	UPlayStage& operator=(const UPlayStage& _Other) = delete;
	UPlayStage& operator=(UPlayStage&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _Level) override;
	void LevelEnd(ULevel* _Level) override;


private:

};
