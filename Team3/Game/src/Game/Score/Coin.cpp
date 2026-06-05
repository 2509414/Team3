#include <DxLib.h>
#include"../Object/Player/Player.h"

#define NUMBER (12)				// 読み込む画像数「0」～「9」
#define NUMBER_SIZE_X (70)		// 数字サイズ横
#define NUMBER_SIZE_Y (72)		// 数字サイズ縦
#define STARTPOS_X (200)		// 表示開始位置横
#define STARTPOS_Y (100)			// 表示開始位置縦
#define DIGIT_NUMBER (5)		// 表示可能な桁数
#define ADD_SCORE_SPD (10)		// 1フレームで加算されるスコア数

#define RESULTPOS_X (700)
#define RESULTPOS_Y (500)



extern PLAYER_DATA g_player;



//	スコア表示用の構造体
typedef struct {
	int m_graphHndl[NUMBER];	// 画像ハンドル
	int m_soundHndl;			// 効果音ハンドル
	int m_score;				// 現在のスコア
	int m_dispScore;			// ディスプレイに表示されているスコア
	VECTOR m_pos;

	int result_coin;

}COIN_DATA;

COIN_DATA	g_coin = { 0 };


//-----------------------------------
//		スコアの初期化
//-----------------------------------
void InitCoin()
{
	for (int i = 0; i < NUMBER; i++)
	{
		g_coin.m_graphHndl[i] = -1;
	}
	g_coin.m_soundHndl = -1;
	g_coin.m_score = 0;
	g_coin.m_dispScore = 0;
	g_coin.m_pos.x = STARTPOS_X;
	g_coin.m_pos.y = STARTPOS_Y;
}


//-----------------------------------
//		スコア画像のロード
//-----------------------------------
void LoadCoin()
{
	LoadDivGraph("Data/Textures/Number.png", NUMBER, 3, 4, NUMBER_SIZE_X, NUMBER_SIZE_Y,
		g_coin.m_graphHndl);
	g_coin.m_soundHndl = LoadSoundMem("Data/Sounds/Se2.mp3");
}


//-----------------------------------
//		スコアの更新処理
//-----------------------------------
void StepCoin()
{
	g_coin.m_score = g_player.m_coin;

	// 表示用スコアと実際のスコアをすり合わせていく
	if (g_coin.m_score != g_coin.m_dispScore)
	{
		PlaySoundMem(g_coin.m_soundHndl, DX_PLAYTYPE_BACK, TRUE);
		// この関数は今回使用するSEが最初に無音が入っているので使用
		// 強制的に1000ミリ秒後からスタートという処理なので、本来は記述不要
		SetCurrentPositionSoundMem(1000, g_coin.m_soundHndl);
		g_coin.m_dispScore += ADD_SCORE_SPD;

		// オーバーした場合は同じにしておく
		if (g_coin.m_dispScore > g_coin.m_score)
		{
			g_coin.m_dispScore = g_coin.m_score;
		}
	}
}


//-----------------------------------
//		スコアの描画処理
//-----------------------------------
void DrawCoin()
{
	// モニターに表示するスコアを仮の変数にセット
	int tempScore = g_coin.m_dispScore;
	for (int i = 0; i < DIGIT_NUMBER; i++)
	{
		//if ((g_player.m_coin/10^i)==0)continue;

		// 下1桁を取り出す
		int num = tempScore % 10;

		if (num == 9) {
			DrawRotaGraph(STARTPOS_X - (i * NUMBER_SIZE_X/2), STARTPOS_Y,
				0.5, 0.0, g_coin.m_graphHndl[num + 1], TRUE);
		}

		DrawRotaGraph(STARTPOS_X - (i * NUMBER_SIZE_X/2), STARTPOS_Y,
			0.5, 0.0, g_coin.m_graphHndl[num], TRUE);
		// 下1桁を削除
		tempScore /= 10;
	}
}


//-----------------------------------
//		スコアのデータ破棄
//-----------------------------------
void ExitCoin(void)
{

	for (int i = 0; i < NUMBER; i++)
	{
		if (g_coin.m_graphHndl[i] != -1)
		{
			DeleteGraph(g_coin.m_graphHndl[i]);
			g_coin.m_graphHndl[i] = -1;
		}
	}

	if (g_coin.m_soundHndl != -1)
	{
		DeleteSoundMem(g_coin.m_soundHndl);
	}
}

int ResultCoin() {

	g_coin.result_coin = g_coin.m_score;

	return g_coin.result_coin;
}





void ResultCoinDraw() {

	int tempScore = g_coin.m_score;
	for (int i = 0; i < DIGIT_NUMBER; i++)
	{
		// 下1桁を取り出す
		int num = tempScore % 10;

		if (num == 9) {
			DrawRotaGraph(RESULTPOS_X - (i * NUMBER_SIZE_X / 2), RESULTPOS_Y,
				0.5, 0.0, g_coin.m_graphHndl[num + 1], TRUE);
		}
		DrawRotaGraph(RESULTPOS_X - (i * NUMBER_SIZE_X / 2), RESULTPOS_Y,
			0.5, 0.0, g_coin.m_graphHndl[num], TRUE);
		// 下1桁を削除
		tempScore /= 10;
	}
}