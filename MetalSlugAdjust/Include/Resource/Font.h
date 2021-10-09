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
    // ��Ʈ ����, ���� ���̸� 0,0���� �ָ� �⺻ũ��� ����
    bool LoadFont(const std::string& Name, const TCHAR* FontName,
        int Width = 0, int Height = 0);
    void SetFont(HDC hDC);
    void ResetFont(HDC hDC);
};

