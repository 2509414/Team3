#include"Plshot.h"
#include"../../../../Comon.h"
#include"../Player.h"
#include"../../../Hitcheck/Hitcheck.h"

#define PLSHOT_SPEED (30.0f)

Shot g_plshot[PLSHOT_MAX];
Shot g_plshot_2[PLSHOT_MAX];
Mouse_Data g_mouse_plshot;

extern PLAYER_DATA g_player;


void RequestPLShot(VECTOR pos) {

	VECTOR offsetpos = GetOffset();
	VECTOR dir;
	VECTOR drawshotpos;
	
	for (int i = 0; i < PLSHOT_MAX; i++)
	{
		if (g_plshot[i].m_isActiv)continue;


		drawshotpos.x = g_plshot[i].m_pos.x + offsetpos.x;
		drawshotpos.y = g_plshot[i].m_pos.y + offsetpos.y;

		dir.x = drawshotpos.x - g_player.m_pos.x;
		dir.y = drawshotpos.y - g_player.m_pos.y;
		//上記方向ベクトルの長さの2乗を計算
		float length = (dir.x * dir.x) + (dir.y * dir.y);
		//長さの２乗になっているので2乗を取っ払う
		length = sqrtf(length);
		if (length > 10) {
			g_plshot[i].m_isActiv = false;
			g_player.m_moveflag = false;
		}
		g_plshot[i].m_moveflag = true;
		g_plshot[i].m_isActiv = true;
		g_plshot[i].m_pos = pos;
		g_plshot[i].m_speed = PLSHOT_SPEED;
		
		g_mouse_plshot.GetMouse();
		g_mouse_plshot.MouseOffset();
		g_mouse_plshot.Player_Mouse_Vector(pos);

		g_plshot[i].m_angle = g_mouse_plshot.Angle(pos);

		g_plshot[i].m_pow = g_mouse_plshot.m_len;

		break;
	}
}


void RequestPLShot_2(VECTOR pos) {

	VECTOR offsetpos = GetOffset();
	VECTOR dir;

	for (int i = 0; i < PLSHOT_MAX; i++)
	{
		if (g_plshot_2[i].m_isActiv)continue;


		dir.x = g_plshot_2[i].m_pos.x - g_player.m_pos.x;
		dir.y = g_plshot_2[i].m_pos.y - g_player.m_pos.y;
		dir.z = g_plshot_2[i].m_pos.z - g_player.m_pos.z;

		//上記方向ベクトルの長さの2乗を計算
		float length = (dir.x * dir.x) + (dir.y * dir.y);
		//長さの２乗になっているので2乗を取っ払う
		length = sqrtf(length);
		if (length > 10)g_plshot_2[i].m_isActiv = false;



		g_plshot_2[i].m_moveflag = true;
		g_plshot_2[i].m_isActiv = true;
		g_plshot_2[i].m_pos = pos;
		g_plshot_2[i].m_speed = PLSHOT_SPEED;

		g_mouse_plshot.GetMouse();
		g_mouse_plshot.MouseOffset();
		g_mouse_plshot.Player_Mouse_Vector(pos);

		g_plshot_2[i].m_angle = g_mouse_plshot.Angle(pos);

		g_plshot_2[i].m_pow = g_mouse_plshot.m_len;

		break;
	}
}



