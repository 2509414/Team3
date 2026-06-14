#include<DxLib.h>

#define FADE_SPEED (3) //フェードの速度
#define WINDOW_SIZE_X (900)
#define WINDOW_SIZE_Y (600)

enum tagFade {
	FADE_NON,		//何もやっていない
	FADE_IN,		//フェードイン中
	FADE_OUT,		//フェードアウト中
	FADE_OUT_WAIT	//フェードアウト後の画面が真っ暗なとき
};

typedef struct {
	tagFade m_state;		//フェードの状態
	int m_count;			//フェード時間のカウント
}FADE_DATA;

static FADE_DATA g_fade;

//初期化
void InitFade()
{
	g_fade.m_state = FADE_NON;
	g_fade.m_count = 0;
}

//フェード更新
void UpdateFade()
{
	switch (g_fade.m_state)
	{
	case FADE_IN:
		g_fade.m_count -= FADE_SPEED;
		if (g_fade.m_count <= 0)
		{
			g_fade.m_count = 0;
			g_fade.m_state = FADE_NON;
		}
		break;

		//徐々に暗くしていく
	case FADE_OUT:
		g_fade.m_count += FADE_SPEED;
		if (g_fade.m_count >= 255)
		{
			g_fade.m_count = 255;
			g_fade.m_state = FADE_OUT_WAIT;
		}

	}
}

//フェード描画
void DrawFade()
{
	switch (g_fade.m_state)
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
		break;
	}
}
//フェードインリクエスト
void RequestFadeIn()
{
	g_fade.m_state = FADE_IN;
	g_fade.m_count = 255;
}

//フェードアウトリクエスト
void RequestFadeOut()
{
	g_fade.m_state = FADE_OUT;
	g_fade.m_count = 0;
}

//フェードインが終了しているか？
bool IsEndFadeIn()
{
	if (g_fade.m_state == FADE_IN)return false;
	else return true;
}

//フェードアウトが終了しているかどうか？
bool IsEndFadeOut()
{
	if (g_fade.m_state == FADE_OUT)return false;
	else return true;
}





