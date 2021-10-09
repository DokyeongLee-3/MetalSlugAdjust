
#include "Input.h"
#include "Resource/ResourceManager.h"

CInput* CInput::m_Inst = nullptr;

CInput::CInput()
{
	// �̸� 256���� KeyState�� �־����
	// m_vecAddKey�� �߰��� Ű���� m_vecKeyState�� �ε�������
	// �����ؼ� UpdateKeyState���� ���
	m_vecKeyState.resize(KEYCOUNT_MAX);

	for (int i = 0; i < KEYCOUNT_MAX; ++i)
	{
		m_vecKeyState[i].Key = i;
	}

	m_Ctrl = false;
	m_Alt = false;
	m_Shift = false;
}

CInput::~CInput()
{
	std::unordered_map<std::string, KeyInfo*>::iterator iter = m_mapInfo.begin();
	std::unordered_map<std::string, KeyInfo*>::iterator iterEnd = m_mapInfo.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}

bool CInput::CreateKey(const std::string& Name, int Key)
{
	KeyInfo* Info = FindKeyInfo(Name);

	if(Info)
		return false;

	Info = new KeyInfo;

	Info->Name = Name;
	Info->State.Key = Key;

	m_mapInfo.insert(std::make_pair(Name, Info));

	bool Add = false;

	size_t Size = m_vecAddKey.size();

	for (size_t i = 0; i < Size; ++i)
	{
		// �̹� ���� Ű�� �߰��Ǿ� �ִ� ���
		if (m_vecAddKey[i] == Key)
		{
			Add = true;
			break;
		}
	}

	if (!Add)
		m_vecAddKey.push_back(Key);

	return true;
}

bool CInput::SetCtrlKey(const std::string& Name, bool State)
{
	KeyInfo* Info = FindKeyInfo(Name);

	if (!Info)
		return false;

	Info->Ctrl = State;

	return true;
}

bool CInput::SetAltKey(const std::string& Name, bool State)
{
	KeyInfo* Info = FindKeyInfo(Name);

	if (!Info)
		return false;

	Info->Alt = State;

	return true;
}

bool CInput::SetShiftKey(const std::string& Name, bool State)
{
	KeyInfo* Info = FindKeyInfo(Name);

	if (!Info)
		return false;

	Info->Shift = State;

	return true;
}

KeyInfo* CInput::FindKeyInfo(const std::string& Name)
{
	std::unordered_map<std::string, KeyInfo*>::iterator iter = m_mapInfo.find(Name);

	if (iter == m_mapInfo.end())
		return nullptr;

	return iter->second;
}

bool CInput::Init(HWND hWnd)
{
	m_hWnd = hWnd;

	CreateKey("MoveUp", 'W');
	CreateKey("MoveDown", 'S');
	CreateKey("MoveLeft", 'A');
	CreateKey("MoveRight", 'D');
	CreateKey("Fire", VK_SPACE);

	CreateKey("Pause", 'P');
	CreateKey("Resume", 'R');
	CreateKey("IncreaseTimeScale", VK_NUMPAD9);
	CreateKey("DecreaseTimeScale", VK_NUMPAD7);

	CreateKey("NextFrame", VK_NUMPAD3);
	CreateKey("PrevFrame", VK_NUMPAD1);

	CreateKey("IncreaseXOffset", VK_NUMPAD6);
	CreateKey("IncreaseYOffset", VK_NUMPAD8);
	CreateKey("DecreaseXOffset", VK_NUMPAD4);
	CreateKey("DecreaseYOffset", VK_NUMPAD2);
	CreateKey("SwapControl", VK_NUMPAD0);

	CreateKey("SaveInfo", VK_ADD);
	CreateKey("LoadInfo", VK_SUBTRACT);

	CreateKey("PrevAnimation", VK_DIVIDE);
	CreateKey("NextAnimation", VK_MULTIPLY);

	CreateKey("IncreaseXFrameSize", VK_RIGHT);
	CreateKey("DecreaseXFrameSize", VK_LEFT);
	CreateKey("IncreaseYFrameSize", VK_UP);
	CreateKey("DecreaseYFrameSize", VK_DOWN);

	CreateKey("RightXStartPos", 'L');
	CreateKey("LeftXStartPos", 'J');
	CreateKey("UpYStartPos", 'I');
	CreateKey("DownYStartPos", 'K');

	CreateKey("RightXStartPos5", 'Z');
	CreateKey("LeftXStartPos5", 'X');

	CreateKey("MergeText", 'M');

	ShowCursor(FALSE);

	return true;
}

