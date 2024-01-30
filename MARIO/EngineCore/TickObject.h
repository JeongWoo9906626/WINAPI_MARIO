#pragma once
#include <Enginebase/EngineDebug.h>

// ���� : ������Ʈ�� �Ǵ� Object
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
	/// ������Ʈ Ȱ��ȭ �Լ�
	/// </summary>
	void ActiveOn()
	{
		IsActiveValue = true;
	}

	/// <summary>
	/// ������Ʈ ��Ȱ��ȭ �Լ�
	/// </summary>
	void ActiveOff()
	{
		IsActiveValue = false;
	}

	/// <summary>
	/// ������Ʈ Ȱ��ȭ ���� �Լ�
	/// </summary>
	/// <param name="_Active">������Ʈ Ȱ��ȭ ����</param>
	void SetActive(bool _Active)
	{
		IsActiveValue = _Active;
	}

	/// <summary>
	/// ������Ʈ Ȱ��ȭ ���� ���� �Լ�
	/// </summary>
	/// <returns></returns>
	bool IsActive()
	{
		return IsActiveValue && IsDestroyValue == false;
	}

	/// <summary>
	/// Object �ı� �Լ�
	/// </summary>
	/// <param name="_DestroyTime">�ı� �Ǵ� �ð�</param>
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
	/// ������Ʈ ���� ���� �Լ�
	/// </summary>
	/// <returns></returns>
	int GetOrder()
	{
		return Order;
	}

	/// <summary>
	/// ������Ʈ ���� ���� �Լ�
	/// </summary>
	/// <param name="_Order">����</param>
	virtual void SetOrder(int _Order)
	{
		Order = _Order;
	}

	/// <summary>
	/// �ı��Ǵ� �ð� ������Ʈ �Լ�
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
	/// Object �ı� ���� ��ȯ �Լ�
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
	// ����
	int Order = 0;
	// �ı� ������Ʈ ����
	bool IsDestroyUpdate = false;
	// �ı� �ð�
	float DestroyTime = 0.0f;
	// Ȱ��ȭ ����
	bool IsActiveValue = true;
	// Object �ı� ����
	bool IsDestroyValue = false;
};

