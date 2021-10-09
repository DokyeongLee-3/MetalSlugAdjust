#pragma once

#include "AnimationInfo.h"

// GameObject�� ���� ���� -> �����Ǵ°� �ƴϹǷ�
// ����鵵 CShredPtr�� ����ϴ� ����� ����
class CAnimation
{
	friend class CGameObject;

private:
	CAnimation();
	CAnimation(const CAnimation& Anim);
	~CAnimation();

private:
	class CGameObject* m_Owner;
	class CScene* m_Scene;
	std::unordered_map<std::string, AnimationInfo*> m_mapAnimation;
	AnimationInfo* m_CurrentAnimation;

public:
	// Player�� Monster���� ���� GameObject���� 
	// ����ϴ� �Լ�
	void AddAnimation(const std::string& SequenceName,
		bool Loop = true, float PlayTime = 1.f,
		float PlayScale = 1.f, bool Reverse = false);
	void SetPlayTime(const std::string& Name,
		float PlayTime);
	void SetPlayScale(const std::string& Name,
		float PlayScale);
	void SetCurrentAnimation(const std::string& Name);
	AnimationInfo* GetCurrentAnimation()	const;
	void ChangeAnimation(const std::string& Name);
	bool CheckCurrentAnimation(const std::string& Name);
	void SetReverse(const std::string& Name, bool Reverse);
	void SetLoop(const std::string& Name, bool Loop);
	void Update(float DeltaTime);
	CAnimation* Clone();

private:
	AnimationInfo* FindInfo(const std::string& Name);

public:
	void SetCurrentAnimationXOffset(float Data, int Index);
	void SetCurrentAnimationYOffset(float Data, int Index);
	void SetCurrentAnimationXFrameSize(float Data, int Index);
	void SetCurrentAnimationYFrameSize(float Data, int Index);
	void SetCurrentAnimationXStartPos(float Data, int Index);
	void SetCurrentAnimationYStartPos(float Data, int Index);
};

