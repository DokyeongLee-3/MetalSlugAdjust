#pragma once

#include "../Ref.h"

class CSound :
    public CRef
{
    friend class CResourceManager;

private:
    CSound();
    ~CSound();

private:
    std::string m_Name;
    // Sound���� �Ѱ��ϴ� ��ü
    FMOD::System* m_System;
    FMOD::Sound* m_Sound;
    // sound�� ���� group(ex. BGM, UI, Effect...)
    FMOD::ChannelGroup* m_Group;
    // Sound Load�� �Ϸ������ m_Channel���� ���,
    // ���� ��������� �����ִ��� Ȯ��,
    // Pause �Ǿ� �ִ��� Ȯ���� Ȯ���� �� �ִ�
    FMOD::Channel* m_Channel;
    // ���� sound�� ��������� �ƴ���
    bool m_Play;
    bool m_Loop;

public:
    bool IsPlay()	const
    {
        return m_Play;
    }

    bool IsLoop()	const
    {
        return m_Loop;
    }

public:
    bool LoadSound(FMOD::System* System, FMOD::ChannelGroup* Group,
        bool Loop, const std::string& Name,
        const char* FileName,
        const std::string& PathName = SOUND_PATH);

    void Play();
    void Stop();
    void Pause();
    void Resume();
};

