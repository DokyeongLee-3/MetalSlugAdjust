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

    // �ð迡�� 10�� ������ ��
    class CNumberWidget* m_NumberWidget;
    // �ð迡�� 1�� ������ ��
    class CNumberWidget* m_Number1Widget;
    // �ð迡�� �� ������ ��
    class CNumberWidget* m_MinuteWidget;

    float m_Time;
    int m_Minute;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

