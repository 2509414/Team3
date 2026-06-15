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
#include "../Attack/Attack.h"
#include "../Attack/Attack2.h"
#include "../Controller/controller.h"
#include"../Item/HpItem.h"
int Winner;					//勝者

extern int Stagenum;

GAME_SCENE g_gameScene = { GAMESCENE_INIT };
Player player1;
Player2 player2;
Knife Knife1;
Knife2 knife2;
Item item;
Attack attack;
Attack2 attack2;
Controller controller;
HpItem hpitem;

int StepGame(int Stagenum) 
{
	int ret = 0;

	//ゲーム本編の状態遷移
	switch (g_gameScene.m_state)
	{
	case GAMESCENE_INIT:
		//初期化処理
		if (Stagenum == 3)
		{
			InitBG();
			InitSound();
			InitFps();
			InitStage();

			Knife1.Init();
			knife2.Init();

			player1.Init(Stagenum);
			player2.Init(Stagenum);

			attack.Init();
			attack2.Init();
			item.Init();
			hpitem.Init();
			controller.Init();
			g_gameScene.m_state = GAMESCENE_LOAD;
			break;
		}
		else
		{
			InitBG();
			InitSound();
			InitFps();
			InitStage();

			Knife1.Init();
			knife2.Init();

			player1.Init(Stagenum);
			player2.Init(Stagenum);

			attack.Init();
			attack2.Init();

			TimerInit(300);	//〇秒タイマー
			TimerStart();	//タイマー開始

			item.Init();
			hpitem.Init();
			controller.Init();
			g_gameScene.m_state = GAMESCENE_LOAD;
			break;
		}
		

	case GAMESCENE_LOAD:
		//データをロード
		if (Stagenum == 3)
		{
			controller.Load();
		}

		LoadBG();
		LoadStageGraph();
		LoadStageData(Stagenum);
		player1.Load();
		player2.Load();
		Knife1.Load();
		knife2.Load();

		attack.Load();
		attack2.Load();
		
		item.Load();
		hpitem.Load();
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

		attack.Step();
		attack2.Step();
		item.Step();
		hpitem.Step();
		UpdateStage();

		
		//プレイヤーとステージの当たり判定
		HitCheckPlayerToStage();
		HitCheckPlayer2ToStage();

		//プレイヤーとナイフの当たり判定
		player1.HitCheckKnifeToPlayer2();
		player2.HitCheckKnifeToPlayer1();

		//ナイフとアイテムの当たり判定
		player1.HitCheckAction1ToItem(item);
		player2.HitCheckAction2ToItem(item);

		//プレイヤーと近接攻撃の当たり判定
		player1.HitCheckAttackToPlayer2();
		player2.HitCheckAttackToPlayer1();

		//プレイヤーとHPアイテムの当たり判定
		player1.HitCheckPlayer1ToHpItem(hpitem);
		player2.HitCheckPlayer2ToHpItem(hpitem);

		//player1のHPが0以下になったらゲーム終了
		if (player1.m_hp <= 0)
		{
			PlaybackSound(13);
			g_gameScene.m_waitCount = ENDWAIT_COUNT + 110;
			g_gameScene.m_state = GAMESCENE_ENDWAIT;
			Winner = 2;
			RequestFadeOut();
		}

		//player2のHPが0以下になったらゲーム終了
		if (player2.m_hp <= 0)
		{
			PlaybackSound(14);
			g_gameScene.m_waitCount = ENDWAIT_COUNT + 110;
			g_gameScene.m_state = GAMESCENE_ENDWAIT;
			Winner = 1;
			RequestFadeOut();
		}

		//時間切れになったら残りHPを見て勝敗を決める
		if (TimeUp() == true && Stagenum != 3)
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
		controller.Exit();
		player1.Exit();
		player2.Exit();
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
		attack.Draw();
		attack2.Draw();
		item.Draw();
		hpitem.Draw();
		controller.Draw();
		PrintFps();
		
		//残り時間変数
		int remaining = TimerGetSec();
		//残り時間を表示
		if (Stagenum == 3)
		{
			DrawFormatString(450, 40, GetColor(0, 0, 0), "∞");
		}
		else
		{
			DrawFormatString(440, 40, GetColor(0, 0, 0), "%d秒", remaining);
		}
		break;
	}
}