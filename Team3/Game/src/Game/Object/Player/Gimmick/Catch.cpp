#include"../../../../Comon.h"
#include"../../Stage/Stage.h"
#include"Catch.h"
#include"../../Player/Player.h"
#include"../../../../Lib/KeyInput/KeyInput.h"


#define CATCH_MOVE_CNT (1)
#define CATCH_MOVE_SPEED (1)




extern STAGE_DATA g_stage;
extern PLAYER_DATA g_player;
Mouse_Data catch_mouse;
Catch_Data g_catch;


void InitCatch() {

	for (int i = 0; i < STAGEID_NUM; i++)
	{
		g_catch.m_hndl[i] = -1;
	}
	g_catch.isActive = false;

	g_catch.on_off_flag =false;

	g_catch.m_nextPos = {0};
	g_catch.m_nowPos = {0};
	g_catch.m_count = 0;
}

void LoadCatch() {

	char graphName[][64] = {
		"Data/Textures/01.png", "Data/Textures/02.png"
	};
	for (int i = 0; i < STAGEID_NUM; i++)
	{
		g_catch.m_hndl[i] = LoadGraph(graphName[i]);
	}
}

void UpdateCatch() {

	if (IsKeyInputTrg(KEY_ATTACK) == 1)
	{
		g_catch.isActive = false;
	}

	if (g_catch.m_count <= 0 )
	{
		// 移動中で無い場合は今の位置と目的地が同じになる
		g_catch.m_nowPos = g_catch.m_nextPos;
		// こちらの場合は基本的に現在の位置がカーソルの位置となる
		g_catch.m_pos = catch_mouse.m_prepos;

		if (g_catch.m_pos.x != catch_mouse.m_posX || g_catch.m_pos.y != catch_mouse.m_posY)
		{
			// 移動時間をセット
			g_catch.m_count = CATCH_MOVE_CNT;
			
			g_catch.m_nextPos = catch_mouse.m_nowpos;
		}
	}
	// カウントが0より大きい時はカーソル移動中
	else
	{
		// カウントを減らす
		g_catch.m_count--;
		// 現在の位置と次の位置までの距離を求める
		VECTOR moveDist = { 0 };
		moveDist.x = (float)(g_catch.m_nextPos.x - g_catch.m_nowPos.x);
		moveDist.y  = (float)(g_catch.m_nextPos.y - g_catch.m_nowPos.y);
		// 求めた距離を移動するのにかかる時間で割ると、1カウントに必要な移動量が分かる
		moveDist.x /= CATCH_MOVE_CNT;
		moveDist.y /= CATCH_MOVE_CNT;

		// 先ほど求めた距離を、現在の位置に足す
		g_catch.m_pos.x += moveDist.x;
		g_catch.m_pos.y += moveDist.y;
	}

	

	catch_mouse.GetPos();










}

void DrawCatch() {


	catch_mouse.GetMouse();
	catch_mouse.MouseOffset();
	catch_mouse.Player_Mouse_Vector(g_player.m_pos);
	catch_mouse.Catch();

	/*catch_mouse.m_catch_len.x = (catch_mouse.m_catch.x + g_player.m_pos.x);
	catch_mouse.m_catch_len.y = (catch_mouse.m_catch.y + g_player.m_pos.y);

	VECTOR offsetPos = GetOffset();
	VECTOR drawPos = { 0 };
	drawPos.x = catch_mouse.m_catch_len.x - offsetPos.x;
	drawPos.y = catch_mouse.m_catch_len.y - offsetPos.y;*/

	if (g_catch.isActive)
	{
		DrawRotaGraph((int)/*drawPos.x*/g_catch.m_pos.x, (int)/*drawPos.y*/g_catch.m_pos.y, 1.0f, 0.0f,
			g_catch.m_hndl[g_catch.m_objnum], TRUE);
	}
}

void ExitCatch() {


	for (int i = 0; i < STAGEID_NUM; i++)
	{
		if (g_catch.m_hndl[i] != -1)
		{
			DeleteGraph(g_catch.m_hndl[i]);
		}
	}
}


void RequestCatch(int num ,VECTOR pos,int y,int x) {

	g_catch.m_objnum = num;
	g_catch.on_off_flag = true;
	g_catch.m_pos = pos;
	g_catch.isActive = true;
}






