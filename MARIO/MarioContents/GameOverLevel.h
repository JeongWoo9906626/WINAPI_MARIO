#pragma once
#include <EngineCore/Level.h>

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
	float ChangeTime = 2.0f;
	float CurChangeTime = 0.0f;
};

