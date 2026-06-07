#include <DxLib.h>
#include"Input.h"
#include "../Game/Player.h"
#include "../Game/Knife.h"
#include "../Game/Knife2.h"
//キーボード入力構造体
typedef struct {
	unsigned int m_nowKey;	//今回入力したキー
	unsigned int m_preKey;	//前回入力したキー
}INPUT_DATA;

static INPUT_DATA g_inputData = { 0 };

extern Knife Knife1;
extern Knife2 knife2;
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//			キー入力更新
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

void UpdateKeyInput()
{
	//前回のデータ更新
	g_inputData.m_preKey = g_inputData.m_nowKey;
	//一度データを0にする
	g_inputData.m_nowKey = 0;

	//Dを押した
	if (CheckHitKey(KEY_INPUT_D))g_inputData.m_nowKey |= KEY_RIGHT;

	//Aを押した
	if (CheckHitKey(KEY_INPUT_A))g_inputData.m_nowKey |= KEY_LEFT;

	//Sを押した
	if (CheckHitKey(KEY_INPUT_S))g_inputData.m_nowKey |= KEY_JUMP;

	//Dかつシフトを押した
	if (CheckHitKey(KEY_INPUT_D) && CheckHitKey(KEY_INPUT_LSHIFT))g_inputData.m_nowKey |= KEY_DASH;
	
	//Aかつシフトを押した
	if (CheckHitKey(KEY_INPUT_A) && CheckHitKey(KEY_INPUT_LSHIFT))g_inputData.m_nowKey |= KEY_LDASH;

	if (CheckHitKey(KEY_INPUT_W) && Knife1.m_isActive == false) g_inputData.m_nowKey |= KEY_KNIFE;
	
	if(IsMouseLeftClick() == true) g_inputData.m_nowKey |= KEY_ITEMCRAFT;


	//Lを押した
	if (CheckHitKey(KEY_INPUT_L))g_inputData.m_nowKey |= KEY_RIGHT2;

	//Jを押した
	if (CheckHitKey(KEY_INPUT_J))g_inputData.m_nowKey |= KEY_LEFT2;

	//Dかつシフトを押した
	if (CheckHitKey(KEY_INPUT_L) && CheckHitKey(KEY_INPUT_RSHIFT))g_inputData.m_nowKey |= KEY_DASH2;

	//Aかつシフトを押した
	if (CheckHitKey(KEY_INPUT_J) && CheckHitKey(KEY_INPUT_RSHIFT))g_inputData.m_nowKey |= KEY_LDASH2;

	//Kを押した
	if (CheckHitKey(KEY_INPUT_K))g_inputData.m_nowKey |= KEY_JUMP2;

	//Iを押した
	if (CheckHitKey(KEY_INPUT_I) && knife2.m_isActive == false) g_inputData.m_nowKey |= KEY_KNIFE2;
}

int IsKeyInput(unsigned int key)
{
	if (g_inputData.m_nowKey & key)return true;
	else return false;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//キー入力判定（トリガー判定）
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
int IsKeyInputTrg(unsigned int key)
{
	if ((g_inputData.m_nowKey & key)
		&& !(g_inputData.m_preKey & key)) return 1;
	else return 0;
}

//右クリックの判定
bool IsMouseRightClick()
{
	//右クリックが押されていたらtrue
	if (GetMouseInput() & MOUSE_INPUT_RIGHT)
	{
		return true;
	}

	//押されてなかったらfalseを返すよ
	return false;
}

//左クリックの判定
bool IsMouseLeftClick()
{
	//左クリックが押されていたらtrue
	if (GetMouseInput() & MOUSE_INPUT_LEFT)
	{
		return true;
	}

	//押されてなかったらfalseを返すよ
	return false;
}


//マウスのX座標を取得
int GetMouseX()
{
	int x, y;
	//x,yに現在のマウス座標を代入
	GetMousePoint(&x, &y);

	//xの座標をreturn
	return x;
}

//マウスのY座標を取得
int GetMouseY()
{
	int x, y;
	//x,yに現在のマウス座標を代入
	GetMousePoint(&x, &y);

	//yの座標をreturn
	return y;
}