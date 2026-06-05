#include<DxLib.h>
#include"../../../Comon.h"
#include"../Player/Player.h"

//定義関連
#define MOVE_SPEED (4.0f);

//背景データに必要な構造体
typedef struct {
	int m_hndl;		//画像ハンドル
	VECTOR m_pos;	//表示位置を保存
}BG_DATA;

static BG_DATA g_bg = { 0 };
extern PLAYER_DATA g_player;


//		背景データ初期化関数
void InitBG()
{
	g_bg.m_hndl = -1;
	g_bg.m_pos.x = (STAGE_X*OBJECT_SIZE_X) * 0.5f;
	g_bg.m_pos.y = STAGE_Y*OBJECT_SIZE_Y;


	/*g_bg.m_pos.x = STAGE_X * OBJECT_SIZE_X;
	g_bg.m_pos.y = STAGE_Y * OBJECT_SIZE_Y;*/



}
//		背景データ読み込み
void LoadBG()
{
	if (g_bg.m_hndl == -1)
	{
		g_bg.m_hndl = LoadGraph("Data/Textures/background00.jpg");
	}

}
//		背景データ更新関数
void StepBG()
{

	////縦スクロール
	//g_bg.m_pos.y += MOVE_SPEED;

	//if (g_bg.m_pos.y == 720)
	//{
	//	g_bg.m_pos.y = WINDOW_SIZE_Y * 0.5f;
	//}


}
//		背景データ表示関数
void DrawBG()
{

	if (g_bg.m_hndl != -1){
	
		DrawRotaGraph((int)g_bg.m_pos.x, (int)g_bg.m_pos.y, 10000000.0, 0.0, g_bg.m_hndl, TRUE);
	}

}

//		終了前の処理関数
void ExitBG()
{
	//画像がロードされているようであれば、画像を破棄する
	if (g_bg.m_hndl != -1)
	{
		DeleteGraph(g_bg.m_hndl);
		//破棄した後は-1を入れることで未使用状態であると分かるようにする
		g_bg.m_hndl = -1;
	}
}