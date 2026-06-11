#pragma once
#include "../Player/Player.h"
#include "../Player/Player2.h"


class Item
{
public:
	int m_drawtime;		//描画するまでの時間
	int m_hndl;			//画像ハンドル
	int m_hp;			//アイテムのHP
	float m_speedX;		//X軸の移動速度
	float m_speedY;		//Y軸の移動速度
	bool m_isdraw;		//描画するかどうか
	int m_differenceHP;	//HPの差を格納する変数
	int m_differenceHP2;//
	VECTOR m_pos;		// 座標

public:

	// 初期化
	void Init();

	// 読み込み
	void Load();

	// 更新
	void Step();

	//しゃがみ
	void Squat();

	// 描画
	void Draw();

	// 終了処理
	void Exit();

};

