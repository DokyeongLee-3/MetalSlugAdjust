
#include "GameObject.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/SceneCollision.h"
#include "../Resource/AnimationSequence.h"

CGameObject::CGameObject()	:
	m_Scene(nullptr),
	m_TimeScale(1.f),
	m_Animation(nullptr),
	m_Start(false),
	m_ObjType(EObject_Type::GameObject)
{
}

CGameObject::CGameObject(const CGameObject& obj) :
	CRef(obj)
{
	m_ObjType = obj.m_ObjType;

	m_Start = false;

	m_Scene = obj.m_Scene;

	if (obj.m_Animation)
		m_Animation = obj.m_Animation->Clone();

	m_Animation->m_Owner = this;

	m_PrevPos = obj.m_PrevPos;
	m_Pos = obj.m_Pos;
	m_Size = obj.m_Size;
	m_Pivot = obj.m_Pivot;
	m_Velocity = obj.m_Velocity;
	m_Offset = obj.m_Offset;
	m_TimeScale = obj.m_TimeScale;
	m_Texture = obj.m_Texture;
	m_ImageStart = obj.m_ImageStart;
}

CGameObject::~CGameObject()
{
	SAFE_DELETE(m_Animation);
}


void CGameObject::CreateAnimation()
{
	if (!m_Animation)
	{
		m_Animation = new CAnimation;

		m_Animation->m_Owner = this;
		m_Animation->m_Scene = m_Scene;
	}
}

void CGameObject::AddAnimation(
	const std::string& SequenceName,
	bool Loop, float PlayTime, float PlayScale,
	bool Reverse)
{
	if (!m_Animation)
	{
		m_Animation = new CAnimation;

		m_Animation->m_Owner = this;
		m_Animation->m_Scene = m_Scene;
	}

	m_Animation->AddAnimation(SequenceName, Loop, PlayTime, PlayScale, Reverse);
}

void CGameObject::SetAnimationPlayTime
(const std::string& Name, float PlayTime)
{
	if (!m_Animation)
		return;

	m_Animation->SetPlayTime(Name, PlayTime);
}

void CGameObject::SetAnimationPlayScale(
	const std::string& Name, float PlayScale)
{
	if (!m_Animation)
		return;

	m_Animation->SetPlayScale(Name, PlayScale);
}

void CGameObject::SetCurrentAnimation(
	const std::string& Name)
{
	if (!m_Animation)
		return;

	m_Animation->SetCurrentAnimation(Name);
}

void CGameObject::ChangeAnimation(
	const std::string& Name)
{
	if (!m_Animation)
		return;

	m_Animation->ChangeAnimation(Name);
}

bool CGameObject::CheckCurrentAnimation(const std::string& Name)
{
	return m_Animation->CheckCurrentAnimation(Name);
}

void CGameObject::SetAnimationReverse(
	const std::string& Name, bool Reverse)
{
	if (!m_Animation)
		return;

	m_Animation->SetReverse(Name, Reverse);
}

void CGameObject::SetAnimationLoop(
	const std::string& Name, bool Loop)
{
	if (!m_Animation)
		return;

	m_Animation->SetLoop(Name, Loop);
}

float CGameObject::GetBottom() const
{
	Vector2 Size = m_Size;

	if (m_Animation)
	{
		AnimationInfo* Info = m_Animation->m_CurrentAnimation;

		const AnimationFrameData& FrameData = Info->Sequence->GetFrameData(Info->Frame);

		Size = FrameData.Size;
	}

	return	m_Pos.y + (1.f - m_Pivot.y) * Size.y + m_Offset.y;
}

void CGameObject::SetScene(CScene* Scene)
{
	m_Scene = Scene;

	if (m_Animation)
		m_Animation->m_Scene = Scene;
}


//void CGameObject::Move(const Vector2& Dir)
//{
//	Vector2 CurrentMove = Dir * m_MoveSpeed * CGameManager::GetInst()->GetDeltaTime() * m_TimeScale;
//	m_Velocity += CurrentMove;
//	m_Pos += CurrentMove;
//}
//
//void CGameObject::Move(const Vector2& Dir, float Speed)
//{
//	Vector2 CurrentMove = Dir * Speed * CGameManager::GetInst()->GetDeltaTime() * m_TimeScale;
//	m_Velocity += CurrentMove;
//	m_Pos += CurrentMove;
//}

void CGameObject::SetTexture(const std::string& Name)
{
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);

	if (m_Texture)
	{
		m_Size.x = (float)m_Texture->GetWidth();
		m_Size.y = (float)m_Texture->GetHeight();
	}
}

