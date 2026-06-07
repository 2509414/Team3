#pragma once
#include "../../Shot.h"
#include"Player.h"

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

	// 着地
	void SetLand();

	bool HitCheckKnifeToPlayer1();

	// 座標設定
	void SetPos(VECTOR pos);
};

