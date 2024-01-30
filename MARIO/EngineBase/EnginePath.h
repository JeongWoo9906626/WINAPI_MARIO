#pragma once
#include <string>
#include <filesystem> 

// ���� : ���� ����� ������ �̵� ó�� Ŭ���� 
class UEnginePath
{
public:
	// constrcuter destructer
	UEnginePath();
	UEnginePath(std::filesystem::path _Path);
	~UEnginePath();

	//// delete Function
	//UEnginePath(const UEnginePath& _Other) = delete;
	//UEnginePath(UEnginePath&& _Other) noexcept = delete;
	//UEnginePath& operator=(const UEnginePath& _Other) = delete;
	//UEnginePath& operator=(UEnginePath&& _Other) noexcept = delete;

	/// <summary>
	/// �������� �ƴ��� ���� �Լ�
	/// </summary>
	/// <returns>���� ����</returns>
	bool IsFile();

	/// <summary>
	/// ���丮���� �ƴ��� ���� �Լ�
	/// </summary>
	/// <returns>���丮 ����</returns>
	bool IsDirectory();

	/// <summary>
	/// ���� ���� ���� ��ȯ �Լ�
	/// </summary>
	/// <returns>���� ���� ����</returns>
	bool IsExists();

	/// <summary>
	/// ���� �̸� ��ȯ �Լ�
	/// </summary>
	/// <returns>FileName</returns>
	std::string GetFileName();

	/// <summary>
	/// Ȯ���� ��ȯ �Լ�
	/// </summary>
	/// <returns>Ext(Ȯ����)</returns>
	std::string GetExtension();

	/// <summary>
	/// ��ü ��� ��ȯ �Լ�
	/// </summary>
	/// <returns>Path(���)</returns>
	std::string GetFullPath()
	{
		return Path.string();
	}

	/// <summary>
	/// ���� ��η� �̵��ϴ� �Լ�
	/// </summary>
	void MoveParent();

	/// <summary>
	/// ���� _Path�� �̵��ϴ� �Լ�
	/// </summary>
	/// <param name="_Path">�̵��� _Path</param>
	void Move(std::string_view _Path);

protected:
	// ���
	std::filesystem::path Path;

private:
};

