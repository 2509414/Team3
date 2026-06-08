#pragma once
//使用するボタンにビットを割り当てる
#define KEY_JUMP		(0b1)		//ジャンプ
#define KEY_DASH		(0b10)		//右ダッシュ
#define KEY_RIGHT		(0b100)		//右 
#define KEY_LEFT		(0b1000)	//左
#define KEY_LDASH		(0b10000)	//左ダッシュ
#define KEY_KNIFE		(0b100000)	//ナイフ
#define KNIFE_SHOT		(0b1000000)	//ボムショット
#define KEY_ITEMCRAFT	(0b10000000)	//アイテムクラフト
#define KEY_DASH2		(0b100000000)		//右ダッシュ
#define KEY_RIGHT2		(0b1000000000)		//右 
#define KEY_LEFT2		(0b10000000000)		//左
#define KEY_LDASH2		(0b100000000000)	//左ダッシュ
#define KEY_KNIFE2		(0b1000000000000)	//ナイフショット
#define KEY_JUMP2		(0b10000000000000)		//ジャンプ

//===============================
// キー入力関連のやつ
// ==============================
// 
//キー入力判定（通常判定）
int IsKeyInput(unsigned int key);
//キー入力判定（トリガー判定）
int IsKeyInputTrg(unsigned int key);
//キー入力更新
void UpdateKeyInput();

//===============================
// マウス入力関連のやつ
// ==============================

//右クリックされているかチェック
bool IsMouseRightClick();

//左クリックされているかチェック
bool IsMouseLeftClick();

//現在のマウスのX座標を取得
int GetMouseX();

//現在のマウスのY座標を取得
int GetMouseY();



