#pragma once

#include "UIImage.h"

class CNumberWidget :
    public CUIImage
{

public:
    CNumberWidget();
    CNumberWidget(const CNumberWidget& widget);
    virtual ~CNumberWidget();

protected:
    int m_Number;
    // m_Number를 자릿수별로 하나씩 m_vecNumber에 넣어줄 것임
    std::vector<int> m_vecNumber;

public:
    void SetNumber(int Number)
    {
        m_Number = Number;
    }

    void AddNumber(int Number)
    {
        m_Number += Number;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(HDC hDC);
    virtual void Render(const Vector2& Pos, HDC hDC);
    virtual CNumberWidget* Clone();

};

