
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

	// CGameObject���� m_DamageEnable�� false�� 
	// 0�� �������� ���̹Ƿ� HP�� �������� ��������
	m_CharacterInfo.HP -= (int)Damage;

	return Damage;
}

void CCharacter::DecreaseMP(float Amount)
{
	m_CharacterInfo.MP -= (int)Amount;
}
