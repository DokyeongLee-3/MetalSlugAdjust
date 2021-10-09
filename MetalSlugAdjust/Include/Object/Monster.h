#pragma once

#include "Character.h"


class CMonster :
    public CCharacter
{
    friend class CScene;

private:
    Vector2 m_Dir;
    // ���ʸ��� �Ѿ��� �߻��ϴ����� ���� ��� ����
    float	m_FireTimeMax;
    // Deltatime�� �������Ѽ� FireLimitTime�� �����ߴ����� üũ�ϴ� ����
    float	m_FireTime;
    // ������ �Ѿ� 3���� 1���� Player������ ��� 
    // �ϱ� ���� 3�߱��� count�ϴ� �뵵
    int m_Count;

protected:
    CMonster();
    CMonster(const CMonster& obj);
    virtual ~CMonster();

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(HDC hDC);
    virtual CMonster* Clone();
    virtual float SetDamage(float Damage);
    virtual void DecreaseMP(float Amount);
};

