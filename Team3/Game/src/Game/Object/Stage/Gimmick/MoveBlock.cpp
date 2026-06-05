#include"MoveBlock.h"
#include"../../Player/Player.h"
#include"../../Stage/Stage.h"


#define BLOCK_MAX (1)
#define MOVE_SPEED (1.0f)

extern PLAYER_DATA g_player;
MOVEBLOCK g_moveblock[BLOCK_MAX];
extern STAGE_DATA g_stage;



void InitBlock() {

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		g_moveblock[i].graphhndl = -1;
		g_moveblock[i].is_Active = false;
		g_moveblock[i].m_pos = {0};
		g_moveblock[i].turnflag = false;
	}
}

void LoadBlock() {

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		g_moveblock[i].graphhndl = LoadDivGraph("Data/Textures/white.png", 1, 1, 1, 32, 32, g_moveblock[i].graph);
	}
}

void UpdateBlock()
{
	/*g_moveblock[0].m_pos.x = g_player.m_pos.x;
	g_moveblock[0].m_pos.y = g_player.m_pos.y;*/

	/*for (int y = 0; y < STAGE_Y; y++)
	{
		for (int x = 0; x < STAGE_Y; x++)
		{

			if (g_stage.m_stageData[y][x].m_state != STAGEID_START)continue;

			g_moveblock[0].StratPos = g_stage.m_stageData[y][x].m_pos;
		}
	}
	for (int y = 0; y < STAGE_Y; y++)
	{
		for (int x = 0; x < STAGE_Y; x++)
		{

			if (g_stage.m_stageData[y][x].m_state != STAGEID_END)continue;

			g_moveblock[0].StratPos = g_stage.m_stageData[y][x].m_pos;
		}
	}*/

	RequestMove(g_moveblock[0].StratPos, g_moveblock[0].EndPos,1);
}


void DrawBlock() {


	for (int i = 0; i < BLOCK_MAX; i++)
	{
		VECTOR offsetPos = GetOffset();
		VECTOR drawPos = { 0 };
		drawPos.x = g_moveblock[i].m_pos.x - offsetPos.x;
		drawPos.y = g_moveblock[i].m_pos.y - offsetPos.y;

		DrawRotaGraph(drawPos.x, drawPos.y, 1.0f, 0.0f, g_moveblock[i].graph[0], TRUE);
	}
	
}
void ExitBlock() {

	for (int i = 0; i < STAGEID_NUM; i++)
	{
		if (g_moveblock[i].graphhndl != -1)
		{
			DeleteGraph(g_moveblock[i].graphhndl);
		}
	}
}

void RequestMove(VECTOR StartPos, VECTOR EndPos, int num)
{

	if (g_moveblock[num].m_pos.x >= EndPos.x)g_moveblock[num].turnflag = true;
	else if (g_moveblock[num].m_pos.x >= EndPos.x)g_moveblock[num].turnflag = false;

	VECTOR dir;

	if (g_moveblock[num].turnflag == false)
	{
		dir.x = EndPos.x - g_moveblock[num].m_pos.x;
		dir.y = EndPos.y - g_moveblock[num].m_pos.y;
	}
	else if (g_moveblock[num].turnflag == true)
	{
		dir.x = StartPos.x - g_moveblock[num].m_pos.x;
		dir.y = StartPos.y - g_moveblock[num].m_pos.y;
	}
	
		//上記方向ベクトルの長さの2乗を計算
		float length = (dir.x * dir.x) + (dir.y * dir.y);
		//長さの２乗になっているので2乗を取っ払う
		length = sqrtf(length);

		//1を長さで割る
		length = 1.0f / length;
		//上の計算結果を方向ベクトルに掛け算する	
		dir.x *= length;
		dir.y *= length;
		//=========================================================================
	
	g_moveblock[num].Movevec.x += dir.x;
	g_moveblock[num].Movevec.y += dir.y;

	g_moveblock[num].m_pos.x += g_moveblock[num].Movevec.x * MOVE_SPEED;
	g_moveblock[num].m_pos.y += g_moveblock[num].Movevec.y * MOVE_SPEED;
}






