#pragma once
#include <string>
#include <string_view>
#include <map>

class UWindowImage;

// 설명 : 게임 리소스 종합 관리 클래스
class UEngineResourcesManager
{
public:
	// delete Function
	UEngineResourcesManager(const UEngineResourcesManager& _Other) = delete;
	UEngineResourcesManager(UEngineResourcesManager&& _Other) noexcept = delete;
	UEngineResourcesManager& operator=(const UEngineResourcesManager& _Other) = delete;
	UEngineResourcesManager& operator=(UEngineResourcesManager&& _Other) noexcept = delete;

	// 싱글톤
	static UEngineResourcesManager& GetInst()
	{
		// 지역static 싱글톤
		static UEngineResourcesManager Inst = UEngineResourcesManager();
		return Inst;
	}

	/// <summary>
	/// 경로에 존재하는 이름에 해당하는 이미지 로드
	/// </summary>
	/// <param name="_Path"></param>
	/// <returns></returns>
	UWindowImage* LoadImg(std::string_view _Path);

	/// <summary>
	/// 경로에 해당 및 이름이 같은 이미지 로드
	/// </summary>
	/// <param name="_Path"></param>
	/// <param name="_Name"></param>
	/// <returns></returns>
	UWindowImage* LoadImg(std::string_view _Path, std::string_view _Name);

	/// <summary>
	/// map에 저장되어 있는 이미지 중에 이름에 해당하는 이미지 찾기
	/// </summary>
	/// <param name="_Name"></param>
	/// <returns></returns>
	UWindowImage* FindImg(std::string_view _Name);

	/// <summary>
	/// 경로에 존재하는 폴더 찾기
	/// </summary>
	/// <param name="_Path"></param>
	/// <returns></returns>
	UWindowImage* LoadFolder(std::string_view _Path);

	/// <summary>
	/// 경로에 해당 및 이름이 같은 폴더 찾기
	/// </summary>
	/// <param name="_Path">경로</param>
	/// <param name="_Name">이름</param>
	/// <returns></returns>
	UWindowImage* LoadFolder(std::string_view _Path, std::string_view _Name);

	/// <summary>
	/// 이미지를 자르는 함수
	/// </summary>
	/// <param name="_Name">사진 이름</param>
	/// <param name="_X">X크기</param>
	/// <param name="_Y">Y크기</param>
	void CuttingImage(std::string_view _Name, int _X, int _Y);

protected:

private:
	// constrcuter destructer
	UEngineResourcesManager();
	~UEngineResourcesManager();

	// 전체 이미지 저장하는 map
	std::map<std::string, UWindowImage*> Images;

};

