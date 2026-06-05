#pragma once
#include"../../../../Comon.h"
#include<DxLib.h>


struct Zip_Data
{
	int m_hndl;
	VECTOR m_pos;
	bool isActive;
	VECTOR m_pow;
	double m_angle;

	int m_y;
	int m_x;

	VECTOR m_nextPos;
	VECTOR m_nowPos;
	int m_count;

	int m_num;
};




//		ステージ初期化
void InitZip();
//		ステージロード
void LoadZip();
//		ステージ更新
void UpdateZip();
//		ステージ描画
void DrawZip();
//		ステージ破棄
void ExitZip();

void RequestZip(VECTOR pos_1,VECTOR pos_2);

