#pragma once
#include <Windows.h>
#include <string>
#include <EngineBase\EngineMath.h>

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
	/// 윈도우 창 반환 함수
	/// </summary>
	/// <returns></returns>
	UWindowImage* GetWindowImage()
	{
		return WindowImage;
	}

	/// <summary>
	/// 백버퍼 이미지 반환 함수
	/// </summary>
	/// <returns></returns>
	UWindowImage* GetBackBufferImage()
	{
		return BackBufferImage;
	}

	/// <summary>
	/// 윈도우 창의 위치 설정 함수
	/// </summary>
	/// <param name="_Pos">위치</param>
	void SetWindowPosition(const FVector& _Pos);

	/// <summary>
	/// 윈도우 창의 크기 설정 함수
	/// </summary>
	/// <param name="_Scale">크기</param>
	void SetWindowScale(const FVector& _Scale);

	/// <summary>
	/// 창을 지우는 함수(단색으로 이미지 출력)
	/// </summary>
	void ScreenClear();
	/// <summary>
	/// 백버퍼 이미지의 위치와 크기 업데이트하고 그리는 함수
	/// </summary>
	void ScreenUpdate();

	/// <summary>
	/// 윈도우 크기 반환
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

	Color8Bit ClearColor = Color8Bit::WhiteA;

	// 윈도우 핸들
	HWND hWnd = nullptr;

	// 윈도우 창 이미지
	UWindowImage* WindowImage = nullptr;

	// 백버퍼 이미지 (랜더링 전에 출력된 이미지를 받아서 저장하는 용도)
	UWindowImage* BackBufferImage = nullptr;

	// 윈도우 창 이미지 크기
	FVector Scale;
	// 윈도우 창 위치
	FVector Position;
};

