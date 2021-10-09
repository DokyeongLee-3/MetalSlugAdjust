
#include "ResourceManager.h"
#include "../PathManager.h"

CResourceManager* CResourceManager::m_Inst = nullptr;

CResourceManager::CResourceManager()
{
}

CResourceManager::~CResourceManager()
{
	m_mapAnimationSequence.clear();
	m_mapTexture.clear();
}

bool CResourceManager::Init()
{
	return true;
}

void CResourceManager::Update()
{
}

bool CResourceManager::LoadTexture(const std::string& Name,
	const TCHAR* FileName, const std::string& PathName)
{
	CTexture* Texture = FindTexture(Name);

	if(Texture)
		return true;

	Texture = new CTexture;

	if (!Texture->LoadTexture(Name, FileName, PathName))
	{
		SAFE_RELEASE(Texture);
		return false;
	}

	m_mapTexture.insert(std::make_pair(Name, Texture));

	return true;
}

bool CResourceManager::LoadTextureFullPath(const std::string& Name,
	const TCHAR* FullPath)
{
	CTexture* Texture = FindTexture(Name);

	if (Texture)
		return true;

	Texture = new CTexture;

	if (!Texture->LoadTextureFullPath(Name, FullPath))
	{
		SAFE_RELEASE(Texture);
		return false;
	}

	m_mapTexture.insert(std::make_pair(Name, Texture));

	return true;
}

bool CResourceManager::LoadTexture(const std::string& Name, 
	const std::vector<std::wstring>& vecFileName, 
	const std::string& PathName)
{
	CTexture* Texture = FindTexture(Name);

	if (Texture)
		return true;

	Texture = new CTexture;

	if (!Texture->LoadTexture(Name, vecFileName, PathName))
	{
		SAFE_RELEASE(Texture);
		return false;
	}

	m_mapTexture.insert(std::make_pair(Name, Texture));

	return true;
}

void CResourceManager::SetTextureColorKey(const std::string& Name, 
	const unsigned char r, const unsigned char g,
	const unsigned char b, int Index)
{
	CTexture* Texture = FindTexture(Name);

	if (!Texture)
		return;

	Texture->SetColorKey(r, g, b, Index);
}

void CResourceManager::ReleaseTexture(const std::string& Name)
{
	auto iter = m_mapTexture.find(Name);

	// ResoureManager만 m_mapTexture에 갖고 참조하고 있다는 뜻
	if (iter->second->GetRefCount() == 1)
	{
		// SharedPtr의 소멸자 호출
		m_mapTexture.erase(iter);
	}

}

CTexture* CResourceManager::FindTexture(const std::string& Name)
{
	auto iter = m_mapTexture.find(Name);

	if (iter == m_mapTexture.end())
		return nullptr;

	return iter->second;
}

bool CResourceManager::CreateAnimationSequence(
	const std::string& SequenceName,
	const std::string& TextureName)
{
	CAnimationSequence* Sequence = FindAnimationSequence(SequenceName);

	if (Sequence)
		return true;

	Sequence = new CAnimationSequence;

	CTexture* Texture = FindTexture(TextureName);

	if (!Sequence->Init(SequenceName, Texture))
	{
		SAFE_DELETE(Sequence);
		return false;
	}

	m_mapAnimationSequence.insert(std::make_pair(SequenceName, Sequence));

	return true;
}

bool CResourceManager::CreateAnimationSequence(
	const std::string& SequenceName,
	const std::string& TextureName, 
	const TCHAR* FileName, const std::string& PathName)
{
	CAnimationSequence* Sequence = FindAnimationSequence(SequenceName);

	if (Sequence)
		return true;

	if (!LoadTexture(TextureName, FileName, PathName))
		return false;

	Sequence = new CAnimationSequence;

	CTexture* Texture = FindTexture(TextureName);

	if (!Sequence->Init(SequenceName, Texture))
	{
		SAFE_RELEASE(Sequence);
		return false;
	}

	m_mapAnimationSequence.insert(std::make_pair(SequenceName, Sequence));

	return true;
}

bool CResourceManager::CreateAnimationSequence(
	const std::string& SequenceName, 
	const std::string& TextureName, 
	const std::vector<std::wstring>& vecFileName, 
	const std::string& PathName)
{
	CAnimationSequence* Sequence = FindAnimationSequence(SequenceName);

	if (Sequence)
		return true;

	if (!LoadTexture(TextureName, vecFileName, PathName))
		return false;

	Sequence = new CAnimationSequence;

	CTexture* Texture = FindTexture(TextureName);

	if (!Sequence->Init(SequenceName, Texture))
	{
		SAFE_RELEASE(Sequence);
		return false;
	}

	m_mapAnimationSequence.insert(std::make_pair(SequenceName, Sequence));

	return true;
}

void CResourceManager::AddAnimationFrameData(
	const std::string& SequenceName, 
	const Vector2& StartPos, const Vector2& Size)
{
	CAnimationSequence* Sequence = FindAnimationSequence(SequenceName);

	if (!Sequence)
		return;

	Sequence->AddFrameData(StartPos, Size);
}

void CResourceManager::AddAnimationFrameData(
	const std::string& SequenceName, 
	float PosX, float PosY, float SizeX, float SizeY)
{
	CAnimationSequence* Sequence = FindAnimationSequence(SequenceName);

	if (!Sequence)
		return;

	Sequence->AddFrameData(PosX, PosY, SizeX, SizeY);
}

void CResourceManager::ReleaseAnimationSequence(
	const std::string& Name)
{
	auto	iter = m_mapAnimationSequence.find(Name);

	if (iter->second->GetRefCount() == 1)
		m_mapAnimationSequence.erase(iter);
}

CAnimationSequence* CResourceManager::FindAnimationSequence(const std::string& Name)
{
	auto iter = m_mapAnimationSequence.find(Name);

	if (iter == m_mapAnimationSequence.end())
		return nullptr;

	return iter->second;
}


