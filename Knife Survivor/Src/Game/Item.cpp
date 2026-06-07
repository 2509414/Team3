#include<DxLib.h>
#include "../Lib/Input.h"
#include"Item.h"
#include "Player.h"

//定義関連
#define WINDOW_SIZE_X (900.0f)	//ウィンドウのサイズ（横）
#define WINDOW_SIZE_Y (600.0f)	//ウィンドウのサイズ（縦）
#define MOVE_SPEED (1)
#define MOVE_JUMPPW (-10)
#define GRAVITY (0.3f)

//実際に使用するデータはこちら
Item_DATA g_item = { 0 };

//アイテムデータ初期化関数
void InitItem(int Stagenum)
{
	if (Stagenum == 0)
	{
		//画像をロードしていないという意味で-1を入れる
		g_item.m_isActive = -1;
		g_item.m_hndl = -1;
		g_item.m_pos.x = 336; /*4750;*/
		g_item.m_pos.y = 390;
	}
	if (Stagenum == 1)
	{
		//画像をロードしていないという意味で-1を入れる
		g_item.m_isActive = -1;
		g_item.m_hndl = -1;
		g_item.m_pos.x = 4850;
		g_item.m_pos.y = 490;
	}
	
}

//		アイテムデータ読み込み関数
void LoadItem()
{
	if (g_item.m_hndl == -1)
	{
		g_item.m_hndl = LoadGraph("Data/Textures/ナイフボックス.png");
	}
}

//		アイテムデータ更新関数
void StepItem() {
	//アイテム移動処理
	//g_item.m_pos.x -= MOVE_SPEED;
}

//アイテムデータ表示関数
void DrawItem()
{
	
	if(g_item.m_isActive != 0)
	//画像描画　第１、２引数は画像の位置、第3引数は拡大縮小率、第４引数は回転率（ラジアン角指定）
	DrawRotaGraph((int)g_item.m_pos.x , (int)g_item.m_pos.y , 1.0, 0.0, g_item.m_hndl, TRUE);
}

//終了前の処理関数
void ExitItem()
{
	//画像がロードされているようであれば、画像を破棄する
	if (g_item.m_hndl != -1)
	{
		DeleteGraph(g_item.m_hndl);
		//破棄した後はー１を入れることで未使用状態であると分かるようにする
		g_item.m_hndl = -1;
	}
}