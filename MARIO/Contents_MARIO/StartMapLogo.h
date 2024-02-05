#pragma once
#include <EngineCore\Actor.h>

// Ό³Έν :
class AStartMapLogo : public AActor
{
public:
	// constrcuter destructer
	AStartMapLogo();
	~AStartMapLogo();

	// delete Function
	AStartMapLogo(const AStartMapLogo& _Other) = delete;
	AStartMapLogo(AStartMapLogo&& _Other) noexcept = delete;
	AStartMapLogo& operator=(const AStartMapLogo& _Other) = delete;
	AStartMapLogo& operator=(AStartMapLogo&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};
