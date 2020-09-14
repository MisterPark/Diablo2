#pragma once

enum SoundChannel { BGM, PLAYER, MONSTER, EFFECT, MAXCHANNEL };

class SoundManager
{
public:
	static SoundManager* GetInstance()
	{
		if (nullptr == pSoundManager)
			pSoundManager = new SoundManager; 

		return pSoundManager; 
	}
	static void DestroyInstance()
	{
		if (pSoundManager)
		{
			delete pSoundManager; 
			pSoundManager = nullptr; 
		}
	}
	
private:
	SoundManager();
	~SoundManager();

public:
	void Initialize(); 

	void Release(); 
public:
	void PlaySound(TCHAR* pSoundKey, SoundChannel eID);
	void PlayBGM(TCHAR* pSoundKey);
	void StopSound(SoundChannel eID);
	void StopAll();
	void SetVolume(SoundChannel channel, float per);

private:
	void LoadSoundFile(); 

private:
	static SoundManager* pSoundManager; 
	// ���� ���ҽ� ������ ���� ��ü 
	map<TCHAR*, FMOD_SOUND*> m_mapSound; 
	// FMOD_CHANNEL : ����ϰ� �ִ� ���带 ������ ��ü 
	FMOD_CHANNEL* m_pChannelArr[MAXCHANNEL]; 
	// ���� ,ä�� ��ü �� ��ġ�� �����ϴ� ��ü 
	FMOD_SYSTEM* m_pSystem; 

};

