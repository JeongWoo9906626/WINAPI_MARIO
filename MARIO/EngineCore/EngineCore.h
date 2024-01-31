#pragma once
#include <EngineBase\EngineDebug.h>
#include <EngineBase\EngineString.h>
#include <EngineBase\EngineTime.h>

#include <EnginePlatform\EngineWindow.h>
#include <EnginePlatform\EngineInput.h>
#include <map>


class ULevel;
// 설명 : DeltaTime측정, 엔진의 전반적인 업무 담당하는 클래스 
// (업데이트, 초기 설정, 소멸, 레벨 생성, 레벨 변경, 프레임 설정)
class UEngineCore
{
public:
	~UEngineCore();

	// delete Function
	UEngineCore(const UEngineCore& _Other) = delete;
	UEngineCore(UEngineCore&& _Other) noexcept = delete;
	UEngineCore& operator=(const UEngineCore& _Other) = delete;
	UEngineCore& operator=(UEngineCore&& _Other) noexcept = delete;

	// 윈도우 창 객체
	UEngineWindow MainWindow;
	// 시간을 측정하는 클래스 객체
	EngineTime MainTimer;

	/// <summary>
	/// 엔진을 시작하는 시작
	/// </summary>
	/// <param name="_hInstance">HINSTANCE</param>
	/// <param name="_UserCore">시작할 코어</param>
	static void EngineStart(HINSTANCE _hInstance, UEngineCore* _UserCore);

	/// <summary>
	/// 코어 설정 함수
	/// </summary>
	/// <param name="_Init">HINSTANCE</param>
	void CoreInit(HINSTANCE _Init);

	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);
	virtual void End();

	/// <summary>
	/// 레벨을 생성하는 함수
	/// </summary>
	/// <typeparam name="LevelType">생성할 레벨의 타입(클래스)</typeparam>
	/// <param name="_Name">레벨의 이름</param>
	template<typename LevelType>
	void CreateLevel(std::string_view _Name)
	{
		std::string UpperName = UEngineString::ToUpper(_Name);

		if (true == AllLevel.contains(UpperName))
		{
			MsgBoxAssert(std::string(_Name) + "이라는 이름의 Level을 또 만들려고 했습니다");
		}

		LevelType* NewLevel = new LevelType();
		LevelInit(NewLevel);
		AllLevel.insert(std::pair<std::string, ULevel*>(UpperName, NewLevel));
	}

	/// <summary>
	///  레벨을 변경하는 함수
	/// </summary>
	/// <param name="_Name">변경할 레벨의 이름</param>
	void ChangeLevel(std::string_view _Name);

	/// <summary>
	/// Frame 설정하는 함수
	/// </summary>
	/// <param name="_Frame">설정할 프레임</param>
	void SetFrame(int _Frame)
	{
		Frame = _Frame;
		FrameTime = 1 / static_cast<float>(Frame);
	}

protected:
	/// <summary>
	/// 아무나 실행시키면 안되기 때문에 Protected
	/// </summary>
	UEngineCore();

private:
	// 프레임
	int Frame = -1;
	// 프레임 돌아가는 시간
	float FrameTime = 0.0f;
	// 현재 프레임 시간
	float CurFrameTime = 0.0f;
	// 엔진의 초기화를 1번만 하기 위해 bool 변수로 확인하기 위해 만든 변수
	bool EngineInit = false;

	// 레벨을 저장하는 map(key : 레벨의 이름)
	std::map<std::string, ULevel*> AllLevel;
	// 현재 레벨
	ULevel* CurLevel = nullptr;

	/// <summary>
	/// Engine Update 함수
	/// </summary>
	static void EngineTick();
	/// <summary>
	/// Engine 종료 함수
	/// </summary>
	static void EngineEnd();

	/// <summary>
	/// DeltaTime 계산하고 레벨을 업데이트 하는 함수
	/// </summary>
	void CoreTick();

	/// <summary>
	/// 레벨의 Update를 실행하는 함수
	/// </summary>
	/// <param name="_Level">실행할 레벨</param>
	void LevelInit(ULevel* _Level);
};

// 해당 클래스를 include만 하면 어디서든 클래스의 객체를 사용하게 하기 위해 전역 변수로 생성
extern UEngineCore* GEngine;


#define ENGINESTART(USERCORE) \
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, \
	_In_opt_ HINSTANCE hPrevInstance, \
	_In_ LPWSTR    lpCmdLine, \
	_In_ int       nCmdShow) \
{ \
    LeakCheck; \
	USERCORE NewUserCore = USERCORE(); \
	EngineCore::EngineStart(hInstance, &NewUserCore); \
}