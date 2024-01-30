#pragma once
#include <string>
#include <string_view>
#include <map>

class UWindowImage;

class UEngineResourcesManager
{
public:
	// delete Function
	UEngineResourcesManager(const UEngineResourcesManager& _Other) = delete;
	UEngineResourcesManager(UEngineResourcesManager&& _Other) noexcept = delete;
	UEngineResourcesManager& operator=(const UEngineResourcesManager& _Other) = delete;
	UEngineResourcesManager& operator=(UEngineResourcesManager&& _Other) noexcept = delete;

	// ½Ì±ÛÅæ
	static UEngineResourcesManager& GetInst()
	{
		// Áö¿ªstatic ½Ì±ÛÅæ
		static UEngineResourcesManager Inst = UEngineResourcesManager();
		return Inst;
	}

	UWindowImage* LoadImg(std::string_view _Path);
	UWindowImage* LoadImg(std::string_view _Path, std::string_view _Name);
	UWindowImage* FindImg(std::string_view _Name);



protected:

private:
	// constrcuter destructer
	UEngineResourcesManager();
	~UEngineResourcesManager();

	std::map<std::string, UWindowImage*> Images;

};

