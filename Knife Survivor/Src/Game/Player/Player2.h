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

	//ナイフとプレイヤーの当たり判定
	bool HitCheckKnifeToPlayer1();

	//近接攻撃とプレイヤーの当たり判定
	bool HitCheckAttackToPlayer1();

	//アクションとアイテムの判定
	bool HitCheckAction2ToItem(Item& item);

	void SetCoul(float time) { time = m_attacktime; }
	float GetCoul() { return m_attacktime; }
};

