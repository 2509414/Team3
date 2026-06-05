#pragma once

#define NUMBER (12)				// 読み込む画像数「0」～「9」
#define NUMBER_SIZE_X (70)		// 数字サイズ横
#define NUMBER_SIZE_Y (72)		// 数字サイズ縦
#define STARTPOS_X (650)		// 表示開始位置横
#define STARTPOS_Y (50)			// 表示開始位置縦
#define DIGIT_NUMBER (2)		// 表示可能な桁数
#define RESULT_POSY (500)

#define DISTANCE (80)			//数字の位置の間隔

#define MAX_TIME (120);			




struct TIME
{
	int m_cnt;

	int m_seconds;
	int m_minutes;

	int hndl;
	int Timehndl;
	int m_white[1];

	int m_time;
	int m_graphHndl[NUMBER];


	int count;
};



void InitTime();

void DrawCanma();

void DrawConma();
void DrawMinutets();
void DrawSeconds();


void LoadTime();

int Time();

void ExitTime();

void ResultTimer();