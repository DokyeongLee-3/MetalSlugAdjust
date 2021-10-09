#pragma once
#include "UIWindow.h"

// StartScene UI Ŭ����
class CUIStart :
    public CUIWindow
{
    friend class CScene;

private:
    CUIStart();
    virtual ~CUIStart();

public:
    virtual bool Init();

public:
    // StartScene���� Start��ư ������ �� �ݹ��Լ�
    void StartClick();
    // StartScene���� Exit��ư ������ �� �ݹ��Լ�
    void ExitClick();
};

