#pragma once

#include "GameInfo.h"
#include "UI/UIImage.h"

enum EMouse_Type
{
	Mouse_Default,
	Mouse_Battle,
	Mouse_End
};

// ���� ����ڰ� ���� Ű ���¸� ����ؼ� ������Ʈ�ϴ� ����ü
struct KeyState
{
	int Key;
	bool State[KeyState_Max];

	KeyState() :
		Key(0),
		State{}
	{

	}
};

// �̸� KeyInfo(ó�� ����ϰ� ����x)�� ����� Ű�� ����س��� KeyState�� ������Ʈ��
// Ű ���¶�, ��ϵ� KeyInfo�� ���ؼ� ������ ����
struct KeyInfo
{
	std::string Name;
	KeyState	State;

	std::function<void(float)>	Callback[KeyState_Max];
	bool Ctrl;
	bool Alt;
	bool Shift;

	KeyInfo() :
		Ctrl(false),
		Alt(false),
		Shift(false)
	{

	}
};

class CInput
{

public:
	CInput();
	~CInput();

private:
	std::unordered_map<std::string, KeyInfo*>	m_mapInfo;
	std::vector<KeyState>	m_vecKeyState;
	// UpdateKeyState���� m_vecAddKey�� ��ϵ� Ű��
	// update�Ϸ��� ������ ��� ����
	std::vector<int>	m_vecAddKey;
	bool m_Ctrl;
	bool m_Alt;
	bool m_Shift;
	HWND m_hWnd;

public:
	bool CreateKey(const std::string& Name, int Key);
	bool SetCtrlKey(const std::string& Name, bool State);
	bool SetAltKey(const std::string& Name, bool State);
	bool SetShiftKey(const std::string& Name, bool State);

private:
	KeyInfo* FindKeyInfo(const std::string& Name);

public:
	bool Init(HWND hWnd);
	void Update(float DeltaTime);
	void Render(HDC hDC);

private:
	void UpdateMouse(float DeltaTime);
	void UpdateKeyState();
	void UpdateKeyInfo(float DeltaTime);

public:
	void ClearCallback();

public:
	template <typename T>
	void SetCallback(const std::string& Name, EKeyState State, T* Obj, void(T::* Func)(float))
	{
		KeyInfo* Info = FindKeyInfo(Name);

		Info->Callback[State] = std::bind(Func, Obj, std::placeholders::_1);
	}

private:
	static CInput* m_Inst;

public:
	static CInput* GetInst()
	{
		if (!m_Inst)
			m_Inst = new CInput;

		return m_Inst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(m_Inst);
	}
};

