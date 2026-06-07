#pragma once
#include<DxLib.h>
// アイテム構造体
typedef struct {
	int m_hndl;		//画像ハンドル
	int m_isActive;	//生存フラグ
	VECTOR m_pos;	//表示位置を保存
}ItemCraft_DATA;

//Itemデータ初期化関数
void InitItemCraft(int Stagenum);

//Itemデータ読み込み関数
void LoadItemCraft();

//Itemデータ更新関数
void StepItemCraft();

//Itemデータ表示関数
void DrawItemCraft();

//終了前の処理関数
void ExitItemCraft();
