
#include "GameManager.h"
#include "Scene/SceneManager.h"
#include "Resource/ResourceManager.h"
#include "Collision/CollisionManager.h"
#include "Scene/MainScene.h"
#include "PathManager.h"
#include "Timer.h"
#include "Input.h"

CGameManager* CGameManager::m_Inst = nullptr;
bool CGameManager::m_Loop = true;

CGameManager::CGameManager() :
	m_Timer(nullptr),
	m_TimeScale(0.f),
	m_PrevTimeScale(1.f),
	m_IsPause(true)
{
}

CGameManager::~CGameManager()
{
	CSceneManager::DestroyInst();

	CInput::DestroyInst();

	CResourceManager::DestroyInst();

	CPathManager::DestroyInst();

	SAFE_DELETE(m_Timer);

	SelectObject(m_hBackDC, m_hPrevBackBmp);

	DeleteObject(m_hBackBmp);

	DeleteDC(m_hBackDC);

	ReleaseDC(m_hWnd, m_hDC);
}

bool CGameManager::Init(HINSTANCE hInst)
{
	m_hInst = hInst;

	m_RS.Width = 1024;
	m_RS.Height = 728;

	Register();
	Create();

	m_hDC = GetDC(m_hWnd);

	if (!CPathManager::GetInst()->Init())
		return false;

	if (!CResourceManager::GetInst()->Init())
		return false;

	if (!CInput::GetInst()->Init(m_hWnd))
		return false;

	if (!CSceneManager::GetInst()->Init())
		return false;

	CSceneManager::GetInst()->CreateScene<CMainScene>();

	m_Timer = new CTimer;

	// 백버퍼의 DC를 생성
	m_hBackDC = CreateCompatibleDC(m_hDC);

	// 화면 DC와 호환되는 BitMap을 생성
	m_hBackBmp = CreateCompatibleBitmap(m_hDC, m_RS.Width,
		m_RS.Height);

	// 화면 DC와 호환되는 BitMap을 백버퍼의 DC에 설정 
	m_hPrevBackBmp = (HBITMAP)SelectObject(m_hBackDC, m_hBackBmp);

	return true;
}

int CGameManager::Run()
{
	MSG msg;

	while (m_Loop)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Logic();
		}
	}

	return (int)msg.wParam;
}

void CGameManager::Logic()
{
	float DeltaTime = m_Timer->Update() * m_TimeScale;

	CResourceManager::GetInst()->Update();

	CInput::GetInst()->Update(DeltaTime);

	if (Update(DeltaTime))
		return;

	if (PostUpdate(DeltaTime))
		return;

	Render(DeltaTime);
}

void CGameManager::Input()
{
}

bool CGameManager::Update(float DeltaTime)
{
	return CSceneManager::GetInst()->Update(DeltaTime);
}

bool CGameManager::PostUpdate(float DeltaTime)
{
	return CSceneManager::GetInst()->PostUpdate(DeltaTime);
}

void CGameManager::Render(float DeltaTime)
{
	Rectangle(m_hBackDC, -1, -1, m_RS.Width + 1, m_RS.Height + 1);

	CSceneManager::GetInst()->Render(m_hBackDC);

	BitBlt(m_hDC, 0, 0, m_RS.Width, m_RS.Height,
		m_hBackDC, 0, 0, SRCCOPY);
}

float CGameManager::GetDeltaTime() const
{
	return m_Timer->GetDeltaTime() * m_TimeScale;
}

void CGameManager::Exit()
{
	DestroyWindow(m_hWnd);
}

ATOM CGameManager::Register()
{
	WNDCLASSEXW wcex;
	
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInst;
	wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = TEXT("MetalSlugAdjust");
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	return RegisterClassExW(&wcex);

}

BOOL CGameManager::Create()
{
	m_hWnd = CreateWindowW(TEXT("MetalSlugAdjust"), TEXT("MetalSlugAdjust"),
		WS_OVERLAPPEDWINDOW, 100, 100, m_RS.Width, m_RS.Height, nullptr, nullptr,
		m_hInst, nullptr);

	if (!m_hWnd)
	{
		return FALSE;
	}

	RECT rc = { 0, 0, m_RS.Width, m_RS.Height };

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	SetWindowPos(m_hWnd, HWND_TOPMOST, 100, 100, 
		rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);


	return 0;
}

LRESULT CGameManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		m_Loop = false;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
