#pragma once

#include "../../../Shot.h"

class Player
{
public:
	int m_hndl[7];			// 画像ハンドル
	int m_playerstate;		// プレイヤーステータス
	float playerSy;			// 縦方向速度
	int groundY;			// 地面
	int m_JpActive;			// ジャンプ生存フラグ
	int Knife;				// ナイフ状態
	int itemcraft;			// アイテムクラフト状態
	int m_shothndl;			// 弾の画像ハンドル
	float m_animCnt;		// アニメーションカウント
	float anim;
	int TurnFrag;			//ターンフラグ
	int m_hp;				//体力

	bool g_isGameClear;		// ゲームクリア判定
	bool m_isBossScene;		// ボスシーン判定
	bool m_isActive;		// 生存フラグ

	VECTOR m_pos;			// 座標
	SHOT_DATA m_shot;		// 弾管理

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

	// 座標取得
	VECTOR GetPos();

	//// 座標設定
	//void SetPos(VECTOR pos);

	//ナイフと敵の当たり判定
	bool HitCheckKnifeToPlayer2();

};

