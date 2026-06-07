#include<DxLib.h>

#define NUMBER (10)						//読み込み画像数 0～9
#define NUMBER_SIZE_X (32)				//数字サイズ横
#define NUMBER_SIZE_Y (38)				//数字サイズ縦
#define STARTPOS_X (500)					//表示開始位置横
#define STARTPOS_Y (50)					//表示開始位置縦
#define DIGIT_NUMBER (5)				//表示可能な桁数
#define ADD_SCORE_SPD (1)				//1フレームで加算されるスコア数


//スコア表示用構造体
typedef struct
{
	int m_graphHndl[NUMBER];	//画像ハンドル
	int m_score;				//現在のスコア
	int m_dispScore;			//ディスプレイに表示されているスコア

}SCORE_DATA;

SCORE_DATA g_score = { 0 };


//スコア初期化！
void InitScore()
{
	g_score.m_score = 0;
	for (int i = 0; i < NUMBER; i++)
	{
		g_score.m_graphHndl[i] = -1;
	}
}

//スコアの画像をロード！
void LoadScore()
{
	LoadDivGraph("Data/Textures/Score.png", NUMBER, 10, 1, NUMBER_SIZE_X, NUMBER_SIZE_Y, g_score.m_graphHndl);
}

//スコアの更新処理！
void StepScore()
{
	if (g_score.m_score != g_score.m_dispScore)
	{
		//スコアを加算する
		g_score.m_dispScore += ADD_SCORE_SPD;

		//目的のスコアを上回ったら止める
		if (g_score.m_dispScore > g_score.m_score)
		{
			g_score.m_dispScore = g_score.m_score;
		}
	}
}

//スコア加算処理
void AddScore()
{
	g_score.m_score += 3;
}

//スコアの描画処理
void DrawScore()
{
	//モニターに表示するスコアを仮の変数にセット
	int tempScore = g_score.m_dispScore;
	for (int i = 0; i < DIGIT_NUMBER; i++)
	{
		//下一桁を取り出す
		int num = tempScore % 10;

		//1桁目を初期位置X=500 Y=140からスコアを表示していく
		DrawRotaGraph(STARTPOS_X - (i * NUMBER_SIZE_X), STARTPOS_Y, 1.0f, 0.0f, g_score.m_graphHndl[num], TRUE);

		//下一桁削除
		tempScore /= 10;
	}
}

//スコアデータを破棄！
void ExitScore(void)
{
	for (int i = 0; i < NUMBER; i++)
	{
		if (g_score.m_graphHndl[i] != -1)
		{
			DeleteGraph(g_score.m_graphHndl[i]);
			g_score.m_graphHndl[i] = -1;
		}
	}
}

int GetScore()
{
	return g_score.m_score;
}

void ReduceScore(int n)
{
	g_score.m_score -= n;

	//0以下にならないように0で固定
	if (g_score.m_score < 0)
	{
		g_score.m_score = 0;
	}
}