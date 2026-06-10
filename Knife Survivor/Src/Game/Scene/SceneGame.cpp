#include "../Player/Player.h"
#include "../Player/Player2.h"
#include "../Knife/Knife.h"
#include "../Knife/Knife2.h"
#include "../Bg/Background.h"
#include "../../Lib/Fps.h"
#include "../../Lib/Time.h"
#include "../../Lib/fade.h"
#include "SceneGame.h"
#include "../Sound/Sound.h"
#include "../Stage/Stage.h"
#include "../HitCheck/HitCheck.h"
#include "../Item/Item.h"

int Winner;					//勝者

GAME_SCENE g_gameScene = { GAMESCENE_INIT };
Player player1;
Player2 player2;
Knife Knife1;
Knife2 knife2;
Item item;

int StepGame(int Stagenum) 
{

	int ret = 0;

	//ゲーム本編の状態遷移
	switch (g_gameScene.m_state)
	{
	case GAMESCENE_INIT:
		//初期化処理
		InitBG();
		InitSound();
		InitFps();
		InitStage();

		Knife1.Init();
		knife2.Init();
		
		TimerInit(300);	//〇秒タイマー
		TimerStart();	//タイマー開始
		player1.Init(Stagenum);
		player2.Init(Stagenum);

		item.Init();
		g_gameScene.m_state = GAMESCENE_LOAD;
		break;

	case GAMESCENE_LOAD:
		//データをロード
		LoadBG();
		LoadStageGraph();
		LoadStageData(Stagenum);
		player1.Load();
		player2.Load();
		Knife1.Load();
		knife2.Load();
		
		item.Load();

		LoadSound();

		RequestFadeIn();

		g_gameScene.m_state = GAMESCENE_START;
		break;

	case GAMESCENE_START:
		//フェードインが終わったら本編へ
		if (IsEndFadeIn())
		{
			PlaybackSound(4);
			g_gameScene.m_state = GAMESCENE_MAIN;
		}
		break;

	case GAMESCENE_MAIN:
		//更新処理
		StepFps();
		player1.Step();
		player2.Step();
		
		Knife1.Step();
		knife2.Step();
		
		TimerGetSec();

		player1.Dash();
		player1.Jump();
		player2.Dash();
		player2.Jump();

		item.Step();
		
		UpdateStage();

		
		//プレイヤーとステージの当たり判定
		HitCheckPlayerToStage();
		HitCheckPlayer2ToStage();

		//プレイヤーとナイフの当たり判定
		player1.HitCheckKnifeToPlayer2();
		player2.HitCheckKnifeToPlayer1();


		//ゲーム終了へ
		if (player1.m_hp == 0)
		{
			PlaybackSound(1);
			g_gameScene.m_waitCount = ENDWAIT_COUNT + 110;
			g_gameScene.m_state = GAMESCENE_ENDWAIT;
			Winner = 2;
			RequestFadeOut();
		}

		if (player2.m_hp == 0)
		{
			PlaybackSound(1);
			g_gameScene.m_waitCount = ENDWAIT_COUNT + 110;
			g_gameScene.m_state = GAMESCENE_ENDWAIT;
			Winner = 1;
			RequestFadeOut();
		}

		//時間切れになったら残りHPを見て勝敗を決める
		if (TimeUp() == true)
		{	
			if (player1.m_hp > player2.m_hp)
			{
				Winner = 1;
			}
			else if (player2.m_hp > player1.m_hp)
			{
				Winner = 2;
			}
			else
			{
				Winner = 0;
			}
			
			g_gameScene.m_waitCount = ENDWAIT_COUNT +110;
			g_gameScene.m_state = GAMESCENE_ENDWAIT;
			
			RequestFadeOut();
		}
		
		break;
		

		//ゲーム終了後の待機
	case GAMESCENE_ENDWAIT:
		
		//カウントを徐々に減らし終わったら終了
		g_gameScene.m_waitCount--;
		
		if (g_gameScene.m_waitCount <= 0)
		{
			if(IsEndFadeOut())
			g_gameScene.m_state = GAMESCENE_END;
		}
		break;

	case GAMESCENE_END:
	
		ExitSound();
		g_gameScene.m_state = GAMESCENE_INIT;
		ret = 1;
	}
	return ret;
}

void DrawGame()
{
	switch (g_gameScene.m_state)
	{
	case GAMESCENE_START:
	case GAMESCENE_MAIN:
	case GAMESCENE_ENDWAIT:

		//画像データ表示関数
		DrawBG();
		DrawStage();
		
		player1.Draw();
		player2.Draw();
		Knife1.Draw();
		knife2.Draw();
	
		item.Draw();
		PrintFps();
		
		int mx, my;
		GetMousePoint(&mx, &my);
		DrawFormatString(10, 10, GetColor(0, 0, 0), "X %d  Y %d", mx, my);
		
		

		//残り時間変数
		int remaining = TimerGetSec();
		//残り時間を表示
		DrawFormatString(220, 45, GetColor(0, 0, 0), "残り時間:%d秒", remaining);
		
		break;
	}
}