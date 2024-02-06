#pragma once
#include <EngineBase\NameObject.h>
#include <EngineBase\EngineMath.h>
#include <map>
#include <list>

class AActor;
class UEngineCore;
class UImageRenderer;

// 설명 : 레벨을 나타내는 클래스
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
	/// 레벨이 시작할 때 해야할 일 (이전 레벨에서 받아올 것?)
	/// </summary>
	/// <param name="_PrevLevel">이전 레벨</param>
	virtual void LevelStart(ULevel* _PrevLevel) {};

	/// <summary>
	/// 레벨이 끝났을 때 해야할 일 (다음 레벨에 전달할 것?)
	/// </summary>
	/// <param name="_NextLevel">다음 레벨</param>
	virtual void LevelEnd(ULevel* _NextLevel) {};

	/// <summary>
	/// 액터 생성
	/// </summary>
	/// <typeparam name="ActorType">액터 클래스</typeparam>
	/// <param name="_Order">랜더링 순서</param>
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
	// 레벨에 속하는 액터를 저장하는 map
	std::map<int, std::list<AActor*>> AllActor;
	
	// 랜더링 해야하는 이미지를 저장하는 map
	std::map<int, std::list<UImageRenderer*>> Renderers;


	FVector CameraPos = FVector::Zero;

	/// <summary>
	/// 액터 초기 설정(레벨 설정, 액터 객체의 설정)
	/// </summary>
	/// <param name="_NewActor"></param>
	void ActorInit(AActor* _NewActor);
	
	/// <summary>
	/// 레벨에 속하는 모든 것(Renderer, Actor) 업데이트
	/// </summary>
	/// <param name="_DeltaTime"></param>
	void LevelTick(float _DeltaTime);
	
	/// <summary>
	/// 레벨에 속하는 모든 것(Renderer, Actor) 랜더링
	/// </summary>
	/// <param name="_DeltaTime"></param>
	void LevelRender(float _DeltaTime);

	/// <summary>
	/// 레벨에 속하는 모든 것(Renderer, Actor) 릴리즈
	/// </summary>
	/// <param name="_DeltaTime"></param>
	void LevelRelease(float _DeltaTime);
};

