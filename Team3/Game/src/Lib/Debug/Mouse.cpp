	#include"Mouse.h"
	#include"../../Comon.h"

Mouse_Data g_mouse_debug;

//		マウスデータ表示関数
void DrawMouse() {

	g_mouse_debug.GetMouse();
	DrawFormatString(16, 32, GetColor(255, 255, 255),
		"マウスX:%d,マウスY:%d", g_mouse_debug.m_posX, g_mouse_debug.m_posY);

}
