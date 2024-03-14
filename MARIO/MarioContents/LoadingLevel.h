#pragma once
#include <EngineCore/Level.h>

class ULoadingLevel : public ULevel
{
public:
	ULoadingLevel();
	~ULoadingLevel();

	ULoadingLevel(const ULoadingLevel& _Other) = delete;
	ULoadingLevel(ULoadingLevel&& _Other) noexcept = delete;
	ULoadingLevel& operator=(const ULoadingLevel& _Other) = delete;
	ULoadingLevel& operator=(ULoadingLevel&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

private:

};

