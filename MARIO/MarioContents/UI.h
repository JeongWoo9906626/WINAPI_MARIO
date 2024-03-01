#pragma once
#include <EngineCore/Actor.h>

class AUI : public AActor
{
public:
	// constrcuter destructer
	AUI();
	~AUI();

	// delete Function
	AUI(const AUI& _Other) = delete;
	AUI(AUI&& _Other) noexcept = delete;
	AUI& operator=(const AUI& _Other) = delete;
	AUI& operator=(AUI&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CoinsUpdate();
	void ScroeUpdate();

private:
	UImageRenderer* ScoreRenderer = nullptr;
	UImageRenderer* Coins[2] = { nullptr, };
	UImageRenderer* ScoreArray[6] = { nullptr, };
	UImageRenderer* CoinImage = nullptr;

};
