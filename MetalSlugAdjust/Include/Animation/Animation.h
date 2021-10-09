#pragma once

#include "AnimationInfo.h"

// GameObject만 갖고 있음 -> 공유되는게 아니므로
// 멤버들도 CShredPtr을 사용하는 멤버가 없음
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
	// Player나 Monster같은 각종 GameObject들이 
	// 사용하는 함수
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

