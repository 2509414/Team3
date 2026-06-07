#pragma once
#include "../../Shot.h"
#include "Knife.h"
class Knife2:public Knife 
{
public:

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

};

