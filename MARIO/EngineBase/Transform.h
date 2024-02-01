#pragma once
#include "EngineMath.h"

// 설명 : 위치와 비율(Scale) 관련 클래스
class FTransform
{
public:
	// constrcuter destructer
	FTransform();
	FTransform(const FVector& _Pos, const FVector& _Scale)
		: Position(_Pos), Scale(_Scale)
	{
	}
	~FTransform();

	// delete Function
	//FTransform(const FTransform& _Other) = delete;
	//FTransform(FTransform&& _Other) noexcept = delete;
	//FTransform& operator=(const FTransform& _Other) = delete;
	//FTransform& operator=(FTransform&& _Other) noexcept = delete;

public:
	/// <summary>
	/// 스케일 설정 함수
	/// </summary>
	/// <param name="_Value">스케일</param>
	void SetScale(FVector _Value)
	{
		Scale = _Value;
	}

	/// <summary>
	/// 스케일 값 리턴 함수
	/// </summary>
	/// <returns></returns>
	FVector GetScale() const
	{
		return Scale;
	}

	/// <summary>
	/// 위치 설정 함수
	/// </summary>
	/// <param name="_Value">위치</param>
	void SetPosition(FVector _Value)
	{
		Position = _Value;
	}

	/// <summary>
	/// 위치 더하는 함수
	/// </summary>
	/// <param name="_Value">더할 위치</param>
	void AddPosition(FVector _Value)
	{
		Position += _Value;
	}

	/// <summary>
	/// 위치 리턴 함수
	/// </summary>
	/// <returns></returns>
	FVector GetPosition() const
	{
		return Position;
	}

	float Left() const
	{
		return Position.X - Scale.hX();
	}
	float Right() const
	{
		return Position.X + Scale.hX();
	}
	float Top() const
	{
		return Position.Y - Scale.hY();
	}
	float Bottom() const
	{
		return Position.Y + Scale.hY();
	}

	int iLeft() const
	{
		return static_cast<int>(Left());
	}
	int iRight() const
	{
		return static_cast<int>(Right());
	}
	int iTop() const
	{
		return static_cast<int>(Top());
	}
	int iBottom() const
	{
		return static_cast<int>(Bottom());
	}

protected:

private:
	// 비율(Scale)
	FVector Scale;
	// 위치(Position)
	FVector Position;
};

