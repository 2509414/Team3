#pragma once
#include<DxLib.h>
#include"Attack.h"

class Attack2 :public Attack
{
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

	void Request(VECTOR pos, bool turn);

};
