#pragma once
#include <string>
#include <string_view>
#include <map>

class UWindowImage;

// ���� : ���� ���ҽ� ���� ���� Ŭ����
class UEngineResourcesManager
{
public:
	// delete Function
	UEngineResourcesManager(const UEngineResourcesManager& _Other) = delete;
	UEngineResourcesManager(UEngineResourcesManager&& _Other) noexcept = delete;
	UEngineResourcesManager& operator=(const UEngineResourcesManager& _Other) = delete;
	UEngineResourcesManager& operator=(UEngineResourcesManager&& _Other) noexcept = delete;

	// �̱���
	static UEngineResourcesManager& GetInst()
	{
		// ����static �̱���
		static UEngineResourcesManager Inst = UEngineResourcesManager();
		return Inst;
	}

	/// <summary>
	/// ��ο� �����ϴ� �̸��� �ش��ϴ� �̹��� �ε�
	/// </summary>
	/// <param name="_Path"></param>
	/// <returns></returns>
	UWindowImage* LoadImg(std::string_view _Path);

	/// <summary>
	/// ��ο� �ش� �� �̸��� ���� �̹��� �ε�
	/// </summary>
	/// <param name="_Path"></param>
	/// <param name="_Name"></param>
	/// <returns></returns>
	UWindowImage* LoadImg(std::string_view _Path, std::string_view _Name);

	/// <summary>
	/// map�� ����Ǿ� �ִ� �̹��� �߿� �̸��� �ش��ϴ� �̹��� ã��
	/// </summary>
	/// <param name="_Name"></param>
	/// <returns></returns>
	UWindowImage* FindImg(std::string_view _Name);

	/// <summary>
	/// ��ο� �����ϴ� ���� ã��
	/// </summary>
	/// <param name="_Path"></param>
	/// <returns></returns>
	UWindowImage* LoadFolder(std::string_view _Path);

	/// <summary>
	/// ��ο� �ش� �� �̸��� ���� ���� ã��
	/// </summary>
	/// <param name="_Path">���</param>
	/// <param name="_Name">�̸�</param>
	/// <returns></returns>
	UWindowImage* LoadFolder(std::string_view _Path, std::string_view _Name);

	/// <summary>
	/// �̹����� �ڸ��� �Լ�
	/// </summary>
	/// <param name="_Name">���� �̸�</param>
	/// <param name="_X">Xũ��</param>
	/// <param name="_Y">Yũ��</param>
	void CuttingImage(std::string_view _Name, int _X, int _Y);

protected:

private:
	// constrcuter destructer
	UEngineResourcesManager();
	~UEngineResourcesManager();

	// ��ü �̹��� �����ϴ� map
	std::map<std::string, UWindowImage*> Images;

};

