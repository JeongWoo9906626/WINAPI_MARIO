#pragma once
#include <EngineCore/EngineCore.h>

class UMarioContentsCore : public UEngineCore
{
public:
	// constrcuter destructer
	UMarioContentsCore();
	~UMarioContentsCore();

	// delete Function
	UMarioContentsCore(const UMarioContentsCore& _Other) = delete;
	UMarioContentsCore(UMarioContentsCore&& _Other) noexcept = delete;
	UMarioContentsCore& operator=(const UMarioContentsCore& _Other) = delete;
	UMarioContentsCore& operator=(UMarioContentsCore&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

