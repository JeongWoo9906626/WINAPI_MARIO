#pragma once
#include "NameObject.h"
#include "EnginePath.h"

// ���� : ��θ� ������ Object
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
	///	��� ����
	/// </summary>
	/// <param name="_View">��� (Path)</param>
	void SetPath(std::string_view _View)
	{
		Path = _View;
	}
	
	/// <summary>
	/// string ������ Path ����
	/// </summary>
	/// <returns></returns>
	std::string GetPath()
	{
		return Path;
	}
	
	/// <summary>
	/// std::filesystem::paht�� Path ����
	/// </summary>
	/// <returns></returns>
	UEnginePath GetEnginePath()
	{
		return UEnginePath(std::filesystem::path(Path));
	}

protected:

private:
	// ���
	std::string Path;
};

