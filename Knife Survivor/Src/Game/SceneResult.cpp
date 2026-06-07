#include<DxLib.h>
#include "../Lib/Input.h"
#include "../Lib/fade.h"
#include "Sound.h"
#include "SceneGame.h"

extern int Winner;

// ==============================
// リザルト画面UI定義
// ==============================
#define START_GOBTN_X (405)//		STARTボタンのX座標
#define START_GOBTN_Y  (400)//		STARTボタンのY座標
#define START_GOBTN_W_ (110)//		横の長さ
#define START_GOBTN_H  (44) //		高さ
#define ResultPic	 (3)  //		リザルトに使う画像の枚数

enum tagResultScene
{
	RESULTSCENE_INIT,	//初期化
	RESULTSCENE_LOAD,	//データロード
	RESULTSCENE_START,	//ゲーム開始前
	RESULTSCENE_MAIN,	//メイン処理
	RESULTSCENE_ENDWAIT,	//ゲーム終了後の待機
	RESULTSCENE_END,		//終了処理

	RESULTSCENE_NUM
};

//タイトル画面中の状態遷移を管理する構造体
typedef struct 
{
	tagResultScene m_state;				//ゲームの状態遷移管理
	int m_hndl[ResultPic];				//タイトル画面となる絵のハンドル
	
}RESULT_SCENE;

//初期値を設定
static RESULT_SCENE g_resultScene = { RESULTSCENE_INIT};

//マウスがスタートボタンの上にあるかどうかチェック
bool IsMouseOnStartButtonGameOver()
{
	int mx = GetMouseX();
	int my = GetMouseY();

	//マウスの座標
	/*DrawFormatString(10, 10, GetColor(255, 255, 255), "Mouse X:%d  Y:%d", mx, my);*/

	//乗ってたらtrue
	if (mx >= START_GOBTN_X &&
		mx <= START_GOBTN_X + START_GOBTN_W_ &&
		my >= START_GOBTN_Y &&
		my <= START_GOBTN_Y + START_GOBTN_H)
	{
		return true;
	}

	return false;
}


//ゲーム全体の管理（処理用）
int StepResult()
{
	int ret = 0;

	switch (g_resultScene.m_state)
	{
		//初期化関連
	case RESULTSCENE_INIT:
		
		//サウンド関連をここで初期化
		InitSound();
		//変数初期化
		for (int i = 0; i < ResultPic; i++)
		{
			g_resultScene.m_hndl[i] = -1;
		}
		//初期化が終わったからstateをRESULTSCENE_LOADにするよ
		g_resultScene.m_state = RESULTSCENE_LOAD;
		break;

		//画像ロード
	case RESULTSCENE_LOAD:
		//サウンドロード
		LoadSound();
		//絵のロード
		
		if (g_resultScene.m_hndl[0] == -1)
		{
			g_resultScene.m_hndl[0] = LoadGraph("Data/Textures/Result.png");
		}

		if (g_resultScene.m_hndl[1] == -1)
		{
			g_resultScene.m_hndl[1] = LoadGraph("Data/Textures/Exit.png");
		}
			
		if (g_resultScene.m_hndl[2] == -1)
		{
			g_resultScene.m_hndl[2] = LoadGraph("Data/Textures/Tie.png");
		}
		
		
		RequestFadeIn();
		//ロードが終わったらゲーム本編へ進む
		g_resultScene.m_state = RESULTSCENE_START;
		break;

		//開始前
	case RESULTSCENE_START:
		//フェードインが終わったら本編へ
		if (IsEndFadeIn())
		{
			g_resultScene.m_state = RESULTSCENE_MAIN;
		}
		break;

		//メイン処理
	case RESULTSCENE_MAIN:
		
		

		//左クリックが押されたかつスタートボタンの上に乗ってたら次に進む
		if (IsMouseLeftClick() == true && IsMouseOnStartButtonGameOver() == true)
		{
			PlaybackSound(2);
			//フェードアウトをリクエストする
			RequestFadeOut();
			g_resultScene.m_state = RESULTSCENE_ENDWAIT;
		}
		break;

		//ゲーム終了後の待機
	case RESULTSCENE_ENDWAIT:
		if (IsEndFadeOut() == true)
		{
			g_resultScene.m_state = RESULTSCENE_END;
		}
		break;

		//ゲーム終了後
	case RESULTSCENE_END:

		ExitSound();

		//画像の破棄
		for (int i = 0; i < ResultPic; i++)
		{
			if (g_resultScene.m_hndl[i] != -1)
			{
				DeleteGraph(g_resultScene.m_hndl[i]);
				g_resultScene.m_hndl[i] = -1;
			}
		}
		
		//最初に戻す
		g_resultScene.m_state = RESULTSCENE_INIT;
		ret = 1;
		break;
	}
	return ret;
}

//タイトル画面全体の管理（描画用）
void DrawResult()
{
	
	switch (g_resultScene.m_state)
	{
		case RESULTSCENE_START:
		case RESULTSCENE_MAIN:
		case RESULTSCENE_ENDWAIT:
			
			//①リザルトを表示
			if (Winner == 0)
			{
				DrawGraph(0, 0, g_resultScene.m_hndl[2], TRUE);
			}
			if(Winner != 0)
			{
				DrawGraph(0, 0, g_resultScene.m_hndl[0], TRUE);
			}

			//②背景
			bool IsMouseOnStartButtonGameOver();

			//マウスがスタートボタンの上に乗っていたらIsonをtrue
			bool Ison = IsMouseOnStartButtonGameOver();
			//IsOnがtrueだったら
			if (Ison == true)
			{
				//サウンドを鳴らす
				
				int a = 5;
				//乗っかっているという意味で色を表示
				DrawBox(START_GOBTN_X -a,
					START_GOBTN_Y - a,
					START_GOBTN_X + START_GOBTN_W_ +a,
					START_GOBTN_Y + START_GOBTN_H +a,
					GetColor(255, 255, 0), //ここで色を指定
					TRUE);
			}
				//③Exitボタン
				DrawGraph(389, 400, g_resultScene.m_hndl[1], TRUE);
				
				//④誰が勝ったか
				if (Winner != 0)
				{
					DrawFormatString(230, 240, GetColor(255, 255, 0), "P  l  a  y  e  r  %d", Winner);
				}
				
				//デバッグ用
				int mx, my;
				GetMousePoint(&mx, &my);
				DrawFormatString(10, 10, GetColor(255, 255, 255), "X %d Y %d", mx, my);

			break;

	}
}

