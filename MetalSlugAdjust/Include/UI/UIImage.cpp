
#include "UIImage.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

CUIImage::CUIImage()    :
    m_FrameIndex(0),
    m_PlayTime(1.f),
    m_AnimTime(0.f)
{
}

CUIImage::CUIImage(const CUIImage& widget)  :
    CUIWidget(widget)
{
    m_Texture = widget.m_Texture;
    m_PlayTime = widget.m_PlayTime;
    m_AnimTime = 0.f;
    m_FrameIndex = 0;
    m_vecFrameData = widget.m_vecFrameData;
}

CUIImage::~CUIImage()
{
}

void CUIImage::SetTexture(const std::string& Name)
{
    CTexture* Texture = m_Scene->GetSceneResource()->FindTexture(Name);

    if (Texture)
    {
        m_Size.x = (float)Texture->GetWidth();
        m_Size.y = (float)Texture->GetHeight();
    }

}

void CUIImage::SetTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
    m_Scene->GetSceneResource()->LoadTexture(Name, 
        FileName, PathName);

    m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);

    if (m_Texture)
    {
        m_Size.x = (float)m_Texture->GetWidth();
        m_Size.y = (float)m_Texture->GetHeight();
    }

}

void CUIImage::SetTextureFullPath(const std::string& Name, const TCHAR* FullPath)
{
    m_Scene->GetSceneResource()->LoadTextureFullPath(Name,
        FullPath);

    m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);

    if (m_Texture)
    {
        m_Size.x = (float)m_Texture->GetWidth();
        m_Size.y = (float)m_Texture->GetHeight();
    }
}

void CUIImage::SetTexture(const std::string& Name,
    const std::vector<std::wstring>& vecFileName,
    const std::string& PathName)
{
    m_Scene->GetSceneResource()->LoadTexture(Name,
        vecFileName, PathName);

    m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);

    if (m_Texture)
    {
        m_Size.x = (float)m_Texture->GetWidth();
        m_Size.y = (float)m_Texture->GetHeight();
    }
}

void CUIImage::SetTextureColorKey(unsigned char r, unsigned char g, unsigned char b, int Index)
{
    if (m_Texture)
        m_Texture->SetColorKey(r, g, b, Index);
}

bool CUIImage::Init()
{
    return true;
}

void CUIImage::Update(float DeltaTime)
{
    // CUIImage가 애니메이션이 있다면(ex.마우스)
    if (!m_vecFrameData.empty())
    {
        m_AnimTime += DeltaTime;

        float FrameTime = m_PlayTime / m_vecFrameData.size();

        if (m_AnimTime >= FrameTime)
        {
            m_AnimTime -= FrameTime;

            m_FrameIndex = (m_FrameIndex + 1) % m_vecFrameData.size();
        }
    }
}

void CUIImage::PostUpdate(float DeltaTime)
{
}

void CUIImage::Collision(float DeltaTime)
{
}

void CUIImage::Render(HDC hDC)
{
    if (m_Texture)
    {
        // 내가 속해있는 CUIWindow로부터 상대적으로
        // 떨어져 있는 만큼으로 CUIImage의 위치 설정
        Vector2 Pos = m_Pos + m_Owner->GetPos();
        Vector2 ImagePos;
        Vector2 Size = m_Size;

        if (!m_vecFrameData.empty())
        {
            ImagePos = m_vecFrameData[m_FrameIndex].StartPos;
            Size = m_vecFrameData[m_FrameIndex].Size;

            if (m_Texture->GetTextureType() == ETexture_Type::Frame)
            {
                m_Texture->Render(hDC, Pos + m_Offset, ImagePos, Size, m_FrameIndex);
            }

            else
            {
                m_Texture->Render(hDC, Pos + m_Offset, ImagePos, Size);
            }

        }

        else
        {
            if (m_Texture->GetTextureType() == ETexture_Type::Frame)
            {
                m_Texture->Render(hDC, Pos + m_Offset, ImagePos, Size, m_FrameIndex);
            }

            else
            {
                m_Texture->Render(hDC, Pos + m_Offset, ImagePos, Size);
            }
        }
    }
}

void CUIImage::Render(const Vector2& Pos, HDC hDC)
{
    if (m_Texture)
    {
        Vector2 ImagePos;
        Vector2 Size = m_Size;

        // UIImage가 애니메이션이 있을 경우(ex. Mouse)
        if (!m_vecFrameData.empty())
        {
            ImagePos = m_vecFrameData[m_FrameIndex].StartPos;
            Size = m_vecFrameData[m_FrameIndex].Size;

            if (m_Texture->GetTextureType() == ETexture_Type::Frame)
            {
                m_Texture->Render(hDC, Pos + m_Offset, ImagePos, Size, m_FrameIndex);
            }

            else
            {
                m_Texture->Render(hDC, Pos + m_Offset, ImagePos, Size);
            }
        }

        // 애니메이션이 없을 경우
        // ex) DamageFont
        else
        {
            if (m_Texture->GetTextureType() == ETexture_Type::Frame)
            {
                m_Texture->Render(hDC, Pos + m_Offset, ImagePos, Size, m_FrameIndex);
            }

            else
            {
                m_Texture->Render(hDC, Pos + m_Offset, ImagePos, Size);
            }
        }
    }
}

CUIImage* CUIImage::Clone()
{
    return new CUIImage(*this);
}
