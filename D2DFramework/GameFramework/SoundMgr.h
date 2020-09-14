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
	// 사운드 리소스 정보를 갖는 객체 
	map<TCHAR*, FMOD_SOUND*> m_mapSound; 
	// FMOD_CHANNEL : 재생하고 있는 사운드를 관리할 객체 
	FMOD_CHANNEL* m_pChannelArr[MAXCHANNEL]; 
	// 사운드 ,채널 객체 및 장치를 관리하는 객체 
	FMOD_SYSTEM* m_pSystem; 

};

