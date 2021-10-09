
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

	

	// MainScene�� ����ǰ� ������ CSharedPtr<CPlayer>Ÿ����
	// m_Player�� delete�Ǿ�� �ϴµ�, m_ObjList���� 
	// ���������ֱ� ������ �ڵ����� delete���� �ʴ´�.
	// m_Player�� ���� ������ �����ε��� ���� ȣ���ϸ�
	// CSharedPtr���� ������ m_Ptr(CPlayer*Ÿ��)�� 
	// ���� �ִ��� release�ϴµ� ���⼭ m_Ptr�� 
	// ref count�� 1�̶� release�ϸ� 0�� �ż�
	// delete�ǰ� m_Ptr���� nullptr�� �Ҵ�ȴ�
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
	// CreateObject���� �����Ǵ� object���� init�� ȣ���ϹǷ�
	// ���� ���⼭ m_ObjList�ȿ� object���� init�� ȣ�� �� �ʿ䰡 ����
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

