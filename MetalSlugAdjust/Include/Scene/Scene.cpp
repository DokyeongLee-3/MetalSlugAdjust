
#include "Scene.h"
#include "SceneResource.h"

CScene::CScene()
{
	m_Resource = new CSceneResource;

	m_RenderCount = 0;
	m_RenderCapacity = 100;
	m_RenderArray = new CGameObject * [m_RenderCapacity];

}

CScene::~CScene()
{
	SAFE_DELETE_ARRAY(m_RenderArray);

	m_ObjList.clear();

	

	// MainScene이 종료되고 나서는 CSharedPtr<CPlayer>타입인
	// m_Player는 delete되어야 하는데, m_ObjList에서 
	// 빠져나와있기 때문에 자동으로 delete되지 않는다.
	// m_Player에 대입 연산자 오버로딩된 것을 호출하면
	// CSharedPtr에서 기존에 m_Ptr(CPlayer*타입)에 
	// 갖고 있던걸 release하는데 여기서 m_Ptr은 
	// ref count가 1이라서 release하면 0이 돼서
	// delete되고 m_Ptr에는 nullptr이 할당된다
	m_Player = nullptr;

	SAFE_DELETE(m_Resource);
}

CSceneResource* CScene::GetSceneResource() const
{
	return m_Resource;
}


CGameObject* CScene::FindObject(const std::string& Name)
{
	auto iter = m_ObjList.begin();
	auto iterEnd = m_ObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == Name)
			return (*iter);
	}

	return nullptr;
}


bool CScene::Init()
{
	// CreateObject에서 생성되는 object들의 init을 호출하므로
	// 굳이 여기서 m_ObjList안에 object들의 init을 호출 할 필요가 없다
	return true;
}

bool CScene::Update(float DeltaTime)
{
	if(m_Player)
		m_Player->Update(DeltaTime);

	{
		auto	iter = m_ObjList.begin();
		auto	iterEnd = m_ObjList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsActive())
			{
				iter = m_ObjList.erase(iter);
				iterEnd = m_ObjList.end();
				continue;
			}

			(*iter)->Update(DeltaTime * (*iter)->m_TimeScale);
			++iter;
		}
	}

	return false;
}

bool CScene::PostUpdate(float DeltaTime)
{
	if (m_Player)
		m_Player->PostUpdate(DeltaTime);

	{
		auto	iter = m_ObjList.begin();
		auto	iterEnd = m_ObjList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsActive())
			{

				iter = m_ObjList.erase(iter);
				iterEnd = m_ObjList.end();
				continue;
			}

			(*iter)->PostUpdate(DeltaTime * (*iter)->m_TimeScale);
			++iter;
		}
	}

	return false;
}

bool CScene::Render(HDC hDC)
{	
	{
		std::list<CSharedPtr<CGameObject>>::iterator	iter = m_ObjList.begin();
		std::list<CSharedPtr<CGameObject>>::iterator	iterEnd = m_ObjList.end();

		for (; iter != iterEnd; )
		{
			if (!(*iter)->IsActive())
			{
				iter = m_ObjList.erase(iter);
				iterEnd = m_ObjList.end();
				continue;
			}

			(*iter)->Render(hDC);

			++iter;
		}
	}

	return false;
}

