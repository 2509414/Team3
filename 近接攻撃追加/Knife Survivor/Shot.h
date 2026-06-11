#pragma once

#include<DxLib.h>

//弾画像操作用構造体
typedef struct
{
	VECTOR m_pos;	//表示位置
	VECTOR m_speed;	//弾の移動速度

	int m_isActive;	//生存フラグ
}SHOT_DATA;