#include<DxLib.h>


//定義関連
#define WINDOW_SIZE_X (900.0f)	//ウィンドウのサイズ（横）
#define WINDOW_SIZE_Y (600.0f)	//ウィンドウのサイズ（縦）
#define MOVE_SPEED (3)
// 背景画像表示用構造体
typedef struct {
	int m_hndl;		//画像ハンドル
	VECTOR m_pos;	//表示位置を保存
}BG_DATA;

//実際に使用するデータはこちら
static BG_DATA g_bg = { 0 };

//背景データ初期化関数
void InitBG()
{
	//画像をロードしていないという意味で-1を入れる
	g_bg.m_hndl = -1;

	g_bg.m_pos.x = WINDOW_SIZE_X * 0.5f;
	g_bg.m_pos.y = WINDOW_SIZE_Y * 0.5f;
}

//		背景データ読み込み関数
void LoadBG()
{
	if (g_bg.m_hndl == -1)
	{
		g_bg.m_hndl = LoadGraph("Data/Textures/背景.png");
	}
}
//背景データ更新関数
void StepBG() {
	//背景を下に移動させる
	g_bg.m_pos.y += MOVE_SPEED;

	//画像が最初の場所まで移動したら、最初の位置に戻す
	if (g_bg.m_pos.y >= WINDOW_SIZE_Y * 0.5f + WINDOW_SIZE_Y)
	{
		g_bg.m_pos.y = WINDOW_SIZE_Y * 0.5;
	}

}
//背景データ表示関数
void DrawBG()
{

	//	画像描画　第１、２引数は画像の位置、第3引数は拡大縮小率、第４引数は回転率（ラジアン角指定）
	DrawRotaGraph((int)g_bg.m_pos.x, (int)g_bg.m_pos.y, 1.0, 0.0, g_bg.m_hndl, TRUE);
	DrawRotaGraph((int)g_bg.m_pos.x, (int)(g_bg.m_pos.y - WINDOW_SIZE_Y), 1.0, 0.0, g_bg.m_hndl, TRUE);
}
//		終了前の処理関数
void ExitBG()
{
	//画像がロードされているようであれば、画像を破棄する
	if (g_bg.m_hndl != -1)
	{
		DeleteGraph(g_bg.m_hndl);
		//破棄した後はー１を入れることで未使用状態であると分かるようにする
		g_bg.m_hndl = -1;
	}

}