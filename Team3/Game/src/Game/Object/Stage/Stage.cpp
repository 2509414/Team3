#include <stdio.h>
#include "Stage.h"
#include "../../../Comon.h"
#include "../../Object/Player/Player.h"
#include"../../Timer/Timer.h"
#include"../Player/Player.h"

STAGE_DATA g_stage = { 0 };
extern PLAYER_DATA g_player;
extern TIME g_timer;



//-------------------------------
//		ステージ初期化
//-------------------------------
void InitStage()
{
	// ステージデータ関連
	for (int y = 0; y < STAGE_Y; y++)
	{
		for (int x = 0; x < STAGE_X; x++)
		{
			g_stage.m_stageData[y][x].m_state = -1;
			g_stage.m_stageData[y][x].m_pos.x = (float)(OBJECT_SIZE_X / 2 + OBJECT_SIZE_X * x);
			g_stage.m_stageData[y][x].m_pos.y = (float)(OBJECT_SIZE_Y / 2 + OBJECT_SIZE_Y * y);
		}
	}

	// 画像関連
	for (int i = 0; i < STAGEID_NUM; i++)
	{
		g_stage.m_graphHndl[i] = -1;
	}
	for (int  i = 0; i < ANIM_NUM; i++)
	{
		g_stage.m_animHndl[i] = -1;
	}

	g_stage.m_magma_cnt = 0;
	
}


//-------------------------------
//		ステージロード
//-------------------------------
void LoadStage()
{
	// ステージデータ------------------------------------------
	FILE* fp;
	if (fopen_s(&fp, "Data/Stages/stage001.csv", "r") != 0) return;

	for (int y = 0; y < STAGE_Y; y++)
	{
		for (int x = 0; x < STAGE_X; x++)
		{
			if (fscanf_s(fp, "%d", &g_stage.m_stageData[y][x].m_state) == 0)
			{
				////コインランダム配置
				//if ((GetRand(50)/2)==0)
				//{
				//	g_stage.m_stageData[y][x].m_state = 2;
				//}
				//else
				//{
				//	g_stage.m_stageData[y][x].m_state = -1;
				//}


				////赤ランダム配置
				//if ((GetRand(100)/2)==0)
				//{
				//	g_stage.m_stageData[y][x].m_state = 5;
				//}
				////青ランダム配置
				//else if ((GetRand(100) / 2) == 0)
				//{
				//	g_stage.m_stageData[y][x].m_state = 6;
				//}
				//else
				//{
				//	g_stage.m_stageData[y][x].m_state = -1;
				//}


			}
			fgetc(fp);
		}
	}
	fclose(fp);

	
		

	//---------------------------------------------------------

	// 画像関連------------------------------------------------
	//g_stage.m_graphHndl[0] = LoadDivGraph("Data/Textures/white.png", 1, 1, 1, 32, 32, g_stage.m_white);
	g_stage.m_graphHndl[0] = LoadGraph("Data/Textures/01.png");
	g_stage.m_graphHndl[1] = LoadGraph("Data/Textures/02.png");
	g_stage.m_graphHndl[2] = LoadDivGraph("Data/Textures/Coin.png", ANIM_NUM, X_NUM, Y_NUM, X_SIZE, Y_SIZE, g_stage.m_animHndl);
	g_stage.m_graphHndl[3] = LoadDivGraph("Data/Textures/magma.png", 1,1,1, 32,32,g_stage.m_magma );
	g_stage.m_graphHndl[4] = LoadDivGraph("Data/Textures/white.png", 1, 1, 1, 32, 32, g_stage.m_white);
	g_stage.m_graphHndl[5] = LoadDivGraph("Data/Textures/red.jpg", 1, 1, 1, 32, 32, g_stage.m_red);
	g_stage.m_graphHndl[6] = LoadDivGraph("Data/Textures/blue.png", 1, 1, 1, 32, 32, g_stage.m_blue);
	g_stage.m_graphHndl[7] = LoadGraph("Data/Textures/02.png");
	//---------------------------------------------------------
}

