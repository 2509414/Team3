#pragma once
#include<DxLib.h>
// アイテム構造体
typedef struct {
	int m_hndl;		//画像ハンドル
	int m_isActive;	//生存フラグ
	float enemySy;	//縦方向速度
	int groundY;	//地面
	int m_JpActive;	//ジャンプ生存フラグ
	VECTOR m_pos;	//表示位置を保存
}Item_DATA;

//Itemデータ初期化関数
void InitItem(int Stagenum);

//Itemデータ読み込み関数
void LoadItem();

//Itemデータ更新関数
void StepItem();

//Itemデータ表示関数
void DrawItem();

//終了前の処理関数
void ExitItem();