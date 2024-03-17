#pragma once
#include <EngineCore/Level.h>
#include <EnginePlatform/EngineSound.h>

class UGameOverLevel : public ULevel
{
public:
	UGameOverLevel();
	~UGameOverLevel();

	UGameOverLevel(const UGameOverLevel& _Other) = delete;
	UGameOverLevel(UGameOverLevel&& _Other) noexcept = delete;
	UGameOverLevel& operator=(const UGameOverLevel& _Other) = delete;
	UGameOverLevel& operator=(UGameOverLevel&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

private:
	UEngineSoundPlayer SoundPlayer;
	float ChangeTime = 3.5f;
	float CurChangeTime = 0.0f;
};

