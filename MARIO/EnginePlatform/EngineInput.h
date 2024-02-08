#pragma once
#include <Windows.h>
#include <map>
#include <EngineBase\EngineDebug.h>

// ���� : �Է� ó�� Ŭ����
class EngineInput
{
	friend class InputInitCreator;

private:
	// ���� : Ű Ŭ����
	class EngineKey
	{
		friend EngineInput;

	public:
		// ���� ����
		bool Down = false;
		// ��� ������ �ִ� ����
		bool Press = false;
		// ���� ����
		bool Up = false; 
		// ������ ���� �ʴ� ����
		bool Free = true; 

		// ���� �ð�
		float PressTime = 0.0f;

		// �Է� Ű
		int Key = -1; // VK_LBUTTON

		/// <summary>
		/// Ű�� ���� üũ�ϴ� �Լ�
		/// </summary>
		void KeyCheck();

		EngineKey()
		{
		}

		EngineKey(int _Key)
			: Key(_Key)
		{
		}
	};

public:
	// constrcuter destructer
	EngineInput();
	~EngineInput();

	// delete Function
	EngineInput(const EngineInput& _Other) = delete;
	EngineInput(EngineInput&& _Other) noexcept = delete;
	EngineInput& operator=(const EngineInput& _Other) = delete;
	EngineInput& operator=(EngineInput&& _Other) noexcept = delete;

	/// <summary>
	/// Ű�� Down ���¸� ��ȯ�ϴ� �Լ�
	/// </summary>
	/// <param name="_Key">�Է� Ű</param>
	/// <returns></returns>
	static bool IsDown(int _Key)
	{
		if (false == AllKeys.contains(_Key))
		{
			MsgBoxAssert("�Է¼����� �������� �ʴ� Ű �Դϴ�");
		}

		return AllKeys[_Key].Down;
	}

	/// <summary>
	/// Ű�� Press ���¸� ��ȯ�ϴ� �Լ�
	/// </summary>
	/// <param name="_Key">�Է� Ű</param>
	/// <returns></returns>
	static bool IsPress(int _Key)
	{
		if (false == AllKeys.contains(_Key))
		{
			MsgBoxAssert("�Է¼����� �������� �ʴ� Ű �Դϴ�");
		}

		return AllKeys[_Key].Press;
	}

	/// <summary>
	/// Ű�� UP ���¸� ��ȯ�ϴ� �Լ�
	/// </summary>
	/// <param name="_Key">�Է� Ű</param>
	/// <returns></returns>
	static bool IsUp(int _Key)
	{
		if (false == AllKeys.contains(_Key))
		{
			MsgBoxAssert("�Է¼����� �������� �ʴ� Ű �Դϴ�");
		}

		return AllKeys[_Key].Up;
	}

	/// <summary>
	/// Ű�� Free ���¸� ��ȯ�ϴ� �Լ�
	/// </summary>
	/// <param name="_Key">�Է� Ű</param>
	/// <returns></returns>
	static bool IsFree(int _Key)
	{
		if (false == AllKeys.contains(_Key))
		{
			MsgBoxAssert("�Է¼����� �������� �ʴ� Ű �Դϴ�");
		}

		return AllKeys[_Key].Free;
	}

	static bool IsAnyKeyDown()
	{
		return AnyKeyDown;
	}

	static bool IsAnyKeyPress()
	{
		return AnyKeyPress;
	}

	static bool IsAnyKeyUp()
	{
		return AnyKeyUp;
	}

	static bool IsAnyKeyFree()
	{
		return AnyKeyFree;
	}


	/// <summary>
	/// Ű�� ���� ������Ʈ �Լ�
	/// </summary>
	/// <param name="_DeltaTime"></param>
	static void KeyCheckTick(float _DeltaTime);

protected:
	// �����Ǵ� Ű ����
	static std::map<int, EngineKey> AllKeys;

	static bool AnyKeyDown;
	static bool AnyKeyPress;
	static bool AnyKeyUp;
	static bool AnyKeyFree;

private:
	/// <summary>
	/// Ű ���� �Լ�
	/// </summary>
	static void InputInit();
};

