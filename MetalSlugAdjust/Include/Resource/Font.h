#pragma once

#include "../Ref.h"

class CFont :
    public CRef
{
    friend class CResourceManager;

private:
    CFont();
    ~CFont();

private:
    LOGFONT m_FontInfo;
    HFONT   m_Font;
    HFONT   m_PrevFont;

public:
    // 폰트 가로, 세로 길이를 0,0으로 주면 기본크기로 적용
    bool LoadFont(const std::string& Name, const TCHAR* FontName,
        int Width = 0, int Height = 0);
    void SetFont(HDC hDC);
    void ResetFont(HDC hDC);
};

