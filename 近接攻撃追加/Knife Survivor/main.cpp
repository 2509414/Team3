#include "DxLib.h"	//DxLibを使用するために必要
#include "Src/Lib/Fps.h"
#include "Src/Lib/Input.h"
#include "Src/Game/Scene/SceneManager.h"
#include "Src/Lib/fade.h"
#include "Src/Game/Scene/SceneTitle.h"

float g_deltaTime = 0.03f;
float g_deltaBossTime = 0.03f;

//main関数の代わり
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);		//ウィンドウモードにするか

	//1回だけやる処理
	//ウィンドウサイズ設定
	SetGraphMode(900, 600, 32);

	//DXライブラリ初期化、必須、基本これより後でDxLib関数を使う
	if (DxLib_Init() == -1) return -1;

	SetDrawScreen(DX_SCREEN_BACK);		//画面のちらつきをなくす


	//ゲームメインループ
	while (ProcessMessage() != -1)		//問題が発生したら終了
	{
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)break;	//escキーが押されたら終了
		if (IsNextFps() == false)continue;
		//描画した画像をすべて消す
		ClearDrawScreen();

		//ゲーム本体の命令はこれより下に書く
		//データ更新処理
		UpdateKeyInput();

		
		if (StepScene() != 0)break;
		//描画処理
		UpdateFade();
		DrawScene();
		DrawTitle();
		//乗っかってたら色を変える
		


		//ゲーム本体の命令はこれより上に書く
		ScreenFlip();

		
	}

	//終了前の処理関数
	
	
	DxLib_End();	//DxLib使用終了時に呼ぶ　必須
	return 0;
}