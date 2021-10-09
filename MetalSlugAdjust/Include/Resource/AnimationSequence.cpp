
#include "AnimationSequence.h"

CAnimationSequence::CAnimationSequence()
{
}

CAnimationSequence::~CAnimationSequence()
{
}

bool CAnimationSequence::Init(const std::string& Name, CTexture* Texture)
{
	m_Name = Name;
	m_Texture = Texture;
	m_TextureType = m_Texture->GetTextureType();

	return true;
}

void CAnimationSequence::AddFrameData(const Vector2& StartPos, const Vector2& Size)
{
	AnimationFrameData Data;
	Data.StartPos = StartPos;
	Data.Size = Size;

	m_vecFrameData.push_back(Data);
}

void CAnimationSequence::AddFrameData(float PosX, float PosY, float SizeX, float SizeY)
{
	AnimationFrameData Data;
	Data.StartPos = Vector2(PosX, PosY);
	Data.Size = Vector2(SizeX, SizeY);

	m_vecFrameData.push_back(Data);
}

void CAnimationSequence::SetOffsetXData(float Data, int Index)
{
	m_vecFrameData[Index].Offset.x += Data;
}

void CAnimationSequence::SetOffsetYData(float Data, int Index)
{
	m_vecFrameData[Index].Offset.y += Data;
}

void CAnimationSequence::SetFrameSizeX(float Data, int Index)
{
	m_vecFrameData[Index].Size.x += Data;
}

void CAnimationSequence::SetFrameSizeY(float Data, int Index)
{
	m_vecFrameData[Index].Size.y += Data;
}

void CAnimationSequence::SetStartPosX(float Data, int Index)
{
	m_vecFrameData[Index].StartPos.x += Data;
}

void CAnimationSequence::SetStartPosY(float Data, int Index)
{
	m_vecFrameData[Index].StartPos.y += Data;
}

void CAnimationSequence::LoadOffsetXData(float Data, int Index)
{
	m_vecFrameData[Index].Offset.x = Data;
}

void CAnimationSequence::LoadOffsetYData(float Data, int Index)
{
	m_vecFrameData[Index].Offset.y = Data;
}

void CAnimationSequence::LoadFrameSizeX(float Data, int Index)
{
	m_vecFrameData[Index].Size.x = Data;
}

void CAnimationSequence::LoadFrameSizeY(float Data, int Index)
{
	m_vecFrameData[Index].Size.y = Data;
}

void CAnimationSequence::LoadStartPosX(float Data, int Index)
{
	m_vecFrameData[Index].StartPos.x = Data;
}

void CAnimationSequence::LoadStartPosY(float Data, int Index)
{
	m_vecFrameData[Index].StartPos.y = Data;
}
