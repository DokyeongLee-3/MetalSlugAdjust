#pragma once

#include "UIWidget.h"
#include "../Resource/Font.h"

class CUIText :
    public CUIWidget
{

public:
    CUIText();
    CUIText(const CUIText& widget);
    ~CUIText();

protected:
    TCHAR* m_Text;
    int m_TextCount;
    int m_TextCapacity;
    COLORREF m_TextColor;
    CSharedPtr<CFont>   m_Font;

public:
    void SetTextColor(unsigned char r, unsigned char g,
        unsigned char b)
    {
        m_TextColor = RGB(r, g, b);
    }

    void SetText(const TCHAR* Text)
    {
        int Length = lstrlen(Text);

        if (Length + 1 > m_TextCapacity)
        {
            m_TextCapacity = Length + 1;

            SAFE_DELETE_ARRAY(m_Text);

            m_Text = new TCHAR[m_TextCapacity];

            memset(m_Text, 0, sizeof(TCHAR) * m_TextCapacity);
        }

        lstrcpy(m_Text, Text);

        m_TextCount = lstrlen(m_Text);
    }

    void AddText(const TCHAR* Text)
    {
        int Length = m_TextCount + lstrlen(Text);

        if (Length + 1 > m_TextCapacity)
        {
            m_TextCapacity = Length + 1;

            TCHAR* Array = new TCHAR[m_TextCapacity];

            memset(Array, 0, sizeof(TCHAR) * m_TextCapacity);

            lstrcpy(Array, m_Text);

            SAFE_DELETE_ARRAY(m_Text);

            m_Text = Array;
        }

        lstrcat(m_Text, Text);

        m_TextCount += lstrlen(Text);
    }

    void pop_back()
    {
        --m_TextCount;

        m_Text[m_TextCount] = 0;
    }

    void Clear()
    {
        m_TextCount = 0;

        memset(m_Text, 0, sizeof(TCHAR) * m_TextCapacity);
    }

    void SetFont(const std::string& Name);

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(HDC hDC);
    // 특정 위치에 render하도록
    virtual void Render(const Vector2& Pos, HDC hDC);
    virtual CUIText* Clone();
};

