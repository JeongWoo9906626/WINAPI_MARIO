#pragma once
#include <Windows.h>

// 설명 : CPU의 시간 측정 클래스
class EngineTime
{
public:
	// constrcuter destructer
	EngineTime();
	~EngineTime();

	// delete Function
	EngineTime(const EngineTime& _Other) = delete;
	EngineTime(EngineTime&& _Other) noexcept = delete;
	EngineTime& operator=(const EngineTime& _Other) = delete;
	EngineTime& operator=(EngineTime&& _Other) noexcept = delete;

	/// <summary>
	/// 시간 측정 시작하는 함수
	/// </summary>
	void TimeCheckStart();

	/// <summary>
	/// 현재 시간을 측정하는 함수
	/// </summary>
	/// <returns></returns>
	float TimeCheck();

protected:

private:
	// 초당 셀 수 있는 양
	LARGE_INTEGER Count;
	// 이전 시간
	LARGE_INTEGER PrevTime;
	// 현재 시간
	LARGE_INTEGER CurTime;
	// 초당 셀 수 있는 양 (LARGE_INTEGER->Double)
	double dCount;
	// 흐른 시간 (CurTime - PrevTime)
	double DeltaTime;
};

