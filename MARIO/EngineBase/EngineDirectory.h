#pragma once
#include "EnginePath.h"
#include <list>

class UEngineFile;
// ���� : ���丮 Ŭ����
class UEngineDirectory : public UEnginePath
{
public:
	// constrcuter destructer
	UEngineDirectory();
	UEngineDirectory(const UEnginePath& _Path);
	~UEngineDirectory();

	// delete Function
	//UEngineDirectory(const UEngineDirectory& _Other) = delete;
	//UEngineDirectory(UEngineDirectory&& _Other) noexcept = delete;
	//UEngineDirectory& operator=(const UEngineDirectory& _Other) = delete;
	//UEngineDirectory& operator=(UEngineDirectory&& _Other) noexcept = delete;

	/// <summary>
	/// ������ ���� ã���ִ� �Լ� (AllFileRecursive ȣ��)
	/// </summary>
	/// <param name="_Ext">ã�� Ȯ����</param>
	/// <param name="_Rescursive">���� ���� Ž�� ����</param>
	/// <returns>File List</returns>
	std::list<UEngineFile> AllFile(std::vector<std::string> _Ext = std::vector<std::string>(), bool _Recursive = false);

protected:

private:
	/// <summary>
	/// ������ ������ ã���ִ� �Լ�
	/// </summary>
	/// <param name="_Path">������ ã�� ���</param>
	/// <param name="_Result">���� ����Ʈ�� ���� list</param>
	/// <param name="_Ext">ã�� Ȯ����</param>
	/// <param name="_Recursive">���� ���� Ž�� ����</param>
	void AllFileRecursive(const std::string_view _Path, std::list<UEngineFile>& _Result, std::vector<std::string> _Ext = std::vector<std::string>(), bool _Recursive = false);
};

