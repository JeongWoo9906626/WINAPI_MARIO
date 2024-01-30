#pragma once
#include <string>
#include <filesystem> 

// 설명 : 파일 경로의 편집과 이동 처리 클래스 
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
	/// 파일인지 아닌지 리턴 함수
	/// </summary>
	/// <returns>파일 여부</returns>
	bool IsFile();

	/// <summary>
	/// 디렉토리인지 아닌지 리턴 함수
	/// </summary>
	/// <returns>디렉토리 여부</returns>
	bool IsDirectory();

	/// <summary>
	/// 파일 존재 여부 반환 함수
	/// </summary>
	/// <returns>파일 존재 여부</returns>
	bool IsExists();

	/// <summary>
	/// 파일 이름 반환 함수
	/// </summary>
	/// <returns>FileName</returns>
	std::string GetFileName();

	/// <summary>
	/// 확장자 반환 함수
	/// </summary>
	/// <returns>Ext(확장자)</returns>
	std::string GetExtension();

	/// <summary>
	/// 전체 경로 반환 함수
	/// </summary>
	/// <returns>Path(경로)</returns>
	std::string GetFullPath()
	{
		return Path.string();
	}

	/// <summary>
	/// 상위 경로로 이동하는 함수
	/// </summary>
	void MoveParent();

	/// <summary>
	/// 지정 _Path로 이동하는 함수
	/// </summary>
	/// <param name="_Path">이동할 _Path</param>
	void Move(std::string_view _Path);

protected:
	// 경로
	std::filesystem::path Path;

private:
};

