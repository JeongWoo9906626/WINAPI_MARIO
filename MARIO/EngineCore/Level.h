#pragma once
#include <EngineBase\NameObject.h>
#include <EngineBase\EngineMath.h>
#include <map>
#include <list>

class AActor;
class UEngineCore;
class UImageRenderer;

// ���� : ������ ��Ÿ���� Ŭ����
class ULevel : public UNameObject
{
	friend UEngineCore;
	friend UImageRenderer;

public:
	ULevel();
	~ULevel();

	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	virtual void BeginPlay() {};
	virtual void Tick(float _DeltaTime) {};

	/// <summary>
	/// ������ ������ �� �ؾ��� �� (���� �������� �޾ƿ� ��?)
	/// </summary>
	/// <param name="_PrevLevel">���� ����</param>
	virtual void LevelStart(ULevel* _PrevLevel) {};

	/// <summary>
	/// ������ ������ �� �ؾ��� �� (���� ������ ������ ��?)
	/// </summary>
	/// <param name="_NextLevel">���� ����</param>
	virtual void LevelEnd(ULevel* _NextLevel) {};

	/// <summary>
	/// ���� ����
	/// </summary>
	/// <typeparam name="ActorType">���� Ŭ����</typeparam>
	/// <param name="_Order">������ ����</param>
	/// <returns></returns>
	template<typename ActorType>
	ActorType* SpawnActor(int _Order = 0)
	{
		ActorType* NewActor = new ActorType();
		ActorInit(NewActor);
		AllActor[_Order].push_back(NewActor);
		return NewActor;
	}

	void SetCameraPos(FVector _CameraPos)
	{
		CameraPos = _CameraPos;
	}


	void AddCameraPos(FVector _CameraPos)
	{
		CameraPos += _CameraPos;
	}

	FVector GetCameraPos()
	{
		return CameraPos;
	}

protected:

private:
	// ������ ���ϴ� ���͸� �����ϴ� map
	std::map<int, std::list<AActor*>> AllActor;
	
	// ������ �ؾ��ϴ� �̹����� �����ϴ� map
	std::map<int, std::list<UImageRenderer*>> Renderers;


	FVector CameraPos = FVector::Zero;

	/// <summary>
	/// ���� �ʱ� ����(���� ����, ���� ��ü�� ����)
	/// </summary>
	/// <param name="_NewActor"></param>
	void ActorInit(AActor* _NewActor);
	
	/// <summary>
	/// ������ ���ϴ� ��� ��(Renderer, Actor) ������Ʈ
	/// </summary>
	/// <param name="_DeltaTime"></param>
	void LevelTick(float _DeltaTime);
	
	/// <summary>
	/// ������ ���ϴ� ��� ��(Renderer, Actor) ������
	/// </summary>
	/// <param name="_DeltaTime"></param>
	void LevelRender(float _DeltaTime);

	/// <summary>
	/// ������ ���ϴ� ��� ��(Renderer, Actor) ������
	/// </summary>
	/// <param name="_DeltaTime"></param>
	void LevelRelease(float _DeltaTime);
};

