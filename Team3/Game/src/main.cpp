#include <DxLib.h>		//DxLibを使用するために必要
#include"Lib/Debug/Fps.h"
#include"Lib/KeyInput/KeyInput.h"
#include"Lib/Debug/display.h"
#include"Game/Scene/Scene_Manager/Scene_Manager.h"
#include"Game/Object/Player/Player.h"
#include"Comon.h"
#include"Lib/Fade/Fade.h"


//main関数の代わりgame
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdshow)
{
	//フルスクリーンモードで開くか
	ChangeWindowMode(true);

	//ウインドウのサイズを変える
	SetGraphMode(WINDOW_SIZE_X,WINDOW_SIZE_Y,32);

	//DXライブラリ初期化、必須、基本これより後でDxLib関数を使う
	if (DxLib_Init() == -1)return-1;

	SetDrawScreen(DX_SCREEN_BACK);		//画面のちらつきをなくす

	int swich = 0;
	Init_Data();
	
	
	

	//ゲームのメインループ
	while (ProcessMessage() != -1)		//問題が発生したら終了
	{
		//「escキー」が押されたらゲーム終了
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)break;

		if (IsNextFrame() == false)continue;
		
		//描画した画像をすべて消す
		ClearDrawScreen();


		//更新処理
		StepScene();
		if (StepScene() != 0)break;
		
		
		
		



		//キー入力
		UpdateKeyInput();



		//ゲーム本体の命令はこれより下に書く

		//更新
		Step_Data();
		UpdeateFade();


		//表示
		Draw_Data();
		DrawScene();
		DrawFade();

		//ゲーム本体の命令はこれより上に書く

		//作成した画面をモニターへ転送
		ScreenFlip();
	}

	
	DxLib_End();	//DxLib使用終了時に呼ぶ、必須

	return 0;
}