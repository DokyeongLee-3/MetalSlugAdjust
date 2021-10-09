#pragma once

#include "../Resource/AnimationSequence.h"


// AnimationInfo는 Animation 클래스에서만 들고 있기 때문에
// 공유되지 않는다 -> CSharedPtr 사용 X
struct AnimationInfo
{
	// AnimationSequence는 공유되니까(by ResourceManager,
	// CSceneResource, AnimationInfo) SharedPtr을 사용
	CSharedPtr<CAnimationSequence> Sequence;
	// 현재 애니메이션이 몇번째 프레임을 렌더링중인지
	int Frame;
	// 이번 프레임 시작하고 얼마나 지났는지
	float Time;
	// 각 프레임별 시간
	float FrameTime;
	// 모션 한번 돌때 필요한 시간
	float PlayTime;
	// 재생 배율
	float PlayScale;
	bool Loop;
	bool Reverse;

	AnimationInfo() :
		Frame(0),
		Time(0.f),
		FrameTime(0.f),
		PlayTime(0.f),
		Loop(false),
		Reverse(false)
	{
	}
	
	~AnimationInfo()
	{
	}

};