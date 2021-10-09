
#include "Animation.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../GameManager.h"

CAnimation::CAnimation()	:
	m_CurrentAnimation(nullptr)
{
}

CAnimation::CAnimation(const CAnimation& Anim)
{
	// Anim�� const ��ü�̹Ƿ� iterator�� const_iterator�� ����ؾ��Ѵ�
	// const iterator�� ++, --�� �����ϴ�(����Ű�� ��ü�� ���ؼ��� ���� �Ұ�)
	std::unordered_map<std::string, AnimationInfo*>::const_iterator iter = Anim.m_mapAnimation.begin();
	std::unordered_map<std::string, AnimationInfo*>::const_iterator iterEnd = Anim.m_mapAnimation.end();
	
	for (; iter != iterEnd; ++iter)
	{
		AnimationInfo* Info = new AnimationInfo;

		Info->Sequence = iter->second->Sequence;
		Info->FrameTime = iter->second->FrameTime;
		Info->PlayTime = iter->second->PlayTime;
		Info->PlayScale = iter->second->PlayScale;
		Info->Loop = iter->second->Loop;
		Info->Reverse = iter->second->Loop;

		// Anim�� ���� �ִ� �������� Sequence�߿�
		// Anim�� ���� �ִϸ��̼��� ���� ���� �ִϸ��̼����� ����
		if (Anim.m_CurrentAnimation->Sequence->GetName() == Info->Sequence->GetName())
			m_CurrentAnimation = Info;

		m_mapAnimation.insert(std::make_pair(iter->first, Info));
	}
}

CAnimation::~CAnimation()
{
	auto iter = m_mapAnimation.begin();
	auto iterEnd = m_mapAnimation.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}

void CAnimation::AddAnimation(
	const std::string& SequenceName,
	bool Loop, float PlayTime,
	float PlayScale, bool Reverse)
{
	// �̹� Sequence�� SceneResource���� load�س����� ���̰�
	// �� �Լ�(AddAnimation)�� Sequence�� load�ǰ� ����
	// CGameObject��(ex.CPlayer, CMonster)�� Init���� 
	// ȣ��� ���̹Ƿ� SceneResource���� �ش� Sequence�� ������
	// ã�� �� ���� ���̴�
	CAnimationSequence* Sequence = m_Scene->GetSceneResource()->FindAnimationSequence(SequenceName);

	if (!Sequence)
		return;

	AnimationInfo* Info = new AnimationInfo;

	Info->Sequence = Sequence;
	Info->Loop = Loop;
	Info->PlayTime = PlayTime;
	Info->PlayScale = PlayScale;
	Info->Reverse = Reverse;
	Info->FrameTime = PlayTime / Sequence->GetFrameCount();

	// ó�� �߰��Ǵ� �ִϸ��̼��� ��� �� �ִϸ��̼���
	// �⺻���� �����Ѵ�
	if (m_mapAnimation.empty())
		m_CurrentAnimation = Info;

	m_mapAnimation.insert(std::make_pair(SequenceName, Info));
}

void CAnimation::SetPlayTime(const std::string& Name,
	float PlayTime)
{
	AnimationInfo* Info = FindInfo(Name);

	if (!Info)
		return;

	Info->PlayTime = PlayTime;
}

void CAnimation::SetPlayScale(const std::string& Name, 
	float PlayScale)
{
	AnimationInfo* Info = FindInfo(Name);

	if (!Info)
		return;

	Info->PlayScale = PlayScale;
}

void CAnimation::SetCurrentAnimation(
	const std::string& Name)
{
	m_CurrentAnimation = FindInfo(Name);

	m_CurrentAnimation->Frame = 0;
	m_CurrentAnimation->Time = 0.f;
}

AnimationInfo* CAnimation::GetCurrentAnimation() const
{
	return m_CurrentAnimation;
}

