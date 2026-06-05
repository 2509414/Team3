#pragma once

//使用するボタンにビットを割り当てる
//0bは二進数
#define KEY_UP		(0b1)		//上ボタン
#define KEY_DOWN	(0b10)		//下ボタン
#define KEY_RIGHT	(0b100)		//右ボタン
#define KEY_LEFT	(0b1000)	//左ボタン
#define KEY_SHOT	(0b10000)	//左クリック
#define KEY_JUMP	(0b100000)	//スペース
#define KEY_ATTACK	(0b1000000)	//右クリック
#define KEY_GIRT	(0b10000000)//左シフト
#define KEY_RE		(0b100000000)

#define KEY_W		(0b1000000000)	//Wボタン
#define KEY_S		(0b10000000000)	//Sボタン
#define KEY_D		(0b100000000000)	//Dボタン
#define KEY_A		(0b1000000000000)	//Aボタン


//キー入力更新
void UpdateKeyInput();

//キー入力判定（通常判定）
bool IsKeyInput(unsigned int key);

//キー入力判定（トリガー判定）
bool IsKeyInputTrg(unsigned int key);

