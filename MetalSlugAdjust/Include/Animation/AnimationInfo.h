#pragma once

#include "../Resource/AnimationSequence.h"


// AnimationInfo�� Animation Ŭ���������� ��� �ֱ� ������
// �������� �ʴ´� -> CSharedPtr ��� X
struct AnimationInfo
{
	// AnimationSequence�� �����Ǵϱ�(by ResourceManager,
	// CSceneResource, AnimationInfo) SharedPtr�� ���
	CSharedPtr<CAnimationSequence> Sequence;
	// ���� �ִϸ��̼��� ���° �������� ������������
	int Frame;
	// �̹� ������ �����ϰ� �󸶳� ��������
	float Time;
	// �� �����Ӻ� �ð�
	float FrameTime;
	// ��� �ѹ� ���� �ʿ��� �ð�
	float PlayTime;
	// ��� ����
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