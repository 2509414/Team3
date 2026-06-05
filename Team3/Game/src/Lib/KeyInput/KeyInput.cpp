#include <DxLib.h>
#include "KeyInput.h"

//キーボード入力情報構造体

typedef struct {

	unsigned int m_nowKey;	//今回入力したキー情報
	unsigned int m_preKey;
}INPUT_DATA;

static INPUT_DATA g_inputData = { 0 };

//指定されたキーを入力しているか
bool IsKeyInput(unsigned int key) {
	if (g_inputData.m_nowKey & key) return true;
	else return false;
}

//指定されたキーを入力しているか（トリガー判定）
bool IsKeyInputTrg(unsigned int key)
{
	if (((g_inputData.m_nowKey & key) != 0) && ((g_inputData.m_preKey & key) == 0))
	{
		return true;
	}
	else return false;
}





//-------------------------
//		キー入力更新
//-------------------------

void UpdateKeyInput() {

	//前回のデータ更新
	g_inputData.m_preKey = g_inputData.m_nowKey;
	//１度データを０にする
	g_inputData.m_nowKey = 0;

	//自分が調べたいボタンが押されていたらビットを立てていく

	//上を押した
	if (CheckHitKey(KEY_INPUT_UP))g_inputData.m_nowKey |= KEY_UP;

	//下を押した
	if (CheckHitKey(KEY_INPUT_DOWN))g_inputData.m_nowKey |= KEY_DOWN;

	//右を押した
	if (CheckHitKey(KEY_INPUT_RIGHT))g_inputData.m_nowKey |= KEY_RIGHT;

	//左を押した
	if (CheckHitKey(KEY_INPUT_LEFT))g_inputData.m_nowKey |= KEY_LEFT;

	//Wを押した
	//if (CheckHitKey(KEY_INPUT_W))g_inputData.m_nowKey |= KEY_W;

	//Sを押した
	if (CheckHitKey(KEY_INPUT_S))g_inputData.m_nowKey |= KEY_S;

	//Dを押した
	if (CheckHitKey(KEY_INPUT_D))g_inputData.m_nowKey |= KEY_D;

	//Aを押した
	if (CheckHitKey(KEY_INPUT_A))g_inputData.m_nowKey |= KEY_A;

	//スペースキーを押した
	if (CheckHitKey(KEY_INPUT_SPACE))g_inputData.m_nowKey |= KEY_JUMP;

	//Wを押した
	if (CheckHitKey(KEY_INPUT_W))g_inputData.m_nowKey |= KEY_GIRT;

	//左クリックを押した
	if (GetMouseInput() & MOUSE_INPUT_LEFT) g_inputData.m_nowKey |= KEY_SHOT;

	//右クリックを押した
	if (GetMouseInput() & MOUSE_INPUT_RIGHT) g_inputData.m_nowKey |= KEY_ATTACK;


	//Wを押した
	if (CheckHitKey(KEY_INPUT_R))g_inputData.m_nowKey |= KEY_RE;
}