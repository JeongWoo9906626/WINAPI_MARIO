#pragma once
#include <EngineCore/Level.h>
#include <EnginePlatform/EngineSound.h>

// Ό³Έν :
class UPlayLevel : public ULevel
{
public:
	// constrcuter destructer
	UPlayLevel();
	~UPlayLevel();

	// delete Function
	UPlayLevel(const UPlayLevel& _Other) = delete;
	UPlayLevel(UPlayLevel&& _Other) noexcept = delete;
	UPlayLevel& operator=(const UPlayLevel& _Other) = delete;
	UPlayLevel& operator=(UPlayLevel&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

private:
	UEngineSoundPlayer SoundPlayer;

	bool Spawn1 = false;
	bool Spawn2 = false;
	bool Spawn3 = false;
	bool Spawn4 = false;
	bool Spawn5 = false;
	bool Spawn6 = false;
	bool Spawn7 = false;
	bool Spawn8 = false;
	bool Spawn9 = false;
};