#include<DxLib.h>
#include "Sound.h"

SOUND_DATA g_sound;

void InitSound()
{
	//サウンドハンドルを初期化！
	for (int i = 0; i < SOUND_NUM; i++)
	{
		g_sound.m_Soundhndl[i] = -1;
	}

}

void LoadSound()
{

	if (g_sound.m_Soundhndl[0] == -1)
	{
		g_sound.m_Soundhndl[0] = LoadSoundMem("Data/Sound/KnifeThrow.mp3");
	}

	if (g_sound.m_Soundhndl[1] == -1)
	{
		g_sound.m_Soundhndl[1] = LoadSoundMem("Data/Sound/sibou.mp3");
	}

	if (g_sound.m_Soundhndl[2] == -1)
	{
		g_sound.m_Soundhndl[2] = LoadSoundMem("Data/Sound/koin.mp3");
	}

	if (g_sound.m_Soundhndl[3] == -1)
	{
		g_sound.m_Soundhndl[3] = LoadSoundMem("Data/Sound/キミの負けだよ.mp3");
	}

	if (g_sound.m_Soundhndl[4] == -1)
	{
		g_sound.m_Soundhndl[4] = LoadSoundMem("Data/Sound/GameMusic.mp3");
	}

	if (g_sound.m_Soundhndl[5] == -1)
	{
		g_sound.m_Soundhndl[5] = LoadSoundMem("Data/Sound/ジャンプ音.mp3");
	}

	if (g_sound.m_Soundhndl[6] == -1)
	{
		g_sound.m_Soundhndl[6] = LoadSoundMem("Data/Sound/ブロック置く時の音.mp3");
	}

	if (g_sound.m_Soundhndl[7] == -1)
	{
		g_sound.m_Soundhndl[7] = LoadSoundMem("Data/Sound/ブロック置けない時の音.mp3");
	}

	if (g_sound.m_Soundhndl[8] == -1)
	{
		g_sound.m_Soundhndl[8] = LoadSoundMem("Data/Sound/攻撃が外れた時の音.mp3");
	}

	if (g_sound.m_Soundhndl[9] == -1)
	{
		g_sound.m_Soundhndl[9] = LoadSoundMem("Data/Sound/BossBGM.mp3");
	}

	if (g_sound.m_Soundhndl[10] == -1)
	{
		g_sound.m_Soundhndl[10] = LoadSoundMem("Data/Sound/Attack.mp3");
	}

}

void PlaybackSound(int SoundId)
{

	if (g_sound.m_Soundhndl[SoundId] != -1)
	{
		PlaySoundMem(g_sound.m_Soundhndl[SoundId], DX_PLAYTYPE_BACK);
	}
}

void ExitSound()
{
	for (int i = 0; i < SOUND_NUM; i++)
	{
		DeleteSoundMem(g_sound.m_Soundhndl[i]);
	}
}