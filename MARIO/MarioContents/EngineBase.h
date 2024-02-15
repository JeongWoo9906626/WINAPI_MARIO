#pragma once
#include <string>
#include <string_view>

// ���� : ���ڿ� ���� ó�� Ŭ����
class UEngineString
{
public:
	/// <summary>
	/// �빮�ڷ� ��ȯ�ϴ� �Լ�
	/// </summary>
	/// <param name="_View">��ȯ�� ���ڿ�</param>
	/// <returns></returns>
	static std::string ToUpper(std::string_view _View);

	/// <summary>
	/// ��Ƽ ����Ʈ ���ڿ��� ���̵� ����Ʈ ���ڿ��� ��ȯ�ϴ� �Լ�
	/// </summary>
	/// <param name="_View">��ȯ�� ���ڿ�</param>
	/// <returns></returns>
	static std::wstring AnsiToUniCode(std::string_view _View);

protected:

private:
	// constrcuter destructer
	UEngineString();
	~UEngineString();

	// delete Function
	UEngineString(const UEngineString& _Other) = delete;
	UEngineString(UEngineString&& _Other) noexcept = delete;
	UEngineString& operator=(const UEngineString& _Other) = delete;
	UEngineString& operator=(UEngineString&& _Other) noexcept = delete;
};

