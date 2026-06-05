#pragma once
#include<DxLib.h>


struct Catch_Data
{
	int m_hndl[STAGEID_NUM];
	VECTOR m_pos;
	bool isActive;

	int m_y;
	int m_x;

	bool on_off_flag;
	int m_objnum;

	VECTOR m_nowPos;				
	VECTOR m_nextPos;
	int m_count;
};




//		ステージ初期化
void InitCatch();
//		ステージロード
void LoadCatch();
//		ステージ更新
void UpdateCatch();
//		ステージ描画
void DrawCatch();
//		ステージ破棄
void ExitCatch();

void RequestCatch(int num,VECTOR pos,int y,int x);