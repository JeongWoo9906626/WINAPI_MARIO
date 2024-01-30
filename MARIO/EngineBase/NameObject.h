#pragma once
#include <string>

// 설명 : 이름 Object
class UNameObject
{
public:
	UNameObject();
	~UNameObject();

	UNameObject(const UNameObject& _Other) = delete;
	UNameObject(UNameObject&& _Other) noexcept = delete;
	UNameObject& operator=(const UNameObject& _Other) = delete;
	UNameObject& operator=(UNameObject&& _Other) noexcept = delete;

	/// <summary>
	/// 이름 설정 함수
	/// </summary>
	/// <param name="_View">이름</param>
	void SetName(std::string_view _View)
	{
		Name = _View;
	}

	/// <summary>
	/// 이름 반환 함수
	/// </summary>
	/// <returns>string Name</returns>
	std::string GetName()
	{
		return Name;
	}

protected:

private:
	// 이름
	std::string Name;
};