void CGameObject::SetTexture(const std::string& Name,
	const TCHAR* FileName, const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, FileName, PathName);

	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);

	if (m_Texture)
	{
		m_Size.x = (float)m_Texture->GetWidth();
		m_Size.y = (float)m_Texture->GetHeight();
	}
}

void CGameObject::SetTextureFullPath(const std::string& Name, const TCHAR* FullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, FullPath);

	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);

	if (m_Texture)
	{
		m_Size.x = (float)m_Texture->GetWidth();
		m_Size.y = (float)m_Texture->GetHeight();
	}
}

void CGameObject::SetTexture(const std::string& Name,
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

void CGameObject::SetTextureColorKey(unsigned char r, 
	unsigned char g, unsigned char b, int Index)
{
	if (m_Texture)
		m_Texture->SetColorKey(r, g, b, Index);
}

bool CGameObject::Init()
{
	return true;
}

void CGameObject::Update(float DeltaTime)
{
	if (m_Animation)
		m_Animation->Update(DeltaTime);
}

void CGameObject::PostUpdate(float DeltaTime)
{
	if (m_Animation)
	{
		AnimationInfo* AnimInfo = m_Animation->m_CurrentAnimation;

		const AnimationFrameData& FrameData =
			AnimInfo->Sequence->GetFrameData(AnimInfo->Frame);

		m_Size = FrameData.Size;
	}
}


void CGameObject::PrevRender()
{
	if (m_Animation)
	{
		AnimationInfo* AnimInfo = m_Animation->m_CurrentAnimation;

		const AnimationFrameData& FrameData = AnimInfo->Sequence->GetFrameData(AnimInfo->Frame);

		m_Size = FrameData.Size;
	}
}

void CGameObject::Render(HDC hDC)
{
	if (m_Animation)
	{

		AnimationInfo* AnimInfo = m_Animation->m_CurrentAnimation;

		// CAnimation::Update에서 m_CurrentAnimation의 Frame 번호를
		// 시간이 지남에 따라 계속 update해주므로, GetFrameData인자에는
		// 순서에 맞는 Frame번호를 넘겨줄 것이고, GetFrameData는
		// CAnimationSequence의 m_vecFrameData에서 Frame번호에 맞는
		// FrameData를 넘겨줄 것이다
		const AnimationFrameData& FrameData =
			AnimInfo->Sequence->GetFrameData(AnimInfo->Frame);

		Vector2 LT = m_RenderPos - m_Pivot * FrameData.Size + FrameData.Offset + m_Offset;

		if (AnimInfo->Sequence->GetTextureType() == ETexture_Type::Atlas)
		{
			AnimInfo->Sequence->GetTexture()->Render(hDC, LT,
				FrameData.StartPos, FrameData.Size);
		}

		// Frame방식
		else
		{
			AnimInfo->Sequence->GetTexture()->Render(hDC, LT,
				FrameData.StartPos, FrameData.Size, AnimInfo->Frame);
		}

		if (GetName() == "PlayerTop")
		{
			std::string tmp = m_Animation->m_CurrentAnimation->Sequence->GetName();
			std::wstring Name;
			Name.clear();
			Name.assign(tmp.begin(), tmp.end());
			TCHAR StrXStartPos[256] = {};
			TCHAR StrYStartPos[256] = {};
			TCHAR XOffset[256] = {};
			TCHAR YOffset[256] = {};

			TCHAR Frame[256] = {};

			TCHAR FrameSizeX[256] = {};
			TCHAR FrameSizeY[256] = {};

			
			wsprintf(XOffset, TEXT("TopFrameXOffset : %d"), (int)FrameData.Offset.x);
			wsprintf(YOffset, TEXT("TopFrameYOffset : %d"), (int)FrameData.Offset.y);
			wsprintf(StrXStartPos, TEXT("TopFrameXStartPos : %d"), (int)FrameData.StartPos.x);
			wsprintf(StrYStartPos, TEXT("TopFrameYStartPos : %d"), (int)FrameData.StartPos.y);
			wsprintf(FrameSizeX, TEXT("TopFrameXSize : %d"), (int)FrameData.Size.x);
			wsprintf(FrameSizeY, TEXT("TopFrameYSize : %d"), (int)FrameData.Size.y);
			wsprintf(Frame, TEXT("TopFrame : %d / %d"), (int)AnimInfo->Frame, AnimInfo->Sequence->GetFrameCount() - 1);

			TextOut(hDC, (int)170.f, (int)60.f, Name.c_str(), lstrlen(Name.c_str()));
			TextOut(hDC, (int)170.f, (int)80.f, Frame, lstrlen(Frame));
			TextOut(hDC, (int)170.f, (int)100.f, StrXStartPos, lstrlen(StrXStartPos));
			TextOut(hDC, (int)170.f, (int)120.f, StrYStartPos, lstrlen(StrYStartPos));
			TextOut(hDC, (int)170.f, (int)140.f, FrameSizeX, lstrlen(FrameSizeX));
			TextOut(hDC, (int)170.f, (int)160.f, FrameSizeY, lstrlen(FrameSizeY));
			TextOut(hDC, (int)170.f, (int)180.f, XOffset, lstrlen(XOffset));
			TextOut(hDC, (int)170.f, (int)200.f, YOffset, lstrlen(YOffset));
		}

		else if (GetName() == "PlayerBottom")
		{
			std::string tmp = m_Animation->m_CurrentAnimation->Sequence->GetName();
			std::wstring Name;
			Name.clear();
			Name.assign(tmp.begin(), tmp.end());
			TCHAR StrXStartPos[256] = {};
			TCHAR StrYStartPos[256] = {};
			TCHAR XOffset[256] = {};
			TCHAR YOffset[256] = {};

			TCHAR Frame[256] = {};

			TCHAR FrameSizeX[256] = {};
			TCHAR FrameSizeY[256] = {};

			wsprintf(XOffset, TEXT("BottomFrameXOffset : %d"), (int)FrameData.Offset.x);
			wsprintf(YOffset, TEXT("BottomFrameYOffset : %d"), (int)FrameData.Offset.y);
			wsprintf(StrXStartPos, TEXT("BottomFrameXStartPos : %d"), (int)FrameData.StartPos.x);
			wsprintf(StrYStartPos, TEXT("BottomFrameYStartPos : %d"), (int)FrameData.StartPos.y);
			wsprintf(FrameSizeX, TEXT("BottomFrameXSize : %d"), (int)FrameData.Size.x);
			wsprintf(FrameSizeY, TEXT("BottomFrameYSize : %d"), (int)FrameData.Size.y);
			wsprintf(Frame, TEXT("BottomFrame : %d / %d"), (int)AnimInfo->Frame, AnimInfo->Sequence->GetFrameCount() - 1);

			TextOut(hDC, (int)170.f, (int)240.f, Name.c_str(), lstrlen(Name.c_str()));
			TextOut(hDC, (int)170.f, (int)260.f, Frame, lstrlen(Frame));
			TextOut(hDC, (int)170.f, (int)280.f, StrXStartPos, lstrlen(StrXStartPos));
			TextOut(hDC, (int)170.f, (int)300.f, StrYStartPos, lstrlen(StrYStartPos));
			TextOut(hDC, (int)170.f, (int)320.f, FrameSizeX, lstrlen(FrameSizeX));
			TextOut(hDC, (int)170.f, (int)340.f, FrameSizeY, lstrlen(FrameSizeY));
			TextOut(hDC, (int)170.f, (int)360.f, XOffset, lstrlen(XOffset));
			TextOut(hDC, (int)170.f, (int)380.f, YOffset, lstrlen(YOffset));
		}
	}

	else
	{
		Vector2 LT = m_RenderPos - m_Pivot * m_Size + m_Offset;

		if (m_Texture)
		{
			m_Texture->Render(hDC, LT, m_ImageStart, m_Size);
		}
	}


	TCHAR SwapControl[32] = {};
	TCHAR IncreaseXOffset[64] = {};
	TCHAR DecreaseXOffset[64] = {};
	TCHAR IncreaseYOffset[64] = {};
	TCHAR DecreaseYOffset[64] = {};

	TCHAR NextFrame[64] = {};
	TCHAR PrevFrame[64] = {};

	TCHAR IncreaseTimeScale[64] = {};
	TCHAR DecreaseTimeScale[64] = {};

	TCHAR SaveInfo[64] = {};
	TCHAR LoadInfo[64] = {};

	TCHAR NextAnimation[64] = {};
	TCHAR PrevAnimation[64] = {};

	TCHAR IncreaseXSize[64] = {};
	TCHAR DecreaseXSize[64] = {};
	TCHAR IncreaseYSize[64] = {};
	TCHAR DecreaseYSize[64] = {};

	TCHAR LeftStartPos[64] = {};
	TCHAR RightStartPos[64] = {};
	TCHAR UpStartPos[64] = {};
	TCHAR DownStartPos[64] = {};
	TCHAR LeftStartPos5[64] = {};
	TCHAR RightStartPos5[64] = {};

	lstrcpy(SwapControl, TEXT("NumPad0 : Swap Control Part"));

	lstrcpy(IncreaseXOffset, TEXT("NumPad6 : Move X Offset +1 Pixel"));
	lstrcpy(DecreaseXOffset, TEXT("NumPad4 : Move X Offset -1 Pixel"));
	lstrcpy(IncreaseYOffset, TEXT("NumPad2 : Move Y Offset +1 Pixel"));
	lstrcpy(DecreaseYOffset, TEXT("NumPad8 : Move Y Offset -1 Pixel"));

	lstrcpy(PrevFrame, TEXT("NumPad1 : Previous Frame"));
	lstrcpy(NextFrame, TEXT("NumPad3 : Next Frame"));

	lstrcpy(IncreaseTimeScale, TEXT("NumPad9 : Increase TimeScale(X1.1)"));
	lstrcpy(DecreaseTimeScale, TEXT("NumPad7 : Decrease TimeScale(X0.9)"));

	lstrcpy(SaveInfo, TEXT("NumPad+ : Save Info"));
	lstrcpy(LoadInfo, TEXT("NumPad- : Load Info"));

	lstrcpy(NextAnimation, TEXT("NumPad Multiply : Next Animation"));
	lstrcpy(PrevAnimation, TEXT("NumPad Divide : Previous Animation"));

	lstrcpy(IncreaseXSize, TEXT("NumPad Right : Increase X FrameSize"));
	lstrcpy(DecreaseXSize, TEXT("NumPad Left : Decrease X FrameSize"));
	lstrcpy(IncreaseYSize, TEXT("NumPad Up : Increase Y FrameSize"));
	lstrcpy(DecreaseYSize, TEXT("NumPad Down : Decrease Y FrameSize"));

	lstrcpy(LeftStartPos, TEXT("L : Left StartPos"));
	lstrcpy(RightStartPos, TEXT("J : Right StartPos"));
	lstrcpy(UpStartPos, TEXT("I : Up StartPos"));
	lstrcpy(DownStartPos, TEXT("K : Down StartPos"));
	lstrcpy(LeftStartPos5, TEXT("Z : Left StartPos + 5"));
	lstrcpy(RightStartPos5, TEXT("X : Right StartPos + 5"));


	TextOut(hDC, (int)700.f, (int)60.f, SwapControl, lstrlen(SwapControl));

	TextOut(hDC, (int)700.f, (int)100.f, IncreaseXOffset, lstrlen(IncreaseXOffset));
	TextOut(hDC, (int)700.f, (int)120.f, DecreaseXOffset, lstrlen(DecreaseXOffset));
	TextOut(hDC, (int)700.f, (int)140.f, IncreaseYOffset, lstrlen(IncreaseYOffset));
	TextOut(hDC, (int)700.f, (int)160.f, DecreaseYOffset, lstrlen(DecreaseYOffset));

	TextOut(hDC, (int)700.f, (int)200.f, PrevFrame, lstrlen(PrevFrame));
	TextOut(hDC, (int)700.f, (int)220.f, NextFrame, lstrlen(NextFrame));

	TextOut(hDC, (int)700.f, (int)260.f, IncreaseTimeScale, lstrlen(IncreaseTimeScale));
	TextOut(hDC, (int)700.f, (int)280.f, DecreaseTimeScale, lstrlen(DecreaseTimeScale));

	TextOut(hDC, (int)700.f, (int)320.f, SaveInfo, lstrlen(SaveInfo));
	TextOut(hDC, (int)700.f, (int)340.f, LoadInfo, lstrlen(LoadInfo));

	TextOut(hDC, (int)700.f, (int)380.f, NextAnimation, lstrlen(NextAnimation));
	TextOut(hDC, (int)700.f, (int)400.f, PrevAnimation, lstrlen(PrevAnimation));

	TextOut(hDC, (int)700.f, (int)440.f, IncreaseXSize, lstrlen(IncreaseXSize));
	TextOut(hDC, (int)700.f, (int)460.f, DecreaseXSize, lstrlen(DecreaseXSize));
	TextOut(hDC, (int)700.f, (int)480.f, IncreaseYSize, lstrlen(IncreaseYSize));
	TextOut(hDC, (int)700.f, (int)500.f, DecreaseYSize, lstrlen(DecreaseYSize));

	TextOut(hDC, (int)700.f, (int)540.f, LeftStartPos, lstrlen(LeftStartPos));
	TextOut(hDC, (int)700.f, (int)560.f, RightStartPos, lstrlen(RightStartPos));
	TextOut(hDC, (int)700.f, (int)580.f, UpStartPos, lstrlen(UpStartPos));
	TextOut(hDC, (int)700.f, (int)600.f, DownStartPos, lstrlen(DownStartPos));

	TextOut(hDC, (int)700.f, (int)640.f, LeftStartPos5, lstrlen(LeftStartPos5));
	TextOut(hDC, (int)700.f, (int)660.f, RightStartPos5, lstrlen(RightStartPos5));
}

CGameObject* CGameObject::Clone()
{
	return nullptr;
}
