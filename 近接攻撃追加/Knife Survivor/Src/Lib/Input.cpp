#include <DxLib.h>
#include"Input.h"
#include "../Game/Knife/Knife.h"
#include "../Game/Knife/Knife2.h"


//キーボード入力構造体
typedef struct {
	unsigned int m_nowKey;	//今回入力したキー
	unsigned int m_preKey;	//前回入力したキー
}INPUT_DATA;

XINPUT_STATE input;
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

	//1P===========================================================================
	GetJoypadXInputState(DX_INPUT_PAD1, &input);
	
	//Dを押したまたはコントローラーの右を押したら (右移動)
	if (CheckHitKey(KEY_INPUT_D)||input.Buttons[XINPUT_BUTTON_DPAD_RIGHT])g_inputData.m_nowKey |= KEY_RIGHT;

	//Aを押したまたはコントローラーの左を押したら (左移動)
	if (CheckHitKey(KEY_INPUT_A)||input.Buttons[XINPUT_BUTTON_DPAD_LEFT])g_inputData.m_nowKey |= KEY_LEFT;

	//Sを押した Aボタンを押した (ジャンプ)
	if (CheckHitKey(KEY_INPUT_S) || input.Buttons[XINPUT_BUTTON_A]) g_inputData.m_nowKey |= KEY_JUMP;

	//Dかつシフトを押した またはコントローラーの右を押したかつXボタンを押したら (ダッシュ)
	if (CheckHitKey(KEY_INPUT_D) && CheckHitKey(KEY_INPUT_LSHIFT)||
		input.Buttons[XINPUT_BUTTON_DPAD_RIGHT] && input.Buttons[XINPUT_BUTTON_X])g_inputData.m_nowKey |= KEY_DASH;
	
	//Aかつシフトを押した またはコントローラーの左を押したかつXボタンを押したら (ダッシュ)
	if (CheckHitKey(KEY_INPUT_A) && CheckHitKey(KEY_INPUT_LSHIFT) ||
		input.Buttons[XINPUT_BUTTON_DPAD_LEFT] && input.Buttons[XINPUT_BUTTON_X])g_inputData.m_nowKey |= KEY_LDASH;
	
	//Wかつナイフの生存フラグがfalse　またはコントローラーのRBを押したかつナイフの生存フラグがfalse (ナイフを投げる)
	if (CheckHitKey(KEY_INPUT_W) && Knife1.m_isActive == false ||
		input.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER] && Knife1.m_isActive == false) g_inputData.m_nowKey |= KEY_KNIFE;
	
	if(IsMouseLeftClick() == true) g_inputData.m_nowKey |= KEY_ITEMCRAFT;

	//Qキーを押した、コントローラのLBを押した（近接攻撃（仮））
	if (CheckHitKey(KEY_INPUT_Q) || input.Buttons[XINPUT_BUTTON_LEFT_SHOULDER]) g_inputData.m_nowKey |= KEY_ATTACK;
	


	//2P===========================================================================
	GetJoypadXInputState(DX_INPUT_PAD2, &input);

	//Lを押した またはコントローラーの右を押したら (右移動)
	if (CheckHitKey(KEY_INPUT_L) || input.Buttons[XINPUT_BUTTON_DPAD_RIGHT])g_inputData.m_nowKey |= KEY_RIGHT2;

	//Jを押した またはコントローラーの左を押したら (左移動)
	if (CheckHitKey(KEY_INPUT_J) || input.Buttons[XINPUT_BUTTON_DPAD_LEFT])g_inputData.m_nowKey |= KEY_LEFT2;

	//Dかつシフトを押した またはコントローラーの右を押したかつXボタンを押したら (ダッシュ)
	if (CheckHitKey(KEY_INPUT_L) && CheckHitKey(KEY_INPUT_RSHIFT) ||
		input.Buttons[XINPUT_BUTTON_DPAD_RIGHT] && input.Buttons[XINPUT_BUTTON_X])g_inputData.m_nowKey |= KEY_DASH2;

	//Aかつシフトを押した またはコントローラーの左を押したかつXボタンを押したら (ダッシュ)
	if (CheckHitKey(KEY_INPUT_J) && CheckHitKey(KEY_INPUT_RSHIFT)||
		input.Buttons[XINPUT_BUTTON_DPAD_LEFT] && input.Buttons[XINPUT_BUTTON_X])g_inputData.m_nowKey |= KEY_LDASH2;

	//Kを押した Aボタンを押した (ジャンプ)
	if (CheckHitKey(KEY_INPUT_K)||
		input.Buttons[XINPUT_BUTTON_A])g_inputData.m_nowKey |= KEY_JUMP2;

	//Iを押した またはコントローラーのRBを押したかつナイフの生存フラグがfalse (ナイフを投げる)
	if (CheckHitKey(KEY_INPUT_I) && knife2.m_isActive == false||
		input.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER] && Knife1.m_isActive == false) g_inputData.m_nowKey |= KEY_KNIFE2;

	//キーを押した、コントローラのLBを押した（近接攻撃（仮））
	if (CheckHitKey(KEY_INPUT_U) || input.Buttons[XINPUT_BUTTON_LEFT_SHOULDER]) g_inputData.m_nowKey |= KEY_ATTACK2;


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
