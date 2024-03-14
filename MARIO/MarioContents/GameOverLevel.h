#pragma once
#include <EngineCore/Level.h>

class GameOverLevel : public ULevel
{
public:
	GameOverLevel();
	~GameOverLevel();

	GameOverLevel(const GameOverLevel& _Other) = delete;
	GameOverLevel(GameOverLevel&& _Other) noexcept = delete;
	GameOverLevel& operator=(const GameOverLevel& _Other) = delete;
	GameOverLevel& operator=(GameOverLevel&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

private:
	float ChangeTime = 2.0f;
	float CurChangeTime = 0.0f;
};

