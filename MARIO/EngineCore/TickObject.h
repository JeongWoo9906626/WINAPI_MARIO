#pragma once
#include <Enginebase/EngineDebug.h>

// 설명 : 업데이트가 되는 Object
class UTickObject
{
public:
	UTickObject();
	virtual ~UTickObject();

	UTickObject(const UTickObject& _Other) = delete;
	UTickObject(UTickObject&& _Other) noexcept = delete;
	UTickObject& operator=(const UTickObject& _Other) = delete;
	UTickObject& operator=(UTickObject&& _Other) noexcept = delete;

	/// <summary>
	/// 업데이트 활성화 함수
	/// </summary>
	void ActiveOn()
	{
		IsActiveValue = true;
	}

	/// <summary>
	/// 업데이트 비활성화 함수
	/// </summary>
	void ActiveOff()
	{
		IsActiveValue = false;
	}

	/// <summary>
	/// 업데이트 활성화 설정 함수
	/// </summary>
	/// <param name="_Active">업데이트 활성화 여부</param>
	void SetActive(bool _Active, float _ActiveTime = 0.0f)
	{
		ActiveTime = _ActiveTime;
		
		if (true == _Active && 0.0f == ActiveTime)
		{
			IsActiveValue = _Active;
			return;
		}

		IsActiveValue = false;
	}

	/// <summary>
	/// 업데이트 활성화 여부 리턴 함수
	/// </summary>
	/// <returns></returns>
	bool IsActive()
	{
		return IsActiveValue && IsDestroyValue == false;
	}

	/// <summary>
	/// Object 파괴 함수
	/// </summary>
	/// <param name="_DestroyTime">파괴 되는 시간</param>
	virtual void Destroy(float _DestroyTime = 0.0f)
	{
		IsDestroyUpdate = true;
		DestroyTime = _DestroyTime;
		if (0.0f >= _DestroyTime)
		{
			IsDestroyValue = true;
		}
	}

	/// <summary>
	/// 업데이트 순서 리턴 함수
	/// </summary>
	/// <returns></returns>
	int GetOrder()
	{
		return Order;
	}

	/// <summary>
	/// 업데이트 순서 설정 함수
	/// </summary>
	/// <param name="_Order">순서</param>
	virtual void SetOrder(int _Order)
	{
		Order = _Order;
	}

	virtual void ActiveUpdate(float _DeltaTime)
	{
		ActiveTime -= _DeltaTime;
		if (true == IsActiveUpdate)
		{
			if (0.0f >= ActiveTime)
			{
				IsActiveUpdate = false;
				IsActiveValue = true;
				return;
			}
		}
	}

	/// <summary>
	/// 파괴되는 시간 업데이트 함수
	/// </summary>
	/// <param name="_DeltaTime"></param>
	virtual void DestroyUpdate(float _DeltaTime)
	{
		if (false == IsDestroyUpdate)
		{
			return;
		}

		DestroyTime -= _DeltaTime;
		if (0.0f >= DestroyTime)
		{
			IsDestroyValue = true;
		}
	}

	/// <summary>
	/// Object 파괴 여부 반환 함수
	/// </summary>
	/// <returns></returns>
	bool IsDestroy()
	{
		return IsDestroyValue;
	}

	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);

protected:

private:
	// 순서
	int Order = 0;
	// 파괴 업데이트 여부
	bool IsDestroyUpdate = false;
	// 파괴 시간
	float DestroyTime = 0.0f;
	// 활성화 여부
	bool IsActiveValue = true;
	// Object 파괴 여부
	bool IsDestroyValue = false;
	bool IsActiveUpdate = false;
	float ActiveTime = 0.0f;
};

