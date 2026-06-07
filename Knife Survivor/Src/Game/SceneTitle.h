#pragma once

// ==============================
// タイトル画面UI定義
// ==============================
#define START_BTN_X  (368)//		STARTボタンのX座標
#define START_BTN_Y  (272)//		STARTボタンのY座標
#define START_BTN_W  (159)//		横の長さ
#define START_BTN_H  (47) //		高さ
#define TitlePic	 (6)  //		タイトルに使う画像の枚数


enum tagTitleScene
{
	TITLESCENE_INIT,	//初期化
	TITLESCENE_LOAD,	//データロード
	TITLESCENE_START,	//ゲーム開始前
	TITLESCENE_MAIN,	//メイン処理
	TITLESCENE_ENDWAIT,	//ゲーム終了後の待機
	TITLESCENE_END,		//終了処理

	TITLESCENE_NUM
};
//タイトル画面中の状態遷移を管理する構造体
typedef struct
{
	tagTitleScene m_state;		//ゲームの状態遷移管理
	int m_hndl[TitlePic];		//タイトル画面となる絵のハンドル
	int m_nextstagenum;			//次のステージを管理するやつ
}TITLE_SCENE;

//初期値を設定
static TITLE_SCENE g_titleScene = { TITLESCENE_INIT };

bool IsMouseOnButton(int x, int y, int w, int h);


	//タイトル画面全体の管理（処理用）
int StepTitle();
	//タイトル画面全体の管理（描画用）
void DrawTitle();

