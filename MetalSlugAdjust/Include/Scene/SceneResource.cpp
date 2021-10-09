
#include "SceneResource.h"
#include "../Resource/ResourceManager.h"

CSceneResource::CSceneResource()
{
}

CSceneResource::~CSceneResource()
{
	{
		auto iter = m_mapAnimationSequence.begin();
		auto iterEnd = m_mapAnimationSequence.end();

		for (; iter != iterEnd;)
		{
			std::string Name = iter->first;

			iter = m_mapAnimationSequence.erase(iter);

			CResourceManager::GetInst()->ReleaseAnimationSequence(Name);
		}
	}
	
	{
		auto iter = m_mapTexture.begin();
		auto iterEnd = m_mapTexture.end();

		for (; iter != iterEnd;)
		{
			std::string Name = iter->first;
			iter = m_mapTexture.erase(iter);

			CResourceManager::GetInst()->ReleaseTexture(Name);
		}
	}
}

bool CSceneResource::LoadTexture(const std::string& Name,
	const TCHAR* FileName, const std::string& PathName)
{
	if (FindTexture(Name))
		return true;

	if (!CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName))
		return false;

	CTexture* Texture = CResourceManager::GetInst()->FindTexture(Name);

	m_mapTexture.insert(std::make_pair(Name, Texture));

	return true;
}

bool CSceneResource::LoadTextureFullPath(const std::string& Name,
	const TCHAR* FullPath)
{
	if (FindTexture(Name))
		return true;

	if (!CResourceManager::GetInst()->LoadTextureFullPath(Name, FullPath))
		return false;

	CTexture* Texture = CResourceManager::GetInst()->FindTexture(Name);

	m_mapTexture.insert(std::make_pair(Name, Texture));

	return true;
}

bool CSceneResource::LoadTexture(const std::string& Name,
	const std::vector<std::wstring>& vecFileName,
	const std::string& PathName)
{
	if (FindTexture(Name))
		return true;

	if (!CResourceManager::GetInst()->LoadTexture(Name, vecFileName, PathName))
		return false;

	CTexture* Texture = CResourceManager::GetInst()->FindTexture(Name);

	m_mapTexture.insert(std::make_pair(Name, Texture));

	return true;
}

CTexture* CSceneResource::FindTexture(const std::string& Name)
{
	auto iter = m_mapTexture.find(Name);

	if (iter == m_mapTexture.end())
		return nullptr;

	return iter->second;
}

void CSceneResource::SetTextureColorKey(
	const std::string& Name,
	const unsigned char r, const unsigned char g,
	const unsigned char b, int Index)
{
	CResourceManager::GetInst()->SetTextureColorKey(Name, r, g, b, Index);

}

bool CSceneResource::CreateAnimationSequence(
	const std::string& SequenceName,
	const std::string& TextureName)
{
	if (FindAnimationSequence(SequenceName))
		return true;

	if (!CResourceManager::GetInst()->CreateAnimationSequence
	(SequenceName, TextureName))
		return false;

	CAnimationSequence* Sequence = CResourceManager::GetInst()->FindAnimationSequence(SequenceName);

	m_mapAnimationSequence.insert(std::make_pair(SequenceName, Sequence));

	return true;
}

bool CSceneResource::CreateAnimationSequence(
	const std::string& SequenceName,
	const std::string& TextureName,
	const TCHAR* FileName, const std::string& PathName)
{
	if (FindAnimationSequence(SequenceName))
		return true;

	// LoadTexture ȣ���ϸ� CSceneResource�� m_mapTexture����,
	// ResourceManager�� m_mapTexture���� �ش� Texture�� ���Եȴ�
	LoadTexture(TextureName, FileName, PathName);

	// ���⼭ �� CResourceManager�� �����ε��� 
	// CreateAnimationSequence �Լ��߿� �� �Լ��� SceneResource����
	// ����ϳĸ� CResourceManager�� �����ε��� 
	// CreateAnimationSequence �Լ��鰣�� ���̴� CreateAnimationSequence
	// ���ο��� LoadTexture ȣ�� ���� Ȥ�� � LoadTexture�� �θ�����
	// ���̸� �ִµ� ������ LoadTexture�� �θ����ν�, SceneResource��
	// LoadTextur���ο��� ResourceManager�� LoadTexture���� ȣ���ϹǷ�,
	// CreateAnimation�� �Ʒ� �Լ� ���� �ٸ� �����ε��� �Լ���
	// �θ��� �ʴ´�. �ٸ� CreateAnimation �Լ��� ���� LoadTexture ������
	// �ι� �ϰ� �� �� �̴�.
	if (!CResourceManager::GetInst()->CreateAnimationSequence(
		SequenceName, TextureName))
		return false;

	CAnimationSequence* Sequence = CResourceManager::GetInst()->FindAnimationSequence(SequenceName);

	m_mapAnimationSequence.insert(std::make_pair(SequenceName, Sequence));

	return true;
}

bool CSceneResource::CreateAnimationSequence(
	const std::string& SequenceName,
	const std::string& TextureName,
	const std::vector<std::wstring>& vecFileName,
	const std::string& PathName)
{
	if (FindAnimationSequence(SequenceName))
		return true;

	LoadTexture(SequenceName, vecFileName, PathName);

	if (!CResourceManager::GetInst()->CreateAnimationSequence(
		SequenceName, TextureName))
		return false;

	CAnimationSequence* Sequence = CResourceManager::GetInst()->FindAnimationSequence(SequenceName);

	m_mapAnimationSequence.insert(std::make_pair(SequenceName, Sequence));

	return true;
}

void CSceneResource::AddAnimationFrameData(
	const std::string& SequenceName,
	const Vector2& StartPos, const Vector2& Size)
{
	CAnimationSequence* Sequence = FindAnimationSequence(SequenceName);

	if (!Sequence)
		return;

	Sequence->AddFrameData(StartPos, Size);
}

void CSceneResource::AddAnimationFrameData(
	const std::string& SequenceName,
	float PosX, float PosY, float SizeX, float SizeY)
{
	CAnimationSequence* Sequence = FindAnimationSequence(SequenceName);

	if (!Sequence)
		return;

	Sequence->AddFrameData(PosX, PosY, SizeX, SizeY);
}

CAnimationSequence* CSceneResource::FindAnimationSequence(const std::string& Name)
{
	auto iter = m_mapAnimationSequence.find(Name);

	if (iter == m_mapAnimationSequence.end())
		return nullptr;

	return iter->second;
}

