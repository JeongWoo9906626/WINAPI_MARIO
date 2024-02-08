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
	/// ������ â ��ȯ �Լ�
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
	/// ������ â�� ��ġ ���� �Լ�
	/// </summary>
	/// <param name="_Pos">��ġ</param>
	void SetWindowPosition(const FVector& _Pos);

	/// <summary>
	/// ������ â�� ũ�� ���� �Լ�
	/// </summary>
	/// <param name="_Scale">ũ��</param>
	void SetWindowScale(const FVector& _Scale);

	/// <summary>
	/// â�� ����� �Լ�(�ܻ����� �̹��� ���)
	/// </summary>
	void ScreenClear();
	/// <summary>
	/// ����� �̹����� ��ġ�� ũ�� ������Ʈ�ϰ� �׸��� �Լ�
	/// </summary>
	void ScreenUpdate();

	/// <summary>
	/// ������ ũ�� ��ȯ
	/// </summary>
	/// <returns></returns>
	FVector GetWindowScale()
	{
		return Scale;
	}
	
	void SetClearColor(Color8Bit _Color)
	{
		_Color.A = 0;
		ClearColor = _Color;
	}


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

	Color8Bit ClearColor = Color8Bit::WhiteA;

	// ������ �ڵ�
	HWND hWnd = nullptr;

	// ������ â �̹���
	UWindowImage* WindowImage = nullptr;

	// ����� �̹��� (������ ���� ��µ� �̹����� �޾Ƽ� �����ϴ� �뵵)
	UWindowImage* BackBufferImage = nullptr;

	// ������ â �̹��� ũ��
	FVector Scale;
	// ������ â ��ġ
	FVector Position;
};

