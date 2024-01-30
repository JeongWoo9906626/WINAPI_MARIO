#include "EngineString.h"
#include <Windows.h>
#include "EngineDebug.h"

UEngineString::UEngineString()
{
}

UEngineString::~UEngineString()
{
}

std::string UEngineString::ToUpper(std::string_view _View)
{
	std::string Name = _View.data();

	for (char& _Ch : Name)
	{
		_Ch = std::toupper(_Ch);
	}

	return Name;
}

std::wstring UEngineString::AnsiToUniCode(std::string_view _View)
{
	int Size = MultiByteToWideChar(CP_ACP, 0, _View.data(), static_cast<int>(_View.size()), nullptr, 0);
	if (0 == Size)
	{
		MsgBoxAssert("���ڿ� ��ȯ�� �����߰ų� ũ�Ⱑ 0�� ���ڿ��� �־�����ϴ�");
		return L"";
	}
	
	std::wstring Result;
	Result.resize(Size);

	// std::vector<char> Vector;
	// Vector[0] => char&
	// &Vector[0] => *char
	Size = MultiByteToWideChar(CP_ACP, 0, _View.data(), static_cast<int>(_View.size()), &Result[0], Size);

	if (0 == Size)
	{
		MsgBoxAssert("���ڿ� ��ȯ�� �����߰ų� ũ�Ⱑ 0�� ���ڿ��� �־�����ϴ�");
		return L"";
	}

	return Result;
}
