#pragma once

#include "Scene.h"

class CMainScene :
    public CScene
{
	friend class CSceneManager;

private:
	CMainScene();
	virtual ~CMainScene();

private:
	bool m_TopControl;
	std::vector<std::string> m_vecAnimationName;
	int m_CurrentTopAnimIndex;
	int m_CurrentBottomAnimIndex;

public:
	virtual bool Init();

private:
	// MainScene���� ���� object���� �� AnimationSequence����
	// �̸� �ε� �س��� Object���� ���߿� �ʿ��� ��
	// ã�Ƽ� ������ �Ѵ�
	void LoadAnimationSequence();

	void SetScenePause(float TimeScale);
	void SetSceneResume(float TimeScale);

	void IncreaseTimeScale(float TimeScale);
	void DecreaseTimeScale(float TimeScale);

	void SetTopControl(float DeltaTime);
	void SetBottomControl(float DeltaTime);

	void NextFrame(float DeltaTime);
	void PrevFrame(float DeltaTime);

	void UpXOffset(float DeltaTime);
	void UpYOffset(float DeltaTime);
	void DownXOffset(float DeltaTime);
	void DownYOffset(float DeltaTime);

	void SwapControl(float DeltaTime);
	void SaveInfo(float DeltaTime);
	void LoadInfo(float DeltaTime);

	void NextAnimation(float DeltaTime);
	void PrevAnimation(float DeltaTime);

	void LeftXStartPos(float DeltaTime);
	void RightXStartPos(float DeltaTime);
	void UpYStartPos(float DeltaTime);
	void DownYStartPos(float DeltaTime);
	void LeftXStartPos5(float DeltaTime);
	void RightXStartPos5(float DeltaTime);

	void IncreaseXFrameSize(float DeltaTime);
	void DecreaseXFrameSize(float DeltaTime);
	void IncreaseYFrameSize(float DeltaTime);
	void DecreaseYFrameSize(float DeltaTime);

	void MergeTextFile(float DeltaTime);
};

