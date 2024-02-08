#pragma once
#include <Windows.h>
#include <map>
#include <EngineBase\EngineDebug.h>

// 설명 : 입력 처리 클래스
class EngineInput
{
	friend class InputInitCreator;

private:
	// 설명 : 키 클래스
	class EngineKey
	{
		friend EngineInput;

	public:
		// 누른 순간
		bool Down = false;
		// 계속 누른고 있는 상태
		bool Press = false;
		// 떼는 순간
		bool Up = false; 
		// 누르고 있지 않는 상태
		bool Free = true; 

		// 누른 시간
		float PressTime = 0.0f;

		// 입력 키
		int Key = -1; // VK_LBUTTON

		/// <summary>
		/// 키의 상태 체크하는 함수
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
	/// 키의 Down 상태를 반환하는 함수
	/// </summary>
	/// <param name="_Key">입력 키</param>
	/// <returns></returns>
	static bool IsDown(int _Key)
	{
		if (false == AllKeys.contains(_Key))
		{
			MsgBoxAssert("입력설정이 존재하지 않는 키 입니다");
		}

		return AllKeys[_Key].Down;
	}

	/// <summary>
	/// 키의 Press 상태를 반환하는 함수
	/// </summary>
	/// <param name="_Key">입력 키</param>
	/// <returns></returns>
	static bool IsPress(int _Key)
	{
		if (false == AllKeys.contains(_Key))
		{
			MsgBoxAssert("입력설정이 존재하지 않는 키 입니다");
		}

		return AllKeys[_Key].Press;
	}

	/// <summary>
	/// 키의 UP 상태를 반환하는 함수
	/// </summary>
	/// <param name="_Key">입력 키</param>
	/// <returns></returns>
	static bool IsUp(int _Key)
	{
		if (false == AllKeys.contains(_Key))
		{
			MsgBoxAssert("입력설정이 존재하지 않는 키 입니다");
		}

		return AllKeys[_Key].Up;
	}

	/// <summary>
	/// 키의 Free 상ㅌ태를 반환하는 함수
	/// </summary>
	/// <param name="_Key">입력 키</param>
	/// <returns></returns>
	static bool IsFree(int _Key)
	{
		if (false == AllKeys.contains(_Key))
		{
			MsgBoxAssert("입력설정이 존재하지 않는 키 입니다");
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
	/// 키의 상태 업데이트 함수
	/// </summary>
	/// <param name="_DeltaTime"></param>
	static void KeyCheckTick(float _DeltaTime);

protected:
	// 설정되는 키 저장
	static std::map<int, EngineKey> AllKeys;

	static bool AnyKeyDown;
	static bool AnyKeyPress;
	static bool AnyKeyUp;
	static bool AnyKeyFree;

private:
	/// <summary>
	/// 키 설정 함수
	/// </summary>
	static void InputInit();
};

