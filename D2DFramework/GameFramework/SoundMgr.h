#pragma once
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
public:
	enum CHANNELID {BGM, PLAYER, MONSTER, EFFECT, UI, MAXCHANNEL};
private:
	SoundManager();
	~SoundManager();

public:
	void Initialize(); 

	void Release(); 
public:
	void PlaySound(TCHAR* pSoundKey, CHANNELID eID);
	void PlayBGM(TCHAR* pSoundKey);
	void StopSound(CHANNELID eID);
	void StopAll();

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

