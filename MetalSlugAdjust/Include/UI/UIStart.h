#pragma once
#include "UIWindow.h"

// StartScene UI 클래스
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
    // StartScene에서 Start버튼 눌렀을 때 콜백함수
    void StartClick();
    // StartScene에서 Exit버튼 눌렀을 때 콜백함수
    void ExitClick();
};

