#pragma once
#include "../Ref.h"

// UIŬ�������� �θ�Ŭ����
class CUIWidget :
    public CRef
{
public:
    CUIWidget();
    CUIWidget(const CUIWidget& widget);
    virtual ~CUIWidget();

protected:
    class CScene* m_Scene;
    // �� ���� ������ �켱������ ���Ƽ� ���߿� �׷���
    int m_ZOrder;
    // UIWindow�� Visibility�ʹ� ������ UIWidget��
    // ������ m_Visibility ����� ���� �ִ�.
    bool m_Visibility;
    class CUIWindow* m_Owner;
    Vector2     m_Pos;
    Vector2     m_Size;
    // CButton���� Ŭ�������� m_MouseHovered�̸�
    // ButtonState�ٲٷ��� ���� ���
    bool    m_MouseHovered;

public:
    Vector2 GetPos()    const
    {
        return m_Pos;
    }

    Vector2 GetSize()   const
    {
        return m_Size;
    }

    void SetPos(const Vector2& Pos)
    {
        m_Pos = Pos;
    }

    void SetPos(float x, float y)
    {
        m_Pos = Vector2(x, y);
    }

    void SetSize(const Vector2& Size)
    {
        m_Size = Size;
    }

    void SetSize(float x, float y)
    {
        m_Size = Vector2(x, y);
    }

    void SetOwner(class CUIWindow* Owner)
    {
        m_Owner = Owner;
    }

    void SetScene(class CScene* Scene)
    {
        m_Scene = Scene;
    }

    void SetVisibility(bool Visibility)
    {
        m_Visibility = Visibility;
    }

    bool GetVisibility()    const
    {
        return m_Visibility;
    }

    void SetZOrder(int ZOrder)
    {
        m_ZOrder = ZOrder;
    }

    int GetZOrder() const
    {
        return m_ZOrder;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(HDC hDC);
    virtual void Render(const Vector2& Pos, HDC hDC);
    virtual CUIWidget* Clone();

public:
    bool CollisionMouse(const Vector2& MousePos, float DeltaTime);

public:
    // Widget�������� ���콺�� �ö���� �� �ݹ��Լ� 
    virtual void CollisionMouseHoveredCallback(float DeltaTime);
    // Widget���� �ٱ����� ���콺�� ���������� �� �ݹ��Լ�
    virtual void CollisionMouseReleaseCallback(float DeltaTime);
};

