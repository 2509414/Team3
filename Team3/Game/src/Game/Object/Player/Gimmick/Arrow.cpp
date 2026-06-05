#include "Arrow.h"
#include"../../../../Comon.h"
#include"../Player.h"
#include"../../../Hitcheck/Hitcheck.h"
#include"../../../../Lib/KeyInput/KeyInput.h"


Arrow g_arrow;
Mouse_Data g_mouse_arrow;
extern PLAYER_DATA g_player;


 
#define ARROW_MAX (100)

//		矢印初期化関数
void InitArrow() {

	g_arrow.isActive = true;
	g_arrow.m_graphHndl = -1;
	g_arrow.m_moveflag = false;
}
//		矢印データ読み込み
void LoadArrow() {

	g_arrow.m_graphHndl = LoadGraph("Data/Textures/Arrow.png");
}
//		矢印データ更新関数
void StepARROW() {

	g_arrow.m_moveflag = true;

	g_arrow.m_pos = g_player.m_pos;

	g_mouse_arrow.GetMouse();
	g_mouse_arrow.MouseOffset();
	g_mouse_arrow.Player_Mouse_Vector(g_player.m_pos);
	g_arrow.m_angle = g_mouse_arrow.Angle(g_player.m_pos);


	/*g_arrow.m_pow.x = g_mouse_arrow.m_len.x;
	g_arrow.m_pow.y = g_mouse_arrow.m_len.y;*/


	/*g_arrow.m_len.x = g_arrow.m_pos.x - g_player.m_pos.x;
	g_arrow.m_len.y = g_arrow.m_pos.y - g_player.m_pos.y;*/

	
	/*while (g_arrow.m_moveflag)
	{
		if (IsKeyInput(KEY_SHOT) == true) {
			g_arrow.isActive = false;
			break;
		}
		else g_arrow.isActive = true;

		g_arrow.m_pos.x += g_arrow.m_pow.x;
		g_arrow.m_pos.y += g_arrow.m_pow.y;
		HitCheckArrowToStage();
		HitCheckArrowToBox();
	}*/

	

}
//		矢印データ表示関数
void DrawArrow(VECTOR Plpos) {

	VECTOR offsetPos = GetOffset();
	VECTOR drawPos_player, drawPos_arrow;
	drawPos_player.x = Plpos.x - offsetPos.x;
	drawPos_player.y = Plpos.y - offsetPos.y;

	//drawPos_arrow.x = g_arrow.m_pos.x - offsetPos.x;
	//drawPos_arrow.y = g_arrow.m_pos.y - offsetPos.y;

	drawPos_arrow.x = g_mouse_arrow.m_posX - offsetPos.x;
	drawPos_arrow.y = g_mouse_arrow.m_posY - offsetPos.y;


	/*DrawLine(drawPos_player.x, drawPos_player.y,
		drawPos_arrow.x, drawPos_arrow.y,
		GetColor(255, 255, 255), 3);*/

	/*if (g_arrow.isActive)
	{
		DrawRotaGraph(drawPos_arrow.x, drawPos_arrow.y, 0.3f, g_arrow.m_angle - 1.5f, g_arrow.m_graphHndl, TRUE);
	}*/
	
}

