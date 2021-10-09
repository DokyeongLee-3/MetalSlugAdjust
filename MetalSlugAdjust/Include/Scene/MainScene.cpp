
#include "MainScene.h"
#include "../Object/Player.h"
#include "../Object/Monster.h"
#include "SceneResource.h"
#include "../GameManager.h"
#include "../Input.h"


CMainScene::CMainScene()	:
	m_TopControl(true),
	m_CurrentTopAnimIndex(0),
	m_CurrentBottomAnimIndex(0)
{
	CInput::GetInst()->SetCallback<CMainScene>("Pause", KeyState_Down, this, &CMainScene::SetScenePause);
	CInput::GetInst()->SetCallback<CMainScene>("Resume", KeyState_Down, this, &CMainScene::SetSceneResume);

	CInput::GetInst()->SetCallback<CMainScene>("IncreaseTimeScale", KeyState_Down, this, &CMainScene::IncreaseTimeScale);
	CInput::GetInst()->SetCallback<CMainScene>("DecreaseTimeScale", KeyState_Down, this, &CMainScene::DecreaseTimeScale);

	CInput::GetInst()->SetCallback<CMainScene>("NextFrame", KeyState_Down, this, &CMainScene::NextFrame);
	CInput::GetInst()->SetCallback<CMainScene>("PrevFrame", KeyState_Down, this, &CMainScene::PrevFrame);

	CInput::GetInst()->SetCallback<CMainScene>("IncreaseXOffset", KeyState_Down, this, &CMainScene::UpXOffset);
	CInput::GetInst()->SetCallback<CMainScene>("IncreaseYOffset", KeyState_Down, this, &CMainScene::UpYOffset);
	CInput::GetInst()->SetCallback<CMainScene>("DecreaseXOffset", KeyState_Down, this, &CMainScene::DownXOffset);
	CInput::GetInst()->SetCallback<CMainScene>("DecreaseYOffset", KeyState_Down, this, &CMainScene::DownYOffset);

	CInput::GetInst()->SetCallback<CMainScene>("SwapControl", KeyState_Down, this, &CMainScene::SwapControl);


	CInput::GetInst()->SetCallback<CMainScene>("SaveInfo", KeyState_Down, this, &CMainScene::SaveInfo);
	CInput::GetInst()->SetCallback<CMainScene>("LoadInfo", KeyState_Down, this, &CMainScene::LoadInfo);

	CInput::GetInst()->SetCallback<CMainScene>("PrevAnimation", KeyState_Down, this, &CMainScene::PrevAnimation);
	CInput::GetInst()->SetCallback<CMainScene>("NextAnimation", KeyState_Down, this, &CMainScene::NextAnimation);

	CInput::GetInst()->SetCallback<CMainScene>("IncreaseXFrameSize", KeyState_Down, this, &CMainScene::IncreaseXFrameSize);
	CInput::GetInst()->SetCallback<CMainScene>("DecreaseXFrameSize", KeyState_Down, this, &CMainScene::DecreaseXFrameSize);
	CInput::GetInst()->SetCallback<CMainScene>("IncreaseYFrameSize", KeyState_Down, this, &CMainScene::IncreaseYFrameSize);
	CInput::GetInst()->SetCallback<CMainScene>("DecreaseYFrameSize", KeyState_Down, this, &CMainScene::DecreaseYFrameSize);

	CInput::GetInst()->SetCallback<CMainScene>("RightXStartPos", KeyState_Down, this, &CMainScene::RightXStartPos);
	CInput::GetInst()->SetCallback<CMainScene>("LeftXStartPos", KeyState_Down, this, &CMainScene::LeftXStartPos);
	CInput::GetInst()->SetCallback<CMainScene>("UpYStartPos", KeyState_Down, this, &CMainScene::UpYStartPos);
	CInput::GetInst()->SetCallback<CMainScene>("DownYStartPos", KeyState_Down, this, &CMainScene::DownYStartPos);

	CInput::GetInst()->SetCallback<CMainScene>("RightXStartPos5", KeyState_Down, this, &CMainScene::RightXStartPos5);
	CInput::GetInst()->SetCallback<CMainScene>("LeftXStartPos5", KeyState_Down, this, &CMainScene::LeftXStartPos5);

	CInput::GetInst()->SetCallback<CMainScene>("MergeText", KeyState_Down, this, &CMainScene::MergeTextFile);
}

CMainScene::~CMainScene()
{

}

