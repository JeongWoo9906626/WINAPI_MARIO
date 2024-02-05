#include <Windows.h>
#include <EngineCore\EngineCore.h>
#include <EnginePlatform\EngineWindow.h>
#include <Contents_MARIO/MarioContentsCore.h>

//ENGINESTART(ContentsCore)

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	LeakCheck;
	UMarioContentsCore NewMarioCore = UMarioContentsCore();
	NewMarioCore.EngineStart(hInstance);
}