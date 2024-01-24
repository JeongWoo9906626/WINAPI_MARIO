#pragma once
#include <EngineCore\Level.h>

class UPlayerLevel : public ULevel
{
public:
	UPlayerLevel();
	~UPlayerLevel();

	UPlayerLevel(const UPlayerLevel& _Other) = delete;
	UPlayerLevel(UPlayerLevel&& _Other) noexcept = delete;
	UPlayerLevel& operator=(const UPlayerLevel& _Other) = delete;
	UPlayerLevel& operator=(UPlayerLevel&& _Other) noexcept = delete;
protected:

private:

};