//-------------------------------
//		ステージ更新
//-------------------------------
void UpdateStage(){

	for (int y = 0; y < STAGE_Y; y++)
	{
		for (int x = 0; x < STAGE_X; x++)
		{
			if (g_stage.m_stageData[y][x].m_state == -1) continue;


			if (g_stage.m_stageData[y][x].m_state == STAGEID_GOAL)
			{
				g_player.goalpos = g_stage.m_stageData[y][x].m_pos.y;
			}


			//カウントを一つずつ増やす　　
			g_stage.m_stageData[y][x].m_animCnt += ANIM_SPEED;

			if (g_stage.m_stageData[y][x].m_animCnt >= ANIM_NUM)
			{
				g_stage.m_stageData[y][x].m_animCnt = 0;
			}
		}
	}



	g_stage.m_cnt++;

	if ((g_stage.m_cnt % 100) == 0)
	{
		g_stage.m_cnt = 0;

		for(int y = 0; y < STAGE_Y; y++)
		{
			for (int x = 0; x < STAGE_X; x++)
			{
				if (g_stage.m_stageData[y][x].m_state != STAGEID_BLUE && g_stage.m_stageData[y][x].m_state != STAGEID_RED  ) continue;

				if (g_stage.m_stageData[y][x].m_state == STAGEID_BLUE)
				{
					g_stage.m_stageData[y][x].m_state = STAGEID_RED;
					continue;
				}

				if (g_stage.m_stageData[y][x].m_state == STAGEID_RED)
				{
					g_stage.m_stageData[y][x].m_state = STAGEID_BLUE;
					continue;
				}
			}
		}
	}

	/*if ((Time() % 30) == 0)
	{
		for (int x = 0; x < STAGE_X; x++)
		{
			if (g_stage.m_stageData[STAGE_Y - g_stage.m_magma_cnt][x].m_state == 0&&
				g_stage.m_stageData[STAGE_Y - g_stage.m_magma_cnt][x].m_state == 3) continue;

			g_stage.m_stageData[STAGE_Y - g_stage.m_magma_cnt][x].m_state = 3;
		}

		g_stage.m_magma_cnt++;
	}*/


}

//-------------------------------
//		ステージ描画
//-------------------------------
void DrawStage()
{
	for (int y = 0; y < STAGE_Y; y++)
	{
		for (int x = 0; x < STAGE_X; x++)
		{
			if (g_stage.m_stageData[y][x].m_state == -1) continue;
			VECTOR offsetPos = GetOffset();
			VECTOR drawPos = {0};
			drawPos.x = g_stage.m_stageData[y][x].m_pos.x -offsetPos.x;
			drawPos.y = g_stage.m_stageData[y][x].m_pos.y -offsetPos.y;

			int animNum = g_stage.m_stageData[y][x].m_animCnt;

			if (g_stage.m_stageData[y][x].m_state == STAGEID_COIN)
			{
				DrawRotaGraph((int)drawPos.x, (int)drawPos.y, 0.5f, 0.0f,
					g_stage.m_animHndl[animNum], TRUE);

				//UIコイン
				DrawRotaGraph(20, 100, 1.0f, 0.0f,
					g_stage.m_animHndl[animNum], TRUE);

				continue;
			}

			/*if (g_stage.m_stageData[y][x].m_state == STAGEID_BLOCK)
			{
				DrawRotaGraph((int)drawPos.x, (int)drawPos.y, 1.0f, 0.0f,
					g_stage.m_white[0], TRUE);

				continue;
			}*/

			if (g_stage.m_stageData[y][x].m_state == STAGEID_MAGMA)
			{
				DrawRotaGraph((int)drawPos.x, (int)drawPos.y, 1.0f, 0.0f,
					g_stage.m_red[0], TRUE);

				continue;
			}

			if (g_stage.m_stageData[y][x].m_state == STAGEID_WHITE)
			{
				DrawRotaGraph((int)drawPos.x, (int)drawPos.y, 1.0f, 0.0f,
					g_stage.m_white[0], TRUE);

				continue;
			}

			if (g_stage.m_stageData[y][x].m_state == STAGEID_RED)
			{
				DrawRotaGraph((int)drawPos.x, (int)drawPos.y, 1.0f, 0.0f,
					g_stage.m_red[0], TRUE);

				continue;
			}

			if (g_stage.m_stageData[y][x].m_state == STAGEID_BLUE)
			{
				DrawRotaGraph((int)drawPos.x, (int)drawPos.y, 1.0f, 0.0f,
					g_stage.m_blue[0], TRUE);

				continue;
			}


			if (g_stage.m_stageData[y][x].m_state == STAGEID_SETTI)
			{
				DrawRotaGraph((int)drawPos.x, (int)drawPos.y, 1.0f, 0.0f,
					g_stage.m_white[0], TRUE);

				continue;
			}

			if (g_stage.m_stageData[y][x].m_state == STAGEID_START)continue;
			if (g_stage.m_stageData[y][x].m_state == STAGEID_END)continue;



			DrawRotaGraph((int)drawPos.x, (int)drawPos.y, 1.0f, 0.0f,
				g_stage.m_graphHndl[g_stage.m_stageData[y][x].m_state], TRUE);
		}
	}
}


//-------------------------------
//		ステージ破棄
//-------------------------------
void ExitStage(void)
{
	for (int i = 0; i < STAGEID_NUM; i++)
	{
		if (g_stage.m_graphHndl[i] != -1)
		{
			DeleteGraph(g_stage.m_graphHndl[i]);
		}
	}
}