
#include"../../../Comon.h"
#include"../../Hitcheck/Hitcheck.h"
#include"../../../Lib/Effect/Effect.h"
#include"../../../Lib/KeyInput/KeyInput.h"
#include"../../../Lib/Fade/Fade.h"

#define ENDWAIT_COUNT (120)//死亡後の待機時間




//状態遷移
enum tagTITLEScene {
	TITLESCENE_INIT,		//初期化
	TITLESCENE_LOAD,	//データロード
	TITLESCENE_START,	//ゲーム開始前
	TITLESCENE_MAIN,		//メイン処理
	TITLESCENE_ENDWAIT,	//終了前の処理
	TITLESCENE_END,		//終了処理
};


//ゲーム中の状態遷移を管理する構造体
typedef struct {

	tagTITLEScene m_state;
	int m_waitCount;//待機時間カウント
	int m_hndl;
	int m_soundhndl;

}TITLE_SCENE;

static TITLE_SCENE g_titlescene = { TITLESCENE_INIT,0,-1 };

int StepTitle() {

	int ret = 0;

	//ゲーム本編の状態遷移

	switch (g_titlescene.m_state)
	{
	case TITLESCENE_INIT:
		
		g_titlescene.m_waitCount = ENDWAIT_COUNT;
		g_titlescene.m_hndl = -1;
		g_titlescene.m_soundhndl = -1;

		g_titlescene.m_state = TITLESCENE_LOAD;
		break;
	case TITLESCENE_LOAD:
	
		//画像ロード
		if (g_titlescene.m_hndl == -1)
		{
			g_titlescene.m_hndl = LoadGraph("Data/Textures/Title.png");
		}
		
		if (g_titlescene.m_soundhndl == -1)
		{
			g_titlescene.m_soundhndl = LoadSoundMem("Data/Sounds/Title_2.mp3");
		}

	
		//フェード呼び出し
		RequestFadeIn();
		g_titlescene.m_state = TITLESCENE_START;

		break;
	case TITLESCENE_START:

		//フェードインが終わったら本編へ
		if (IsEndFadeIn())
		{
			g_titlescene.m_state = TITLESCENE_MAIN;
		}
			
		

		break;
	case TITLESCENE_MAIN:
		//更新処理
		
		if (IsKeyInputTrg(KEY_SHOT) == true) {

			PlaySoundMem(g_titlescene.m_soundhndl ,DX_PLAYTYPE_BACK);


			g_titlescene.m_state = TITLESCENE_ENDWAIT;
			ret = 1;
		}

		break;
	case TITLESCENE_ENDWAIT:



		if (IsEndFadeOut())
		{
			g_titlescene.m_waitCount--;
			if (g_titlescene.m_waitCount <= 0)
			{
				g_titlescene.m_state = TITLESCENE_END;
			}
			}
		

		break;
	case TITLESCENE_END:

		if (g_titlescene.m_hndl != -1)
		{
			DeleteGraph(g_titlescene.m_hndl);
			g_titlescene.m_hndl = -1;
		}
		ret = 1;

		g_titlescene.m_state = TITLESCENE_INIT;
		break;
	default:
		break;
	}

	return ret;
}

void DrawTitle() {


	switch (g_titlescene.m_state)
	{
	case TITLESCENE_START:
	case TITLESCENE_MAIN:
	case TITLESCENE_ENDWAIT:
		//描画

		DrawRotaGraph(WINDOW_SIZE_X/2, WINDOW_SIZE_Y/2,0.8,0.0, g_titlescene.m_hndl, TRUE);
		
		break;
	}
}

