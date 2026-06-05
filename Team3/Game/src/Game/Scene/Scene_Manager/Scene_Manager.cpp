#include"../Scene_Game/Scene_Game.h"
#include"../Scene_Title/SceneTitle.h"
#include"../Scene_Result/Scene_Result.h"

//状態遷移
enum tagScene {
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_RESULT,
};


//ゲーム中の状態遷移を管理する構造体
typedef struct {
	tagScene m_state;
}SCENE_MANAGER;

static SCENE_MANAGER g_scene = { SCENE_TITLE};


int StepScene() {

	int ret = 0;	//ゲームが終了して消す時だけ値が変わる
	int next = 0;	//次のシーンに進むかどうか

	//ゲーム本編の状態遷移

	switch (g_scene.m_state)
	{
	case SCENE_TITLE:
		next = StepTitle();

		if (next == 1)
		{
			g_scene.m_state = SCENE_GAME;
		}
		break;

	case SCENE_GAME:
		next = StepGame();

		if (next == 1)
		{
			g_scene.m_state = SCENE_RESULT;
		}
		break;

	case SCENE_RESULT:
		next = StepResult();

		if (next == 1)
		{
			g_scene.m_state = SCENE_GAME;
		}
		break;
	

	default:
		break;
	}

	return ret;
}

void DrawScene() {


	switch (g_scene.m_state)
	{
	case SCENE_TITLE:
		DrawTitle();

		break;
	case SCENE_GAME:
		DrawGame();

		break;
	case SCENE_RESULT:
		DrawResult();

		break;
	}
}
