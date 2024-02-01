#pragma once
#include "EnginePath.h"
#include <list>

class UEngineFile;
// 설명 : 디렉토리 클래스
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
	/// 파일을 전부 찾아주는 함수 (AllFileRecursive 호출)
	/// </summary>
	/// <param name="_Ext">찾을 확장자</param>
	/// <param name="_Rescursive">하위 폴더 탐색 여부</param>
	/// <returns>File List</returns>
	std::list<UEngineFile> AllFile(std::vector<std::string> _Ext = std::vector<std::string>(), bool _Recursive = false);

protected:

private:
	/// <summary>
	/// 실제로 파일을 찾아주는 함수
	/// </summary>
	/// <param name="_Path">파일을 찾을 경로</param>
	/// <param name="_Result">파일 리스트를 담을 list</param>
	/// <param name="_Ext">찾을 확장자</param>
	/// <param name="_Recursive">하위 폴더 탐색 여부</param>
	void AllFileRecursive(const std::string_view _Path, std::list<UEngineFile>& _Result, std::vector<std::string> _Ext = std::vector<std::string>(), bool _Recursive = false);
};

