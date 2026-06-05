#include"../../../Comon.h"
#include"../../Hitcheck/Hitcheck.h"
#include"../../../Lib/Effect/Effect.h"
#include"../../../Lib/KeyInput/KeyInput.h"
#include"../../../Lib/Fade/Fade.h"
#include"../../Score/Coin.h"
#include"../../Score/Score.h"
#include"Scene_Result.h"
#include"../../Timer/Timer.h"



#define ENDWAIT_COUNT (120)//死亡後の待機時間

//状態遷移
enum tagRESULTScene {
	RESULTSCENE_INIT,		//初期化
	RESULTSCENE_LOAD,	//データロード
	RESULTSCENE_START,	//ゲーム開始前
	RESULTSCENE_MAIN,		//メイン処理
	RESULTSCENE_ENDWAIT,	//終了前の処理
	RESULTSCENE_END,		//終了処理
};


//ゲーム中の状態遷移を管理する構造体
typedef struct {

	tagRESULTScene m_state;
	int m_waitCount;//待機時間カウント
	int m_hndl;
	int m_BGhndl;
	int m_soundhndl;

	bool m_soundflag;

}RESULT_SCENE;

static RESULT_SCENE g_resultscene = { RESULTSCENE_INIT,0,-1 };
ResultData g_result;

int StepResult() {

	int ret = 0;

	//ゲーム本編の状態遷移

	switch (g_resultscene.m_state)
	{
	case RESULTSCENE_INIT:

		g_resultscene.m_waitCount = ENDWAIT_COUNT;
		g_resultscene.m_hndl = -1;
		g_resultscene.m_soundhndl = -1;

		g_resultscene.m_state = RESULTSCENE_LOAD;
		break;
	case RESULTSCENE_LOAD:

		//画像ロード
		if (g_resultscene.m_hndl == -1)
		{
			g_resultscene.m_hndl = LoadGraph("Data/Textures/clear.jpeg");
			g_resultscene.m_BGhndl = LoadGraph("Data/Textures/white.png");
		}

		if (g_resultscene.m_soundhndl == -1)
		{
			g_resultscene.m_soundhndl = LoadSoundMem("Data/Sounds/result.mp3");
		}

		LoadCoin();
		LoadScore();

		//フェード呼び出し
		RequestFadeIn();
		g_resultscene.m_state = RESULTSCENE_START;

		break;
	case RESULTSCENE_START:
				
		PlaySoundMem(g_resultscene.m_soundhndl, DX_PLAYTYPE_BACK);

		//フェードインが終わったら本編へ
		if (IsEndFadeIn())
		{
			g_resultscene.m_state = RESULTSCENE_MAIN;
		}

		break;
	case RESULTSCENE_MAIN:
		//更新処理
		
		if (IsKeyInputTrg(KEY_SHOT) == true) {
			g_resultscene.m_state = RESULTSCENE_ENDWAIT;
			ret = 1;
		}

		break;
	case RESULTSCENE_ENDWAIT:

		if (IsEndFadeOut())
		{
			g_resultscene.m_state = RESULTSCENE_END;
		}

		break;
	case RESULTSCENE_END:

		if (g_resultscene.m_hndl != -1)
		{
			DeleteGraph(g_resultscene.m_hndl);
			g_resultscene.m_hndl = -1;
		}
		ret = 1;

		g_resultscene.m_state = RESULTSCENE_INIT;
		break;
	default:
		break;
	}

	return ret;
}

void DrawResult() {


	switch (g_resultscene.m_state)
	{
	case RESULTSCENE_START:
	case RESULTSCENE_MAIN:
	case RESULTSCENE_ENDWAIT:
		//描画
		DrawRotaGraph(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2, 5.0f, 0.0f, g_resultscene.m_BGhndl, FALSE);
		DrawRotaGraph(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 4, 1.0f, 0.0f, g_resultscene.m_hndl, FALSE);
		ResultTimer();
		DrawFormatString(16, 32, GetColor(0, 0, 0), "Time %d:%d;%d", g_result.minutes, g_result.seconds, g_result.conma);

		break;
	}
}

