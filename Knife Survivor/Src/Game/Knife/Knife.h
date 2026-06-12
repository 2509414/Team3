#pragma once

#include "../../../Shot.h"


class Knife
{
public:
	int m_hndl;
	VECTOR m_pos;
	VECTOR m_speed;	// ナイフの飛ぶ速度
	float m_timer;	//	ナイフを投げてからの経過時間
	float m_cooltime;// クールタイム用
	bool m_isActive;

public:
	//ナイフデータ初期化関数
	void Init();

	//ナイフデータ読み込み関数
	void Load();

	//ナイフデータ更新関数
	void Step();

	//ナイフデータ表示関数
	void Draw();

	//終了前の処理関数
	void Exit();

	void Request(VECTOR pos, VECTOR speed);

	
	void SetCoul(float time) { time = m_cooltime; } 
	float GetCoul(){ return m_cooltime; }
};

typedef struct
{

}Knife_DATA;

