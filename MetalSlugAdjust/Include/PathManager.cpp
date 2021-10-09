#include "PathManager.h"

CPathManager* CPathManager::m_Inst = nullptr;

CPathManager::CPathManager()
{
}

CPathManager::~CPathManager()
{
	auto iter = m_mapPath.begin();
	auto iterEnd = m_mapPath.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}

}

bool CPathManager::Init()
{
	// Bin ���������� ��θ� RootPath�� �����ϰ�
	// Bin ���������� ��θ� ���´�
	TCHAR Path[MAX_PATH] = {};

	// ���� ���������� �ִ� ��� + ��������.exe �����ؼ�
	// ��ü ��θ� ���´�
	GetModuleFileName(0, Path, MAX_PATH);

	int Length = lstrlen(Path);

	for (int i = Length - 1; i > 0; --i)
	{
		// ������������ Ư�����ڴ� �ι� ����� �νİ���
		if (Path[i] == '\\')
		{
			memset(&Path[i + 1], 0, sizeof(TCHAR) * Length - i - 1);
			break;
		}
	}

	PathInfo* Info = new PathInfo;

	lstrcpy(Info->Path, Path);

#ifdef UNICODE
	// �����ڵ� ���ڿ��� ��Ƽ����Ʈ ���ڿ��� ��ȯ�Ѵ�
	// 4��° ���ڷ� -1�� �ָ� 3��° ���� ��ü ���� ��ŭ ��ȯ�Ѵٴ� �ǹ�
	// ���� 5��° ���ڷ� nullptr�� �ָ�, 3��° ���ڸ� ��Ƽ����Ʈ�� ��ȯ�ϴµ�
	// �ʿ��� ����Ʈ���� �������ش�(�ڿ� ������ ���ڵ��� 0����)
	int ConvertLength = WideCharToMultiByte(CP_ACP, 0, Path, -1, nullptr, 0, 0, 0);

	WideCharToMultiByte(CP_ACP, 0, Path, -1, Info->PathMultibyte, ConvertLength, 0, 0);
#else
	strcpy_s(Info->PathMultibyte, Path);
#endif	//UNICODE

	m_mapPath.insert(std::make_pair(ROOT_PATH, Info));

	// RootPath�� Texture�� �ٿ��� TexturePath�� ����
	AddPath(TEXTURE_PATH, TEXT("Texture\\"));

	AddPath(SOUND_PATH, TEXT("Sound\\"));

	AddPath(FONT_PATH, TEXT("Font\\"));

	return true;
}

bool CPathManager::AddPath(const std::string& Name,
	const TCHAR* Path, const std::string& BaseName)
{
	if (FindPath(Name))
		return false;

	const PathInfo* BaseInfo = FindPath(BaseName);

	if (!BaseInfo)
		return false;

	PathInfo* Info = new PathInfo;

	lstrcpy(Info->Path, BaseInfo->Path);
	lstrcat(Info->Path, Path);

#ifdef UNICODE
	int ConvertLength = WideCharToMultiByte(CP_ACP, 0, Info->Path,
		-1, nullptr, 0, 0, 0);

	WideCharToMultiByte(CP_ACP, 0, Info->Path, -1, Info->PathMultibyte,
		ConvertLength, 0, 0);

#else
	strcpy_s(Info->PathMultiByte, Info->Path);
#endif	// UNICODE


	m_mapPath.insert(std::make_pair(Name, Info));

	return true;
}

const PathInfo* CPathManager::FindPath(const std::string& Name)
{
	auto iter = m_mapPath.find(Name);

	if (iter == m_mapPath.end())
		return nullptr;

	return iter->second;
}
