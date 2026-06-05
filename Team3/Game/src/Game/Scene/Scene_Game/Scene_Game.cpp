#include"../../Object/Player/Player.h"
#include"../../Object/Player/Gimmick/Plshot.h"
#include"../../../Comon.h"
#include"../../Object/Stage/Stage.h"
#include"../../Hitcheck/Hitcheck.h"
#include"../../../Lib/Effect/Effect.h"
#include"../../../Lib/KeyInput/KeyInput.h"
#include"../../Object/Enemy/Enemy.h"
#include"../../Score/Score.h"
#include"../../Score/Coin.h"
#include"../../Timer/Timer.h"
#include"../Scene_Result/Scene_Result.h"
#include"../../Object/Player/Gimmick/Arrow.h"
#include"../../Object/BG/BG.h"
#include"../../Object/Stage/Gimmick/MoveBlock.h"
#include"../../../Lib/Fade/Fade.h"

#define ENDWAIT_COUNT (120)//死亡後の待機時間


//状態遷移
enum tagGameScene {
	GAMESCENE_INIT,		//初期化
	GAMESCENE_LOAD,	//データロード
	GAMESCENE_START,	//ゲーム開始前
	GAMESCENE_MAIN,		//メイン処理
	GAMESCENE_ENDWAIT,	//終了前の処理
	GAMESCENE_END,		//終了処理
};


//ゲーム中の状態遷移を管理する構造体
typedef struct {

	tagGameScene m_state;
	int m_waitCount;//待機時間カウント
	int m_soundhndl;

}GAME_SCENE;

static GAME_SCENE g_gamescene = { GAMESCENE_INIT,0,-1 };
extern PLAYER_DATA g_player;
extern Shot g_plshot[PLSHOT_MAX];
extern TIME g_timer;
extern ResultData g_result;