void CAnimation::ChangeAnimation(const std::string& Name)
{
	if (m_CurrentAnimation->Sequence->GetName() == Name)
		return;

	// ���� �������� �ִϸ��̼��� frame�� 0���� ��������
	// �ٸ������� ����
	m_CurrentAnimation->Frame = 0;
	m_CurrentAnimation->Time = 0.f;

	m_CurrentAnimation = FindInfo(Name);

	if (m_CurrentAnimation->Reverse)
		m_CurrentAnimation->Frame = m_CurrentAnimation->Sequence->GetFrameCount() - 1;

	else
		m_CurrentAnimation->Frame = 0;

	m_CurrentAnimation->Time = 0.f;

}

bool CAnimation::CheckCurrentAnimation(const std::string& Name)
{
	return m_CurrentAnimation->Sequence->GetName() == Name;
}

void CAnimation::SetReverse(const std::string& Name,
	bool Reverse)
{
	AnimationInfo* Info = FindInfo(Name);

	if (!Info)
		return;

	Info->Reverse = Reverse;
}

void CAnimation::SetLoop(const std::string& Name, 
	bool Loop)
{
	AnimationInfo* Info = FindInfo(Name);

	if (!Info)
		return;

	Info->Loop = Loop;
}

void CAnimation::Update(float DeltaTime)
{
	bool AnimEnd = false;

	if (!CGameManager::GetInst()->GetIsPause())
	{
		m_CurrentAnimation->Time += DeltaTime * m_CurrentAnimation->PlayScale * m_Owner->GetTimeScale();

		if (m_CurrentAnimation->Time >= m_CurrentAnimation->FrameTime)
		{
			m_CurrentAnimation->Time -= m_CurrentAnimation->FrameTime;

			if (m_CurrentAnimation->Reverse)
			{
				--m_CurrentAnimation->Frame;

				if (m_CurrentAnimation->Frame < 0)
					AnimEnd = true;
			}

			else
			{
				++m_CurrentAnimation->Frame;

				if (m_CurrentAnimation->Frame == m_CurrentAnimation->Sequence->GetFrameCount())
					AnimEnd = true;
			}
		}
	}

	if (AnimEnd)
	{
		if (m_CurrentAnimation->Loop)
		{

			if (m_CurrentAnimation->Reverse)
				m_CurrentAnimation->Frame = m_CurrentAnimation->Sequence->GetFrameCount() - 1;
			else
				m_CurrentAnimation->Frame = 0;
		}

		else
		{
			// Loop �ɼ��� �ƴϸ� ������ �����ӿ� ������ �ֵ���
			if (m_CurrentAnimation->Reverse)
				m_CurrentAnimation->Frame = 0;

			else
				m_CurrentAnimation->Frame = m_CurrentAnimation->Sequence->GetFrameCount() - 1;
		}
	}

}

CAnimation* CAnimation::Clone()
{
	return new CAnimation(*this);
}

AnimationInfo* CAnimation::FindInfo(
	const std::string& Name)
{
	auto iter = m_mapAnimation.find(Name);

	if (iter == m_mapAnimation.end())
		return nullptr;

	return iter->second;
}

void CAnimation::SetCurrentAnimationXOffset(float Data, int Index)
{
	m_CurrentAnimation->Sequence->SetOffsetXData(Data, Index);
}

void CAnimation::SetCurrentAnimationYOffset(float Data, int Index)
{
	m_CurrentAnimation->Sequence->SetOffsetYData(Data, Index);
}

void CAnimation::SetCurrentAnimationXFrameSize(float Data, int Index)
{
	m_CurrentAnimation->Sequence->SetFrameSizeX(Data, Index);
}

void CAnimation::SetCurrentAnimationYFrameSize(float Data, int Index)
{
	m_CurrentAnimation->Sequence->SetFrameSizeY(Data, Index);
}

void CAnimation::SetCurrentAnimationXStartPos(float Data, int Index)
{
	m_CurrentAnimation->Sequence->SetStartPosX(Data, Index);
}

void CAnimation::SetCurrentAnimationYStartPos(float Data, int Index)
{
	m_CurrentAnimation->Sequence->SetStartPosY(Data, Index);
}

