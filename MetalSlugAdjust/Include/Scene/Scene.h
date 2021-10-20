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
	// ObjList에 넣어서 Update, PostUpdate등을 해주는게 아니라
	// 따로 빼서 제일 먼저 Update, PostUpdate등을 처리해준다
	// 왜냐하면 Player의 갱신된 정보를 바탕으로 처리해야 할 것들이 있기 때문
	CSharedPtr<CGameObject>	m_Player;
	// list보다 삽입, 삭제를 빠르게 할 수 있는
	// 동적 배열 사용. 화면 안에 있는 object들만 여기 담아서
	// Rendering 할 것임
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

		// 생성된 모든 객체는 Init전에 Start를 호출하고
		// m_ObjList(혹은 m_mapPrototype)으로 삽입됨
		// 여기서 Start를 해주면 안된다. 왜냐하면
		// Obj->Start();

		// Obj가 push_back인자로 넘어갈 때 복사 T* Ptr을 인자로 받는 
		// 복사 생성자 한번 호출(ref count = 1),
		// vector 외부에 CSharedPtr이 내부에 있는 CSharedPtr로 복사 될 때
		// CSharedPtr<T> Ptr을 인자로 받는 복사 생성자 한 번 호출(ref count = 2)
		// 외부에 CSharedPtr 소멸되면서 소멸자 호출(Ref count = 1)
		m_ObjList.push_back(Obj);

		return Obj;
	}

};