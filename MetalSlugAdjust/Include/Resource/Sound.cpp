
#include "Sound.h"
#include "../PathManager.h"

CSound::CSound()	:
	m_System(nullptr),
	m_Sound(nullptr),
	m_Group(nullptr),
	m_Channel(nullptr),
	m_Play(false),
	m_Loop(false)
{
}

CSound::~CSound()
{
	if (m_Sound)
		m_Sound->release();
}

bool CSound::LoadSound(FMOD::System* System,
	FMOD::ChannelGroup* Group, bool Loop, 
	const std::string& Name,
	const char* FileName, const std::string& PathName)
{
	m_Name = Name;
	m_System = System;
	m_Group = Group;
	m_Loop = Loop;

	char FullPath[MAX_PATH] = {};

	const PathInfo* PathInfo = CPathManager::GetInst()->FindPath(PathName);

	if (PathInfo)
		strcpy_s(FullPath, PathInfo->PathMultibyte);

	strcat_s(FullPath, FileName);

	FMOD_MODE Mode = FMOD_DEFAULT;

	if (Loop)
		Mode = FMOD_LOOP_NORMAL;

	if (m_System->createSound(FullPath, Mode, nullptr, &m_Sound) != FMOD_OK)
		return false;

	return true;
}

void CSound::Play()
{
	// playSound함수 결과로 m_Channel에 채널이 할당됨
	m_System->playSound(m_Sound, m_Group, false, &m_Channel);
	m_Play = true;
}

void CSound::Stop()
{
	if (m_Channel)
	{
		bool Playing = false;

		m_Channel->isPlaying(&Playing);

		if (Playing)
		{
			m_Channel->stop();
			// 재생을 멈추면 처음 play할 때 할당됐던
			// channel도 다시 nullptr로 돌려준다
			m_Channel = nullptr;

			m_Play = false;
		}
	}
}

void CSound::Pause()
{
	if (!m_Channel)
		return;

	bool Playing = false;

	m_Channel->isPlaying(&Playing);

	if (Playing)
		m_Channel->setPaused(true);

	m_Play = false;
}

void CSound::Resume()
{
	if (!m_Channel)
		return;

	bool Playing = false;

	m_Channel->isPlaying(&Playing);

	if (!Playing)
		m_Channel->setPaused(false);

	m_Play = true;

}
