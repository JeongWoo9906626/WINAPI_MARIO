#pragma once
#include <string>
#include "EngineString.h"

// ���� : �̸� Object
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
	/// �̸� ���� �Լ�
	/// </summary>
	/// <param name="_View">�̸�</param>
	void SetName(std::string_view _View)
	{
		Name = UEngineString::ToUpper(_View);
	}

	/// <summary>
	/// �̸� ��ȯ �Լ�
	/// </summary>
	/// <returns>string Name</returns>
	std::string GetName()
	{
		return Name;
	}

protected:

private:
	// �̸�
	std::string Name;
};