bool CMainScene::Init()
{
	LoadAnimationSequence();

	CGameObject* Background = CreateObject<CGameObject>("Background", Vector2(0.f, 0.f), Vector2(1024.f, 768.f));

	Background->SetTexture("Background", TEXT("Back.bmp"));

	CGameObject* Bottom = CreateObject<CGameObject>("PlayerBottom");

	Bottom->SetPivot(0.5f, 1.f);
	Bottom->SetRenderPos(512.f, 384.f);
	Bottom->CreateAnimation();

	Bottom->AddAnimation("PlayerIdleRightBottom1", true, 0.8f, 1.f, false);
	Bottom->m_vecAnimation.push_back("PlayerIdleRightBottom1");
	Bottom->AddAnimation("PlayerIdleLeftBottom1", true, 0.8f, 1.f, true);
	Bottom->m_vecAnimation.push_back("PlayerIdleLeftBottom1");

	Bottom->AddAnimation("PlayerNormalFireRightBottom", true, 0.8f, 1.f, false);
	Bottom->m_vecAnimation.push_back("PlayerNormalFireRightBottom");
	Bottom->AddAnimation("PlayerNormalFireLeftBottom", true, 0.8f, 1.f, true);
	Bottom->m_vecAnimation.push_back("PlayerNormalFireLeftBottom");

	Bottom->AddAnimation("PlayerRunRightBottom", true, 1.f, 1.f, false);
	Bottom->m_vecAnimation.push_back("PlayerRunRightBottom");
	Bottom->AddAnimation("PlayerRunLeftBottom", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("PlayerRunLeftBottom");

	Bottom->AddAnimation("PlayerVerticalJumpRightBottom1", true, 1.f, 1.f, false);
	Bottom->m_vecAnimation.push_back("PlayerVerticalJumpRightBottom1");
	Bottom->AddAnimation("PlayerVerticalJumpLeftBottom1", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("PlayerVerticalJumpLeftBottom1");

	Bottom->AddAnimation("NormalAttackBottomEffect", true, 1.f, 1.f, false);
	Bottom->m_vecAnimation.push_back("NormalAttackBottomEffect");

	Bottom->AddAnimation("PlayerVerticalJumpRightBottom2", true, 1.f, 1.f, false);
	Bottom->m_vecAnimation.push_back("PlayerVerticalJumpRightBottom2");
	Bottom->AddAnimation("PlayerVerticalJumpLeftBottom2", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("PlayerVerticalJumpLeftBottom2");

	Bottom->AddAnimation("PlayerVerticalJumpRightBottom3", true, 1.f, 1.f, false);
	Bottom->m_vecAnimation.push_back("PlayerVerticalJumpRightBottom3");
	Bottom->AddAnimation("PlayerVerticalJumpLeftBottom3", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("PlayerVerticalJumpLeftBottom3");

	Bottom->AddAnimation("PlayerIdleRightBottom2", true, 0.8f, 1.f, false);
	Bottom->m_vecAnimation.push_back("PlayerIdleRightBottom2");
	Bottom->AddAnimation("PlayerIdleLeftBottom2", true, 0.8f, 1.f, true);
	Bottom->m_vecAnimation.push_back("PlayerIdleLeftBottom2");

	Bottom->AddAnimation("PlayerIdleRightBottom3", true, 0.8f, 1.f, false);
	Bottom->m_vecAnimation.push_back("PlayerIdleRightBottom3");
	Bottom->AddAnimation("PlayerIdleLeftBottom3", true, 0.8f, 1.f, true);
	Bottom->m_vecAnimation.push_back("PlayerIdleLeftBottom3");

	Bottom->AddAnimation("PlayerFrontJumpRightBottom", true, 1.f, 1.f, false);
	Bottom->m_vecAnimation.push_back("PlayerFrontJumpRightBottom");
	Bottom->AddAnimation("PlayerFrontJumpLeftBottom", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("PlayerFrontJumpLeftBottom");

	Bottom->AddAnimation("PlayerSitDownIdleRight", true, 1.f, 1.f, false);
	Bottom->m_vecAnimation.push_back("PlayerSitDownIdleRight");
	Bottom->AddAnimation("PlayerSitDownIdleLeft", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("PlayerSitDownIdleLeft");

	Bottom->AddAnimation("PlayerCrawlRight", true, 0.8f, 1.f, false);
	Bottom->m_vecAnimation.push_back("PlayerCrawlRight");
	Bottom->AddAnimation("PlayerCrawlLeft", true, 0.8f, 1.f, true);
	Bottom->m_vecAnimation.push_back("PlayerCrawlLeft");

	Bottom->AddAnimation("PlayerSitDownNormalAttackRight", true, 1.f, 1.f, false);
	Bottom->m_vecAnimation.push_back("PlayerSitDownNormalAttackRight");
	Bottom->AddAnimation("PlayerSitDownNormalAttackLeft", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("PlayerSitDownNormalAttackLeft");

	Bottom->AddAnimation("PlayerIdleRightBottom4", true, 1.f, 1.f, false);
	Bottom->m_vecAnimation.push_back("PlayerIdleRightBottom4");
	Bottom->AddAnimation("PlayerIdleLeftBottom4", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("PlayerIdleLeftBottom4");

	Bottom->AddAnimation("BombRight", true, 1.f, 1.f, false);
	Bottom->m_vecAnimation.push_back("BombRight");
	Bottom->AddAnimation("BombLeft", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("BombLeft");

	Bottom->AddAnimation("BombExplosion", true, 1.f);
	Bottom->m_vecAnimation.push_back("BombExplosion");

	Bottom->AddAnimation("PlayerSitDownBombRight", true, 1.f);
	Bottom->m_vecAnimation.push_back("PlayerSitDownBombRight");
	Bottom->AddAnimation("PlayerSitDownBombLeft", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("PlayerSitDownBombLeft");


	CGameObject* Top = CreateObject<CGameObject>("PlayerTop");

	Top->SetPivot(0.5f, 1.f);
	Top->SetRenderPos(512.f, 384.f - PLAYER_BOTTOMHEIGHT);
	Top->CreateAnimation();

	Top->AddAnimation("PlayerIdleRightTop", true, 0.8f, 1.f, false);
	Top->m_vecAnimation.push_back("PlayerIdleRightTop");
	Top->AddAnimation("PlayerIdleLeftTop", true, 0.8f, 1.f, true);
	Top->m_vecAnimation.push_back("PlayerIdleLeftTop");

	Top->AddAnimation("PlayerNormalFireRightTop", true, 0.8f, 1.f, false);
	Top->m_vecAnimation.push_back("PlayerNormalFireRightTop");
	Top->AddAnimation("PlayerNormalFireLeftTop", true, 0.8f, 1.f, true);
	Top->m_vecAnimation.push_back("PlayerNormalFireLeftTop");

	Top->AddAnimation("PlayerRunRightTop", true, 1.f, 1.f, false);
	Top->m_vecAnimation.push_back("PlayerRunRightTop");
	Top->AddAnimation("PlayerRunLeftTop", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("PlayerRunLeftTop");

	Top->AddAnimation("PlayerVerticalJumpRightTop", true, 1.f, 1.f, false);
	Top->m_vecAnimation.push_back("PlayerVerticalJumpRightTop");
	Top->AddAnimation("PlayerVerticalJumpLeftTop", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("PlayerVerticalJumpLeftTop");

	Top->AddAnimation("NormalAttackTopEffect", true, 1.f, 1.f, false);
	Top->m_vecAnimation.push_back("NormalAttackTopEffect");

	Top->AddAnimation("PlayerJumpDownRightTop", true, 1.f, 1.f, false);
	Top->m_vecAnimation.push_back("PlayerJumpDownRightTop");
	Top->AddAnimation("PlayerJumpDownLeftTop", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("PlayerJumpDownLeftTop");

	Top->AddAnimation("PlayerJumpAttackDownRightTop", true, 1.f, 1.f, false);
	Top->m_vecAnimation.push_back("PlayerJumpAttackDownRightTop");
	Top->AddAnimation("PlayerJumpAttackDownLeftTop", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("PlayerJumpAttackDownLeftTop");

	Top->AddAnimation("PlayerLookUpRightTop", true, 1.f, 1.f, false);
	Top->m_vecAnimation.push_back("PlayerLookUpRightTop");
	Top->AddAnimation("PlayerLookUpLeftTop", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("PlayerLookUpLeftTop");

	Top->AddAnimation("PlayerLookUpAttackRightTop", true, 1.f, 1.f, false);
	Top->m_vecAnimation.push_back("PlayerLookUpAttackRightTop");
	Top->AddAnimation("PlayerLookUpAttackLeftTop", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("PlayerLookUpAttackLeftTop");

	Top->AddAnimation("PlayerFrontJumpRightTop", true, 1.f, 1.f, false);
	Top->m_vecAnimation.push_back("PlayerFrontJumpRightTop");
	Top->AddAnimation("PlayerFrontJumpLeftTop", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("PlayerFrontJumpLeftTop");

	Top->AddAnimation("Blank1", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank1");
	Top->AddAnimation("Blank2", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank2");

	Top->AddAnimation("Blank3", true, 0.8f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank3");
	Top->AddAnimation("Blank4", true, 0.8f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank4");

	Top->AddAnimation("Blank5", true, 0.8f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank5");
	Top->AddAnimation("Blank6", true, 0.8f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank6");

	Top->AddAnimation("PlayerBombRightTop", true, 1.f, 1.f, false);
	Top->m_vecAnimation.push_back("PlayerBombRightTop");
	Top->AddAnimation("PlayerBombLeftTop", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("PlayerBombLeftTop");

	Top->AddAnimation("Blank7", true, 1.f, 1.f, false);
	Top->m_vecAnimation.push_back("Blank7");
	Top->AddAnimation("Blank8", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank8");

	Top->AddAnimation("Blank9", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank9");

	Top->AddAnimation("Blank10", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank10");
	Top->AddAnimation("Blank11", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank11");

	return true;
}

void CMainScene::LoadAnimationSequence()
{
	// 총알이 바닥과 닿으면 생기는 effect의 애니메이션
	GetSceneResource()->CreateAnimationSequence("NormalAttackTopEffect",
		"NormalAttackTopEffect", TEXT("NormalAttackEffect.bmp"));

	GetSceneResource()->SetTextureColorKey("NormalAttackTopEffect",
		255, 0, 255);

	for (int i = 0; i < 12; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("NormalAttackTopEffect",
			i * 66.f, 0.f, 66.f, 125.f);
	}

	GetSceneResource()->CreateAnimationSequence("NormalAttackBottomEffect",
		"NormalAttackBottomEffect", TEXT("NormalAttackEffect.bmp"));

	GetSceneResource()->SetTextureColorKey("NormalAttackBottomEffect",
		255, 0, 255);

	for (int i = 0; i < 12; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("NormalAttackBottomEffect",
			i * 66.f, 0.f, 66.f, 125.f);
	}

	m_vecAnimationName.push_back("NormalAttackEffect");

	/////////// PlayerIdle 상하체 애니메이션 저장 ////////////

	GetSceneResource()->CreateAnimationSequence("PlayerIdleRightTop",
		"PlayerIdleRightTop", TEXT("Player/Idle/Right/Marco_IdleTop.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerIdleRightTop",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerIdleRightTop",
			i * 110.f, 0.f, 110.f, 86.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerIdleRightBottom1",
		"PlayerIdleRightBottom1", TEXT("Player/Idle/Right/Marco_IdleBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerIdleRightBottom1",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerIdleRightBottom1",
			i * 75.f, 0.f, 75.f, 57.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerIdleRightBottom2",
		"PlayerIdleRightBottom2", TEXT("Player/Idle/Right/Marco_IdleBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerIdleRightBottom2",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerIdleRightBottom2",
			i * 75.f, 0.f, 75.f, 57.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerIdleRightBottom3",
		"PlayerIdleRightBottom3", TEXT("Player/Idle/Right/Marco_IdleBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerIdleRightBottom3",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerIdleRightBottom3",
			i * 75.f, 0.f, 75.f, 57.f);
	}

	// 파일 이름용도로만 쓰이는 Animation이름들 저장을 위한 vector
	m_vecAnimationName.push_back("PlayerIdleRight");


	GetSceneResource()->CreateAnimationSequence("PlayerIdleLeftTop",
		"PlayerIdleLeftTop", TEXT("Player/Idle/Left/Marco_IdleTop.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerIdleLeftTop",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerIdleLeftTop",
			i * 110.f, 0.f, 110.f, 86.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerIdleLeftBottom1",
		"PlayerIdleLeftBottom1", TEXT("Player/Idle/Left/Marco_IdleBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerIdleLeftBottom1",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerIdleLeftBottom1",
			i * 75.f, 0.f, 75.f, 57.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerIdleLeftBottom2",
		"PlayerIdleLeftBottom2", TEXT("Player/Idle/Left/Marco_IdleBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerIdleLeftBottom2",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerIdleLeftBottom2",
			i * 75.f, 0.f, 75.f, 57.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerIdleLeftBottom3",
		"PlayerIdleLeftBottom3", TEXT("Player/Idle/Left/Marco_IdleBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerIdleLeftBottom3",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerIdleLeftBottom3",
			i * 75.f, 0.f, 75.f, 57.f);
	}

	// 파일 이름용도로만 쓰이는 Animation이름들 저장을 위한 vector
	m_vecAnimationName.push_back("PlayerIdleLeft");


	/////////// PlayerNormalFire 상하체 애니메이션 저장 ////////////

	GetSceneResource()->CreateAnimationSequence("PlayerNormalFireRightTop",
		"PlayerNormalFireRightTop", TEXT("Player/Attack/Right/Marco_NormalFireTop.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerNormalFireRightTop",
		255, 255, 255);

	for (int i = 0; i < 10; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerNormalFireRightTop",
			i * 130.f, 0.f, 130.f, 90.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerNormalFireRightBottom",
		"PlayerNormalFireRightBottom", TEXT("Player/Attack/Right/Marco_NormalFireBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerNormalFireRightBottom",
		255, 255, 255);

	for (int i = 0; i < 10; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerNormalFireRightBottom",
			i * 75.f, 0.f, 75.f, 57.f);
	}

	m_vecAnimationName.push_back("PlayerNormalFireRight");


	GetSceneResource()->CreateAnimationSequence("PlayerNormalFireLeftTop",
		"PlayerNormalFireLeftTop", TEXT("Player/Attack/Left/Marco_NormalFireTop.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerNormalFireLeftTop",
		255, 255, 255);

	for (int i = 0; i < 10; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerNormalFireLeftTop",
			i * 130.f, 0.f, 130.f, 90.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerNormalFireLeftBottom",
		"PlayerNormalFireLeftBottom", TEXT("Player/Attack/Left/Marco_NormalFireBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerNormalFireLeftBottom",
		255, 255, 255);

	for (int i = 0; i < 10; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerNormalFireLeftBottom",
			i * 75.f, 0.f, 75.f, 57.f);
	}

	m_vecAnimationName.push_back("PlayerNormalFireLeft");



	/////////// PlayerRun 상하체 애니메이션 저장 ////////////

	GetSceneResource()->CreateAnimationSequence("PlayerRunRightTop",
		"PlayerRunRightTop", TEXT("Player/Run/Right/Marco_RunTop.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerRunRightTop",
		255, 255, 255);

	for (int i = 0; i < 12; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerRunRightTop",
			i * 110.f, 0.f, 110.f, 86.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerRunRightBottom",
		"PlayerRunRightBottom", TEXT("Player/Run/Right/Marco_RunBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerRunRightBottom",
		255, 255, 255);

	for (int i = 0; i < 18; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerRunRightBottom",
			i * 75.f, 0.f, 75.f, 56.f);
	}

	m_vecAnimationName.push_back("PlayerRunRight");


	GetSceneResource()->CreateAnimationSequence("PlayerRunLeftTop",
		"PlayerRunLeftTop", TEXT("Player/Run/Left/Marco_RunTop.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerRunLeftTop",
		255, 255, 255);

	for (int i = 0; i < 12; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerRunLeftTop",
			i * 110.f, 0.f, 110.f, 86.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerRunLeftBottom",
		"PlayerRunLeftBottom", TEXT("Player/Run/Left/Marco_RunBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerRunLeftBottom",
		255, 255, 255);

	for (int i = 0; i < 18; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerRunLeftBottom",
			i * 75.f, 0.f, 75.f, 56.f);
	}

	m_vecAnimationName.push_back("PlayerRunLeft");




	/////////// PlayerJump 상하체 애니메이션 저장 ////////////

	GetSceneResource()->CreateAnimationSequence("PlayerVerticalJumpRightTop",
		"PlayerVerticalJumpRightTop", TEXT("Player/Jump/Right/Marco_VerticalJumpTop.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerVerticalJumpRightTop",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerVerticalJumpRightTop",
			i * 105.f, 0.f, 105.f, 82.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerVerticalJumpRightBottom1",
		"PlayerVerticalJumpRightBottom1", TEXT("Player/Jump/Right/Marco_VerticalJumpBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerVerticalJumpRightBottom1",
		255, 255, 255);

	for (int i = 0; i < 11; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerVerticalJumpRightBottom1",
			i * 90.f, 0.f, 90.f, 60.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerVerticalJumpRightBottom2",
		"PlayerVerticalJumpRightBottom2", TEXT("Player/Jump/Right/Marco_VerticalJumpBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerVerticalJumpRightBottom2",
		255, 255, 255);

	for (int i = 0; i < 11; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerVerticalJumpRightBottom2",
			i * 90.f, 0.f, 90.f, 60.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerVerticalJumpRightBottom3",
		"PlayerVerticalJumpRightBottom3", TEXT("Player/Jump/Right/Marco_VerticalJumpBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerVerticalJumpRightBottom3",
		255, 255, 255);

	for (int i = 0; i < 11; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerVerticalJumpRightBottom3",
			i * 90.f, 0.f, 90.f, 60.f);
	}

	m_vecAnimationName.push_back("PlayerJumpRight");


	GetSceneResource()->CreateAnimationSequence("PlayerVerticalJumpLeftTop",
		"PlayerVerticalJumpLeftTop", TEXT("Player/Jump/Left/Marco_VerticalJumpTop.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerVerticalJumpLeftTop",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerVerticalJumpLeftTop",
			i * 105.f, 0.f, 105.f, 82.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerVerticalJumpLeftBottom1",
		"PlayerVerticalJumpLeftBottom1", TEXT("Player/Jump/Left/Marco_VerticalJumpBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerVerticalJumpLeftBottom1",
		255, 255, 255);

	for (int i = 0; i < 11; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerVerticalJumpLeftBottom1",
			i * 90.f, 0.f, 90.f, 60.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerVerticalJumpLeftBottom2",
		"PlayerVerticalJumpLeftBottom2", TEXT("Player/Jump/Left/Marco_VerticalJumpBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerVerticalJumpLeftBottom2",
		255, 255, 255);

	for (int i = 0; i < 11; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerVerticalJumpLeftBottom2",
			i * 90.f, 0.f, 90.f, 60.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerVerticalJumpLeftBottom3",
		"PlayerVerticalJumpLeftBottom3", TEXT("Player/Jump/Left/Marco_VerticalJumpBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerVerticalJumpLeftBottom3",
		255, 255, 255);

	for (int i = 0; i < 11; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerVerticalJumpLeftBottom3",
			i * 90.f, 0.f, 90.f, 60.f);
	}

	m_vecAnimationName.push_back("PlayerJumpLeft");

	/////////// PlayerJumpDown 상체 애니메이션 저장 ////////////

	GetSceneResource()->CreateAnimationSequence("PlayerJumpDownRightTop",
		"PlayerJumpDownRightTop", TEXT("Player/Jump/Right/Marco_JumpDownTop.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerJumpDownRightTop",
		255, 255, 255);


	GetSceneResource()->AddAnimationFrameData("PlayerJumpDownRightTop",
			0.f, 0.f, 70.f, 123.f);


	m_vecAnimationName.push_back("PlayerJumpDownRight");


	GetSceneResource()->CreateAnimationSequence("PlayerJumpDownLeftTop",
		"PlayerJumpDownLeftTop", TEXT("Player/Jump/Left/Marco_JumpDownTop.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerJumpDownLeftTop",
		255, 255, 255);

	GetSceneResource()->AddAnimationFrameData("PlayerJumpDownLeftTop",
		0.f, 0.f, 70.f, 123.f);

	// Jump하면서 아래로 공격할때 하체는 Vertial Jump의 Bottom을 그대로 이용하기 때문에
	// 여기서 추가로 Load할 필요 X

	m_vecAnimationName.push_back("PlayerJumpDownLeftTop");


	/////////// PlayerJumpAttackDown 상체 애니메이션 저장 ////////////

	GetSceneResource()->CreateAnimationSequence("PlayerJumpAttackDownRightTop",
		"PlayerJumpAttackDownRightTop", TEXT("Player/Jump/Right/Marco_JumpAttackDownTop.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerJumpAttackDownRightTop",
		255, 255, 255);

	for (int i = 0; i < 7; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerJumpAttackDownRightTop",
			i * 80.f, 0.f, 80.f, 189.f);
	}
	
	// Jump하면서 아래로 공격할때 하체는 Vertial Jump의 Bottom을 그대로 이용하기 때문에
	// 여기서 추가로 Load할 필요 X

	m_vecAnimationName.push_back("PlayerJumpAttackRight");



	GetSceneResource()->CreateAnimationSequence("PlayerJumpAttackDownLeftTop",
		"PlayerJumpAttackDownLeftTop", TEXT("Player/Jump/Left/Marco_JumpAttackDownTop.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerJumpAttackDownLeftTop",
		255, 255, 255);

	for (int i = 0; i < 7; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerJumpAttackDownLeftTop",
			i * 80.f, 0.f, 80.f, 189.f);
	}

	// Jump하면서 아래로 공격할때 하체는 Vertial Jump의 Bottom을 그대로 이용하기 때문에
	// 여기서 추가로 Load할 필요 X

	m_vecAnimationName.push_back("PlayerJumpAttackLeft");


	/////////// PlayerLookUp 상체 애니메이션 저장 ////////////

	GetSceneResource()->CreateAnimationSequence("PlayerLookUpRightTop",
		"PlayerLookUpRightTop", TEXT("Player/LookUp/Right/LookUpTop.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerLookUpRightTop",
		255, 255, 255);

	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerLookUpRightTop",
			i * 100.f, 0.f, 100.f, 84.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerLookUpLeftTop",
		"PlayerLookUpLeftTop", TEXT("Player/LookUp/Left/LookUpTop.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerLookUpLeftTop",
		255, 255, 255);

	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerLookUpLeftTop",
			i * 100.f, 0.f, 100.f, 84.f);
	}

	m_vecAnimationName.push_back("PlayerLookUpTop");

	/////////// PlayerLookUpAttack 상체 애니메이션 저장 ////////////

	GetSceneResource()->CreateAnimationSequence("PlayerLookUpAttackRightTop",
		"PlayerLookUpAttackRightTop", TEXT("Player/LookUp/Right/LookUpNormalAttackTop.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerLookUpAttackRightTop",
		255, 255, 255);

	for (int i = 0; i < 10; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerLookUpAttackRightTop",
			i * 90.f, 0.f, 90.f, 208.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerLookUpAttackLeftTop",
		"PlayerLookUpAttackLeftTop", TEXT("Player/LookUp/Left/LookUpNormalAttackTop.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerLookUpAttackLeftTop",
		255, 255, 255);

	for (int i = 0; i < 10; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerLookUpAttackLeftTop",
			i * 90.f, 0.f, 90.f, 208.f);
	}

	m_vecAnimationName.push_back("PlayerLookAttackTop");


	/////////// PlayerFrontJumpAnimation 애니메이션 저장 ////////////

	GetSceneResource()->CreateAnimationSequence("PlayerFrontJumpRightTop",
		"PlayerFrontJumpRightTop", TEXT("Player/Jump/Right/Marco_FrontJumpTop.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerFrontJumpRightTop",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerFrontJumpRightTop",
			i * 89.f, 0.f, 89.f, 113.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerFrontJumpLeftTop",
		"PlayerFrontJumpLeftTop", TEXT("Player/Jump/Left/Marco_FrontJumpTop.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerFrontJumpLeftTop",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerFrontJumpLeftTop",
			i * 89.f, 0.f, 89.f, 113.f);
	}
	m_vecAnimationName.push_back("PlayerFrontJumpTop");


	GetSceneResource()->CreateAnimationSequence("PlayerFrontJumpRightBottom",
		"PlayerFrontJumpRightBottom", TEXT("Player/Jump/Right/Marco_FrontJumpBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerFrontJumpRightBottom",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerFrontJumpRightBottom",
			i * 110.f, 0.f, 110.f, 73.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerFrontJumpLeftBottom",
		"PlayerFrontJumpLeftBottom", TEXT("Player/Jump/Left/Marco_FrontJumpBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerFrontJumpLeftBottom",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerFrontJumpLeftBottom",
			i * 110.f, 0.f, 110.f, 73.f);
	}

	m_vecAnimationName.push_back("PlayerFrontJumpBottom");

	// SitDownIdle

	GetSceneResource()->CreateAnimationSequence("PlayerSitDownIdleRight",
		"PlayerSitDownIdleRight", TEXT("Player/SitDown/Right/SitDownIdleRight.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerSitDownIdleRight",
		255, 255, 255);

	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerSitDownIdleRight",
			i * 110.f, 0.f, 110.f, 75.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerSitDownIdleLeft",
		"PlayerSitDownIdleLeft", TEXT("Player/SitDown/Left/SitDownIdleLeft.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerSitDownIdleLeft",
		255, 255, 255);

	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerSitDownIdleLeft",
			i * 110.f, 0.f, 110.f, 75.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank1",
		"Blank1", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank1",
		255, 255, 255);

	for (int i = 0; i < 1; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank1",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank2",
		"Blank2", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank2",
		255, 255, 255);

	for (int i = 0; i < 1; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank2",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	m_vecAnimationName.push_back("PlayerSitDownRight");

	// Crawl

	GetSceneResource()->CreateAnimationSequence("PlayerCrawlRight",
		"PlayerCrawlRight", TEXT("Player/SitDown/Right/CrawlRight.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerCrawlRight",
		255, 255, 255);

	for (int i = 0; i < 7; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerCrawlRight",
			i * 115.f, 0.f, 115.f, 74.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerCrawlLeft",
		"PlayerCrawlLeft", TEXT("Player/SitDown/Left/CrawlLeft.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerCrawlLeft",
		255, 255, 255);

	for (int i = 0; i < 7; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerCrawlLeft",
			i * 115.f, 0.f, 115.f, 74.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank3",
		"Blank3", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank3",
		255, 255, 255);

	for (int i = 0; i < 1; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank3",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank4",
		"Blank4", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank4",
		255, 255, 255);

	for (int i = 0; i < 1; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank4",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	// SitDownNormalAttack
	GetSceneResource()->CreateAnimationSequence("PlayerSitDownNormalAttackRight",
		"PlayerSitDownNormalAttackRight", TEXT("Player/SitDown/Right/SitDownNormalAttack.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerSitDownNormalAttackRight",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerSitDownNormalAttackRight",
			i * 130.f, 0.f, 130.f, 88.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerSitDownNormalAttackLeft",
		"PlayerSitDownNormalAttackLeft", TEXT("Player/SitDown/Left/SitDownNormalAttack.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerSitDownNormalAttackLeft",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerSitDownNormalAttackLeft",
			i * 130.f, 0.f, 130.f, 88.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank5",
		"Blank5", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank5",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank5",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank6",
		"Blank6", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank6",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank6",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	// PlayerBomb
	GetSceneResource()->CreateAnimationSequence("PlayerBombRightTop",
		"PlayerBombRightTop", TEXT("Player/Bomb/Right/BombTop.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerBombRightTop",
		255, 255, 255);

	for (int i = 0; i < 5; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerBombRightTop",
			i * 105.f, 0.f, 105.f, 93.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerBombLeftTop",
		"PlayerBombLeftTop", TEXT("Player/Bomb/Left/BombTop.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerBombLeftTop",
		255, 255, 255);

	for (int i = 0; i < 5; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerBombLeftTop",
			i * 105.f, 0.f, 105.f, 93.f);
	}

	///// Bomb를 위한 IdleBottom
	GetSceneResource()->CreateAnimationSequence("PlayerIdleRightBottom4",
		"PlayerIdleRightBottom4", TEXT("Player/Idle/Right/Marco_IdleBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerIdleRightBottom4",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerIdleRightBottom4",
			i * 75.f, 0.f, 75.f, 57.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerIdleLeftBottom4",
		"PlayerIdleLeftBottom4", TEXT("Player/Idle/Left/Marco_IdleBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerIdleLeftBottom4",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerIdleLeftBottom4",
			i * 75.f, 0.f, 75.f, 57.f);
	}

	// Bomb
	GetSceneResource()->CreateAnimationSequence("BombRight",
		"BombRight", TEXT("Item/Bomb/Right/Bomb.bmp"));

	GetSceneResource()->SetTextureColorKey("BombRight",
		0, 248, 0);

	for (int i = 0; i < 16; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("BombRight",
			i * 49.f, 0.f, 49.f, 50.f);
	}

	GetSceneResource()->CreateAnimationSequence("BombLeft",
		"BombLeft", TEXT("Item/Bomb/Left/Bomb.bmp"));

	GetSceneResource()->SetTextureColorKey("BombLeft",
		0, 248, 0);

	for (int i = 0; i < 16; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("BombLeft",
			i * 49.f, 0.f, 49.f, 50.f);
	}

	// Bomb를 위한 Blank
	GetSceneResource()->CreateAnimationSequence("Blank7",
		"Blank7", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank7",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank7",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank8",
		"Blank8", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank8",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank8",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("BombExplosion",
		"BombExplosion", TEXT("Effect/BombExplosion.bmp"));

	GetSceneResource()->SetTextureColorKey("BombExplosion",
		0, 248, 0);

	for (int i = 0; i < 21; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("BombExplosion",
			i * 150.f, 0.f, 150.f, 311.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank9",
		"Blank9", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank9",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank9",
			i * 100.f, 0.f, 100.f, 68.f);
	}


	// SitDownBomb
	GetSceneResource()->CreateAnimationSequence("PlayerSitDownBombRight",
		"PlayerSitDownBombRight", TEXT("Player/SitDown/Right/SitDownBomb.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerSitDownBombRight",
		255, 255, 255);

	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerSitDownBombRight",
			i * 120.f, 0.f, 120.f, 88.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerSitDownBombLeft",
		"PlayerSitDownBombLeft", TEXT("Player/SitDown/Left/SitDownBomb.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerSitDownBombLeft",
		255, 255, 255);

	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerSitDownBombLeft",
			i * 120.f, 0.f, 120.f, 88.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank10",
		"Blank10", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank10",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank10",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank11",
		"Blank11", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank11",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank11",
			i * 100.f, 0.f, 100.f, 68.f);
	}
}

void CMainScene::SetScenePause(float TimeScale)
{
	CGameManager::GetInst()->SetPrevTimeScale(CGameManager::GetInst()->GetTimeScale());
	CGameManager::GetInst()->SetTimeScale(0.f);
}

void CMainScene::SetSceneResume(float TimeScale)
{
	float _TimeScale = CGameManager::GetInst()->GetPrevTimeScale();
	CGameManager::GetInst()->SetTimeScale(_TimeScale);
}

void CMainScene::IncreaseTimeScale(float TimeScale)
{
	CGameManager::GetInst()->SetTimeScale(CGameManager::GetInst()->GetTimeScale() * 1.1f);
}

void CMainScene::DecreaseTimeScale(float TimeScale)
{
	CGameManager::GetInst()->SetTimeScale(CGameManager::GetInst()->GetTimeScale() * 0.9f);
}

void CMainScene::SetTopControl(float DeltaTime)
{
	m_TopControl = true;
}

void CMainScene::SetBottomControl(float DeltaTime)
{
	m_TopControl = false;
}

void CMainScene::NextFrame(float DeltaTime)
{
	if (m_TopControl)
	{
		CGameObject* PlayerTop = FindObject("PlayerTop");

		AnimationInfo* Info = PlayerTop->m_Animation->GetCurrentAnimation();

		if (PlayerTop->m_Animation->GetCurrentAnimation()->Sequence->GetFrameCount() - 1 == Info->Frame)
			return;

		Info->Frame++;
	}

	else
	{
		CGameObject* PlayerBottom = FindObject("PlayerBottom");
		AnimationInfo* Info = PlayerBottom->m_Animation->GetCurrentAnimation();

		if (PlayerBottom->m_Animation->GetCurrentAnimation()->Sequence->GetFrameCount() - 1 == Info->Frame)
			return;

		Info->Frame++;
	}
}

void CMainScene::PrevFrame(float DeltaTime)
{
	if (m_TopControl)
	{
		CGameObject* PlayerTop = FindObject("PlayerTop");

		AnimationInfo* Info = PlayerTop->m_Animation->GetCurrentAnimation();

		if (Info->Frame == 0)
			return;

		Info->Frame--;
	}

	else
	{
		CGameObject* PlayerBottom = FindObject("PlayerBottom");
		AnimationInfo* Info = PlayerBottom->m_Animation->GetCurrentAnimation();

		if (Info->Frame == 0)
			return;

		Info->Frame--;
	}
}

void CMainScene::UpXOffset(float DeltaTime)
{
	if (m_TopControl)
	{
		CGameObject* PlayerTop = FindObject("PlayerTop");

		AnimationInfo* Info = PlayerTop->m_Animation->GetCurrentAnimation();

		PlayerTop->m_Animation->SetCurrentAnimationXOffset(1.f, Info->Frame);

	}

	else
	{
		CGameObject* PlayerBottom = FindObject("PlayerBottom");

		AnimationInfo* Info = PlayerBottom->m_Animation->GetCurrentAnimation();

		PlayerBottom->m_Animation->SetCurrentAnimationXOffset(1.f, Info->Frame);
	}
}

void CMainScene::UpYOffset(float DeltaTime)
{
	if (m_TopControl)
	{
		CGameObject* PlayerTop = FindObject("PlayerTop");

		AnimationInfo* Info = PlayerTop->m_Animation->GetCurrentAnimation();

		PlayerTop->m_Animation->SetCurrentAnimationYOffset(-1.f, Info->Frame);

	}

	else
	{
		CGameObject* PlayerBottom = FindObject("PlayerBottom");

		AnimationInfo* Info = PlayerBottom->m_Animation->GetCurrentAnimation();

		PlayerBottom->m_Animation->SetCurrentAnimationYOffset(-1.f, Info->Frame);
	}
}

void CMainScene::DownXOffset(float DeltaTime)
{
	if (m_TopControl)
	{
		CGameObject* PlayerTop = FindObject("PlayerTop");

		AnimationInfo* Info = PlayerTop->m_Animation->GetCurrentAnimation();

		PlayerTop->m_Animation->SetCurrentAnimationXOffset(-1.f, Info->Frame);

	}

	else
	{
		CGameObject* PlayerBottom = FindObject("PlayerBottom");

		AnimationInfo* Info = PlayerBottom->m_Animation->GetCurrentAnimation();

		PlayerBottom->m_Animation->SetCurrentAnimationXOffset(-1.f, Info->Frame);
	}
}

void CMainScene::DownYOffset(float DeltaTime)
{
	if (m_TopControl)
	{
		CGameObject* PlayerTop = FindObject("PlayerTop");

		AnimationInfo* Info = PlayerTop->m_Animation->GetCurrentAnimation();

		PlayerTop->m_Animation->SetCurrentAnimationYOffset(1.f, Info->Frame);

	}

	else
	{
		CGameObject* PlayerBottom = FindObject("PlayerBottom");

		AnimationInfo* Info = PlayerBottom->m_Animation->GetCurrentAnimation();

		PlayerBottom->m_Animation->SetCurrentAnimationYOffset(1.f, Info->Frame);
	}
}

void CMainScene::SwapControl(float DeltaTime)
{
	if (m_TopControl)
		m_TopControl = false;
	else
		m_TopControl = true;
}

void CMainScene::SaveInfo(float DeltaTime)
{
	FILE* FileStream;

	CGameObject* Top = FindObject("PlayerTop");

	std::string FileName = Top->m_vecAnimation[m_CurrentTopAnimIndex];

	FileName += "_New.txt";

	fopen_s(&FileStream, FileName.c_str(), "wt");

	if (FileStream)
	{
		FileName.clear();
		FileName = Top->m_vecAnimation[m_CurrentTopAnimIndex];
		int Length = (int)FileName.length();
		fwrite(&Length, sizeof(int), 1, FileStream);
		fwrite(FileName.c_str(), sizeof(char), Length, FileStream);

		int FrameCount = Top->m_Animation->GetCurrentAnimation()->Sequence->GetFrameCount();

		for (int j = 0; j < FrameCount; ++j)
		{
			const AnimationFrameData& Data = Top->m_Animation->GetCurrentAnimation()->Sequence->GetFrameData(j);
			fwrite(&Data, sizeof(AnimationFrameData), 1, FileStream);
		}
		
		fclose(FileStream);
	}

	CGameObject* Bottom = FindObject("PlayerBottom");

	FileName.clear();
	FileName = Bottom->m_vecAnimation[m_CurrentBottomAnimIndex];
	FileName += "_New.txt";

	fopen_s(&FileStream, FileName.c_str(), "wt");

	if (FileStream)
	{
		FileName.clear();
		FileName = Bottom->m_vecAnimation[m_CurrentBottomAnimIndex];
		int Length = (int)FileName.length();
		fwrite(&Length, sizeof(int), 1, FileStream);
		fwrite(FileName.c_str(), sizeof(char), Length, FileStream);

		int FrameCount = Bottom->m_Animation->GetCurrentAnimation()->Sequence->GetFrameCount();

		for (int j = 0; j < FrameCount; ++j)
		{
			const AnimationFrameData& Data = Bottom->m_Animation->GetCurrentAnimation()->Sequence->GetFrameData(j);
			fwrite(&Data, sizeof(AnimationFrameData), 1, FileStream);
		}

		fclose(FileStream);
	}
}

void CMainScene::LoadInfo(float DeltaTime)
{
	FILE* FileStream;

	CGameObject* Top = FindObject("PlayerTop");

	std::string FileName = Top->m_vecAnimation[m_CurrentTopAnimIndex];

	FileName += ".txt";

	fopen_s(&FileStream, FileName.c_str(), "rt");

	if (FileStream)
	{
		FileName.clear();
		FileName = Top->m_vecAnimation[m_CurrentTopAnimIndex];

		char	Line[128] = {};
		fgets(Line, 128, FileStream);

		int FrameCount = Top->m_Animation->GetCurrentAnimation()->Sequence->GetFrameCount();
		AnimationFrameData Data;
		for (int j = 0; j < FrameCount; ++j)
		{
			Data = {};
			fread(&Data, sizeof(AnimationFrameData), 1, FileStream);
			Top->m_Animation->GetCurrentAnimation()->Sequence->LoadStartPosX(Data.StartPos.x, j);
			Top->m_Animation->GetCurrentAnimation()->Sequence->LoadStartPosY(Data.StartPos.y, j);
			Top->m_Animation->GetCurrentAnimation()->Sequence->LoadFrameSizeX(Data.Size.x, j);
			Top->m_Animation->GetCurrentAnimation()->Sequence->LoadFrameSizeY(Data.Size.y, j);
			Top->m_Animation->GetCurrentAnimation()->Sequence->LoadOffsetXData(Data.Offset.x, j);
			Top->m_Animation->GetCurrentAnimation()->Sequence->LoadOffsetYData(Data.Offset.y, j);
		}

		fclose(FileStream);
	}

	//
	CGameObject* Bottom = FindObject("PlayerBottom");

	FileName = Bottom->m_vecAnimation[m_CurrentBottomAnimIndex];

	FileName += ".txt";

	fopen_s(&FileStream, FileName.c_str(), "rt");

	if (FileStream)
	{
		FileName.clear();
		FileName = Bottom->m_vecAnimation[m_CurrentBottomAnimIndex];

		char	Line[128] = {};
		fgets(Line, 128, FileStream);

		int FrameCount = Bottom->m_Animation->GetCurrentAnimation()->Sequence->GetFrameCount();
		AnimationFrameData Data;
		for (int j = 0; j < FrameCount; ++j)
		{
			Data = {};
			fread(&Data, sizeof(AnimationFrameData), 1, FileStream);
			Bottom->m_Animation->GetCurrentAnimation()->Sequence->LoadStartPosX(Data.StartPos.x, j);
			Bottom->m_Animation->GetCurrentAnimation()->Sequence->LoadStartPosY(Data.StartPos.y, j);
			Bottom->m_Animation->GetCurrentAnimation()->Sequence->LoadFrameSizeX(Data.Size.x, j);
			Bottom->m_Animation->GetCurrentAnimation()->Sequence->LoadFrameSizeY(Data.Size.y, j);
			Bottom->m_Animation->GetCurrentAnimation()->Sequence->LoadOffsetXData(Data.Offset.x, j);
			Bottom->m_Animation->GetCurrentAnimation()->Sequence->LoadOffsetYData(Data.Offset.y, j);
		}

		fclose(FileStream);
	}
}

void CMainScene::NextAnimation(float DeltaTime)
{
	CGameObject* PlayerTop = FindObject("PlayerTop");
	CGameObject* PlayerBottom = FindObject("PlayerBottom");

	if (m_CurrentTopAnimIndex == (int)(PlayerTop->m_vecAnimation.size() - 1) || m_CurrentBottomAnimIndex == (int)(PlayerBottom->m_vecAnimation.size() - 1))
	{
		return;
	}


	++m_CurrentTopAnimIndex;

	std::string NextAnim = PlayerTop->m_vecAnimation[m_CurrentTopAnimIndex];

	PlayerTop->m_Animation->ChangeAnimation(NextAnim);

	++m_CurrentBottomAnimIndex;

	NextAnim = PlayerBottom->m_vecAnimation[m_CurrentBottomAnimIndex];

	PlayerBottom->m_Animation->ChangeAnimation(NextAnim);
}

void CMainScene::PrevAnimation(float DeltaTime)
{
	CGameObject* PlayerTop = FindObject("PlayerTop");
	CGameObject* PlayerBottom = FindObject("PlayerBottom");

	if (m_CurrentTopAnimIndex == 0 || m_CurrentBottomAnimIndex == 0)
	{
		return;
	}

	--m_CurrentTopAnimIndex;

	std::string NextAnim = PlayerTop->m_vecAnimation[m_CurrentTopAnimIndex];

	PlayerTop->m_Animation->ChangeAnimation(NextAnim);

	--m_CurrentBottomAnimIndex;

	NextAnim = PlayerBottom->m_vecAnimation[m_CurrentBottomAnimIndex];

	PlayerBottom->m_Animation->ChangeAnimation(NextAnim);
}

void CMainScene::LeftXStartPos(float DeltaTime)
{
	if (m_TopControl)
	{
		CGameObject* PlayerTop = FindObject("PlayerTop");

		AnimationInfo* Info = PlayerTop->m_Animation->GetCurrentAnimation();

		PlayerTop->m_Animation->SetCurrentAnimationXStartPos(-1.f, Info->Frame);

	}

	else
	{
		CGameObject* PlayerBottom = FindObject("PlayerBottom");

		AnimationInfo* Info = PlayerBottom->m_Animation->GetCurrentAnimation();

		PlayerBottom->m_Animation->SetCurrentAnimationXStartPos(-1.f, Info->Frame);
	}
}

void CMainScene::RightXStartPos(float DeltaTime)
{
	if (m_TopControl)
	{
		CGameObject* PlayerTop = FindObject("PlayerTop");

		AnimationInfo* Info = PlayerTop->m_Animation->GetCurrentAnimation();

		PlayerTop->m_Animation->SetCurrentAnimationXStartPos(1.f, Info->Frame);

	}

	else
	{
		CGameObject* PlayerBottom = FindObject("PlayerBottom");

		AnimationInfo* Info = PlayerBottom->m_Animation->GetCurrentAnimation();

		PlayerBottom->m_Animation->SetCurrentAnimationXStartPos(1.f, Info->Frame);
	}
}

void CMainScene::UpYStartPos(float DeltaTime)
{
	if (m_TopControl)
	{
		CGameObject* PlayerTop = FindObject("PlayerTop");

		AnimationInfo* Info = PlayerTop->m_Animation->GetCurrentAnimation();

		PlayerTop->m_Animation->SetCurrentAnimationYStartPos(-1.f, Info->Frame);

	}

	else
	{
		CGameObject* PlayerBottom = FindObject("PlayerBottom");

		AnimationInfo* Info = PlayerBottom->m_Animation->GetCurrentAnimation();

		PlayerBottom->m_Animation->SetCurrentAnimationYStartPos(-1.f, Info->Frame);
	}
}

void CMainScene::DownYStartPos(float DeltaTime)
{
	if (m_TopControl)
	{
		CGameObject* PlayerTop = FindObject("PlayerTop");

		AnimationInfo* Info = PlayerTop->m_Animation->GetCurrentAnimation();

		PlayerTop->m_Animation->SetCurrentAnimationYStartPos(1.f, Info->Frame);

	}

	else
	{
		CGameObject* PlayerBottom = FindObject("PlayerBottom");

		AnimationInfo* Info = PlayerBottom->m_Animation->GetCurrentAnimation();

		PlayerBottom->m_Animation->SetCurrentAnimationYStartPos(1.f, Info->Frame);
	}
}

void CMainScene::LeftXStartPos5(float DeltaTime)
{
	if (m_TopControl)
	{
		CGameObject* PlayerTop = FindObject("PlayerTop");

		AnimationInfo* Info = PlayerTop->m_Animation->GetCurrentAnimation();

		PlayerTop->m_Animation->SetCurrentAnimationXStartPos(-5.f, Info->Frame);

	}

	else
	{
		CGameObject* PlayerBottom = FindObject("PlayerBottom");

		AnimationInfo* Info = PlayerBottom->m_Animation->GetCurrentAnimation();

		PlayerBottom->m_Animation->SetCurrentAnimationXStartPos(-5.f, Info->Frame);
	}
}

void CMainScene::RightXStartPos5(float DeltaTime)
{
	if (m_TopControl)
	{
		CGameObject* PlayerTop = FindObject("PlayerTop");

		AnimationInfo* Info = PlayerTop->m_Animation->GetCurrentAnimation();

		PlayerTop->m_Animation->SetCurrentAnimationXStartPos(5.f, Info->Frame);

	}

	else
	{
		CGameObject* PlayerBottom = FindObject("PlayerBottom");

		AnimationInfo* Info = PlayerBottom->m_Animation->GetCurrentAnimation();

		PlayerBottom->m_Animation->SetCurrentAnimationXStartPos(5.f, Info->Frame);
	}
}


void CMainScene::IncreaseXFrameSize(float DeltaTime)
{
	if (m_TopControl)
	{
		CGameObject* PlayerTop = FindObject("PlayerTop");

		AnimationInfo* Info = PlayerTop->m_Animation->GetCurrentAnimation();

		PlayerTop->m_Animation->SetCurrentAnimationXFrameSize(1.f, Info->Frame);

	}

	else
	{
		CGameObject* PlayerBottom = FindObject("PlayerBottom");

		AnimationInfo* Info = PlayerBottom->m_Animation->GetCurrentAnimation();

		PlayerBottom->m_Animation->SetCurrentAnimationXFrameSize(1.f, Info->Frame);
	}
}

void CMainScene::DecreaseXFrameSize(float DeltaTime)
{
	if (m_TopControl)
	{
		CGameObject* PlayerTop = FindObject("PlayerTop");

		AnimationInfo* Info = PlayerTop->m_Animation->GetCurrentAnimation();

		PlayerTop->m_Animation->SetCurrentAnimationXFrameSize(-1.f, Info->Frame);

	}

	else
	{
		CGameObject* PlayerBottom = FindObject("PlayerBottom");

		AnimationInfo* Info = PlayerBottom->m_Animation->GetCurrentAnimation();

		PlayerBottom->m_Animation->SetCurrentAnimationXFrameSize(-1.f, Info->Frame);
	}
}

void CMainScene::IncreaseYFrameSize(float DeltaTime)
{
	if (m_TopControl)
	{
		CGameObject* PlayerTop = FindObject("PlayerTop");

		AnimationInfo* Info = PlayerTop->m_Animation->GetCurrentAnimation();

		PlayerTop->m_Animation->SetCurrentAnimationYFrameSize(1.f, Info->Frame);

	}

	else
	{
		CGameObject* PlayerBottom = FindObject("PlayerBottom");

		AnimationInfo* Info = PlayerBottom->m_Animation->GetCurrentAnimation();

		PlayerBottom->m_Animation->SetCurrentAnimationYFrameSize(1.f, Info->Frame);
	}
}

void CMainScene::DecreaseYFrameSize(float DeltaTime)
{
	if (m_TopControl)
	{
		CGameObject* PlayerTop = FindObject("PlayerTop");

		AnimationInfo* Info = PlayerTop->m_Animation->GetCurrentAnimation();

		PlayerTop->m_Animation->SetCurrentAnimationYFrameSize(-1.f, Info->Frame);

	}

	else
	{
		CGameObject* PlayerBottom = FindObject("PlayerBottom");

		AnimationInfo* Info = PlayerBottom->m_Animation->GetCurrentAnimation();

		PlayerBottom->m_Animation->SetCurrentAnimationYFrameSize(-1.f, Info->Frame);
	}
}

void CMainScene::MergeTextFile(float DeltaTime)
{
	FILE* FileStream;

	std::vector<std::string> m_vecTopFrame;
	std::vector<std::string> m_vecBottomFrame;

	CGameObject* Top = FindObject("PlayerTop");
	CGameObject* Bottom = FindObject("PlayerBottom");

	m_vecTopFrame.push_back("PlayerIdleRightTop");
	m_vecTopFrame.push_back("PlayerIdleLeftTop");
	m_vecTopFrame.push_back("PlayerNormalFireRightTop");
	m_vecTopFrame.push_back("PlayerNormalFireLeftTop");
	m_vecTopFrame.push_back("PlayerRunRightTop");
	m_vecTopFrame.push_back("PlayerRunLeftTop");
	m_vecTopFrame.push_back("PlayerVerticalJumpRightTop");
	m_vecTopFrame.push_back("PlayerVerticalJumpLeftTop");
	m_vecTopFrame.push_back("PlayerJumpDownRightTop");
	m_vecTopFrame.push_back("PlayerJumpDownLeftTop");
	m_vecTopFrame.push_back("PlayerJumpAttackDownRightTop");
	m_vecTopFrame.push_back("PlayerJumpAttackDownLeftTop");
	m_vecTopFrame.push_back("PlayerLookUpRightTop");
	m_vecTopFrame.push_back("PlayerLookUpLeftTop");
	m_vecTopFrame.push_back("PlayerLookUpAttackRightTop");
	m_vecTopFrame.push_back("PlayerLookUpAttackLeftTop");
	m_vecTopFrame.push_back("PlayerFrontJumpRightTop");
	m_vecTopFrame.push_back("PlayerFrontJumpLeftTop");
	m_vecTopFrame.push_back("PlayerBombRightTop");
	m_vecTopFrame.push_back("PlayerBombLeftTop");


	m_vecBottomFrame.push_back("PlayerIdleRightBottom1");
	m_vecBottomFrame.push_back("PlayerIdleLeftBottom1");
	m_vecBottomFrame.push_back("PlayerNormalFireRightBottom");
	m_vecBottomFrame.push_back("PlayerNormalFireLeftBottom");
	m_vecBottomFrame.push_back("PlayerRunRightBottom");
	m_vecBottomFrame.push_back("PlayerRunLeftBottom");
	m_vecBottomFrame.push_back("PlayerVerticalJumpRightBottom1");
	m_vecBottomFrame.push_back("PlayerVerticalJumpLeftBottom1");
	m_vecBottomFrame.push_back("PlayerFrontJumpRightBottom");
	m_vecBottomFrame.push_back("PlayerFrontJumpLeftBottom");
	m_vecBottomFrame.push_back("PlayerSitDownIdleRight");
	m_vecBottomFrame.push_back("PlayerSitDownIdleLeft");
	m_vecBottomFrame.push_back("PlayerCrawlRight");
	m_vecBottomFrame.push_back("PlayerCrawlLeft");
	m_vecBottomFrame.push_back("PlayerSitDownNormalAttackRight");
	m_vecBottomFrame.push_back("PlayerSitDownNormalAttackLeft");
	m_vecBottomFrame.push_back("PlayerSitDownBombRight");
	m_vecBottomFrame.push_back("PlayerSitDownBombLeft");

	const std::string FileName = "PlayerFrameData.fdat";

	fopen_s(&FileStream, FileName.c_str(), "wb");

	if (FileStream)
	{	
		// TopAnimation FrameData 작성
		int Size = (size_t)m_vecTopFrame.size();
		for (int i = 0; i < Size; ++i)
		{
			int AnimNameLength = (int)m_vecTopFrame[i].length();
			fwrite(&AnimNameLength, sizeof(int), 1, FileStream);
			fwrite(m_vecTopFrame[i].c_str(), sizeof(char), AnimNameLength, FileStream);

			int FrameCount = GetSceneResource()->FindAnimationSequence(m_vecTopFrame[i])->GetFrameCount();
			
			for (int j = 0; j < FrameCount; ++j)
			{
				const AnimationFrameData& Data = GetSceneResource()->FindAnimationSequence(m_vecTopFrame[i])->GetFrameData(j);
				fwrite(&Data, sizeof(AnimationFrameData), 1, FileStream);
			}

		}

		// BottomAnimation FrameData 작성
		Size = (size_t)m_vecBottomFrame.size();
		for (int i = 0; i < Size; ++i)
		{
			int AnimNameLength = (int)m_vecBottomFrame[i].length();
			fwrite(&AnimNameLength, sizeof(int), 1, FileStream);
			fwrite(m_vecBottomFrame[i].c_str(), sizeof(char), AnimNameLength, FileStream);

			int FrameCount = GetSceneResource()->FindAnimationSequence(m_vecBottomFrame[i])->GetFrameCount();

			for (int j = 0; j < FrameCount; ++j)
			{
				const AnimationFrameData& Data = GetSceneResource()->FindAnimationSequence(m_vecBottomFrame[i])->GetFrameData(j);
				fwrite(&Data, sizeof(AnimationFrameData), 1, FileStream);
			}

		}
	}
}

