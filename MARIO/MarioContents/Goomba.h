#pragma once
#include <EngineCore/Actor.h>

class AGoomba : public AActor
{
public:
	AGoomba();
	~AGoomba();

	AGoomba(const AGoomba& _Other) = delete;
	AGoomba(AGoomba&& _Other) noexcept = delete;
	AGoomba& operator=(const AGoomba& _Other) = delete;
	AGoomba& operator=(AGoomba&& _Other) noexcept = delete;
protected:

private:

};

