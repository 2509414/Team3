#include<DxLib.h>
#include "../../Lib/Input.h"
#include "../../Lib/fade.h"
#include "SceneTitle.h"
#include "../Sound/Sound.h"

bool IsMouseOnButton(int x, int y, int w, int h)
{
	int mx, my;
	GetMousePoint(&mx, &my);

	return (mx >= x && mx <= x + w &&
		my >= y && my <= y + h);
}

//マウスがスタートボタンの上にあるかどうかチェック
bool IsMouseOnStartButton()
{
	int mx = GetMouseX();
	int my = GetMouseY();

	//マウスの座標
	DrawFormatString(10, 10, GetColor(0, 0, 0), "Mouse X:%d  Y:%d", mx, my);

	//乗ってたらtrue
	if (mx >= START_BTN_X &&
		mx <= START_BTN_X + START_BTN_W &&
		my >= START_BTN_Y &&
		my <= START_BTN_Y + START_BTN_H)
	{
		return true;
	}

	return false;
}

//ゲーム全体の管理（処理用）
int StepTitle()
{
	int ret = 0;

	switch (g_titleScene.m_state)
	{
		//初期化関連
	case TITLESCENE_INIT:
		
		//サウンド関連をここで初期化
		InitSound();

		//変数初期化
		for (int i = 0; i < TitlePic; i++)
		{
			g_titleScene.m_hndl[i] = -1;
		}
		//初期化が終わったからstateをTITLESCENE_LOADにするよ
		g_titleScene.m_state = TITLESCENE_LOAD;
		break;

		//画像ロード
	case TITLESCENE_LOAD:
			//サウンドロード
			LoadSound();
		//絵のロード
		for (int i = 0; i < TitlePic; i++)
		{
			if (g_titleScene.m_hndl[0] == -1)
			{
				g_titleScene.m_hndl[0] = LoadGraph("Data/Textures/タイトル画面（仮）.png");
			}

			if (g_titleScene.m_hndl[1] == -1)
			{
				g_titleScene.m_hndl[1] = LoadGraph("Data/Textures/タイトルスタートボタン.png");
			}

			if (g_titleScene.m_hndl[2] == -1)
			{
				g_titleScene.m_hndl[2] = LoadGraph("Data/Textures/ゲームタイトル.png");
			}

			if (g_titleScene.m_hndl[3] == -1)
			{
				g_titleScene.m_hndl[3] = LoadGraph("Data/Textures/STAGE1.png");
			}

			if (g_titleScene.m_hndl[4] == -1)
			{
				g_titleScene.m_hndl[4] = LoadGraph("Data/Textures/STAGE2.png");
			}

			if (g_titleScene.m_hndl[5] == -1)
			{
				g_titleScene.m_hndl[5] = LoadGraph("Data/Textures/モノクロボス.png");
			}

			if (g_titleScene.m_hndl[6] == -1)
			{
				g_titleScene.m_hndl[6] = LoadGraph("Data/Textures/controller.png");
			}

			if (g_titleScene.m_hndl[7] == -1)
			{
				g_titleScene.m_hndl[7] = LoadGraph("Data/Textures/STAGE4.png");
			}
		}
		
		RequestFadeIn();
		//ロードが終わったらゲーム本編へ進む
		g_titleScene.m_state = TITLESCENE_START;
		break;

		//開始前
	case TITLESCENE_START:
		//フェードインが終わったら本編へ
		if (IsEndFadeIn())
		{
			g_titleScene.m_state = TITLESCENE_MAIN;
		}
		break;

		//メイン処理
	case TITLESCENE_MAIN:
		
		

		//左クリックが押されたかつBOSSSTAGEボタンの上に乗ってたら次に進む
		if (IsMouseLeftClick() == true && IsMouseOnButton(START_BTN_X - 5,
														  START_BTN_Y - 5,
														  START_BTN_W + 5,
														  START_BTN_H + 5) == true)
		{
			PlaybackSound(2);
			//フェードアウトをリクエストする
			RequestFadeOut();
			g_titleScene.m_state = TITLESCENE_ENDWAIT;
		}

		//左クリックが押されたかつSTAGE2ボタンの上に乗ってたら次に進む
		if (IsMouseLeftClick() == true && IsMouseOnButton(START_BTN_X - 5,
														  START_BTN_Y + 100,
														  START_BTN_W + 5,
													   	  START_BTN_H + 5) == true)
		{
			PlaybackSound(2);
			//フェードアウトをリクエストする
			RequestFadeOut();
			g_titleScene.m_state = TITLESCENE_ENDWAIT;
		}
		

		//左クリックが押されたかつSTAGE1ボタンの上に乗ってたら次に進む
		if (IsMouseLeftClick() == true && IsMouseOnButton(START_BTN_X - 5,
														  START_BTN_Y + 200,
														  START_BTN_W + 5,
														  START_BTN_H + 5) == true)
		{
			PlaybackSound(2);
			//フェードアウトをリクエストする
			RequestFadeOut();
			g_titleScene.m_state = TITLESCENE_ENDWAIT;
		}

		//左クリックが押されたかつSTAGE4ボタンの上に乗ってたら次に進む
		if (IsMouseLeftClick() == true && IsMouseOnButton(40, 485, START_BTN_W, START_BTN_H))
		{
			PlaybackSound(2);
			//フェードアウトをリクエストする
			RequestFadeOut();
			g_titleScene.m_state = TITLESCENE_ENDWAIT;
		}
		break;

		//ゲーム終了後の待機

	case TITLESCENE_ENDWAIT:
		if (IsEndFadeOut() == true)
		{
			g_titleScene.m_state = TITLESCENE_END;
		}
		break;

		//ゲーム終了後
	case TITLESCENE_END:

		ExitSound();

		//画像の破棄
		for (int i = 0; i < TitlePic; i++)
		{
			if (g_titleScene.m_hndl[TitlePic] != -1)
			{
				DeleteGraph(g_titleScene.m_hndl[TitlePic]);
				g_titleScene.m_hndl[TitlePic] = -1;
			}
		}
		

		//最初に戻す
		g_titleScene.m_state = TITLESCENE_INIT;

		ret = 1;
		break;
	}
	return ret;
}

