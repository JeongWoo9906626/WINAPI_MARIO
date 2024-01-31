#pragma once
#include <EngineBase\EngineDebug.h>
#include <EngineBase\EngineString.h>
#include <EngineBase\EngineTime.h>

#include <EnginePlatform\EngineWindow.h>
#include <EnginePlatform\EngineInput.h>
#include <map>


class ULevel;
// ���� : DeltaTime����, ������ �������� ���� ����ϴ� Ŭ���� 
// (������Ʈ, �ʱ� ����, �Ҹ�, ���� ����, ���� ����, ������ ����)
class UEngineCore
{
public:
	~UEngineCore();

	// delete Function
	UEngineCore(const UEngineCore& _Other) = delete;
	UEngineCore(UEngineCore&& _Other) noexcept = delete;
	UEngineCore& operator=(const UEngineCore& _Other) = delete;
	UEngineCore& operator=(UEngineCore&& _Other) noexcept = delete;

	// ������ â ��ü
	UEngineWindow MainWindow;
	// �ð��� �����ϴ� Ŭ���� ��ü
	EngineTime MainTimer;

	/// <summary>
	/// ������ �����ϴ� ����
	/// </summary>
	/// <param name="_hInstance">HINSTANCE</param>
	/// <param name="_UserCore">������ �ھ�</param>
	static void EngineStart(HINSTANCE _hInstance, UEngineCore* _UserCore);

	/// <summary>
	/// �ھ� ���� �Լ�
	/// </summary>
	/// <param name="_Init">HINSTANCE</param>
	void CoreInit(HINSTANCE _Init);

	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);
	virtual void End();

	/// <summary>
	/// ������ �����ϴ� �Լ�
	/// </summary>
	/// <typeparam name="LevelType">������ ������ Ÿ��(Ŭ����)</typeparam>
	/// <param name="_Name">������ �̸�</param>
	template<typename LevelType>
	void CreateLevel(std::string_view _Name)
	{
		std::string UpperName = UEngineString::ToUpper(_Name);

		if (true == AllLevel.contains(UpperName))
		{
			MsgBoxAssert(std::string(_Name) + "�̶�� �̸��� Level�� �� ������� �߽��ϴ�");
		}

		LevelType* NewLevel = new LevelType();
		LevelInit(NewLevel);
		AllLevel.insert(std::pair<std::string, ULevel*>(UpperName, NewLevel));
	}

	/// <summary>
	///  ������ �����ϴ� �Լ�
	/// </summary>
	/// <param name="_Name">������ ������ �̸�</param>
	void ChangeLevel(std::string_view _Name);

	/// <summary>
	/// Frame �����ϴ� �Լ�
	/// </summary>
	/// <param name="_Frame">������ ������</param>
	void SetFrame(int _Frame)
	{
		Frame = _Frame;
		FrameTime = 1 / static_cast<float>(Frame);
	}

protected:
	/// <summary>
	/// �ƹ��� �����Ű�� �ȵǱ� ������ Protected
	/// </summary>
	UEngineCore();

private:
	// ������
	int Frame = -1;
	// ������ ���ư��� �ð�
	float FrameTime = 0.0f;
	// ���� ������ �ð�
	float CurFrameTime = 0.0f;
	// ������ �ʱ�ȭ�� 1���� �ϱ� ���� bool ������ Ȯ���ϱ� ���� ���� ����
	bool EngineInit = false;

	// ������ �����ϴ� map(key : ������ �̸�)
	std::map<std::string, ULevel*> AllLevel;
	// ���� ����
	ULevel* CurLevel = nullptr;

	/// <summary>
	/// Engine Update �Լ�
	/// </summary>
	static void EngineTick();
	/// <summary>
	/// Engine ���� �Լ�
	/// </summary>
	static void EngineEnd();

	/// <summary>
	/// DeltaTime ����ϰ� ������ ������Ʈ �ϴ� �Լ�
	/// </summary>
	void CoreTick();

	/// <summary>
	/// ������ Update�� �����ϴ� �Լ�
	/// </summary>
	/// <param name="_Level">������ ����</param>
	void LevelInit(ULevel* _Level);
};

// �ش� Ŭ������ include�� �ϸ� ��𼭵� Ŭ������ ��ü�� ����ϰ� �ϱ� ���� ���� ������ ����
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