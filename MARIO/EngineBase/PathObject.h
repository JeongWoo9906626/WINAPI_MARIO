#pragma once
#include "NameObject.h"
#include "EnginePath.h"

// 설명 : 경로를 가지는 Object
class UPathObject : public UNameObject
{
public:
	UPathObject();
	~UPathObject();

	UPathObject(const UPathObject& _Other) = delete;
	UPathObject(UPathObject&& _Other) noexcept = delete;
	UPathObject& operator=(const UPathObject& _Other) = delete;
	UPathObject& operator=(UPathObject&& _Other) noexcept = delete;

	/// <summary>
	///	경로 설정
	/// </summary>
	/// <param name="_View">경로 (Path)</param>
	void SetPath(std::string_view _View)
	{
		Path = _View;
	}
	
	/// <summary>
	/// string 형식의 Path 리턴
	/// </summary>
	/// <returns></returns>
	std::string GetPath()
	{
		return Path;
	}
	
	/// <summary>
	/// std::filesystem::paht의 Path 리턴
	/// </summary>
	/// <returns></returns>
	UEnginePath GetEnginePath()
	{
		return UEnginePath(std::filesystem::path(Path));
	}

protected:

private:
	// 경로
	std::string Path;
};

