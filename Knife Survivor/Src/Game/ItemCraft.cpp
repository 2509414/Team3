#include<DxLib.h>
#include "../Lib/Input.h"
#include"ItemCraft.h"
#include "Player.h"
#include "Stage.h"

//定義関連
#define WINDOW_SIZE_X (900.0f)	//ウィンドウのサイズ（横）
#define WINDOW_SIZE_Y (600.0f)	//ウィンドウのサイズ（縦）
#define MOVE_SPEED (1)
#define MOVE_JUMPPW (-10)
#define GRAVITY (0.3f)

//実際に使用するデータはこちら
ItemCraft_DATA g_itemcraft = { 0 };

//アイテムデータ初期化関数
void InitItemCraft(int Stagenum)
{
	if (Stagenum == 0)
	{
		//画像をロードしていないという意味で-1を入れる
		g_itemcraft.m_isActive = -1;
		g_itemcraft.m_hndl = -1;
		g_itemcraft.m_pos.x = 3100; /*4750;*/
		g_itemcraft.m_pos.y = 500;
	}
	if (Stagenum == 1)
	{
		g_itemcraft.m_isActive = -1;
		g_itemcraft.m_hndl = -1;
		g_itemcraft.m_pos.x = 4900;
		g_itemcraft.m_pos.y = 490;
	}

	if (Stagenum == 2)
	{
		g_itemcraft.m_isActive = -1;
		g_itemcraft.m_hndl = -1;
		g_itemcraft.m_pos.x = 230;
		g_itemcraft.m_pos.y = 310;
	}

}

//		アイテムデータ読み込み関数
void LoadItemCraft()
{
	if (g_itemcraft.m_hndl == -1)
	{
		g_itemcraft.m_hndl = LoadGraph("Data/Textures/アイテムボックス.png");
	}
}

//		アイテムデータ更新関数
void StepItemCraft() {
	//アイテム移動処理
	//g_itemcraft.m_pos.x -= MOVE_SPEED;
}

//アイテムデータ表示関数
void DrawItemCraft()
{
	
	if(g_itemcraft.m_isActive != 0)
	//画像描画　第１、２引数は画像の位置、第3引数は拡大縮小率、第４引数は回転率（ラジアン角指定）
	DrawRotaGraph((int)g_itemcraft.m_pos.x, (int)g_itemcraft.m_pos.y, 1.0, 0.0, g_itemcraft.m_hndl, TRUE);
}

//終了前の処理関数
void ExitItemCraft()
{
	//画像がロードされているようであれば、画像を破棄する
	if (g_itemcraft.m_hndl != -1)
	{
		DeleteGraph(g_itemcraft.m_hndl);
		//破棄した後はー１を入れることで未使用状態であると分かるようにする
		g_itemcraft.m_hndl = -1;
	}
}
