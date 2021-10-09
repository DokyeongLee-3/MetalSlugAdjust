#pragma once
#include "GameObject.h"

class CCharacter :
    public CGameObject
{
    friend class CScene;

protected:
    CCharacter();
	CCharacter(const CCharacter& obj);
    virtual ~CCharacter();

protected:
	CharacterInfo m_CharacterInfo;

public:
	void SetCharacterInfo(int Attack, int Armor, int HP,
		int MP, int Level, int Exp, int Gold, float AttackSpeed,
		float AttackDistance)
	{
		m_CharacterInfo.Attack = Attack;
		m_CharacterInfo.Armor = Armor;
		m_CharacterInfo.HP = HP;
		m_CharacterInfo.HPMax = HP;
		m_CharacterInfo.MP = MP;
		m_CharacterInfo.MPMax = MP;
		m_CharacterInfo.Level = Level;
		m_CharacterInfo.Exp = Exp;
		m_CharacterInfo.Gold = Gold;
		m_CharacterInfo.AttackSpeed = AttackSpeed;
		m_CharacterInfo.AttackDistance = AttackDistance;
	}

	// ���������� ���� �ӵ��� ���߷��� ���ݸ�ǿ� ���� animation 
	// SequenceName�� �˾ƾ��ϴµ� �װ� CPlayer::Init���� �����Ǳ� ������
	// ���⼭�� �𸥴�. �׷��� CCharacter�� �ش�Ǵ� Player, Monster ���
	// AttackSpeed�� �����ϰ� �ϰ� ������ SetAttackSpeed�� virtual�� ���
	// CPlayer���� SetAttackSpeed�� �ڽĿ��� �������ؼ�, �ڽĿ��� �Ʒ�
	// �Լ��� �ҷ��� AttackSpeed�� �����ϰ�, � �̸��� ���� �ִϸ��̼ǿ� 
	// ����� AttackSpeed�� �����Ұ����� ���� �ڽ� Ŭ�������� �����ǵ�
	// SetAttackSpeed���� �����ϱ�� �Ѵ�
	virtual void SetAttackSpeed(float Speed)
	{
		m_CharacterInfo.AttackSpeed = Speed;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(HDC hDC);
	virtual CCharacter* Clone();
	virtual float SetDamage(float Damage);
	virtual void DecreaseMP(float Amount);
};

