#pragma once
#include<DxLib.h>

#define SOUND_NUM  (10)
typedef struct {
	int m_Soundhndl[SOUND_NUM];

}SOUND_DATA;

void InitSound();

void LoadSound();

void PlaybackSound(int SoundId);

void ExitSound();