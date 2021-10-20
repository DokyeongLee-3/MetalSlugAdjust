
#include "MainScene.h"
#include "../Object/Player.h"
#include "../Object/Monster.h"
#include "SceneResource.h"
#include "../GameManager.h"
#include "../Input.h"


CMainScene::CMainScene()	:
	m_TopControl(true),
	m_CurrentTopAnimIndex(0),
	m_CurrentBottomAnimIndex(0),
	m_TopBiggerZOrder(true)
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

	CInput::GetInst()->SetCallback<CMainScene>("MergePlayerFile", KeyState_Down, this, &CMainScene::MergePlayerFrameDataFile);
	CInput::GetInst()->SetCallback<CMainScene>("MergeArabianFile", KeyState_Down, this, &CMainScene::MergeArabianFrameDataFile);
	CInput::GetInst()->SetCallback<CMainScene>("MergeNPCFile", KeyState_Down, this, &CMainScene::MergeNPCFrameDataFile);

	CInput::GetInst()->SetCallback<CMainScene>("SwapZOrder", KeyState_Down, this, &CMainScene::SwapZOrder);
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

	Bottom->AddAnimation("BombExplosionEffect", true, 1.f);
	Bottom->m_vecAnimation.push_back("BombExplosionEffect");

	Bottom->AddAnimation("PlayerSitDownBombRight", true, 1.f);
	Bottom->m_vecAnimation.push_back("PlayerSitDownBombRight");
	Bottom->AddAnimation("PlayerSitDownBombLeft", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("PlayerSitDownBombLeft");


	Bottom->AddAnimation("ArabianShuffleRight", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("ArabianShuffleRight");
	Bottom->AddAnimation("ArabianShuffleLeft", true, 1.f);
	Bottom->m_vecAnimation.push_back("ArabianShuffleLeft");

	Bottom->AddAnimation("ArabianRunRight", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("ArabianRunRight");
	Bottom->AddAnimation("ArabianRunLeft", true, 1.f);
	Bottom->m_vecAnimation.push_back("ArabianRunLeft");

	Bottom->AddAnimation("ArabianTurn", true, 1.f);
	Bottom->m_vecAnimation.push_back("ArabianTurn");

	Bottom->AddAnimation("ArabianPrepareRight", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("ArabianPrepareRight");
	Bottom->AddAnimation("ArabianPrepareLeft", true, 1.f);
	Bottom->m_vecAnimation.push_back("ArabianPrepareLeft");

	Bottom->AddAnimation("ArabianAttackRight", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("ArabianAttackRight");
	Bottom->AddAnimation("ArabianAttackLeft", true, 1.f);
	Bottom->m_vecAnimation.push_back("ArabianAttackLeft");

	Bottom->AddAnimation("ArabianThrowRight", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("ArabianThrowRight");
	Bottom->AddAnimation("ArabianThrowLeft", true, 1.f);
	Bottom->m_vecAnimation.push_back("ArabianThrowLeft");

	Bottom->AddAnimation("ArabianDeathAnimationRight2", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("ArabianDeathAnimationRight2");
	Bottom->AddAnimation("ArabianDeathAnimationLeft2", true, 1.f);
	Bottom->m_vecAnimation.push_back("ArabianDeathAnimationLeft2");

	Bottom->AddAnimation("ArabianDeathAnimationRight1", true, 2.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("ArabianDeathAnimationRight1");
	Bottom->AddAnimation("ArabianDeathAnimationLeft1", true, 2.f);
	Bottom->m_vecAnimation.push_back("ArabianDeathAnimationLeft1");

	Bottom->AddAnimation("ArabianDeathAnimationRight3", true, 2.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("ArabianDeathAnimationRight3");
	Bottom->AddAnimation("ArabianDeathAnimationLeft3", true, 2.f);
	Bottom->m_vecAnimation.push_back("ArabianDeathAnimationLeft3");

	Bottom->AddAnimation("ArabianJumpRight", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("ArabianJumpRight");
	Bottom->AddAnimation("ArabianJumpLeft", true, 1.f);
	Bottom->m_vecAnimation.push_back("ArabianJumpLeft");

	Bottom->AddAnimation("KnifeRotateRight", true, 1.f);
	Bottom->m_vecAnimation.push_back("KnifeRotateRight");
	Bottom->AddAnimation("KnifeRotateLeft", true, 1.f);
	Bottom->m_vecAnimation.push_back("KnifeRotateLeft");

	Bottom->AddAnimation("PlayerDeathRight", true, 2.f);
	Bottom->m_vecAnimation.push_back("PlayerDeathRight");
	Bottom->AddAnimation("PlayerDeathLeft", true, 2.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("PlayerDeathLeft");

	Bottom->AddAnimation("HelperEscapeLeft", true, 1.f);
	Bottom->m_vecAnimation.push_back("HelperEscapeLeft");
	Bottom->AddAnimation("HelperGiveLeft", true, 1.f);
	Bottom->m_vecAnimation.push_back("HelperGiveLeft");
	Bottom->AddAnimation("HelperIdleLeft", true, 1.f);
	Bottom->m_vecAnimation.push_back("HelperIdleLeft");
	Bottom->AddAnimation("HelperRunLeft", true, 1.f);
	Bottom->m_vecAnimation.push_back("HelperRunLeft");
	Bottom->AddAnimation("HelperSaluteLeft", true, 1.f);
	Bottom->m_vecAnimation.push_back("HelperSaluteLeft");
	Bottom->AddAnimation("HelperWalkLeft", true, 1.f);
	Bottom->m_vecAnimation.push_back("HelperWalkLeft");
	Bottom->AddAnimation("HelperWalkRight", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("HelperWalkRight");

	Bottom->AddAnimation("ItemGetEffect", true, 0.5f);
	Bottom->m_vecAnimation.push_back("ItemGetEffect");


	Bottom->AddAnimation("PlayerIdleLeftBottom5", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("PlayerIdleLeftBottom5");
	Bottom->AddAnimation("PlayerIdleRightBottom5", true, 1.f);
	Bottom->m_vecAnimation.push_back("PlayerIdleRightBottom5");

	// Bottom For HeavyRun
	Bottom->AddAnimation("PlayerRunLeftBottom1", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("PlayerRunLeftBottom1");
	Bottom->AddAnimation("PlayerRunRightBottom1", true, 1.f, 1.f, false);
	Bottom->m_vecAnimation.push_back("PlayerRunRightBottom1");


	Bottom->AddAnimation("PlayerIdleLeftBottom6", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("PlayerIdleLeftBottom6");
	Bottom->AddAnimation("PlayerIdleRightBottom6", true, 1.f);
	Bottom->m_vecAnimation.push_back("PlayerIdleRightBottom6");
	Bottom->AddAnimation("PlayerIdleLeftBottom7", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("PlayerIdleLeftBottom7");
	Bottom->AddAnimation("PlayerIdleRightBottom7", true, 1.f);
	Bottom->m_vecAnimation.push_back("PlayerIdleRightBottom7");

	Bottom->AddAnimation("PlayerIdleLeftBottom8", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("PlayerIdleLeftBottom8");
	Bottom->AddAnimation("PlayerIdleRightBottom8", true, 1.f);
	Bottom->m_vecAnimation.push_back("PlayerIdleRightBottom8");

	Bottom->AddAnimation("PlayerIdleLeftBottom9", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("PlayerIdleLeftBottom9");
	Bottom->AddAnimation("PlayerIdleRightBottom9", true, 1.f);
	Bottom->m_vecAnimation.push_back("PlayerIdleRightBottom9");

	Bottom->AddAnimation("PlayerIdleLeftBottom10", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("PlayerIdleLeftBottom10");
	Bottom->AddAnimation("PlayerIdleRightBottom10", true, 1.f);
	Bottom->m_vecAnimation.push_back("PlayerIdleRightBottom10");

	Bottom->AddAnimation("PlayerIdleLeftBottom11", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("PlayerIdleLeftBottom11");
	Bottom->AddAnimation("PlayerIdleRightBottom11", true, 1.f);
	Bottom->m_vecAnimation.push_back("PlayerIdleRightBottom11");

	// 여기부터 Vertical로
	Bottom->AddAnimation("PlayerVerticalJumpLeftBottom4", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("PlayerVerticalJumpLeftBottom4");
	Bottom->AddAnimation("PlayerVerticalJumpRightBottom4", true, 1.f);
	Bottom->m_vecAnimation.push_back("PlayerVerticalJumpRightBottom4");

	Bottom->AddAnimation("PlayerVerticalJumpLeftBottom5", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("PlayerVerticalJumpLeftBottom5");
	Bottom->AddAnimation("PlayerVerticalJumpRightBottom5", true, 1.f);
	Bottom->m_vecAnimation.push_back("PlayerVerticalJumpRightBottom5");

	Bottom->AddAnimation("PlayerVerticalJumpLeftBottom6", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("PlayerVerticalJumpLeftBottom6");
	Bottom->AddAnimation("PlayerVerticalJumpRightBottom6", true, 1.f);
	Bottom->m_vecAnimation.push_back("PlayerVerticalJumpRightBottom6");

	Bottom->AddAnimation("PlayerVerticalJumpLeftBottom7", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("PlayerVerticalJumpLeftBottom7");
	Bottom->AddAnimation("PlayerVerticalJumpRightBottom7", true, 1.f);
	Bottom->m_vecAnimation.push_back("PlayerVerticalJumpRightBottom7");

	Bottom->AddAnimation("HeavySitDownIdleLeft", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("HeavySitDownIdleLeft");
	Bottom->AddAnimation("HeavySitDownIdleRight", true, 1.f);
	Bottom->m_vecAnimation.push_back("HeavySitDownIdleRight");

	Bottom->AddAnimation("HeavySitDownBombLeft", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("HeavySitDownBombLeft");
	Bottom->AddAnimation("HeavySitDownBombRight", true, 1.f);
	Bottom->m_vecAnimation.push_back("HeavySitDownBombRight");

	Bottom->AddAnimation("HeavyCrawlLeft", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("HeavyCrawlLeft");
	Bottom->AddAnimation("HeavyCrawlRight", true, 1.f);
	Bottom->m_vecAnimation.push_back("HeavyCrawlRight");

	Bottom->AddAnimation("HeavySitDownIdleAfterBombLeft", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("HeavySitDownIdleAfterBombLeft");
	Bottom->AddAnimation("HeavySitDownIdleAfterBombRight", true, 1.f);
	Bottom->m_vecAnimation.push_back("HeavySitDownIdleAfterBombRight");
	Bottom->AddAnimation("HeavySitDownFireLeft", true, 1.f, 1.f, true);
	Bottom->m_vecAnimation.push_back("HeavySitDownFireLeft");
	Bottom->AddAnimation("HeavySitDownFireRight", true, 1.f);
	Bottom->m_vecAnimation.push_back("HeavySitDownFireRight");

	Bottom->AddAnimation("PlayerIdleLeftBottom12", true, 1.f);
	Bottom->m_vecAnimation.push_back("PlayerIdleLeftBottom12");
	Bottom->AddAnimation("PlayerIdleRightBottom12", true, 1.f);
	Bottom->m_vecAnimation.push_back("PlayerIdleRightBottom12");

	Bottom->AddAnimation("PlayerIdleLeftBottom13", true, 1.f);
	Bottom->m_vecAnimation.push_back("PlayerIdleLeftBottom13");
	Bottom->AddAnimation("PlayerIdleRightBottom13", true, 1.f);
	Bottom->m_vecAnimation.push_back("PlayerIdleRightBottom13");

	Bottom->AddAnimation("PlayerVerticalJumpLeftBottom8", true, 1.f);
	Bottom->m_vecAnimation.push_back("PlayerVerticalJumpLeftBottom8");
	Bottom->AddAnimation("PlayerVerticalJumpRightBottom8", true, 1.f);
	Bottom->m_vecAnimation.push_back("PlayerVerticalJumpRightBottom8");

	Bottom->AddAnimation("PlayerVerticalJumpLeftBottom9", true, 1.f);
	Bottom->m_vecAnimation.push_back("PlayerVerticalJumpLeftBottom9");
	Bottom->AddAnimation("PlayerVerticalJumpRightBottom9", true, 1.f);
	Bottom->m_vecAnimation.push_back("PlayerVerticalJumpRightBottom9");

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

	Top->AddAnimation("Blank12", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank12");
	Top->AddAnimation("Blank13", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank13");

	Top->AddAnimation("Blank14", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank14");
	Top->AddAnimation("Blank15", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank15");

	Top->AddAnimation("Blank16", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank16");

	Top->AddAnimation("Blank17", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank17");
	Top->AddAnimation("Blank18", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank18");

	Top->AddAnimation("Blank19", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank19");
	Top->AddAnimation("Blank20", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank20");

	Top->AddAnimation("Blank21", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank21");
	Top->AddAnimation("Blank22", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank22");

	Top->AddAnimation("Blank23", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank23");
	Top->AddAnimation("Blank24", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank24");

	Top->AddAnimation("Blank25", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank25");
	Top->AddAnimation("Blank26", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank26");

	Top->AddAnimation("Blank27", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank27");
	Top->AddAnimation("Blank28", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank28");

	Top->AddAnimation("Blank29", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank29");
	Top->AddAnimation("Blank30", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank30");

	Top->AddAnimation("Blank31", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank31");
	Top->AddAnimation("Blank32", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank32");

	Top->AddAnimation("Blank33", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank33");
	Top->AddAnimation("Blank34", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank34");

	Top->AddAnimation("Blank35", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank35");
	Top->AddAnimation("Blank36", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank36");
	Top->AddAnimation("Blank37", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank37");
	Top->AddAnimation("Blank38", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank38");
	Top->AddAnimation("Blank39", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank39");
	Top->AddAnimation("Blank40", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank40");
	Top->AddAnimation("Blank41", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank41");

	Top->AddAnimation("Blank42", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank42");

	Top->AddAnimation("HeavyIdleLeftTop", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("HeavyIdleLeftTop");
	Top->AddAnimation("HeavyIdleRightTop", true, 1.f);
	Top->m_vecAnimation.push_back("HeavyIdleRightTop");
	Top->AddAnimation("HeavyRunLeftTop", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("HeavyRunLeftTop");
	Top->AddAnimation("HeavyRunRightTop", true, 1.f);
	Top->m_vecAnimation.push_back("HeavyRunRightTop");

	Top->AddAnimation("HeavyFireLeftTop", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("HeavyFireLeftTop");
	Top->AddAnimation("HeavyFireRightTop", true, 1.f);
	Top->m_vecAnimation.push_back("HeavyFireRightTop");
	// 7
	Top->AddAnimation("HeavyLookUpLeftTop", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("HeavyLookUpLeftTop");
	// 7
	Top->AddAnimation("HeavyLookUpRightTop", true, 1.f);
	Top->m_vecAnimation.push_back("HeavyLookUpRightTop");


	// 8
	Top->AddAnimation("HeavyUpperLiftUpLeftTop", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("HeavyUpperLiftUpLeftTop");
	// 8
	Top->AddAnimation("HeavyUpperLiftUpRightTop", true, 1.f);
	Top->m_vecAnimation.push_back("HeavyUpperLiftUpRightTop");

	// 9
	Top->AddAnimation("HeavyUpperLiftUpFireLeftTop", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("HeavyUpperLiftUpFireLeftTop");
	// 9
	Top->AddAnimation("HeavyUpperLiftUpFireRightTop", true, 1.f);
	Top->m_vecAnimation.push_back("HeavyUpperLiftUpFireRightTop");


	// 10
	Top->AddAnimation("HeavyUpperLiftDownLeftTop", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("HeavyUpperLiftDownLeftTop");
	// 10
	Top->AddAnimation("HeavyUpperLiftDownRightTop", true, 1.f);
	Top->m_vecAnimation.push_back("HeavyUpperLiftDownRightTop");

	// 11
	Top->AddAnimation("HeavyUpperLiftDownFireLeftTop", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("HeavyUpperLiftDownFireLeftTop");
	// 11
	Top->AddAnimation("HeavyUpperLiftDownFireRightTop", true, 1.f);
	Top->m_vecAnimation.push_back("HeavyUpperLiftDownFireRightTop");

	
	/////

	// 12
	Top->AddAnimation("HeavyLowerLiftUpLeftTop", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("HeavyLowerLiftUpLeftTop");
	// 12
	Top->AddAnimation("HeavyLowerLiftUpRightTop", true, 1.f);
	Top->m_vecAnimation.push_back("HeavyLowerLiftUpRightTop");

	// 13
	Top->AddAnimation("HeavyLowerLiftUpFireLeftTop", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("HeavyLowerLiftUpFireLeftTop");
	// 13
	Top->AddAnimation("HeavyLowerLiftUpFireRightTop", true, 1.f);
	Top->m_vecAnimation.push_back("HeavyLowerLiftUpFireRightTop");


	// 14
	Top->AddAnimation("HeavyLowerLiftDownLeftTop", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("HeavyLowerLiftDownLeftTop");
	// 14
	Top->AddAnimation("HeavyLowerLiftDownRightTop", true, 1.f);
	Top->m_vecAnimation.push_back("HeavyLowerLiftDownRightTop");

	// 15
	Top->AddAnimation("HeavyLowerLiftDownFireLeftTop", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("HeavyLowerLiftDownFireLeftTop");
	// 15
	Top->AddAnimation("HeavyLowerLiftDownFireRightTop", true, 1.f);
	Top->m_vecAnimation.push_back("HeavyLowerLiftDownFireRightTop");


	Top->AddAnimation("Blank43", true, 1.f);
	Top->m_vecAnimation.push_back("Blank43");
	Top->AddAnimation("Blank44", true, 1.f);
	Top->m_vecAnimation.push_back("Blank44");

	Top->AddAnimation("Blank45", true, 1.f);
	Top->m_vecAnimation.push_back("Blank45");
	Top->AddAnimation("Blank46", true, 1.f);
	Top->m_vecAnimation.push_back("Blank46");

	Top->AddAnimation("Blank47", true, 1.f);
	Top->m_vecAnimation.push_back("Blank47");
	Top->AddAnimation("Blank48", true, 1.f);
	Top->m_vecAnimation.push_back("Blank48");

	Top->AddAnimation("Blank49", true, 1.f);
	Top->m_vecAnimation.push_back("Blank49");
	Top->AddAnimation("Blank50", true, 1.f);
	Top->m_vecAnimation.push_back("Blank50");

	Top->AddAnimation("Blank51", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank51");
	Top->AddAnimation("Blank52", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("Blank52");

	Top->AddAnimation("HeavyBombLeftTop", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("HeavyBombLeftTop");
	Top->AddAnimation("HeavyBombRightTop", true, 1.f);
	Top->m_vecAnimation.push_back("HeavyBombRightTop");

	Top->AddAnimation("HeavyLookUpFireLeftTop", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("HeavyLookUpFireLeftTop");
	Top->AddAnimation("HeavyLookUpFireRightTop", true, 1.f);
	Top->m_vecAnimation.push_back("HeavyLookUpFireRightTop");

	Top->AddAnimation("HeavyJumpAttackDownLeftTop", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("HeavyJumpAttackDownLeftTop");
	Top->AddAnimation("HeavyJumpAttackDownRightTop", true, 1.f);
	Top->m_vecAnimation.push_back("HeavyJumpAttackDownRightTop");

	Top->AddAnimation("HeavyJumpDownLeftTop", true, 1.f, 1.f, true);
	Top->m_vecAnimation.push_back("HeavyJumpDownLeftTop");
	Top->AddAnimation("HeavyJumpDownRightTop", true, 1.f);
	Top->m_vecAnimation.push_back("HeavyJumpDownRightTop");

	Bottom->AddAnimation("CamelRun", true, 2.f);
	Bottom->m_vecAnimation.push_back("CamelRun");
	Bottom->AddAnimation("CamelRun1", true, 2.f);
	Bottom->m_vecAnimation.push_back("CamelRun1");
	Bottom->AddAnimation("CamelDown", true, 1.f);
	Bottom->m_vecAnimation.push_back("CamelDown");
	Bottom->AddAnimation("CamelIdle", true, 2.f);
	Bottom->m_vecAnimation.push_back("CamelIdle");

	Top->AddAnimation("CamelArabianIdle", true, 1.f);
	Top->m_vecAnimation.push_back("CamelArabianIdle");
	Top->AddAnimation("CamelArabianEntrance", true, 1.f);
	Top->m_vecAnimation.push_back("CamelArabianEntrance");
	Top->AddAnimation("CamelArabianDown", true, 1.f);
	Top->m_vecAnimation.push_back("CamelArabianDown");
	Top->AddAnimation("CamelArabianAttack", true, 1.f);
	Top->m_vecAnimation.push_back("CamelArabianAttack");

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

	GetSceneResource()->CreateAnimationSequence("BombExplosionEffect",
		"BombExplosionEffect", TEXT("Effect/BombExplosion.bmp"));

	GetSceneResource()->SetTextureColorKey("BombExplosionEffect",
		0, 248, 0);

	for (int i = 0; i < 21; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("BombExplosionEffect",
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


	GetSceneResource()->CreateAnimationSequence("ArabianShuffleLeft",
		"ArabianShuffleLeft", TEXT("Arabian/Shuffle/Left/Arabian_Shuffle.bmp"));

	GetSceneResource()->SetTextureColorKey("ArabianShuffleLeft",
		255, 255, 255);

	for (int i = 0; i < 12; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("ArabianShuffleLeft",
			i * 160.f, 0.f, 160.f, 162.f);
	}

	GetSceneResource()->CreateAnimationSequence("ArabianShuffleRight",
		"ArabianShuffleRight", TEXT("Arabian/Shuffle/Right/Arabian_Shuffle.bmp"));

	GetSceneResource()->SetTextureColorKey("ArabianShuffleRight",
		255, 255, 255);

	for (int i = 0; i < 12; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("ArabianShuffleRight",
			i * 160.f, 0.f, 160.f, 162.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank12",
		"Blank12", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank12",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank12",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank13",
		"Blank13", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank13",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank13",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("ArabianRunLeft",
		"ArabianRunLeft", TEXT("Arabian/Run/Left/Arabian_Run.bmp"));

	GetSceneResource()->SetTextureColorKey("ArabianRunLeft",
		255, 255, 255);

	for (int i = 0; i < 12; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("ArabianRunLeft",
			i * 160.f, 0.f, 160.f, 161.f);
	}

	GetSceneResource()->CreateAnimationSequence("ArabianRunRight",
		"ArabianRunRight", TEXT("Arabian/Run/Right/Arabian_Run.bmp"));

	GetSceneResource()->SetTextureColorKey("ArabianRunRight",
		255, 255, 255);

	for (int i = 0; i < 12; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("ArabianRunRight",
			i * 160.f, 0.f, 160.f, 161.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank14",
		"Blank14", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank14",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank14",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank15",
		"Blank15", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank15",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank15",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("ArabianTurn",
		"ArabianTurn", TEXT("Arabian/Turn/Turn.bmp"));

	GetSceneResource()->SetTextureColorKey("ArabianTurn",
		255, 255, 255);

	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("ArabianTurn",
			i * 115.f, 0.f, 115.f, 135.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank16",
		"Blank16", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank16",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank16",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("ArabianPrepareLeft",
		"ArabianPrepareLeft", TEXT("Arabian/Prepare/Left/Prepare.bmp"));

	GetSceneResource()->SetTextureColorKey("ArabianPrepareLeft",
		255, 255, 255);

	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("ArabianPrepareLeft",
			i * 200.f, 0.f, 200.f, 141.f);
	}

	GetSceneResource()->CreateAnimationSequence("ArabianPrepareRight",
		"ArabianPrepareRight", TEXT("Arabian/Prepare/Right/Prepare.bmp"));

	GetSceneResource()->SetTextureColorKey("ArabianPrepareRight",
		255, 255, 255);

	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("ArabianPrepareRight",
			i * 200.f, 0.f, 200.f, 141.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank17",
		"Blank17", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank17",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank17",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank18",
		"Blank18", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank18",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank18",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("ArabianAttackLeft",
		"ArabianAttackLeft", TEXT("Arabian/Attack/Left/ArabianAttack.bmp"));

	GetSceneResource()->SetTextureColorKey("ArabianAttackLeft",
		255, 255, 255);

	for (int i = 0; i < 7; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("ArabianAttackLeft",
			i * 206.f, 0.f, 206.f, 172.f);
	}

	GetSceneResource()->CreateAnimationSequence("ArabianAttackRight",
		"ArabianAttackRight", TEXT("Arabian/Attack/Right/ArabianAttack.bmp"));

	GetSceneResource()->SetTextureColorKey("ArabianAttackRight",
		255, 255, 255);

	for (int i = 0; i < 7; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("ArabianAttackRight",
			i * 206.f, 0.f, 206.f, 172.f);
	}


	GetSceneResource()->CreateAnimationSequence("Blank19",
		"Blank19", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank19",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank19",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank20",
		"Blank20", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank20",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank20",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("ArabianThrowRight",
		"ArabianThrowRight", TEXT("Arabian/Throwing/Right/Throw.bmp"));

	GetSceneResource()->SetTextureColorKey("ArabianThrowRight",
		255, 255, 255);

	for (int i = 0; i < 19; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("ArabianThrowRight",
			i * 140.f, 0.f, 140.f, 169.f);
	}

	GetSceneResource()->CreateAnimationSequence("ArabianThrowLeft",
		"ArabianThrowLeft", TEXT("Arabian/Throwing/Left/Throw.bmp"));

	GetSceneResource()->SetTextureColorKey("ArabianThrowLeft",
		255, 255, 255);

	for (int i = 0; i < 19; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("ArabianThrowLeft",
			i * 140.f, 0.f, 140.f, 169.f);
	}

	GetSceneResource()->CreateAnimationSequence("ArabianDeathAnimationRight2",
		"ArabianDeathAnimationRight2", TEXT("Arabian/Death/Right/DeathAnimation2.bmp"));

	GetSceneResource()->SetTextureColorKey("ArabianDeathAnimationRight2",
		255, 255, 255);

	for (int i = 0; i < 19; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("ArabianDeathAnimationRight2",
			i * 170.f, 0.f, 170.f, 142.f);
	}

	GetSceneResource()->CreateAnimationSequence("ArabianDeathAnimationLeft2",
		"ArabianDeathAnimationLeft2", TEXT("Arabian/Death/Left/DeathAnimation2.bmp"));

	GetSceneResource()->SetTextureColorKey("ArabianDeathAnimationLeft2",
		255, 255, 255);

	for (int i = 0; i < 19; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("ArabianDeathAnimationLeft2",
			i * 170.f, 0.f, 170.f, 142.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank21",
		"Blank21", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank21",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank21",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank22",
		"Blank22", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank22",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank22",
			i * 100.f, 0.f, 100.f, 68.f);
	}


	GetSceneResource()->CreateAnimationSequence("ArabianDeathAnimationRight1",
		"ArabianDeathAnimationRight1", TEXT("Arabian/Death/Right/DeathAnimation1.bmp"));

	GetSceneResource()->SetTextureColorKey("ArabianDeathAnimationRight1",
		255, 255, 255);

	for (int i = 0; i < 28; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("ArabianDeathAnimationRight1",
			i * 160.f, 0.f, 160.f, 163.f);
	}

	GetSceneResource()->CreateAnimationSequence("ArabianDeathAnimationLeft1",
		"ArabianDeathAnimationLeft1", TEXT("Arabian/Death/Left/DeathAnimation1.bmp"));

	GetSceneResource()->SetTextureColorKey("ArabianDeathAnimationLeft1",
		255, 255, 255);

	for (int i = 0; i < 28; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("ArabianDeathAnimationLeft1",
			i * 160.f, 0.f, 160.f, 163.f);
	}


	GetSceneResource()->CreateAnimationSequence("Blank23",
		"Blank23", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank23",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank23",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank24",
		"Blank24", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank24",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank24",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("ArabianDeathAnimationRight3",
		"ArabianDeathAnimationRight3", TEXT("Arabian/Death/Right/DeathAnimation3.bmp"));

	GetSceneResource()->SetTextureColorKey("ArabianDeathAnimationRight3",
		255, 255, 255);

	for (int i = 0; i < 13; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("ArabianDeathAnimationRight3",
			i * 205.f, 0.f, 205.f, 139.f);
	}

	GetSceneResource()->CreateAnimationSequence("ArabianDeathAnimationLeft3",
		"ArabianDeathAnimationLeft3", TEXT("Arabian/Death/Left/DeathAnimation3.bmp"));

	GetSceneResource()->SetTextureColorKey("ArabianDeathAnimationLeft3",
		255, 255, 255);

	for (int i = 0; i < 13; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("ArabianDeathAnimationLeft3",
			i * 205.f, 0.f, 205.f, 139.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank25",
		"Blank25", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank25",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank25",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank26",
		"Blank26", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank26",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank26",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("ArabianJumpLeft",
		"ArabianJumpLeft", TEXT("Arabian/Jump/Left/Jump.bmp"));

	GetSceneResource()->SetTextureColorKey("ArabianJumpLeft",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("ArabianJumpLeft",
			i * 145.f, 0.f, 145.f, 137.f);
	}

	GetSceneResource()->CreateAnimationSequence("ArabianJumpRight",
		"ArabianJumpRight", TEXT("Arabian/Jump/Right/Jump.bmp"));

	GetSceneResource()->SetTextureColorKey("ArabianJumpRight",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("ArabianJumpRight",
			i * 145.f, 0.f, 145.f, 137.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank27",
		"Blank27", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank27",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank27",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank28",
		"Blank28", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank28",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank28",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank29",
		"Blank29", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank29",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank29",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank30",
		"Blank30", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank30",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank30",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("KnifeRotateLeft",
		"KnifeRotateLeft", TEXT("Arabian/Item/Left/ArabianKnife.bmp"));

	GetSceneResource()->SetTextureColorKey("KnifeRotateLeft",
		255, 255, 255);

	for (int i = 0; i < 18; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("KnifeRotateLeft",
			i * 95.f, 0.f, 95.f, 111.f);
	}

	GetSceneResource()->CreateAnimationSequence("KnifeRotateRight",
		"KnifeRotateRight", TEXT("Arabian/Item/Right/ArabianKnife.bmp"));

	GetSceneResource()->SetTextureColorKey("KnifeRotateRight",
		255, 255, 255);

	for (int i = 0; i < 18; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("KnifeRotateRight",
			i * 95.f, 0.f, 95.f, 111.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank31",
		"Blank31", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank31",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank31",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank32",
		"Blank32", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank32",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank32",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	// DeathAnimation
	GetSceneResource()->CreateAnimationSequence("PlayerDeathRight",
		"PlayerDeathRight", TEXT("Player/Death/Right/PlayerDeath.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerDeathRight",
		255, 255, 255);

	for (int i = 0; i < 29; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerDeathRight",
			i * 100.f, 0.f, 100.f, 123.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerDeathLeft",
		"PlayerDeathLeft", TEXT("Player/Death/Left/PlayerDeath.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerDeathLeft",
		255, 255, 255);

	for (int i = 0; i < 29; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerDeathLeft",
			i * 100.f, 0.f, 100.f, 123.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank33",
		"Blank33", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank33",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank33",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank34",
		"Blank34", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank34",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank34",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	// CamelArabian 시작

	GetSceneResource()->CreateAnimationSequence("CamelArabianIdle",
		"CamelArabianIdle", TEXT("CamelArabian/Idle/Left/CamelArabianIdle.bmp"));

	GetSceneResource()->SetTextureColorKey("CamelArabianIdle",
		255, 255, 255);

	for (int i = 0; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("CamelArabianIdle",
			i * 140.f, 0.f, 140.f, 152.f);
	}

	GetSceneResource()->CreateAnimationSequence("CamelRun",
		"CamelRun", TEXT("Vehicle/Camel/Run/Left/CamelRun.bmp"));

	GetSceneResource()->SetTextureColorKey("CamelRun",
		255, 255, 255);

	for (int i = 0; i < 12; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("CamelRun",
			i * 275.f, 0.f, 275.f, 196.f);
	}

	GetSceneResource()->CreateAnimationSequence("CamelRun1",
		"CamelRun1", TEXT("Vehicle/Camel/Run/Left/CamelRun.bmp"));

	GetSceneResource()->SetTextureColorKey("CamelRun1",
		255, 255, 255);

	for (int i = 0; i < 12; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("CamelRun1",
			i * 275.f, 0.f, 275.f, 196.f);
	}

	GetSceneResource()->CreateAnimationSequence("CamelArabianEntrance",
		"CamelArabianEntrance", TEXT("CamelArabian/Entrance/Left/CamelArabianEntrance.bmp"));

	GetSceneResource()->SetTextureColorKey("CamelArabianEntrance",
		255, 255, 255);

	for (int i = 0; i < 10; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("CamelArabianEntrance",
			i * 180.f, 0.f, 180.f, 155.f);
	}

	GetSceneResource()->CreateAnimationSequence("CamelArabianDown",
		"CamelArabianDown", TEXT("CamelArabian/Down/Left/CamelArabianDown.bmp"));

	GetSceneResource()->SetTextureColorKey("CamelArabianDown",
		255, 255, 255);

	for (int i = 0; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("CamelArabianDown",
			i * 210.f, 0.f, 210.f, 174.f);
	}

	GetSceneResource()->CreateAnimationSequence("CamelDown",
		"CamelDown", TEXT("Vehicle/Camel/Down/Left/CamelDown.bmp"));

	GetSceneResource()->SetTextureColorKey("CamelDown",
		255, 255, 255);

	for (int i = 0; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("CamelDown",
			i * 261.f, 0.f, 261.f, 177.f);
	}

	GetSceneResource()->CreateAnimationSequence("CamelArabianAttack",
		"CamelArabianAttack", TEXT("CamelArabian/Attack/Left/CamelArabianAttack.bmp"));

	GetSceneResource()->SetTextureColorKey("CamelArabianAttack",
		255, 255, 255);

	for (int i = 0; i < 7; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("CamelArabianAttack",
			i * 190.f, 0.f, 190.f, 153.f);
	}

	GetSceneResource()->CreateAnimationSequence("CamelIdle",
		"CamelIdle", TEXT("Vehicle/Camel/Idle/Left/CamelIdle.bmp"));

	GetSceneResource()->SetTextureColorKey("CamelIdle",
		255, 255, 255);

	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("CamelIdle",
			i * 260.f, 0.f, 260.f, 140.f);
	}

	// CamelArabian 끝

	GetSceneResource()->CreateAnimationSequence("HelperEscapeLeft",
		"HelperEscapeLeft", TEXT("NPC/Escape/Left/HelperEscape.bmp"));

	GetSceneResource()->SetTextureColorKey("HelperEscapeLeft",
		255, 255, 255);

	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HelperEscapeLeft",
			i * 140.f, 0.f, 140.f, 114.f);
	}

	GetSceneResource()->CreateAnimationSequence("HelperGiveLeft",
		"HelperGiveLeft", TEXT("NPC/Give/Left/HelperGive.bmp"));

	GetSceneResource()->SetTextureColorKey("HelperGiveLeft",
		255, 255, 255);

	for (int i = 0; i < 11; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HelperGiveLeft",
			i * 105.f, 0.f, 105.f, 120.f);
	}

	GetSceneResource()->CreateAnimationSequence("HelperIdleLeft",
		"HelperIdleLeft", TEXT("NPC/Idle/Left/HelperIdle.bmp"));

	GetSceneResource()->SetTextureColorKey("HelperIdleLeft",
		255, 255, 255);

	for (int i = 0; i < 5; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HelperIdleLeft",
			i * 126.f, 0.f, 126.f, 93.f);
	}

	GetSceneResource()->CreateAnimationSequence("HelperRunLeft",
		"HelperRunLeft", TEXT("NPC/Run/Left/HelperRun.bmp"));

	GetSceneResource()->SetTextureColorKey("HelperRunLeft",
		255, 255, 255);

	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HelperRunLeft",
			i * 135.f, 0.f, 135.f, 138.f);
	}

	GetSceneResource()->CreateAnimationSequence("HelperSaluteLeft",
		"HelperSaluteLeft", TEXT("NPC/Salute/Left/HelperSalute.bmp"));

	GetSceneResource()->SetTextureColorKey("HelperSaluteLeft",
		255, 255, 255);

	for (int i = 0; i < 14; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HelperSaluteLeft",
			i * 90.f, 0.f, 90.f, 120.f);
	}

	GetSceneResource()->CreateAnimationSequence("HelperWalkLeft",
		"HelperWalkLeft", TEXT("NPC/Walk/Left/HelperWalk.bmp"));

	GetSceneResource()->SetTextureColorKey("HelperWalkLeft",
		255, 255, 255);

	for (int i = 0; i < 12; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HelperWalkLeft",
			i * 90.f, 0.f, 90.f, 125.f);
	}

	GetSceneResource()->CreateAnimationSequence("HelperWalkRight",
		"HelperWalkRight", TEXT("NPC/Walk/Right/HelperWalk.bmp"));

	GetSceneResource()->SetTextureColorKey("HelperWalkRight",
		255, 255, 255);

	for (int i = 0; i < 12; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HelperWalkRight",
			i * 90.f, 0.f, 90.f, 125.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank35",
		"Blank35", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank35",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank35",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank36",
		"Blank36", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank36",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank36",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank37",
		"Blank37", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank37",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank37",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank38",
		"Blank38", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank38",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank38",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank39",
		"Blank39", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank39",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank39",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank40",
		"Blank40", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank40",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank40",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank41",
		"Blank41", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank41",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank41",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("ItemGetEffect",
		"ItemGetEffect", TEXT("Effect/ItemGetEffect.bmp"));

	GetSceneResource()->SetTextureColorKey("ItemGetEffect",
		0, 248, 0);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("ItemGetEffect",
			i * 70.f, 0.f, 70.f, 81.f);
	}


	GetSceneResource()->CreateAnimationSequence("Blank42",
		"Blank42", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank42",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank42",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	// Heavy MachineGun 관련 애니메이션
	GetSceneResource()->CreateAnimationSequence("HeavyIdleLeftTop",
		"HeavyIdleLeftTop", TEXT("Player/Idle/Left/HeavyIdleTop.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyIdleLeftTop",
		255, 255, 255);

	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyIdleLeftTop",
			i * 120.f, 0.f, 120.f, 86.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerIdleLeftBottom5",
		"PlayerIdleLeftBottom5", TEXT("Player/Idle/Left/Marco_IdleBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerIdleLeftBottom5",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerIdleLeftBottom5",
			i * 75.f, 0.f, 75.f, 57.f);
	}

	GetSceneResource()->CreateAnimationSequence("HeavyIdleRightTop",
		"HeavyIdleRightTop", TEXT("Player/Idle/Right/HeavyIdleTop.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyIdleRightTop",
		255, 255, 255);

	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyIdleRightTop",
			i * 120.f, 0.f, 120.f, 86.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerIdleRightBottom5",
		"PlayerIdleRightBottom5", TEXT("Player/Idle/Right/Marco_IdleBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerIdleRightBottom5",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerIdleRightBottom5",
			i * 75.f, 0.f, 75.f, 57.f);
	}

	GetSceneResource()->CreateAnimationSequence("HeavyFireLeftTop",
		"HeavyFireLeftTop", TEXT("Player/Attack/Left/HeavyFireTop.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyFireLeftTop",
		255, 255, 255);

	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyFireLeftTop",
			i * 190.f, 0.f, 190.f, 84.f);
	}
	//

	GetSceneResource()->CreateAnimationSequence("HeavyBombLeftTop",
		"HeavyBombLeftTop", TEXT("Player/Bomb/Left/HeavyBombTop.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyBombLeftTop",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyBombLeftTop",
			i * 125.f, 0.f, 125.f, 89.f);
	}

	GetSceneResource()->CreateAnimationSequence("HeavyBombRightTop",
		"HeavyBombRightTop", TEXT("Player/Bomb/Right/HeavyBombTop.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyBombRightTop",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyBombRightTop",
			i * 125.f, 0.f, 125.f, 89.f);
	}


	GetSceneResource()->CreateAnimationSequence("PlayerIdleLeftBottom12",
		"PlayerIdleLeftBottom12", TEXT("Player/Idle/Left/Marco_IdleBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerIdleLeftBottom12",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerIdleLeftBottom12",
			i * 75.f, 0.f, 75.f, 57.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerIdleRightBottom12",
		"PlayerIdleRightBottom12", TEXT("Player/Idle/Right/Marco_IdleBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerIdleRightBottom12",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerIdleRightBottom12",
			i * 75.f, 0.f, 75.f, 57.f);
	}

	//
	GetSceneResource()->CreateAnimationSequence("HeavyRunLeftTop",
		"HeavyRunLeftTop", TEXT("Player/Run/Left/HeavyRunTop.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyRunLeftTop",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyRunLeftTop",
			i * 133.f, 0.f, 133.f, 87.f);
	}

	GetSceneResource()->CreateAnimationSequence("HeavyRunRightTop",
		"HeavyRunRightTop", TEXT("Player/Run/Right/HeavyRunTop.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyRunRightTop",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyRunRightTop",
			i * 133.f, 0.f, 133.f, 87.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerRunLeftBottom1",
		"PlayerRunLeftBottom1", TEXT("Player/Run/Left/Marco_RunBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerRunLeftBottom1",
		255, 255, 255);

	for (int i = 0; i < 18; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerRunLeftBottom1",
			i * 75.f, 0.f, 75.f, 56.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerRunRightBottom1",
		"PlayerRunRightBottom1", TEXT("Player/Run/Right/Marco_RunBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerRunRightBottom1",
		255, 255, 255);

	for (int i = 0; i < 18; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerRunRightBottom1",
			i * 75.f, 0.f, 75.f, 56.f);
	}

	//


	GetSceneResource()->CreateAnimationSequence("PlayerIdleLeftBottom6",
		"PlayerIdleLeftBottom6", TEXT("Player/Idle/Left/Marco_IdleBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerIdleLeftBottom6",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerIdleLeftBottom6",
			i * 75.f, 0.f, 75.f, 57.f);
	}

	GetSceneResource()->CreateAnimationSequence("HeavyFireRightTop",
		"HeavyFireRightTop", TEXT("Player/Attack/Right/HeavyFireTop.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyFireRightTop",
		255, 255, 255);

	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyFireRightTop",
			i * 190.f, 0.f, 190.f, 84.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerIdleRightBottom6",
		"PlayerIdleRightBottom6", TEXT("Player/Idle/Right/Marco_IdleBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerIdleRightBottom6",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerIdleRightBottom6",
			i * 75.f, 0.f, 75.f, 57.f);
	}

	GetSceneResource()->CreateAnimationSequence("HeavyLookUpLeftTop",
		"HeavyLookUpLeftTop", TEXT("Player/LookUp/Left/HeavyLookUpTop.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyLookUpLeftTop",
		255, 255, 255);

	for (int i = 0; i < 7; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyLookUpLeftTop",
			i * 105.f, 0.f, 105.f, 121.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerIdleLeftBottom7",
		"PlayerIdleLeftBottom7", TEXT("Player/Idle/Left/Marco_IdleBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerIdleLeftBottom7",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerIdleLeftBottom7",
			i * 75.f, 0.f, 75.f, 57.f);
	}

	GetSceneResource()->CreateAnimationSequence("HeavyLookUpRightTop",
		"HeavyLookUpRightTop", TEXT("Player/LookUp/Right/HeavyLookUpTop.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyLookUpRightTop",
		255, 255, 255);

	for (int i = 0; i < 7; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyLookUpRightTop",
			i * 105.f, 0.f, 105.f, 121.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerIdleRightBottom7",
		"PlayerIdleRightBottom7", TEXT("Player/Idle/Right/Marco_IdleBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerIdleRightBottom7",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerIdleRightBottom7",
			i * 75.f, 0.f, 75.f, 57.f);
	}
	//
	GetSceneResource()->CreateAnimationSequence("HeavyLookUpFireLeftTop",
		"HeavyLookUpFireLeftTop", TEXT("Player/LookUp/Left/HeavyLookUpFire.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyLookUpFireLeftTop",
		255, 255, 255);

	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyLookUpFireLeftTop",
			i * 75.f, 0.f, 75.f, 216.f);
	}

	GetSceneResource()->CreateAnimationSequence("HeavyLookUpFireRightTop",
		"HeavyLookUpFireRightTop", TEXT("Player/LookUp/Right/HeavyLookUpFire.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyLookUpFireRightTop",
		255, 255, 255);

	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyLookUpFireRightTop",
			i * 75.f, 0.f, 75.f, 216.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerIdleLeftBottom13",
		"PlayerIdleLeftBottom13", TEXT("Player/Idle/Left/Marco_IdleBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerIdleLeftBottom13",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerIdleLeftBottom13",
			i * 75.f, 0.f, 75.f, 57.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerIdleRightBottom13",
		"PlayerIdleRightBottom13", TEXT("Player/Idle/Right/Marco_IdleBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerIdleRightBottom13",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerIdleRightBottom13",
			i * 75.f, 0.f, 75.f, 57.f);
	}

	// here
	GetSceneResource()->CreateAnimationSequence("HeavyJumpAttackDownLeftTop",
		"HeavyJumpAttackDownLeftTop", TEXT("Player/Jump/Left/HeavyJumpAttackDownTop.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyJumpAttackDownLeftTop",
		255, 255, 255);

	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyJumpAttackDownLeftTop",
			i * 110.f, 0.f, 110.f, 194.f);
	}

	GetSceneResource()->CreateAnimationSequence("HeavyJumpAttackDownRightTop",
		"HeavyJumpAttackDownRightTop", TEXT("Player/Jump/Right/HeavyJumpAttackDownTop.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyJumpAttackDownRightTop",
		255, 255, 255);

	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyJumpAttackDownRightTop",
			i * 110.f, 0.f, 110.f, 194.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerVerticalJumpLeftBottom8",
		"PlayerVerticalJumpLeftBottom8", TEXT("Player/Jump/Left/Marco_VerticalJumpBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerVerticalJumpLeftBottom8",
		255, 255, 255);

	for (int i = 0; i < 11; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerVerticalJumpLeftBottom8",
			i * 90.f, 0.f, 90.f, 60.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerVerticalJumpRightBottom8",
		"PlayerVerticalJumpRightBottom8", TEXT("Player/Jump/Right/Marco_VerticalJumpBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerVerticalJumpRightBottom8",
		255, 255, 255);

	for (int i = 0; i < 11; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerVerticalJumpRightBottom8",
			i * 90.f, 0.f, 90.f, 60.f);
	}


	//
	GetSceneResource()->CreateAnimationSequence("HeavyUpperLiftUpLeftTop",
		"HeavyUpperLiftUpLeftTop", TEXT("Player/UpperLiftUp/Left/HeavyLiftUpTop.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyUpperLiftUpLeftTop",
		255, 255, 255);

	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyUpperLiftUpLeftTop",
			i * 120.f, 0.f, 120.f, 109.f);
	}

	GetSceneResource()->CreateAnimationSequence("HeavyUpperLiftUpRightTop",
		"HeavyUpperLiftUpRightTop", TEXT("Player/UpperLiftUp/Right/HeavyLiftUpTop.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyUpperLiftUpRightTop",
		255, 255, 255);

	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyUpperLiftUpRightTop",
			i * 120.f, 0.f, 120.f, 109.f);
	}

	/// LiftUpFireLeft

	GetSceneResource()->CreateAnimationSequence("HeavyUpperLiftUpFireLeftTop",
		"HeavyUpperLiftUpFireLeftTop", TEXT("Player/UpperLiftUp/Left/HeavyLiftUpFireTop.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyUpperLiftUpFireLeftTop",
		255, 255, 255);

	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyUpperLiftUpFireLeftTop",
			i * 180.f, 0.f, 180.f, 183.f);
	}

	GetSceneResource()->CreateAnimationSequence("HeavyUpperLiftUpFireRightTop",
		"HeavyUpperLiftUpFireRightTop", TEXT("Player/UpperLiftUp/Right/HeavyLiftUpFireTop.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyUpperLiftUpFireRightTop",
		255, 255, 255);

	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyUpperLiftUpFireRightTop",
			i * 180.f, 0.f, 180.f, 183.f);
	}
	// 끝



	GetSceneResource()->CreateAnimationSequence("HeavyUpperLiftDownLeftTop",
		"HeavyUpperLiftDownLeftTop", TEXT("Player/UpperLiftDown/Left/HeavyUpperLiftDownTop.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyUpperLiftDownLeftTop",
		255, 255, 255);

	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyUpperLiftDownLeftTop",
			i * 120.f, 0.f, 120.f, 109.f);
	}

	GetSceneResource()->CreateAnimationSequence("HeavyUpperLiftDownRightTop",
		"HeavyUpperLiftDownRightTop", TEXT("Player/UpperLiftDown/Right/HeavyUpperLiftDownTop.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyUpperLiftDownRightTop",
		255, 255, 255);

	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyUpperLiftDownRightTop",
			i * 120.f, 0.f, 120.f, 109.f);
	}

	GetSceneResource()->CreateAnimationSequence("HeavyUpperLiftDownFireLeftTop",
		"HeavyUpperLiftDownFireLeftTop", TEXT("Player/UpperLiftDown/Left/HeavyUpperLiftDownFireTop.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyUpperLiftDownFireLeftTop",
		255, 255, 255);

	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyUpperLiftDownFireLeftTop",
			i * 150.f, 0.f, 150.f, 186.f);
	}

	GetSceneResource()->CreateAnimationSequence("HeavyUpperLiftDownFireRightTop",
		"HeavyUpperLiftDownFireRightTop", TEXT("Player/UpperLiftDown/Right/HeavyUpperLiftDownFireTop.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyUpperLiftDownFireRightTop",
		255, 255, 255);

	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyUpperLiftDownFireRightTop",
			i * 150.f, 0.f, 150.f, 186.f);
	}

	//////



	GetSceneResource()->CreateAnimationSequence("PlayerIdleLeftBottom8",
		"PlayerIdleLeftBottom8", TEXT("Player/Idle/Left/Marco_IdleBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerIdleLeftBottom8",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerIdleLeftBottom8",
			i * 75.f, 0.f, 75.f, 57.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerIdleRightBottom8",
		"PlayerIdleRightBottom8", TEXT("Player/Idle/Right/Marco_IdleBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerIdleRightBottom8",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerIdleRightBottom8",
			i * 75.f, 0.f, 75.f, 57.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerIdleLeftBottom9",
		"PlayerIdleLeftBottom9", TEXT("Player/Idle/Left/Marco_IdleBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerIdleLeftBottom9",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerIdleLeftBottom9",
			i * 75.f, 0.f, 75.f, 57.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerIdleRightBottom9",
		"PlayerIdleRightBottom9", TEXT("Player/Idle/Right/Marco_IdleBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerIdleRightBottom9",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerIdleRightBottom9",
			i * 75.f, 0.f, 75.f, 57.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerIdleLeftBottom10",
		"PlayerIdleLeftBottom10", TEXT("Player/Idle/Left/Marco_IdleBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerIdleLeftBottom10",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerIdleLeftBottom10",
			i * 75.f, 0.f, 75.f, 57.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerIdleRightBottom10",
		"PlayerIdleRightBottom10", TEXT("Player/Idle/Right/Marco_IdleBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerIdleRightBottom10",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerIdleRightBottom10",
			i * 75.f, 0.f, 75.f, 57.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerIdleLeftBottom11",
		"PlayerIdleLeftBottom11", TEXT("Player/Idle/Left/Marco_IdleBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerIdleLeftBottom11",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerIdleLeftBottom11",
			i * 75.f, 0.f, 75.f, 57.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerIdleRightBottom11",
		"PlayerIdleRightBottom11", TEXT("Player/Idle/Right/Marco_IdleBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerIdleRightBottom11",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerIdleRightBottom11",
			i * 75.f, 0.f, 75.f, 57.f);
	}
	// Upper 끝


	// Lower 시작

	GetSceneResource()->CreateAnimationSequence("HeavyLowerLiftUpLeftTop",
		"HeavyLowerLiftUpLeftTop", TEXT("Player/LowerLiftUp/Left/HeavyLowerLiftUpTop.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyLowerLiftUpLeftTop",
		255, 255, 255);

	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyLowerLiftUpLeftTop",
			i * 95.f, 0.f, 95.f, 129.f);
	}

	GetSceneResource()->CreateAnimationSequence("HeavyLowerLiftUpRightTop",
		"HeavyLowerLiftUpRightTop", TEXT("Player/LowerLiftUp/Right/HeavyLowerLiftUpTop.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyLowerLiftUpRightTop",
		255, 255, 255);

	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyLowerLiftUpRightTop",
			i * 95.f, 0.f, 95.f, 129.f);
	}
	// LowerLiftUpFire 시작

	GetSceneResource()->CreateAnimationSequence("HeavyLowerLiftUpFireLeftTop",
		"HeavyLowerLiftUpFireLeftTop", TEXT("Player/LowerLiftUp/Left/HeavyLowerLiftUpFireTop.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyLowerLiftUpFireLeftTop",
		255, 255, 255);

	for (int i = 0; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyLowerLiftUpFireLeftTop",
			i * 140.f, 0.f, 140.f, 172.f);
	}

	GetSceneResource()->CreateAnimationSequence("HeavyLowerLiftUpFireRightTop",
		"HeavyLowerLiftUpFireRightTop", TEXT("Player/LowerLiftUp/Right/HeavyLowerLiftUpFireTop.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyLowerLiftUpFireRightTop",
		255, 255, 255);

	for (int i = 0; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyLowerLiftUpFireRightTop",
			i * 140.f, 0.f, 140.f, 172.f);
	}
	// 끝
	GetSceneResource()->CreateAnimationSequence("HeavyLowerLiftDownLeftTop",
		"HeavyLowerLiftDownLeftTop", TEXT("Player/LowerLiftDown/Left/HeavyLowerLiftDownTop.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyLowerLiftDownLeftTop",
		255, 255, 255);

	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyLowerLiftDownLeftTop",
			i * 95.f, 0.f, 95.f, 129.f);
	}

	GetSceneResource()->CreateAnimationSequence("HeavyLowerLiftDownRightTop",
		"HeavyLowerLiftDownRightTop", TEXT("Player/LowerLiftDown/Right/HeavyLowerLiftDownTop.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyLowerLiftDownRightTop",
		255, 255, 255);

	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyLowerLiftDownRightTop",
			i * 95.f, 0.f, 95.f, 129.f);
	}

	GetSceneResource()->CreateAnimationSequence("HeavyLowerLiftDownFireLeftTop",
		"HeavyLowerLiftDownFireLeftTop", TEXT("Player/LowerLiftDown/Left/HeavyLowerLiftDownFireTop.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyLowerLiftDownFireLeftTop",
		255, 255, 255);

	for (int i = 0; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyLowerLiftDownFireLeftTop",
			i * 140.f, 0.f, 140.f, 172.f);
	}

	GetSceneResource()->CreateAnimationSequence("HeavyLowerLiftDownFireRightTop",
		"HeavyLowerLiftDownFireRightTop", TEXT("Player/LowerLiftDown/Right/HeavyLowerLiftDownFireTop.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyLowerLiftDownFireRightTop",
		255, 255, 255);

	for (int i = 0; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyLowerLiftDownFireRightTop",
			i * 140.f, 0.f, 140.f, 172.f);
	}

	/// 여기부터 VerticalBottom으로
	GetSceneResource()->CreateAnimationSequence("PlayerVerticalJumpLeftBottom4",
		"PlayerVerticalJumpLeftBottom4", TEXT("Player/Jump/Left/Marco_VerticalJumpBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerVerticalJumpLeftBottom4",
		255, 255, 255);

	for (int i = 0; i < 11; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerVerticalJumpLeftBottom4",
			i * 90.f, 0.f, 90.f, 60.f);
	}


	GetSceneResource()->CreateAnimationSequence("PlayerVerticalJumpRightBottom4",
		"PlayerVerticalJumpRightBottom4", TEXT("Player/Jump/Right/Marco_VerticalJumpBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerVerticalJumpRightBottom4",
		255, 255, 255);

	for (int i = 0; i < 11; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerVerticalJumpRightBottom4",
			i * 90.f, 0.f, 90.f, 60.f);
	}


	GetSceneResource()->CreateAnimationSequence("PlayerVerticalJumpLeftBottom5",
		"PlayerVerticalJumpLeftBottom5", TEXT("Player/Jump/Left/Marco_VerticalJumpBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerVerticalJumpLeftBottom5",
		255, 255, 255);

	for (int i = 0; i < 11; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerVerticalJumpLeftBottom5",
			i * 90.f, 0.f, 90.f, 60.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerVerticalJumpRightBottom5",
		"PlayerVerticalJumpRightBottom5", TEXT("Player/Jump/Right/Marco_VerticalJumpBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerVerticalJumpRightBottom5",
		255, 255, 255);

	for (int i = 0; i < 11; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerVerticalJumpRightBottom5",
			i * 90.f, 0.f, 90.f, 60.f);
	}


	GetSceneResource()->CreateAnimationSequence("PlayerVerticalJumpLeftBottom6",
		"PlayerVerticalJumpLeftBottom6", TEXT("Player/Jump/Left/Marco_VerticalJumpBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerVerticalJumpLeftBottom6",
		255, 255, 255);

	for (int i = 0; i < 11; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerVerticalJumpLeftBottom6",
			i * 90.f, 0.f, 90.f, 60.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerVerticalJumpRightBottom6",
		"PlayerVerticalJumpRightBottom6", TEXT("Player/Jump/Right/Marco_VerticalJumpBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerVerticalJumpRightBottom6",
		255, 255, 255);

	for (int i = 0; i < 11; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerVerticalJumpRightBottom6",
			i * 90.f, 0.f, 90.f, 60.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerVerticalJumpLeftBottom7",
		"PlayerVerticalJumpLeftBottom7", TEXT("Player/Jump/Left/Marco_VerticalJumpBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerVerticalJumpLeftBottom7",
		255, 255, 255);

	for (int i = 0; i < 11; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerVerticalJumpLeftBottom7",
			i * 90.f, 0.f, 90.f, 60.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerVerticalJumpRightBottom7",
		"PlayerVerticalJumpRightBottom7", TEXT("Player/Jump/Right/Marco_VerticalJumpBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerVerticalJumpRightBottom7",
		255, 255, 255);

	for (int i = 0; i < 11; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerVerticalJumpRightBottom7",
			i * 90.f, 0.f, 90.f, 60.f);
	}

	GetSceneResource()->CreateAnimationSequence("HeavySitDownIdleLeft",
		"HeavySitDownIdleLeft", TEXT("Player/SitDown/Left/HeavySitDownIdle.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavySitDownIdleLeft",
		255, 255, 255);

	for (int i = 0; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavySitDownIdleLeft",
			i * 133.f, 0.f, 133.f, 75.f);
	}

	GetSceneResource()->CreateAnimationSequence("HeavySitDownIdleRight",
		"HeavySitDownIdleRight", TEXT("Player/SitDown/Right/HeavySitDownIdle.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavySitDownIdleRight",
		255, 255, 255);

	for (int i = 0; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavySitDownIdleRight",
			i * 133.f, 0.f, 133.f, 75.f);
	}
	
	//
	
	GetSceneResource()->CreateAnimationSequence("HeavySitDownFireLeft",
		"HeavySitDownFireLeft", TEXT("Player/SitDown/Left/HeavySitDownFire.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavySitDownFireLeft",
		255, 255, 255);

	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavySitDownFireLeft",
			i * 210.f, 0.f, 210.f, 81.f);
	}

	GetSceneResource()->CreateAnimationSequence("HeavySitDownFireRight",
		"HeavySitDownFireRight", TEXT("Player/SitDown/Right/HeavySitDownFire.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavySitDownFireRight",
		255, 255, 255);

	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavySitDownFireRight",
			i * 210.f, 0.f, 210.f, 81.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank51",
		"Blank51", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank51",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank51",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank52",
		"Blank52", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank52",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank52",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	//

	GetSceneResource()->CreateAnimationSequence("Blank43",
		"Blank43", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank43",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank43",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank44",
		"Blank44", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank44",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank44",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("HeavySitDownBombLeft",
		"HeavySitDownBombLeft", TEXT("Player/SitDown/Left/HeavySitDownBomb.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavySitDownBombLeft",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavySitDownBombLeft",
			i * 125.f, 0.f, 125.f, 113.f);
	}

	GetSceneResource()->CreateAnimationSequence("HeavySitDownBombRight",
		"HeavySitDownBombRight", TEXT("Player/SitDown/Right/HeavySitDownBomb.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavySitDownBombRight",
		255, 255, 255);

	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavySitDownBombRight",
			i * 125.f, 0.f, 125.f, 113.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank45",
		"Blank45", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank45",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank45",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank46",
		"Blank46", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank46",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank46",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("HeavyCrawlLeft",
		"HeavyCrawlLeft", TEXT("Player/SitDown/Left/HeavyCrawl.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyCrawlLeft",
		255, 255, 255);

	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyCrawlLeft",
			i * 135.f, 0.f, 135.f, 74.f);
	}

	GetSceneResource()->CreateAnimationSequence("HeavyCrawlRight",
		"HeavyCrawlRight", TEXT("Player/SitDown/Right/HeavyCrawl.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyCrawlRight",
		255, 255, 255);

	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyCrawlRight",
			i * 135.f, 0.f, 135.f, 74.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank47",
		"Blank47", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank47",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank47",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank48",
		"Blank48", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank48",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank48",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("HeavySitDownIdleAfterBombLeft",
		"HeavySitDownIdleAfterBombLeft", TEXT("Player/SitDown/Left/HeavySitDownIdleAfterBomb.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavySitDownIdleAfterBombLeft",
		255, 255, 255);

	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavySitDownIdleAfterBombLeft",
			i * 112.f, 0.f, 112.f, 113.f);
	}

	GetSceneResource()->CreateAnimationSequence("HeavySitDownIdleAfterBombRight",
		"HeavySitDownIdleAfterBombRight", TEXT("Player/SitDown/Right/HeavySitDownIdleAfterBomb.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavySitDownIdleAfterBombRight",
		255, 255, 255);

	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavySitDownIdleAfterBombRight",
			i * 112.f, 0.f, 112.f, 113.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank49",
		"Blank49", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank49",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank49",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("Blank50",
		"Blank50", TEXT("Player/SitDown/Right/Blank.bmp"));

	GetSceneResource()->SetTextureColorKey("Blank50",
		255, 255, 255);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("Blank50",
			i * 100.f, 0.f, 100.f, 68.f);
	}

	GetSceneResource()->CreateAnimationSequence("HeavyJumpDownLeftTop",
		"HeavyJumpDownLeftTop", TEXT("Player/Jump/Left/HeavyJumpDownTop.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyJumpDownLeftTop",
		255, 255, 255);

	for (int i = 0; i < 1; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyJumpDownLeftTop",
			i * 105.f, 0.f, 105.f, 127.f);
	}

	GetSceneResource()->CreateAnimationSequence("HeavyJumpDownRightTop",
		"HeavyJumpDownRightTop", TEXT("Player/Jump/Right/HeavyJumpDownTop.bmp"));

	GetSceneResource()->SetTextureColorKey("HeavyJumpDownRightTop",
		255, 255, 255);

	for (int i = 0; i < 1; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("HeavyJumpDownRightTop",
			i * 105.f, 0.f, 105.f, 127.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerVerticalJumpLeftBottom9",
		"PlayerVerticalJumpLeftBottom9", TEXT("Player/Jump/Left/Marco_VerticalJumpBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerVerticalJumpLeftBottom9",
		255, 255, 255);

	for (int i = 0; i < 11; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerVerticalJumpLeftBottom9",
			i * 90.f, 0.f, 90.f, 60.f);
	}

	GetSceneResource()->CreateAnimationSequence("PlayerVerticalJumpRightBottom9",
		"PlayerVerticalJumpRightBottom9", TEXT("Player/Jump/Right/Marco_VerticalJumpBottom.bmp"));

	GetSceneResource()->SetTextureColorKey("PlayerVerticalJumpRightBottom9",
		255, 255, 255);

	for (int i = 0; i < 11; ++i)
	{
		GetSceneResource()->AddAnimationFrameData("PlayerVerticalJumpRightBottom9",
			i * 90.f, 0.f, 90.f, 60.f);
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

	FileName += ".fdat";

	fopen_s(&FileStream, FileName.c_str(), "wb");

	if (FileStream)
	{
		FileName.clear();
		FileName = Top->m_vecAnimation[m_CurrentTopAnimIndex];
		FileName += "\n";
		fputs(FileName.c_str(), FileStream);

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
	FileName += ".fdat";

	fopen_s(&FileStream, FileName.c_str(), "wb");

	if (FileStream)
	{
		FileName.clear();
		FileName = Bottom->m_vecAnimation[m_CurrentTopAnimIndex];
		FileName += "\n";
		fputs(FileName.c_str(), FileStream);

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

	FileName += ".fdat";

	fopen_s(&FileStream, FileName.c_str(), "rb");

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

	CGameObject* Bottom = FindObject("PlayerBottom");

	FileName = Bottom->m_vecAnimation[m_CurrentBottomAnimIndex];

	if (FileName.find("VerticalJumpLeftBottom") != std::string::npos)
	{
		FileName = "PlayerVerticalJumpLeftBottom1";
	}

	else if (FileName.find("VerticalJumpRightBottom") != std::string::npos)
	{
		FileName = "PlayerVerticalJumpRightBottom1";
	}

	else if (FileName.find("PlayerRunRightBottom1") != std::string::npos)
	{
		FileName = "PlayerRunRightBottom";
	}

	else if (FileName.find("PlayerRunLeftBottom1") != std::string::npos)
	{
		FileName = "PlayerRunLeftBottom";
	}

	else if (FileName.find("CamelRun1") != std::string::npos)
	{
		FileName = "CamelRun";
	}


	FileName += ".fdat";

	fopen_s(&FileStream, FileName.c_str(), "rb");

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
		m_CurrentTopAnimIndex = 0;
		m_CurrentBottomAnimIndex = 0;
	}

	else
	{
		++m_CurrentTopAnimIndex;
		++m_CurrentBottomAnimIndex;
	}

	std::string NextAnim = PlayerTop->m_vecAnimation[m_CurrentTopAnimIndex];

	PlayerTop->m_Animation->ChangeAnimation(NextAnim);

	NextAnim = PlayerBottom->m_vecAnimation[m_CurrentBottomAnimIndex];

	PlayerBottom->m_Animation->ChangeAnimation(NextAnim);
}

void CMainScene::PrevAnimation(float DeltaTime)
{
	CGameObject* PlayerTop = FindObject("PlayerTop");
	CGameObject* PlayerBottom = FindObject("PlayerBottom");

	if (m_CurrentTopAnimIndex == 0 || m_CurrentBottomAnimIndex == 0)
	{
		m_CurrentTopAnimIndex = (int)(PlayerTop->m_vecAnimation.size() - 1);
		m_CurrentBottomAnimIndex = (int)(PlayerBottom->m_vecAnimation.size() - 1);
	}
	
	else
	{
		--m_CurrentTopAnimIndex;
		--m_CurrentBottomAnimIndex;
	}


	std::string NextAnim = PlayerTop->m_vecAnimation[m_CurrentTopAnimIndex];

	PlayerTop->m_Animation->ChangeAnimation(NextAnim);


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

void CMainScene::MergePlayerFrameDataFile(float DeltaTime)
{
	FILE* FileStream;

	std::vector<std::string> vecTopFrame;
	std::vector<std::string> vecBottomFrame;

	CGameObject* Top = FindObject("PlayerTop");
	CGameObject* Bottom = FindObject("PlayerBottom");

	vecTopFrame.push_back("PlayerIdleRightTop");
	vecTopFrame.push_back("PlayerIdleLeftTop");
	vecTopFrame.push_back("PlayerNormalFireRightTop");
	vecTopFrame.push_back("PlayerNormalFireLeftTop");
	vecTopFrame.push_back("PlayerRunRightTop");
	vecTopFrame.push_back("PlayerRunLeftTop");
	vecTopFrame.push_back("PlayerVerticalJumpRightTop");
	vecTopFrame.push_back("PlayerVerticalJumpLeftTop");
	vecTopFrame.push_back("PlayerJumpDownRightTop");
	vecTopFrame.push_back("PlayerJumpDownLeftTop");
	vecTopFrame.push_back("PlayerJumpAttackDownRightTop");
	vecTopFrame.push_back("PlayerJumpAttackDownLeftTop");
	vecTopFrame.push_back("PlayerLookUpRightTop");
	vecTopFrame.push_back("PlayerLookUpLeftTop");
	vecTopFrame.push_back("PlayerLookUpAttackRightTop");
	vecTopFrame.push_back("PlayerLookUpAttackLeftTop");
	vecTopFrame.push_back("PlayerFrontJumpRightTop");
	vecTopFrame.push_back("PlayerFrontJumpLeftTop");
	vecTopFrame.push_back("PlayerBombRightTop");
	vecTopFrame.push_back("PlayerBombLeftTop");
	vecTopFrame.push_back("Blank1");
	vecTopFrame.push_back("Blank2");

	vecTopFrame.push_back("HeavyIdleLeftTop");
	vecTopFrame.push_back("HeavyIdleRightTop");
	vecTopFrame.push_back("HeavyRunLeftTop");
	vecTopFrame.push_back("HeavyRunRightTop");
	vecTopFrame.push_back("HeavyFireLeftTop");
	vecTopFrame.push_back("HeavyFireRightTop");
	vecTopFrame.push_back("HeavyBombLeftTop");
	vecTopFrame.push_back("HeavyBombRightTop");
	vecTopFrame.push_back("HeavyLookUpLeftTop");
	vecTopFrame.push_back("HeavyLookUpRightTop");
	vecTopFrame.push_back("HeavyJumpAttackDownLeftTop");
	vecTopFrame.push_back("HeavyJumpAttackDownRightTop");


	vecTopFrame.push_back("HeavyUpperLiftUpLeftTop");
	vecTopFrame.push_back("HeavyUpperLiftUpRightTop");
	vecTopFrame.push_back("HeavyUpperLiftUpFireLeftTop");
	vecTopFrame.push_back("HeavyUpperLiftUpFireRightTop");
	vecTopFrame.push_back("HeavyUpperLiftDownLeftTop");
	vecTopFrame.push_back("HeavyUpperLiftDownRightTop");
	vecTopFrame.push_back("HeavyUpperLiftDownFireLeftTop");
	vecTopFrame.push_back("HeavyUpperLiftDownFireRightTop");
	vecTopFrame.push_back("HeavyLowerLiftUpLeftTop");
	vecTopFrame.push_back("HeavyLowerLiftUpRightTop");
	vecTopFrame.push_back("HeavyLowerLiftUpFireLeftTop");
	vecTopFrame.push_back("HeavyLowerLiftUpFireRightTop");
	vecTopFrame.push_back("HeavyLowerLiftDownLeftTop");
	vecTopFrame.push_back("HeavyLowerLiftDownRightTop");
	vecTopFrame.push_back("HeavyLowerLiftDownFireLeftTop");
	vecTopFrame.push_back("HeavyLowerLiftDownFireRightTop");
	vecTopFrame.push_back("HeavyLookUpFireLeftTop");
	vecTopFrame.push_back("HeavyLookUpFireRightTop");


	vecBottomFrame.push_back("PlayerIdleRightBottom1");
	vecBottomFrame.push_back("PlayerIdleLeftBottom1");
	vecBottomFrame.push_back("PlayerNormalFireRightBottom");
	vecBottomFrame.push_back("PlayerNormalFireLeftBottom");
	vecBottomFrame.push_back("PlayerRunRightBottom");
	vecBottomFrame.push_back("PlayerRunLeftBottom");
	vecBottomFrame.push_back("PlayerVerticalJumpRightBottom1");
	vecBottomFrame.push_back("PlayerVerticalJumpLeftBottom1");
	vecBottomFrame.push_back("PlayerFrontJumpRightBottom");
	vecBottomFrame.push_back("PlayerFrontJumpLeftBottom");
	vecBottomFrame.push_back("PlayerSitDownIdleRight");
	vecBottomFrame.push_back("PlayerSitDownIdleLeft");
	vecBottomFrame.push_back("PlayerCrawlRight");
	vecBottomFrame.push_back("PlayerCrawlLeft");
	vecBottomFrame.push_back("PlayerSitDownNormalAttackRight");
	vecBottomFrame.push_back("PlayerSitDownNormalAttackLeft");
	vecBottomFrame.push_back("PlayerSitDownBombRight");
	vecBottomFrame.push_back("PlayerSitDownBombLeft");
	vecBottomFrame.push_back("PlayerDeathRight");
	vecBottomFrame.push_back("PlayerDeathLeft");

	vecBottomFrame.push_back("HeavySitDownIdleLeft");
	vecBottomFrame.push_back("HeavySitDownIdleRight");
	vecBottomFrame.push_back("HeavySitDownFireLeft");
	vecBottomFrame.push_back("HeavySitDownFireRight");
	vecBottomFrame.push_back("HeavySitDownBombLeft");
	vecBottomFrame.push_back("HeavySitDownBombRight");
	vecBottomFrame.push_back("HeavyCrawlLeft");
	vecBottomFrame.push_back("HeavyCrawlRight");
	vecBottomFrame.push_back("HeavySitDownIdleAfterBombLeft");
	vecBottomFrame.push_back("HeavySitDownIdleAfterBombRight");


	const std::string FileName = "PlayerFrameData.fdat";

	fopen_s(&FileStream, FileName.c_str(), "wb");

	if (FileStream)
	{	
		// TopAnimation FrameData 작성
		int Size = (int)vecTopFrame.size();
		for (int i = 0; i < Size; ++i)
		{
			int AnimNameLength = (int)vecTopFrame[i].length();

			fwrite(&AnimNameLength, sizeof(int), 1, FileStream);
			fwrite(vecTopFrame[i].c_str(), sizeof(char), AnimNameLength, FileStream);

			int FrameCount = GetSceneResource()->FindAnimationSequence(vecTopFrame[i])->GetFrameCount();
			
			for (int j = 0; j < FrameCount; ++j)
			{
				const AnimationFrameData& Data = GetSceneResource()->FindAnimationSequence(vecTopFrame[i])->GetFrameData(j);
				fwrite(&Data, sizeof(AnimationFrameData), 1, FileStream);
			}

		}

		// BottomAnimation FrameData 작성
		Size = (int)vecBottomFrame.size();
		for (int i = 0; i < Size; ++i)
		{
			int AnimNameLength = (int)vecBottomFrame[i].length();
			fwrite(&AnimNameLength, sizeof(int), 1, FileStream);
			fwrite(vecBottomFrame[i].c_str(), sizeof(char), AnimNameLength, FileStream);

			int FrameCount = GetSceneResource()->FindAnimationSequence(vecBottomFrame[i])->GetFrameCount();

			for (int j = 0; j < FrameCount; ++j)
			{
				const AnimationFrameData& Data = GetSceneResource()->FindAnimationSequence(vecBottomFrame[i])->GetFrameData(j);
				fwrite(&Data, sizeof(AnimationFrameData), 1, FileStream);
			}

		}
	}

	fclose(FileStream);
}

void CMainScene::MergeArabianFrameDataFile(float DeltaTime)
{
	FILE* FileStream;

	std::vector<std::string> vecFrame;


	CGameObject* Bottom = FindObject("PlayerBottom");

	vecFrame.push_back("ArabianShuffleRight");
	vecFrame.push_back("ArabianShuffleLeft");
	vecFrame.push_back("ArabianRunRight");
	vecFrame.push_back("ArabianRunLeft");
	vecFrame.push_back("ArabianPrepareRight");
	vecFrame.push_back("ArabianPrepareLeft");
	vecFrame.push_back("ArabianAttackRight");
	vecFrame.push_back("ArabianAttackLeft");
	vecFrame.push_back("ArabianThrowRight");
	vecFrame.push_back("ArabianThrowLeft");
	vecFrame.push_back("ArabianDeathAnimationRight1");
	vecFrame.push_back("ArabianDeathAnimationLeft1");
	vecFrame.push_back("ArabianDeathAnimationRight2");
	vecFrame.push_back("ArabianDeathAnimationLeft2");
	vecFrame.push_back("ArabianDeathAnimationRight3");
	vecFrame.push_back("ArabianDeathAnimationLeft3");
	vecFrame.push_back("ArabianJumpRight");
	vecFrame.push_back("ArabianJumpLeft");
	vecFrame.push_back("CamelArabianIdle");
	vecFrame.push_back("CamelRun");
	vecFrame.push_back("CamelArabianEntrance");
	vecFrame.push_back("CamelArabianDown");
	vecFrame.push_back("CamelDown");
	vecFrame.push_back("CamelArabianAttack");
	vecFrame.push_back("CamelIdle");

	const std::string FileName = "ArabianFrameData.fdat";

	fopen_s(&FileStream, FileName.c_str(), "wb");

	if (FileStream)
	{
		// TopAnimation FrameData 작성
		int Size = (int)vecFrame.size();
		for (int i = 0; i < Size; ++i)
		{
			int AnimNameLength = (int)vecFrame[i].length();
			fwrite(&AnimNameLength, sizeof(int), 1, FileStream);
			fwrite(vecFrame[i].c_str(), sizeof(char), AnimNameLength, FileStream);

			int FrameCount = GetSceneResource()->FindAnimationSequence(vecFrame[i])->GetFrameCount();

			for (int j = 0; j < FrameCount; ++j)
			{
				const AnimationFrameData& Data = GetSceneResource()->FindAnimationSequence(vecFrame[i])->GetFrameData(j);
				fwrite(&Data, sizeof(AnimationFrameData), 1, FileStream);
			}

		}
	}

	fclose(FileStream);
}

void CMainScene::MergeNPCFrameDataFile(float DeltaTime)
{
	FILE* FileStream;

	std::vector<std::string> vecFrame;

	CGameObject* Bottom = FindObject("PlayerBottom");

	vecFrame.push_back("HelperEscapeLeft");
	vecFrame.push_back("HelperGiveLeft");
	vecFrame.push_back("HelperIdleLeft");
	vecFrame.push_back("HelperRunLeft");
	vecFrame.push_back("HelperSaluteLeft");
	vecFrame.push_back("HelperWalkLeft");
	vecFrame.push_back("HelperWalkRight");

	const std::string FileName = "NPCFrameData.fdat";

	fopen_s(&FileStream, FileName.c_str(), "wb");

	if (FileStream)
	{
		int Size = (int)vecFrame.size();
		for (int i = 0; i < Size; ++i)
		{
			int AnimNameLength = (int)vecFrame[i].length();
			fwrite(&AnimNameLength, sizeof(int), 1, FileStream);
			fwrite(vecFrame[i].c_str(), sizeof(char), AnimNameLength, FileStream);

			int FrameCount = GetSceneResource()->FindAnimationSequence(vecFrame[i])->GetFrameCount();

			for (int j = 0; j < FrameCount; ++j)
			{
				const AnimationFrameData& Data = GetSceneResource()->FindAnimationSequence(vecFrame[i])->GetFrameData(j);
				fwrite(&Data, sizeof(AnimationFrameData), 1, FileStream);
			}

		}
	}

	fclose(FileStream);

	vecFrame.clear();
	vecFrame.push_back("BombExplosionEffect");
	vecFrame.push_back("ItemGetEffect");


	const std::string FileName2 = "EffectsFrameData.fdat";

	fopen_s(&FileStream, FileName2.c_str(), "wb");

	if (FileStream)
	{
		int Size = (int)vecFrame.size();
		for (int i = 0; i < Size; ++i)
		{
			int AnimNameLength = (int)vecFrame[i].length();
			fwrite(&AnimNameLength, sizeof(int), 1, FileStream);
			fwrite(vecFrame[i].c_str(), sizeof(char), AnimNameLength, FileStream);

			int FrameCount = GetSceneResource()->FindAnimationSequence(vecFrame[i])->GetFrameCount();

			for (int j = 0; j < FrameCount; ++j)
			{
				const AnimationFrameData& Data = GetSceneResource()->FindAnimationSequence(vecFrame[i])->GetFrameData(j);
				fwrite(&Data, sizeof(AnimationFrameData), 1, FileStream);
			}

		}
	}

	fclose(FileStream);
}

void CMainScene::SwapZOrder(float DeltaTime)
{
	CGameObject* Top = FindObject("PlayerTop");

	CGameObject* Bottom = FindObject("PlayerBottom");

	// m_ObjList에서 Top이 2번 Index, Bottom이 1번 Index
	if (m_TopBiggerZOrder)
	{
		m_ObjList.push_back(Bottom);

		auto iter = m_ObjList.begin();

		// iter는 Bottom을 가리키게 될 것
		std::advance(iter, 1);

		m_ObjList.erase(iter);

		m_TopBiggerZOrder = false;
	}

	// m_ObjList에서 Top이 1번 Index, Bottom이 2번 Index
	else
	{
		m_ObjList.push_back(Top);

		auto iter = m_ObjList.begin();

		// iter는 Top을 가리키게 될 것
		std::advance(iter, 1);

		m_ObjList.erase(iter);

		m_TopBiggerZOrder = true;
	}
}

