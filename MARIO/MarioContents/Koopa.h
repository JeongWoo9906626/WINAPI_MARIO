#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"

class AKoopa : public AActor
{
public:
	AKoopa();
	~AKoopa();

	AKoopa(const AKoopa& _Other) = delete;
	AKoopa(AKoopa&& _Other) noexcept = delete;
	AKoopa& operator=(const AKoopa& _Other) = delete;
	AKoopa& operator=(AKoopa&& _Other) noexcept = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void DirCheck();
	void Walk(float _DeltaTime);

	std::string GetAnimationName(std::string _Name);

private:
	UImageRenderer* Renderer = nullptr;
	UCollision* Collision = nullptr;
	UCollision* BottomCollision = nullptr;

	EKoopaState State = EKoopaState::None;
	EActorDir DirState = EActorDir::Left;

	float JumpSpeed = 0.0f;
	float GravitySpeed = 150.0f;
	float WalkSpeed = 100.0f;

	float JumpTime = 1.0f;
	float CurJumpTime = 0.0f;
	float FireTime = 3.5f;
	float CurFireTime = 0.0f;
	float CurChangeTime = 0.0f;
	float ChangeTime = 0.3f;

	int Dir = -1;

	bool IsCollision = false;
	bool IsJump = true;
	bool IsMarioDie = false;
	bool FirstShot = false;
	bool IsRendererChange = false;

	FVector JumpVector = FVector::Zero;
};

// TODO : 쿠파 이동 로직 (X축 범위 지정 및 랜덤하게 이동)
// TODO : 몬스터 죽일 때 100, 200, 1000 UI 생성
// TODO : Troopa가 Hide상태일떄 몬스터 Dir변경
// TODO : Monster클래스 HeadHit상태 변경 및 (Dead상태 추가 해볼것- > 100UI스폰)
// TODO : Stage 이동하기 전 점수 추가
// TODO : 몬스터 MarioFire에 맞을 경우 이미지 뒤집기
// TODO : 깃발 내려오게 하기
// TODO : Item 먹을 때 점수 UI 스폰
// TODO : 마리오 목숨 및 Loading(change Loading) 레벨 생성
// TODO : 쿠파 클래스 리펙토링