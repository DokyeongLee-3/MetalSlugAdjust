#pragma once

#include "../Ref.h"
#include "../Resource/Texture.h"
#include "../Animation/Animation.h"
#include "../Collision/Collider.h"

class CGameObject	:
	public CRef
{
	friend class CScene;
	friend class CMainScene;

public:
	CGameObject();
	CGameObject(const CGameObject& obj);
	virtual ~CGameObject();

protected:
	// ������ � scene�� �����ִ��� ����Ű�� ���
	class CScene* m_Scene;
	Vector2		m_PrevPos;
	Vector2		m_Pos;
	// ȭ����� ��ġ(m_Pos�� World���� ��ġ)
	Vector2		m_RenderPos;
	Vector2		m_Size;
	Vector2		m_Pivot;
	// �� �����Ӵ� �̵��� ũ��� ������ ���� �ִ� ����
	Vector2		m_Velocity;
	// �ִϸ��̼��� �������� �ణ�� �߹ؿ� ������ �����ִ�
	// ��찡 �ֱ� ������ �̸� �������ִ� offset
	Vector2		m_Offset;
	float		m_TimeScale;

	CSharedPtr<CTexture>	m_Texture;
	Vector2		m_ImageStart;

	bool m_Start;
	EObject_Type	m_ObjType;

public:
	//std::vector<std::wstring> m_vecAnimation;
	std::vector<std::string> m_vecAnimation;

public:
	EObject_Type GetObjType()	const
	{
		return m_ObjType;
	}

protected:
	CAnimation* m_Animation;

public:
	// m_Animation�� nullptr�̸� �����Ҵ����ְ�
	// m_Animation�� m_Owner�� �� �ڽ�����,
	// m_Animation�� m_Scene�� ���� �����ִ� Scene��
	// �Ҵ����ִ� �Լ�
	void CreateAnimation();
	// AnimationŬ�������� AnimationInfo�� �����Ҵ��ϰ�
	// �̹� CSceneResource�� load�ص� Sequence�� 
	// AnimationInfo�� Sequence����� �Ҵ����༭
	// �ϼ��� AnimationInfo�� CAnimation�� �����
	// m_mapAnimation�� insert���ִ� �Լ�
	void AddAnimation(const std::string& SequenceName,
		bool Loop = true, float PlayTime = 1.f, float PlayScale = 1.f,
		bool Reverse = false);
	void SetAnimationPlayTime(const std::string& Name,
		float PlayTime);
	void SetAnimationPlayScale(const std::string& Name, 
		float PlayScale);
	void SetCurrentAnimation(const std::string& Name);
	void ChangeAnimation(const std::string& Name);
	bool CheckCurrentAnimation(const std::string& Name);
	void SetAnimationReverse(const std::string& Name,
		bool Reverse);
	void SetAnimationLoop(const std::string& Name,
		bool Loop);

public:
	Vector2	GetOffset() const
	{
		return m_Offset;
	}

	Vector2 GetPos()	const
	{
		return m_Pos;
	}

	Vector2 GetSize()	const
	{
		return m_Size;
	}

	Vector2	GetPivot()	const
	{
		return m_Pivot;
	}

	Vector2	GetVelocity()	const
	{
		return m_Velocity;
	}

	float GetTimeScale()	const
	{
		return m_TimeScale;
	}

	float GetBottom()	const;

public:
	void SetScene(class CScene* Scene);

	void SetOffset(const Vector2& Offset)
	{
		m_Offset = Offset;
	}

	void SetOffset(float x, float y)
	{
		m_Offset.x = x;
		m_Offset.y = y;
	}

	void SetPos(float x, float y)
	{
		m_Pos.x = x;
		m_Pos.y = y;
	}

	void SetPos(const Vector2& Pos)
	{
		m_Pos = Pos;
	}

	void SetSize(float x, float y)
	{
		m_Size.x = x;
		m_Size.y = y;
	}

	void SetSize(const Vector2& Size)
	{
		m_Size = Size;
	}

	void SetPivot(float x, float y)
	{
		m_Pivot.x = x;
		m_Pivot.y = y;
	}

	void SetPivot(const Vector2& Pivot)
	{
		m_Pivot = Pivot;
	}

	void SetTimeScale(float TimeScale)
	{
		m_TimeScale = TimeScale;
	}

	void SetRenderPos(float x, float y)
	{
		Vector2 Pos(x, y);
		m_RenderPos = Pos;
	}

	void SetImageStart(float x, float y)
	{
		m_ImageStart.x = x;
		m_ImageStart.y = y;
	}

	void SetImageStart(const Vector2& ImageStart)
	{
		m_ImageStart = ImageStart;
	}

public:
	void SetTexture(CTexture* Texture)
	{
		m_Texture = Texture;

		if (m_Texture)
		{
			m_Size.x = (float)m_Texture->GetWidth();
			m_Size.y = (float)m_Texture->GetHeight();
		}
	}
	// �̹� SceneResource�� Texture�� load�Ǿ� m_mapTexture�� ��� ������ ���� �Լ�
	void SetTexture(const std::string& Name);
	// �� �Ʒ� �Լ����� SceneResource�� ó�� load�� �� ���� �Լ���
	void SetTexture(const std::string& Name, const TCHAR* FileName,
		const std::string& PathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& Name, const TCHAR* FullPath);
	void SetTexture(const std::string& Name,
		const std::vector<std::wstring>& vecFileName,
		const std::string& PathName = TEXTURE_PATH);
	void SetTextureColorKey(unsigned char r, unsigned char g,
		unsigned char b, int Index = 0);

public:
	// ���� Object���� Clone���� ����� �� �༮���̶��
	// m_BeginFunction�̳� m_EndFunction�� �ܼ��� ���� ��ü����
	// �ܼ��� �����ϸ� �ȵȴ�. m_BeginFunction�̳� m_EndFunction��
	// �������ٶ� ���ڷ� this�� �־���µ� �� this�� ������ü��
	// �ǹ��ϴ� this����, ����Ǵ� ��ü�� ����Ű�� this�� �ƴϱ�
	// �����̴�.
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	// ȭ��ۿ� �ִ� ������Ʈ���� �ɷ����� �۾�(Culling)�� ���ش�
	virtual void PrevRender();
	virtual void Render(HDC hDC);
	virtual CGameObject* Clone();

};

