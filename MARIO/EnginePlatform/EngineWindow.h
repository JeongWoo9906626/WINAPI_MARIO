#pragma once
#include <Windows.h>
#include <string>

class UWindowImage;
// 설명 : Window 창 클래스
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
	/// 윈도우 창 생성하는 함수
	/// </summary>
	/// <param name="_Title">생성할 윈도우 창 이름</param>
	void Open(std::string_view _Title = "Title");

	/// <summary>
	/// HINSTANCE 초기화 함수
	/// </summary>
	/// <param name="_hInst"></param>
	static void Init(HINSTANCE _hInst);

	/// <summary>
	/// 윈도우 메시지 루프 함수
	/// </summary>
	/// <param name="_Update">업데이트 될 때 실행될 Update 함수 포인터</param>
	/// <param name="_End">종료할 때 실행될 End 함수 포인터</param>
	/// <returns></returns>
	static unsigned __int64 WindowMessageLoop(void(*_Update)(), void(*_End)());

	/// <summary>
	/// 이미지 반환 함수
	/// </summary>
	/// <returns></returns>
	UWindowImage* GetWindowImage()
	{
		return WindowImage;
	}

protected:

private:
	// 윈도우 창 업데이트 여부
	static bool WindowLive;
	
	// HINSTANCE
	static HINSTANCE hInstance;

	/// <summary>
	/// 메시지 콜백 함수
	/// </summary>
	/// <param name="">HWND</param>
	/// <param name="">UINT</param>
	/// <param name="">WPARAM</param>
	/// <param name="">LPARAM</param>
	/// <returns></returns>
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	// 윈도우 핸들
	HWND hWnd = nullptr;

	// 이미지
	UWindowImage* WindowImage = nullptr;
};

