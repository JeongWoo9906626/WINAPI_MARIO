#pragma once
#include <EngineCore/Actor.h>

// ���� :
class ATitleLogo : public AActor
{
public:
	// constrcuter destructer
	ATitleLogo();
	~ATitleLogo();

	// delete Function
	ATitleLogo(const ATitleLogo& _Other) = delete;
	ATitleLogo(ATitleLogo&& _Other) noexcept = delete;
	ATitleLogo& operator=(const ATitleLogo& _Other) = delete;
	ATitleLogo& operator=(ATitleLogo&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void ScoreUpdate();

private:
	UImageRenderer* TimeHideRenderer = nullptr;
	UImageRenderer* HighScoreRenderer[6] = { nullptr, };
};

