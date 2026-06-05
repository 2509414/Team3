#include"../../../../Comon.h"
#include"../../Stage/Stage.h"
#include"Zip.h"
#include"../../Player/Player.h"
#include"../../../../Lib/KeyInput/KeyInput.h"
#include"../../Player/Gimmick/Plshot.h"


#define Zip_MOVE_CNT (1)
#define Zip_MOVE_SPEED (1)


extern STAGE_DATA g_stage;
extern PLAYER_DATA g_player;
extern Shot g_plshot[PLSHOT_MAX];
Mouse_Data Zip_mouse;
Zip_Data g_Zip;


void InitZip() {

	g_Zip.m_hndl = -1;
	g_Zip.isActive = false;
	g_Zip.m_nextPos = { 0 };
	g_Zip.m_nowPos = { 0 };
	g_Zip.m_count = 0;
}

void UpdateZip() {
	
}

void DrawZip() {


	
}

void ExitZip() {

	
}


void RequestZip(VECTOR pos_1,VECTOR pos_2) {

	
}



