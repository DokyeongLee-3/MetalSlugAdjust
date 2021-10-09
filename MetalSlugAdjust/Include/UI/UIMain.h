#pragma once
#include "UIWindow.h"

class CUIMain :
    public CUIWindow
{
    friend class CScene;

private:
    CUIMain();
    virtual ~CUIMain();

private:
    class CUIText* m_Text;
    float m_TextTime;

    int m_OutputText;
    int m_OutputIndex;

    // 시계에서 10초 단위의 수
    class CNumberWidget* m_NumberWidget;
    // 시계에서 1초 단위의 수
    class CNumberWidget* m_Number1Widget;
    // 시계에서 분 단위의 수
    class CNumberWidget* m_MinuteWidget;

    float m_Time;
    int m_Minute;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

