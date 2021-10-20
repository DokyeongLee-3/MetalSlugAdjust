#pragma once

#include "../GameInfo.h"
#include "../Object/GameObject.h"

class CScene
{
	friend class CSceneManager;

protected:
	CScene();
	virtual ~CScene();

private:
	class CSceneResource* m_Resource;

public:
	CSceneResource* GetSceneResource()	const;


protected:
	std::list<CSharedPtr<CGameObject>>	m_ObjList;

private:
	// ObjList�� �־ Update, PostUpdate���� ���ִ°� �ƴ϶�
	// ���� ���� ���� ���� Update, PostUpdate���� ó�����ش�
	// �ֳ��ϸ� Player�� ���ŵ� ������ �������� ó���ؾ� �� �͵��� �ֱ� ����
	CSharedPtr<CGameObject>	m_Player;
	// list���� ����, ������ ������ �� �� �ִ�
	// ���� �迭 ���. ȭ�� �ȿ� �ִ� object�鸸 ���� ��Ƽ�
	// Rendering �� ����
	CGameObject** m_RenderArray;
	int m_RenderCount;
	int m_RenderCapacity;

public:
	virtual bool Init();
	virtual bool Update(float DeltaTime);
	virtual bool PostUpdate(float DeltaTime);
	virtual bool Render(HDC hDC);

public:
	CGameObject* FindObject(const std::string& Name);

public:
	template <typename T>
	T* CreateObject(const std::string& Name,
		const Vector2& Pos = Vector2(0.f, 0.f),
		const Vector2& Size = Vector2(100.f, 100.f))
	{
		T* Obj = new T;

		Obj->SetScene(this);
		Obj->SetPos(Pos);
		Obj->SetSize(Size);
		Obj->SetName(Name);

		if (!Obj->Init())
		{
			SAFE_DELETE(Obj);
			return nullptr;
		}

		// ������ ��� ��ü�� Init���� Start�� ȣ���ϰ�
		// m_ObjList(Ȥ�� m_mapPrototype)���� ���Ե�
		// ���⼭ Start�� ���ָ� �ȵȴ�. �ֳ��ϸ�
		// Obj->Start();

		// Obj�� push_back���ڷ� �Ѿ �� ���� T* Ptr�� ���ڷ� �޴� 
		// ���� ������ �ѹ� ȣ��(ref count = 1),
		// vector �ܺο� CSharedPtr�� ���ο� �ִ� CSharedPtr�� ���� �� ��
		// CSharedPtr<T> Ptr�� ���ڷ� �޴� ���� ������ �� �� ȣ��(ref count = 2)
		// �ܺο� CSharedPtr �Ҹ�Ǹ鼭 �Ҹ��� ȣ��(Ref count = 1)
		m_ObjList.push_back(Obj);

		return Obj;
	}

};