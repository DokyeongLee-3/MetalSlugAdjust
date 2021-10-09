
#include "Texture.h"
#include "../PathManager.h"
#include "../GameManager.h"

CTexture::CTexture()
{
}

CTexture::~CTexture()
{
	size_t Size = m_vecTextureInfo.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(m_vecTextureInfo[i]);
	}
}

bool CTexture::LoadTexture(const std::string& Name,
	const TCHAR* FileName, const std::string& PathName)
{
	const PathInfo* Info = CPathManager::GetInst()->FindPath(PathName);

	TCHAR FullPath[MAX_PATH] = {};

	if (Info)
		lstrcpy(FullPath, Info->Path);
	lstrcat(FullPath, FileName);

	return LoadTextureFullPath(Name, FullPath);
}

bool CTexture::LoadTextureFullPath(const std::string& Name,
	const TCHAR* FullPath)
{
	SetName(Name);

	TextureInfo* Info = new TextureInfo;

	// 1. memoryDC �����(�׸��� ����)
	Info->hDC = CreateCompatibleDC(CGameManager::GetInst()->GetWindowDC());

	// 2. � �׸��� �׸����� ���� ������ LoadImage�� ���ͼ�
	// HBITMAPŸ���� ������ �����ϱ�
	Info->hBmp = (HBITMAP)LoadImage(CGameManager::GetInst()->GetWindowInstance(),
		FullPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// 3. memoryDC��� �׸��� �������ٰ� � �׸��� 
	// �׸����� ���� ����(HBITMAP Ÿ�� ����)�� 
	// SelectObject�� �������ֱ�
	Info->hPrev = (HBITMAP)SelectObject(Info->hDC, Info->hBmp);

	// 4. ��Ʈ�� ����(ex.���� / ���� ũ��)�� GetObject�� ���ͼ� BITMAPŸ�� ������ �����ϱ�
	GetObject(Info->hBmp, sizeof(BITMAP), &Info->BmpInfo);

	m_vecTextureInfo.push_back(Info);

	if (m_vecTextureInfo.size() == 1)
		m_TextureType = ETexture_Type::Atlas;

	else
		m_TextureType = ETexture_Type::Frame;

	return true;
}

bool CTexture::LoadTexture(const std::string& Name,
	const std::vector<std::wstring>& vecFileName,
	const std::string& PathName)
{
	const PathInfo* Info = CPathManager::GetInst()->FindPath(Name);

	size_t Size = vecFileName.size();

	for (size_t i = 0; i < Size; ++i)
	{
		TCHAR FullPath[MAX_PATH] = {};

		if (Info)
			lstrcpy(FullPath, Info->Path);
		lstrcat(FullPath, vecFileName[i].c_str());

		if (!LoadTexture(Name, FullPath))
			return false;
	}

	if (m_vecTextureInfo.size() == 1)
		m_TextureType = ETexture_Type::Atlas;

	else
		m_TextureType = ETexture_Type::Frame;

	return true;
}

void CTexture::Render(HDC hDC, const Vector2& WindowPos,
	const Vector2& ImgPos, const Vector2& Size,
	int Index)
{
	if (m_vecTextureInfo[Index]->ColorKeyEnable)
	{
		// 1�� ���� : ��� ��� DC
		// 2�� ���� : ����� ������ �� x ��ǥ
		// 3�� ���� : ����� ������ �� y ��ǥ
		// 4�� ���� : ����� ������ �󿡼� width
		// 5�� ���� : ����� ������ �󿡼� height
		// 6�� ���� : ����� �̹����� DC
		// 7�� ���� : ����� �̹��� �󿡼� ���� x ��ǥ
		// 8�� ���� : ����� �̹��� �󿡼� ���� y ��ǥ
		// 9�� ���� : ����� �̹��� ���� ũ��
		// 10�� ���� : ����� �̹��� ���� ũ��
		// 11�� ���� : ColorKey
		TransparentBlt(hDC, (int)WindowPos.x, (int)WindowPos.y
			, (int)Size.x, (int)Size.y,
			m_vecTextureInfo[Index]->hDC,
			(int)ImgPos.x, (int)ImgPos.y,
			(int)Size.x, (int)Size.y,
			m_vecTextureInfo[Index]->ColorKey);
	}

	else
	{
		BitBlt(hDC, (int)WindowPos.x, (int)WindowPos.y,
			(int)Size.x, (int)Size.y,
			m_vecTextureInfo[Index]->hDC,
			(int)ImgPos.x, (int)ImgPos.y,
			SRCCOPY);
	}


}
