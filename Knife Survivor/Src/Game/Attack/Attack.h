#pragma once
#include<DxLib.h>


class Attack
{
public:

	int m_hndl[3];
	float anim_cnt;
	VECTOR m_pos;
	float m_timer;	//	攻撃からの経過時間
	float m_cooltime;// クールタイム用
	bool m_isActive;
	bool turn_flg;

public:
	//攻撃データ初期化関数
	void Init();

	//攻撃データ読み込み関数
	void Load();

	//攻撃データ更新関数
	void Step();

	//攻撃データ表示関数
	void Draw();

	//終了前の処理関数
	void Exit();

    void Request(VECTOR pos,bool turn);

};
