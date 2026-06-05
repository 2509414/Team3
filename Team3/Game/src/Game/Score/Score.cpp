#include <DxLib.h>
#include"../Object/Player/Player.h"

#define NUMBER (12)				// 読み込む画像数「0」～「9」
#define NUMBER_SIZE_X (70)		// 数字サイズ横
#define NUMBER_SIZE_Y (72)		// 数字サイズ縦
#define STARTPOS_X (200)		// 表示開始位置横
#define STARTPOS_Y (50)		// 表示開始位置縦
#define DIGIT_NUMBER (3)		// 表示可能な桁数
#define ADD_SCORE_SPD (10)		// 1フレームで加算されるスコア数


#define RESULTPOS_X (700)
#define RESULTPOS_Y (550)


extern PLAYER_DATA g_player;



//	スコア表示用の構造体
typedef struct {
	int m_graphHndl[NUMBER];	// 画像ハンドル
	int m_soundHndl;			// 効果音ハンドル
	int m_score;				// 現在のスコア
	int m_dispScore;			// ディスプレイに表示されているスコア
	VECTOR m_pos;

	int hndl;

	int resultscore;

	int white[1];

}SCORE_DATA;

SCORE_DATA	g_score = { 0 };


//-----------------------------------
//		スコアの初期化
//-----------------------------------
void InitScore()
{
	for (int i = 0; i < NUMBER; i++)
	{
		g_score.m_graphHndl[i] = -1;
	}
	g_score.m_soundHndl = -1;
	g_score.m_score = 0;
	g_score.m_dispScore = 0;
	g_score.m_pos.x = STARTPOS_X;
	g_score.m_pos.y = STARTPOS_Y;
	g_score.hndl = -1;
}


//-----------------------------------
//		スコア画像のロード
//-----------------------------------
void LoadScore()
{
	LoadDivGraph("Data/Textures/Number.png", NUMBER, 3, 4, NUMBER_SIZE_X, NUMBER_SIZE_Y,
		g_score.m_graphHndl);

	LoadDivGraph("Data/Textures/white.png", 1, 1, 1, 32, 32, g_score.white);

	g_score.hndl = LoadGraph("Data/Textures/Persent.png");

	g_score.m_soundHndl = LoadSoundMem("Data/Sounds/Se2.mp3");
}


//-----------------------------------
//		スコアの更新処理
//-----------------------------------
void StepScore()
{
	g_score.m_score = score();

	// 表示用スコアと実際のスコアをすり合わせていく
	if (g_score.m_score != g_score.m_dispScore)
	{
		PlaySoundMem(g_score.m_soundHndl, DX_PLAYTYPE_BACK, TRUE);
		// この関数は今回使用するSEが最初に無音が入っているので使用
		// 強制的に1000ミリ秒後からスタートという処理なので、本来は記述不要
		SetCurrentPositionSoundMem(1000, g_score.m_soundHndl);
		g_score.m_dispScore += ADD_SCORE_SPD;

		// オーバーした場合は同じにしておく
		if (g_score.m_dispScore > g_score.m_score)
		{
			g_score.m_dispScore = g_score.m_score;
		}
	}
}


//-----------------------------------
//		スコアの描画処理
//-----------------------------------
void DrawScore()
{

	DrawRotaGraph(STARTPOS_X, STARTPOS_Y+15, 4, 0.0, g_score.white[0], TRUE);
	DrawRotaGraph(STARTPOS_X - 32*4, STARTPOS_Y + 15, 4, 0.0, g_score.white[0], TRUE);
	DrawRotaGraph(STARTPOS_X - (32 * 4)*2, STARTPOS_Y + 15, 4, 0.0, g_score.white[0], TRUE);



	DrawRotaGraph(STARTPOS_X + 25 , STARTPOS_Y +45 ,0.7, 0.0, g_score.hndl, TRUE);


	









	// モニターに表示するスコアを仮の変数にセット
	int tempScore = g_score.m_dispScore;
	for (int i = 0; i < DIGIT_NUMBER; i++)
	{
		// 下1桁を取り出す
		int num = tempScore % 10;

		if (num == 9){
			// 1桁目を初期位置X=580, Y=140からスコアを表示していく
			DrawRotaGraph(STARTPOS_X - (i * NUMBER_SIZE_X/2), STARTPOS_Y,
				0.5, 0.0, g_score.m_graphHndl[num+1], TRUE);
		}

		// 1桁目を初期位置X=580, Y=140からスコアを表示していく
		DrawRotaGraph(STARTPOS_X - (i * NUMBER_SIZE_X/2), STARTPOS_Y,
			0.5, 0.0, g_score.m_graphHndl[num], TRUE);
		// 下1桁を削除
		tempScore /= 10;
	}
}


//-----------------------------------
//		スコアのデータ破棄
//-----------------------------------
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

	if (g_score.m_soundHndl != -1)
	{
		DeleteSoundMem(g_score.m_soundHndl);
	}
}

int ResultScore() {

	g_score.resultscore = g_score.m_score;

	return g_score.resultscore;

}


void ResultScoreDraw() {

	int tempScore = g_score.resultscore;
	for (int i = 0; i < DIGIT_NUMBER; i++)
	{
		// 下1桁を取り出す
		int num = tempScore % 10;

		if (num == 9) {
			DrawRotaGraph(RESULTPOS_X - (i * NUMBER_SIZE_X / 2), RESULTPOS_Y,
				0.5, 0.0, g_score.m_graphHndl[num + 1], TRUE);
		}
		DrawRotaGraph(RESULTPOS_X - (i * NUMBER_SIZE_X / 2), RESULTPOS_Y,
			0.5, 0.0, g_score.m_graphHndl[num], TRUE);
		// 下1桁を削除
		tempScore /= 10;
	}
}