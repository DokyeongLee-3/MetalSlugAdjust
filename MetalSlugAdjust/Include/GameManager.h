#pragma once

#include "GameInfo.h"
#include <list>

class CGameManager
{
private:
	CGameManager();
	~CGameManager();

public:
	bool Init(HINSTANCE hInst);
	int Run();

private:
	void Logic();
	void Input();
	bool Update(float DeltaTime);
	bool PostUpdate(float DeltaTime);
	void Render(float DeltaTime);

private:
	static bool m_Loop;
	HINSTANCE m_hInst;
	HWND m_hWnd;
	HDC m_hDC;
	HDC m_hBackDC;
	HBITMAP	m_hBackBmp;
	HBITMAP	m_hPrevBackBmp;
	Resolution m_RS;
	class CTimer* m_Timer;
	float m_TimeScale;
	float m_PrevTimeScale;
	bool m_IsPause;

public:
	HDC GetBackBuffer()	const
	{
		return m_hBackDC;
	}

	Resolution GetResolution()	const
	{
		return m_RS;
	}

	HDC GetWindowDC()	const
	{
		return m_hDC;
	}

	HWND GetWindowHandle()	const
	{
		return m_hWnd;
	}

	HINSTANCE GetWindowInstance()	const
	{
		return m_hInst;
	}

public:
	void SetPrevTimeScale(float TimeScale)
	{
		m_PrevTimeScale = TimeScale;

		if (m_PrevTimeScale == 0.f)
			m_IsPause = true;
		else
			m_IsPause = false;
	}

	float GetPrevTimeScale()	const
	{
		return m_PrevTimeScale;
	}


	void SetTimeScale(float TimeScale)
	{
		m_TimeScale = TimeScale;

		if (m_TimeScale == 0.f)
			m_IsPause = true;
		else
			m_IsPause = false;
	}

	float GetTimeScale()	const 
	{
		return m_TimeScale;
	}

	bool GetIsPause()	const
	{
		return m_IsPause;
	}

	float GetDeltaTime()	const;
	void Exit();

private:
	ATOM Register();
	BOOL Create();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	static CGameManager* m_Inst;

public:
	static CGameManager* GetInst()
	{
		if (!m_Inst)
		{
			m_Inst = new CGameManager;
		}
		return m_Inst;
	}

	static void DestoryInst()
	{
		SAFE_DELETE(m_Inst);
	}
};