//タイトル画面全体の管理（描画用）
void DrawTitle()
{
	switch (g_titleScene.m_state)
	{
		case TITLESCENE_START:
		case TITLESCENE_MAIN:
		case TITLESCENE_ENDWAIT:

			//①タイトルを表示
			DrawGraph(0, 0, g_titleScene.m_hndl[0], TRUE);
			
			//ゲームタイトル表示
			DrawGraph(200, 70, g_titleScene.m_hndl[2], TRUE);
			//②背景

			//マウスがSTAGEBOSS上に乗っていたらBossをtrue
			int a = 5;
			bool Boss = IsMouseOnButton(START_BTN_X - a,
										START_BTN_Y - a,
										START_BTN_W + a,
										START_BTN_H + a);
										
			//Bossがtrueだったら
			if (Boss == true)
			{
				
				//乗っかっているという意味で色を表示
				DrawBox(START_BTN_X-a,
					START_BTN_Y-a,
					START_BTN_X + START_BTN_W+a,
					START_BTN_Y + START_BTN_H+a,
					GetColor(255, 255, 0), //ここで色を指定
					TRUE);
			}


			//マウスがSTAGE2上に乗っていたらSTAGE2をtrue
			bool Stage2 = IsMouseOnButton(START_BTN_X - a,
										  START_BTN_Y + 100,
										  START_BTN_W + a,
										  START_BTN_H + a);
			//Stage2がtrueだったら
			if (Stage2 == true)
			{

				//乗っかっているという意味で色を表示
				DrawBox(START_BTN_X - a,
					START_BTN_Y +100 ,
					START_BTN_X + START_BTN_W,
					START_BTN_Y + 100 + START_BTN_H,
					GetColor(255, 255, 0), //ここで色を指定
					TRUE);
			}

			//マウスがSTAGE1上に乗っていたらSTAGE1をtrue
			bool Stage1 = IsMouseOnButton(START_BTN_X - a,
				START_BTN_Y + 200,
				START_BTN_W + a,
				START_BTN_H + a);
			//Stage1がtrueだったら
			if (Stage1 == true)
			{

				//乗っかっているという意味で色を表示
				DrawBox(START_BTN_X - a,
					START_BTN_Y + 200,
					START_BTN_X + START_BTN_W,
					START_BTN_Y + 200 + START_BTN_H,
					GetColor(255, 255, 0), //ここで色を指定
					TRUE);
			}

			//マウスがSTAGE4上に乗っていたらSTAGE4をtrue
			//Stage4がtrueだったら
			bool Stage4 = IsMouseOnButton(40, 485, START_BTN_W, START_BTN_H);

			//Stage2がtrueだったら
			if (Stage4 == true)
			{
				//乗っかっているという意味で色を表示
				DrawBox(40,
						485,
						40 + START_BTN_W,
						485 + START_BTN_H,
						GetColor(255, 255, 0), TRUE); //ここで色を指定

			}

				//③文字
				
				//訓練所
				DrawGraph(40, 485, g_titleScene.m_hndl[7], TRUE);

				//ボスステージ
				DrawGraph(369, START_BTN_Y, g_titleScene.m_hndl[1], TRUE);

				//ステージ2
				DrawGraph(369, 372, g_titleScene.m_hndl[4], TRUE);

				//ステージ1
				DrawGraph(369, 472, g_titleScene.m_hndl[3], TRUE);

				//モノクロボス
				DrawGraph(680, 50, g_titleScene.m_hndl[5], TRUE);

				DrawGraph(80, 50, g_titleScene.m_hndl[5], TRUE);

				////操作方法
				//DrawGraph(-10, 350, g_titleScene.m_hndl[6], TRUE);

				// 点滅スピード調整
				int blink = (GetNowCount() / 750) % 2;

				if (blink == 0)
				{
					DrawFormatString(315,205,GetColor(0, 0, 0),"Choose a stage and left-click");
				}
			break;

	}
}

