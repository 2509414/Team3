#include<DxLib.h>

#define FRAME_RATE (60)
#define FRAME_RATE_MILLI_SECOND (1000 / FRAME_RATE)

//FPS表示用構造体
typedef struct {
	double m_drawFps;	//実際に表示するfps
	int m_nowtime;		//現在のPC時間
	int	m_prevtime;		//1秒前のPC時間
	int m_prevDrawTime;
	int m_count;		//カウント用
}FpsData;

//上記構造体を基に、グローバル変数を作成
static FpsData g_fps= { 0.0 };
//変数初期化
void InitFps()
{
	g_fps.m_drawFps = 0.0;
	g_fps.m_nowtime = 0;
	g_fps.m_count = 0;
	g_fps.m_prevDrawTime = g_fps.m_prevDrawTime = GetNowCount();
}
//次に進めていいか
bool IsNextFps()
{
	//最新時間取得
	g_fps.m_nowtime = GetNowCount();
	//前回から今回までの差
	int diftime = g_fps.m_nowtime - g_fps.m_prevtime;
	//想定の時間が経過したかをチェック
	if (diftime >= FRAME_RATE_MILLI_SECOND)
	{
		return true;
	}
	else return false;

}
void StepFps()
{
	g_fps.m_prevtime = g_fps.m_nowtime;
}

//-------------
// FPS表示関数
//-------------
void PrintFps() 
{
	//想定通りなら１フレーム進んだはず	
	g_fps.m_count++;
	int diftime = g_fps.m_nowtime - g_fps.m_prevDrawTime;
	//1秒以上経過したら計算開始
	if (diftime >= 1000)
	{
		//fps計算
		float frameCount = (float)(g_fps.m_count * 1000);
		g_fps.m_drawFps = frameCount / diftime;
		//カウントは０に戻す
		g_fps.m_count = 0;
		g_fps.m_prevDrawTime = g_fps.m_nowtime;
	}
	//FPSは常に表示を続ける
	//DrawFormatString(16, 16, GetColor(255, 255, 255), "FPS:%.1lf", g_fps.m_drawFps);
}

