#pragma once

#include "../Resource/Texture.h"
#include "../Resource/AnimationSequence.h"

class CSceneResource
{
	friend class CScene;

private:
	CSceneResource();
	~CSceneResource();

private:
	std::unordered_map<std::string, CSharedPtr<CTexture>>	m_mapTexture;
	std::unordered_map<std::string, CSharedPtr<CAnimationSequence>>	m_mapAnimationSequence;

public:
	bool LoadTexture(const std::string& Name, const TCHAR* FileName,
		const std::string& PathName = TEXTURE_PATH);
	// �ִϸ��̼��� Frame������� ������ load�Ϸ��� �� ��
	bool LoadTexture(const std::string& Name, const std::vector<std::wstring>& vecFileName,
		const std::string& PathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& Name,
		const TCHAR* FullPath);
	CTexture* FindTexture(const std::string& Name);
	void SetTextureColorKey(const std::string& Name,
		const unsigned char r, const unsigned char g,
		const unsigned char b, int Index = 0);

public:
	// CreateAnimationSequence�Լ����� Texture(�̹� load �Ǿ��ٸ�
	// 1��° CreateAnimationSequence�� ���, load�� ���� �ؾ��Ѵٸ�
	// 2��°�� 3��° CreateAnimationSequence�� ���)�� �Բ�
	// CAnimationSequence�� binding�ϴ� ������ �Ѵ�.


	// �̹� texture�� load�Ǿ CSceneResource��
	// m_mapAnimationSequence�� CResourceManager��
	// m_mapAnimationSequence�� TextureName�� ����
	// Texture�� �̹� ��� �ִ� ���
	bool CreateAnimationSequence(const std::string& SequenceName,
		const std::string& TextureName);

	// TextureName�� ���� Texture�� load�ϸ鼭 ���ÿ�
	// �� Texture�� CAnimationSequence�� binding ����� 
	// �� �� ����ϴ� �Լ�
	bool CreateAnimationSequence(const std::string& SequenceName,
		const std::string& TextureName,
		const TCHAR* FileName,
		const std::string& PathName = TEXTURE_PATH);
	bool CreateAnimationSequence(const std::string& SequenceName,
		const std::string& TextureName,
		const std::vector<std::wstring>& vecFileName,
		const std::string& PathName = TEXTURE_PATH);
	// ���� CreateAnimationSequence�� �ٸ��� CResourceManage ��ġ�� �ʰ�
	// �ٷ� CSceneResource�� m_mapAnimationSequence���� Sequence ã�Ƽ�
	// Sequence�� AddFrameData ȣ�� 
	void AddAnimationFrameData(const std::string& SequenceName,
		const Vector2& StartPos,
		const Vector2& Size);
	void AddAnimationFrameData(const std::string& SequenceName,
		float PosX, float PosY, float SizeX, float SizeY);

	CAnimationSequence* FindAnimationSequence(const std::string& Name);

};

