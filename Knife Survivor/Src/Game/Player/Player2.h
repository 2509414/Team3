#pragma once

#include "../../../Shot.h"
#include"Player2.h"
#include"Player.h"
#include "../Item/Item.h"

class Item;

class Player2:public Player
{
public:

	// 初期化
	void Init(int stageNum);

	// 読み込み
	void Load();

	// 更新
	void Step();

	// ダッシュ
	void Dash();

	// ジャンプ
	void Jump();

	// 描画
	void Draw();

	// 終了処理
	void Exit();

	//しゃがみ
	void Squat();

	// 着地
	void SetLand();

	bool HitCheckKnifeToPlayer1();

	//ナイフとアイテムの判定
	bool HitCheckKnife2ToItem(Item& item);

	// 座標設定
	void SetPos(VECTOR pos);
};

