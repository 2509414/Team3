#include<DxLib.h>
#include"../../Comon.h"
#include"Fade.h"

#define FADE_SPEED (5)

enum tagFade
{
	FADE_NON,		//何もやっていない
	FADE_IN,		//フェードイン中
	FADE_OUT,		//フェードアウト中
	FADE_OUT_WAIT	//フェードアウト後の画面が真っ暗な状態
};


typedef struct
{
	tagFade m_sate;
	int m_count;

}FADE_DATA;

static FADE_DATA g_fade;

void InitFade() {

	g_fade.m_count = FADE_NON;
	g_fade.m_count = 0;
}

void UpdeateFade() {

	switch (g_fade.m_sate)
	{
	case FADE_IN:

		g_fade.m_count -= FADE_SPEED;
		if (g_fade.m_count <= 0)
		{
			g_fade.m_count = 255;
			g_fade.m_sate = FADE_NON;
		}
		break;
	case FADE_OUT:
		g_fade.m_count += FADE_SPEED;
		if (g_fade.m_count >= 255)
		{
			g_fade.m_count = 0;
			g_fade.m_sate = FADE_OUT_WAIT;
		}

		break;

	default:
		break;
	}
}

void DrawFade() {
	switch (g_fade.m_sate)
	{
	case FADE_IN:
	case FADE_OUT:
	case FADE_OUT_WAIT:

		//αブレンド開始
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, g_fade.m_count);

		//フェード用の黒い板
		DrawBox(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y, GetColor(0, 0, 0), TRUE);

		//αブレンド終了
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	default:
		break;
	}
}


void RequestFadeIn() {
	g_fade.m_sate = FADE_IN;
	g_fade.m_count = 255;
}

void RequestFadeOut() {
	g_fade.m_sate = FADE_OUT;
	g_fade.m_count = 0;
}

bool IsEndFadeIn() {
	if (g_fade.m_sate == FADE_IN)return false;
	else return true;
}

bool IsEndFadeOut() {
	if (g_fade.m_sate == FADE_OUT)return false;
	else return true;
}




