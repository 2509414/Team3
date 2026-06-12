#include<DxLib.h>
#include"SceneTitle.h"
#include "SceneGame.h"

#include "SceneResult.h"

#include "../../Lib/fade.h"

enum tagScene
{
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_RESULT,

	SCENE_NUM
};

int Stagenum = -1;

//ゲーム全体の状態遷移を管理する構造体
typedef struct
{
	tagScene m_state;	//ゲームの状態遷移管理
	int m_waitCount;	//待機時間カウント
}SCENE_MANAGER;

//初期値を設定しておく
static SCENE_MANAGER g_scene = { SCENE_TITLE };


extern TITLE_SCENE g_titleScene;

//シーン全体の管理（処理用）
int StepScene()
{
	int ret = 0;	//ゲームが終了したかどうか
	int next = 0;	//次の状態遷移に進むかどうか

	switch (g_scene.m_state)
	{
		//タイトル画面
	case SCENE_TITLE:
		next = StepTitle();
		if (next == 1)
		{
			
			//STAGEBOSSの上で押されてたらg_titleScene.m_nextstagenum = 0にする
			if (IsMouseOnButton(START_BTN_X - 5,
				START_BTN_Y - 5,
				START_BTN_W + 5,
				START_BTN_H + 5) == true)
			{
				
				//stateをSCENE_GAMEに
				Stagenum = 1;
				g_scene.m_state = SCENE_GAME;
			}
	

			//STAGE2の上で押されてたらg_titleScene.m_nextstagenum = 0にする
			if (IsMouseOnButton(START_BTN_X - 5,
				START_BTN_Y + 100,
				START_BTN_W + 5,
				START_BTN_H + 5) == true)
			{
			
				//stateをSCENE_GAMEに
				Stagenum = 0;
				g_scene.m_state = SCENE_GAME;
			}
		
			//STAGE1の上で押されてたらg_titleScene.m_nextstagenum = 2にする
			if (IsMouseOnButton(START_BTN_X - 5,
				START_BTN_Y + 200,
				START_BTN_W + 5,
				START_BTN_H + 5) == true)
			{
				Stagenum = 2;
				//stateをSCENE_GAMEに
				g_scene.m_state = SCENE_GAME;
			}

			//訓練場の上で押されていたらg_titleScene.m_nextstagenum = 3にする
			if (IsMouseOnButton(40, 485, START_BTN_W, START_BTN_H) == true)
			{
				Stagenum = 3;
				//stateをSCENE_GAMEに
				g_scene.m_state = SCENE_GAME;
			}

	
		}
		break;

		//ゲーム本編
	case SCENE_GAME:
		next = StepGame(Stagenum);
		if (next == 1)
		{
			g_scene.m_state = SCENE_RESULT;
		}
	
		break;


		//RESULT
	case SCENE_RESULT:
		next = StepResult();
		if (next == 1)
		{
			g_scene.m_state = SCENE_TITLE;
		}
		break;
	}
	return ret;
}

	
	

//シーン全体の管理（描画用）
void DrawScene()
{
	switch (g_scene.m_state)
	{
		//タイトル
	case SCENE_TITLE:
		DrawTitle();
		break;
	
		//ゲーム本編
	case SCENE_GAME:
		DrawGame();
		break;

		//リザルト
	case SCENE_RESULT:
		DrawResult();
		break;

	
	}

	//フェードの描画は必ず一番最後で
	DrawFade();
}
