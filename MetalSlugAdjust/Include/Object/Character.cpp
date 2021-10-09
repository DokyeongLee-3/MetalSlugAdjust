
#include "Character.h"

CCharacter::CCharacter()	:
	m_CharacterInfo{}
{
}

CCharacter::CCharacter(const CCharacter& obj) :
	CGameObject(obj)
{
	m_CharacterInfo = obj.m_CharacterInfo;
}

CCharacter::~CCharacter()
{
}

void CCharacter::Start()
{
	CGameObject::Start();
}

bool CCharacter::Init()
{
	if (!CGameObject::Init())
		return false;

	return true;
}

void CCharacter::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CCharacter::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CCharacter::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CCharacter::Render(HDC hDC)
{
	CGameObject::Render(hDC);
}

CCharacter* CCharacter::Clone()
{
	return nullptr;
}

float CCharacter::SetDamage(float Damage)
{
	Damage = CGameObject::SetDamage(Damage);

	// CGameObject에서 m_DamageEnable가 false면 
	// 0을 리턴했을 것이므로 HP가 감소하지 않을것임
	m_CharacterInfo.HP -= (int)Damage;

	return Damage;
}

void CCharacter::DecreaseMP(float Amount)
{
	m_CharacterInfo.MP -= (int)Amount;
}
