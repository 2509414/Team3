#pragma once

#define ENDWAIT_COUNT (60)	//死亡からゲーム終了までの時間

enum tagGameScene {
	//状態遷移
	GAMESCENE_INIT,			//初期化
	GAMESCENE_LOAD,			//データロード
	GAMESCENE_START,		//ゲーム開始前
	GAMESCENE_MAIN,			//メイン処理
	GAMESCENE_ENDWAIT,		//終了前の処理
	GAMESCENE_END,			//終了処理

	GAMESCENE_NUM
};

//ゲーム中の状態遷移を管理する構造体
typedef struct {
	int m_state;		//ゲームの状態遷移管理
	int m_waitCount;	//待機時間カウント
	
}GAME_SCENE;

extern GAME_SCENE g_gameScene;

//ゲーム全体の管理（計算処理）
int StepGame(int STAGENUM);

//ゲーム全体の管理（描画）
void DrawGame();

