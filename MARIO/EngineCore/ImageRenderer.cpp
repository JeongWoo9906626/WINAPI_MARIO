#include "ImageRenderer.h"
#include "EngineCore.h"
#include "Actor.h"
#include "Level.h"
#include <EngineCore\EngineResourcesManager.h>

UImageRenderer::UImageRenderer()
{
}

UImageRenderer::~UImageRenderer()
{
}

void UImageRenderer::SetOrder(int _Order)
{
	AActor* Owner = GetOwner();
	ULevel* Level = Owner->GetWorld();

	std::map<int, std::list<UImageRenderer*>>& Renderers = Level->Renderers;
	Renderers[GetOrder()].remove(this);
	
	UTickObject::SetOrder(_Order);
	Renderers[GetOrder()].push_back(this);
}

void UImageRenderer::Render(float _DeltaTime)
{
	if (nullptr == Image)
	{
		MsgBoxAssert("이미지가 존재하지 않는 랜더러 입니다");
	}

	if (nullptr != CurAnimation)
	{
		Image = CurAnimation->Image;
		InfoIndex = CurAnimation->Update(_DeltaTime);
	}

	// 렌더러의 위치
	FTransform RendererTrans = GetTransform();
	// 액터의 위치(부모)
	FTransform ActorTrans = GetOwner()->GetTransform();

	// 컴포넌트의 위치는 부모에게서 상대적
	// 출력시에는 부모의 위치를 더해줘야 한다.
	RendererTrans.AddPosition(ActorTrans.GetPosition());

	EWIndowImageType ImageType = Image->GetImageType();

	switch (ImageType)
	{
	case EWIndowImageType::IMG_BMP:
		GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, RendererTrans, InfoIndex, TransColor);
		break;
	case EWIndowImageType::IMG_PNG:
		// 투명 처리
		GEngine->MainWindow.GetBackBufferImage()->AlphaCopy(Image, RendererTrans, InfoIndex, TransColor);
		break;
	default:
		MsgBoxAssert("투명처리가 불가능한 이미지 입니다.");
		break;
	}

	GEngine->MainWindow.GetWindowImage()->TransCopy(Image, RendererTrans, InfoIndex);
}

void UImageRenderer::CreateAnimation(std::string_view _AnimationName, std::string_view _ImageName, int _Start, int _End, float _Inter, bool _Loop)
{
	UWindowImage* FindImage = UEngineResourcesManager::GetInst().FindImg(_ImageName);
	if (nullptr == FindImage)
	{
		MsgBoxAssert(std::string(_ImageName) + "이미지가 존재하지 않습니다.");
		return;
	}

	std::string UpperAniName = UEngineString::ToUpper(_AnimationName);
	if (true == AnimationInfos.contains(UpperAniName))
	{
		MsgBoxAssert(std::string(UpperAniName) + "라는 이름의 애니메이션이 이미 존재합니다.");
		return;
	}

	UAnimationInfo& Info = AnimationInfos[UpperAniName];
	Info.Image = FindImage;
	Info.CurFrame = 0;
	Info.Start = _Start;
	Info.End = _End;
	Info.CurFrame = 0.0f;
	Info.Loop = _Loop;

	int Size = Info.End - Info.Start;
	Info.Times.reserve(Size);
	Info.Indexs.reserve(Size);
	
	for (int i = _Start; i <= _End; i++)
	{
		Info.Times.push_back(_Inter);
	}
	for (int i = _Start; i <= _End; i++)
	{
		Info.Indexs.push_back(i);
	}
}

void UImageRenderer::ChangeAnimation(std::string_view _AnimationName)
{
	std::string UpperAniName = UEngineString::ToUpper(_AnimationName);
	if (false == AnimationInfos.contains(UpperAniName))
	{
		MsgBoxAssert(std::string(UpperAniName) + "라는 이름의 애니메이션이 존재하지 않습니다.");
		return;
	}

	UAnimationInfo& Info = AnimationInfos[UpperAniName];
	CurAnimation = &Info;
	CurAnimation->CurFrame = 0;
	CurAnimation->CurTime = CurAnimation->Times[0];
}

void UImageRenderer::AnimationReset()
{
	CurAnimation = nullptr;
}

void UImageRenderer::BeginPlay()
{
	USceneComponent::BeginPlay();
}

void UImageRenderer::SetImage(std::string_view _Name, int _InfoIndex)
{
	// 이미지 설정
	Image = UEngineResourcesManager::GetInst().FindImg(_Name);

	// 설정 했는데 이미지가 없을 경우
	if (nullptr == Image)
	{
		MsgBoxAssert(std::string(_Name) + "이미지가 존재하지 않습니다.");
		return;
	}

	InfoIndex = _InfoIndex;
}

int UAnimationInfo::Update(float _DeltaTime)
{
	CurTime -= _DeltaTime;

	if (0.0f >= CurTime)
	{
		CurTime = Times[CurFrame];
		++CurFrame;
	}

	if (Indexs.size() <= CurFrame)
	{
		if (true == Loop)
		{
			CurFrame = 0;
		}
		else
		{
			--CurFrame;
		}
	}

	int Index = Indexs[CurFrame];

	return Index;
}
