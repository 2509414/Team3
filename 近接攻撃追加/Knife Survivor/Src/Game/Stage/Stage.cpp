#include<DxLib.h>
#include "Stage.h"
#include "../Scene/SceneTitle.h"


Stage_DATA g_stageData;
extern TITLE_SCENE g_titleScene;
//画像のファイルパス
static const char MAP_CHIP_PATH[] = "Data/Textures/ステージアイテム素材.png";

//ステージデータのファイルパス
											//STAGE2(0)				//STAGEBOSS(1)				//STAGE1(2)
static const char STAGE_PATH[][256] = { "Data/Stages/stage.csv", "Data/Stages/stage2.csv","Data/Stages/stage3.csv"};

//初期化処理
void InitStage()
{
	for (int y = 0; y < STAGE_Y; y++)
	{
		for (int x = 0; x < STAGE_X; x++)
		{
			g_stageData.m_stageData[y][x].m_state = -1;
			g_stageData.m_BlockTimer[y][x] = 0;
			g_stageData.m_stageData[y][x].m_pos.x = (float)(OBJECT_SIZE_X / 2 + OBJECT_SIZE_X * x);
			g_stageData.m_stageData[y][x].m_pos.y = (float)(OBJECT_SIZE_Y / 2 + OBJECT_SIZE_Y * y);
		}
	}

	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			g_stageData.m_mapData[i][j] = 0;
		}
	}
	for (int i = 0; i < MAP_CHIP_X * MAP_CHIP_Y; i++)
	{
		g_stageData.m_hndl[i] = -1;
	}
}
//終了処理
void ExitStage()
{
	// 画像データの破棄
	for (int i = 0; i < MAP_CHIP_X * MAP_CHIP_Y; i++)
	{
		if (g_stageData.m_hndl[i] != -1)
		{
			DeleteGraph(g_stageData.m_hndl[i]);
			g_stageData.m_hndl[i] = -1;
		}
	}
}

//マップチップ画像読み込み
void LoadStageGraph()
{
	int ret = LoadDivGraph(MAP_CHIP_PATH, MAP_CHIP_X * MAP_CHIP_Y, MAP_CHIP_X, MAP_CHIP_Y, MAP_CHIP_SIZE, MAP_CHIP_SIZE, g_stageData.m_hndl);
}

//ステージデータの読み込み
void LoadStageData(int Stagenum)
{
	FILE* fp;
	// 失敗したら強制終了
	if (fopen_s(&fp, STAGE_PATH[Stagenum], "rb") != 0) return;

	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			// 数字1個+「,」をまとめて取得
			fscanf_s(fp, "%d,", &g_stageData.m_mapData[i][j]);
		}
	}
	fclose(fp);
}

//	ステージの描画
void DrawStage()
{
	for (int y = 0; y < STAGE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			
			VECTOR drawPos;

			drawPos.x = g_stageData.m_stageData[y][x].m_pos.x;
			drawPos.y = g_stageData.m_stageData[y][x].m_pos.y;
			int useID = g_stageData.m_mapData[y][x];
			int useHndl = g_stageData.m_hndl[useID];
				DrawRotaGraph((int)drawPos.x, (int)drawPos.y, 1.0f, 0.0f,
					useHndl, TRUE);


			//// 本来は必要ない処理だけど分かりやすいように
			//// 二次元配列に格納された値を変数に入れる
			//int useID = g_stageData.m_mapData[y][x];
			//// さらにそこから使用する画像ハンドルを探し出す
			//int useHndl = g_stageData.m_hndl[useID];

			//// 指定された画像を描画
			//DrawGraph(MAP_CHIP_SIZE * x, MAP_CHIP_SIZE * y, useHndl, TRUE);
		}
	}
}

//ステージ更新処理
void UpdateStage()
{
	for (int y = 0; y < STAGE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			if (g_stageData.m_BlockTimer[y][x] > 0)
			{
				g_stageData.m_BlockTimer[y][x]--;

				if (g_stageData.m_BlockTimer[y][x] == 0)
				{
					g_stageData.m_mapData[y][x] = -1;
				}
			}
		}
	}
}