void CInput::Update(float DeltaTime)
{
	// ������ Ű�� �ִٸ� ǥ�����ִ� �Լ�
	UpdateKeyState();

	UpdateMouse(DeltaTime);

	// Ű�� ���������� Ű�� �ش��ϴ� �ݹ��� ȣ�����ִ� �Լ�
	UpdateKeyInfo(DeltaTime);

}

void CInput::Render(HDC hDC)
{

}

void CInput::UpdateMouse(float DeltaTime)
{
	POINT ptMouse;

	// �Ʒ� �Լ��� ���콺 ��ġ�� ��ũ�� ��ǥ �������� �����ش�
	GetCursorPos(&ptMouse);

	// ��ũ�� ��ǥ�� Ŭ���̾�Ʈ ��ǥ�� ��ȯ�Ѵ�
	ScreenToClient(m_hWnd, &ptMouse);

	//Vector2 Pos;
	//Pos.x = (float)ptMouse.x;
	//Pos.y = (float)ptMouse.y;

}

void CInput::UpdateKeyState()
{
	size_t Size = m_vecAddKey.size();

	for (size_t i = 0; i < Size; ++i)
	{
		int Key = m_vecAddKey[i];

		if (GetAsyncKeyState(Key) & 0x8000)
		{
			if (!m_vecKeyState[Key].State[KeyState_Down] &&
				!m_vecKeyState[Key].State[KeyState_Push])
			{
				m_vecKeyState[Key].State[KeyState_Down] = true;
				m_vecKeyState[Key].State[KeyState_Push] = true;
			}

			else
			{
				m_vecKeyState[Key].State[KeyState_Down] = false;
			}
		}

		else if (m_vecKeyState[Key].State[KeyState_Push])
		{
			m_vecKeyState[Key].State[KeyState_Down] = false;
			m_vecKeyState[Key].State[KeyState_Push] = false;
			m_vecKeyState[Key].State[KeyState_Up] = true;
		}

		else if(m_vecKeyState[Key].State[KeyState_Up])
		{
			m_vecKeyState[Key].State[KeyState_Up] = false;
		}
	}

	if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
	{
		m_Ctrl = true;
	}

	else
		m_Ctrl = false;

	if (GetAsyncKeyState(VK_MENU) & 0x8000)
	{
		m_Alt = true;
	}

	else
		m_Alt = false;

	if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
	{
		m_Shift = true;
	}

	else
		m_Shift = false;
}

void CInput::UpdateKeyInfo(float DeltaTime)
{
	std::unordered_map<std::string, KeyInfo*>::iterator iter = m_mapInfo.begin();
	std::unordered_map<std::string, KeyInfo*>::iterator iterEnd = m_mapInfo.end();

	for (; iter != iterEnd; ++iter)
	{
		int Key = iter->second->State.Key;

		if (m_vecKeyState[Key].State[KeyState_Down] &&
			iter->second->Ctrl == m_Ctrl &&
			iter->second->Shift == m_Shift &&
			iter->second->Alt == m_Alt)
		{
			if (iter->second->Callback[KeyState_Down])
				iter->second->Callback[KeyState_Down](DeltaTime);
		}

		if (m_vecKeyState[Key].State[KeyState_Push] &&
			iter->second->Ctrl == m_Ctrl &&
			iter->second->Shift == m_Shift &&
			iter->second->Alt == m_Alt)
		{
			if (iter->second->Callback[KeyState_Push])
				iter->second->Callback[KeyState_Push](DeltaTime);
		}

		if (m_vecKeyState[Key].State[KeyState_Up] &&
			iter->second->Ctrl == m_Ctrl &&
			iter->second->Shift == m_Shift &&
			iter->second->Alt == m_Alt)
		{
			if (iter->second->Callback[KeyState_Up])
				iter->second->Callback[KeyState_Up](DeltaTime);
		}
	}

}

void CInput::ClearCallback()
{
	auto iter = m_mapInfo.begin();
	auto iterEnd = m_mapInfo.end();

	for (; iter != iterEnd; ++iter)
	{
		for (int i = 0; i < KeyState_Max; ++i)
		{
			iter->second->Callback[i] = nullptr;
		}
	}
}
