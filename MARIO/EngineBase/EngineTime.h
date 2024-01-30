#pragma once
#include <Windows.h>

// ���� : CPU�� �ð� ���� Ŭ����
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
	/// �ð� ���� �����ϴ� �Լ�
	/// </summary>
	void TimeCheckStart();

	/// <summary>
	/// ���� �ð��� �����ϴ� �Լ�
	/// </summary>
	/// <returns></returns>
	float TimeCheck();

protected:

private:
	// �ʴ� �� �� �ִ� ��
	LARGE_INTEGER Count;
	// ���� �ð�
	LARGE_INTEGER PrevTime;
	// ���� �ð�
	LARGE_INTEGER CurTime;
	// �ʴ� �� �� �ִ� �� (LARGE_INTEGER->Double)
	double dCount;
	// �帥 �ð� (CurTime - PrevTime)
	double DeltaTime;
};