int StepGame() {

	int ret = 0;

	//ゲーム本編の状態遷移

	switch (g_gamescene.m_state)
	{
	case GAMESCENE_INIT:
		//初期化
		InitPlayer();
		InitStage();
		InitEffect();
		InitEnemy();
		InitScore();
		InitCoin();
		InitTime();
		InitArrow();
		InitBG();
		InitBlock();

		for (int i = 0; i < PLSHOT_MAX; i++)
		{
			g_plshot[i].Init();
		}
		
		g_gamescene.m_soundhndl = -1;

		g_gamescene.m_state = GAMESCENE_LOAD;
		break;
	case GAMESCENE_LOAD:
		//データロード
		LoadPlayer();
		LoadStage();
		LoadEffect();
		LoadEnemy();
		LoadScore();
		LoadCoin();
		LoadTime();
		LoadArrow();
		LoadBG();
		LoadBlock();


		for (int i = 0; i < PLSHOT_MAX; i++)
		{
			g_plshot[i].Load();
		}
		
		if (g_gamescene.m_soundhndl == -1)
		{
			g_gamescene.m_soundhndl = LoadSoundMem("Data/Sounds/bgm00.mp3");
		}


		//フェード呼び出し
		RequestFadeIn();

		//PlaySoundMem(g_gamescene.m_soundhndl, DX_PLAYTYPE_LOOP);

		g_gamescene.m_state = GAMESCENE_START;
		
		break;
	case GAMESCENE_START:
		
		//フェードインが終わったら本編へ
		if (IsEndFadeIn())
		{
			//PlaySoundMem(g_gamescene.m_soundhndl, DX_PLAYTYPE_LOOP);

			g_gamescene.m_state = GAMESCENE_MAIN;
		}

		break;
	case GAMESCENE_MAIN:
		//更新処理
		StepPlayer();
		StepEnemy();
		for (int i = 0; i < PLSHOT_MAX; i++)
		{
			if (!g_plshot[i].m_isActiv)continue;

			if (!g_plshot[i].m_moveflag)
			{
				if (IsKeyInput(KEY_SHOT) == 1) {
					
					if (g_player.m_moveflag)
					{
						plshotmove(i, g_player.m_pos, g_plshot[i].m_pos);
					}
				}
				else {
					if (IsKeyInput(KEY_ATTACK) == 1) {
						g_player.plshotmove = { 0 };
					}
					g_plshot[i].m_isActiv = false;
					g_player.m_moveflag = false;
				}
			}
			if (IsKeyInput(KEY_SHOT) == 1)
			{
				if (g_plshot[i].m_moveflag)
				{
					g_plshot[i].Step();
				}
			}
		}


		
		Time();
		UpdateStage();
		StepEffect();
		StepScore();
		StepCoin();
		StepARROW();
		StepBG();
		UpdateBlock();


		//当たり判定処理
		
		HitCheckPlayerToStage();
		HitCheckPlShotToStage();
		HitCheckEnemyToStage();
		HitCheckPlShotToStage_2();
		HitCheckPlayerToCoin();
		HitCheckPlshotToCoin();
		HitCheckPlayerToMagma();
		HitCheckPlshotToWhite();
		HitCheckPlayerToWhite();
		HitCheckPlshotToRed();
		HitCheckPlayerToBlue();
		HitCheckPlshotToBlue();
		HitCheckPlayerToGoal();
		HitCheckPlayerToSetti();
		HitCheckPlshotToSetti();
		HitCheckPlayerToRed();

	//	HitCheckWireToStage();
		
	

		//if (g_player.m_mode != 1)
		//{
			for (int i = 0; i < PLSHOT_MAX; i++)
			{
				if (IsKeyInput(KEY_SHOT) == 0)
				{
					if (g_player.seiseicapa > 0)
					{
						HitCheckPlShotToSpace();
					//	g_player.seiseicapa--;
					}
					else
					{
						g_plshot[i].m_isActiv = false;
					}
				}
			}
		//}
		

		if (g_player.goalflag)
		{

			g_result.conma = g_timer.m_cnt;
			g_result.seconds = g_timer.m_seconds;
			g_result.minutes = g_timer.m_minutes;
			
			g_gamescene.m_state = GAMESCENE_ENDWAIT;

			break;
		}


		if (g_player.dead_flag)
		{
			PlaySoundMem(g_player.damagesound, DX_PLAYTYPE_BACK);
			
			g_player.plshotmove.x = 0;
			g_player.plshotmove.y = 0;

			g_player.m_pos.x = g_player.checkpoint.x;
			g_player.m_pos.y = g_player.checkpoint.y;
			g_player.dead_flag = false;
		}

		g_gamescene.m_waitCount = ENDWAIT_COUNT;
		g_gamescene.m_state = GAMESCENE_START;

		break;
	case GAMESCENE_ENDWAIT:

		g_gamescene.m_waitCount--;
		if (g_gamescene.m_waitCount <= 0)
		{
			g_gamescene.m_state = GAMESCENE_END;
		}

		break;
	case GAMESCENE_END:

		ExitPlayer();
		ExitStage();
		ExitEffect();
		ExitEnemy();
		ExitScore();
		ExitCoin();
		ExitTime();
		ExitBG();
		ExitBlock();

		//if (g_gamescene.m_soundhndl != -1)
		//{
		//	DeleteSoundMem(g_gamescene.m_soundhndl);//音楽データ削除

		//	g_gamescene.m_soundhndl = -1;
		//}


		g_gamescene.m_state = GAMESCENE_INIT;
		ret = 1;
		break;
	default:
		break;
	}

	return ret;
}

void DrawGame() {


	switch (g_gamescene.m_state)
	{
	case GAMESCENE_START:
	case GAMESCENE_MAIN:
	case GAMESCENE_ENDWAIT:
		//描画
		

	
		DrawPlayer();
		for (int i = 0; i < PLSHOT_MAX; i++)
		{
			if (!g_plshot[i].m_isActiv)continue;
			g_plshot[i].Draw();
			plshotline(i);
		}
		

		DrawEffect();
		DrawEnemy();
		DrawStage();
		DrawScore();
		DrawCoin();
		
		DrawCanma();
		DrawConma();
		DrawSeconds();
		DrawMinutets();

		DrawArrow(g_player.m_pos);
		DrawBG();
		DrawBlock();



		break;
	}
}
