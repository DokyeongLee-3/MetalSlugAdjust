#pragma once

#include "../GameInfo.h"

class CSceneCollision
{
	friend class CScene;

private:
	CSceneCollision();
	~CSceneCollision();

private:
	class CScene* m_Scene;
	std::vector<class CCollider*> m_vecCollider;
	std::vector<class CUIWindow*> m_vecUIWindow;
	// ���콺�� �浹�� Widget
	class CUIWidget* m_MouseHoveredWidget;
	class CUIWidget* m_SelectWidget;
	// Mouse�� �浹�� �浹ü. ���콺�� �浹�ߴٸ�
	// �� �浹ü�� ���� �ִ� bool m_MouseCollision�� true��
	// ������༭ �浹ü �׵θ��� ������ Pen���� �׸�����
	// �ϱ� ���ؼ� Mouse�� �浹�� �浹ü�� �� �ʿ䰡 �ִ�
	class CCollider* m_MouseCollision;
	
public:
	void SetSelectWidget(class CUIWidget* Widget)
	{
		m_SelectWidget = Widget;
	}

	void ClearMouseCollision(class CCollider* Collider)
	{
		if (m_MouseCollision == Collider)
			m_MouseCollision = nullptr;
	}

public:
	void AddCollider(class CCollider* Collider);
	// CGameObject::Collision���� �� object���� m_ColliderList��
	// ������ �ִ� Collider���� SceneCollision�� m_vecCollider��
	// �ְ�, Scene::Collision���� SceneCollision::Collision ȣ�� 
	void Collision(float DeltaTime);
	void AddUIWindow(class CUIWindow* Window);
	void CollisionMouse(float DeltaTime);

private:
	static int SortY(const void* Src, const void* Dest);
};
