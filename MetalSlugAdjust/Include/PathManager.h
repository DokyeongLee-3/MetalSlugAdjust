#pragma once

#include "GameInfo.h"

struct PathInfo
{
	// TCHAR : 유니코드 문자열을 저장하기 위한 타입
	// 프로젝트가 멀티바이트를 사용하면 char로 정의되고
	// 유니코드를 사용하면 wchar_t로 정의된다
	TCHAR Path[MAX_PATH];
	char PathMultibyte[MAX_PATH];
	
	PathInfo() :
		Path{},
		PathMultibyte{}
	{

	}
};

class CPathManager
{

private:
	CPathManager();
	~CPathManager();

private:
	std::unordered_map<std::string, PathInfo*> m_mapPath;


public:
	bool Init();
	bool AddPath(const std::string& Name, const TCHAR* Path,
		const std::string& BaseName = ROOT_PATH);
	const PathInfo* FindPath(const std::string& Name);

private:
	static CPathManager* m_Inst;

public:
	static CPathManager* GetInst()
	{
		if (!m_Inst)
		{
			m_Inst = new CPathManager;
		}
		return m_Inst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(m_Inst);
	}
};

