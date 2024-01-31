#pragma once
#include <Windows.h>
#include <string>
#include <EngineBase\EngineMath.h>

class UWindowImage;
// ���� : Window â Ŭ����
class UEngineWindow
{
public:
	// constrcuter destructer
	UEngineWindow();
	~UEngineWindow();

	// delete Function
	UEngineWindow(const UEngineWindow& _Other) = delete;
	UEngineWindow(UEngineWindow&& _Other) noexcept = delete;
	UEngineWindow& operator=(const UEngineWindow& _Other) = delete;
	UEngineWindow& operator=(UEngineWindow&& _Other) noexcept = delete;

	/// <summary>
	/// ������ â �����ϴ� �Լ�
	/// </summary>
	/// <param name="_Title">������ ������ â �̸�</param>
	void Open(std::string_view _Title = "Title");

	/// <summary>
	/// HINSTANCE �ʱ�ȭ �Լ�
	/// </summary>
	/// <param name="_hInst"></param>
	static void Init(HINSTANCE _hInst);

	/// <summary>
	/// ������ �޽��� ���� �Լ�
	/// </summary>
	/// <param name="_Update">������Ʈ �� �� ����� Update �Լ� ������</param>
	/// <param name="_End">������ �� ����� End �Լ� ������</param>
	/// <returns></returns>
	static unsigned __int64 WindowMessageLoop(void(*_Update)(), void(*_End)());

	/// <summary>
	/// �̹��� ��ȯ �Լ�
	/// </summary>
	/// <returns></returns>
	UWindowImage* GetWindowImage()
	{
		return WindowImage;
	}

	/// <summary>
	/// ����� �̹��� ��ȯ �Լ�
	/// </summary>
	/// <returns></returns>
	UWindowImage* GetBackBufferImage()
	{
		return BackBufferImage;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="_Pos"></param>
	void SetWindowPosition(const FVector& _Pos);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="_Scale"></param>
	void SetWindowSclale(const FVector& _Scale);

	/// <summary>
	/// 
	/// </summary>
	void ScreenClear();
	/// <summary>
	/// 
	/// </summary>
	void ScreenUpdate();

protected:

private:
	// ������ â ������Ʈ ����
	static bool WindowLive;

	// HINSTANCE
	static HINSTANCE hInstance;

	/// <summary>
	/// �޽��� �ݹ� �Լ�
	/// </summary>
	/// <param name="">HWND</param>
	/// <param name="">UINT</param>
	/// <param name="">WPARAM</param>
	/// <param name="">LPARAM</param>
	/// <returns></returns>
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	// ������ �ڵ�
	HWND hWnd = nullptr;

	// �̹���
	UWindowImage* WindowImage = nullptr;

	// ����� �̹��� (������ ���� ��µ� �̹����� �޾Ƽ� �����ϴ� �뵵)
	UWindowImage* BackBufferImage = nullptr;

	// �̹��� ũ��
	FVector Scale;
};

