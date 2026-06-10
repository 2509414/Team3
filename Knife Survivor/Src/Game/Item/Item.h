#pragma once

class Item
{
public:
	int m_drawtime;		//描画するまでの時間
	int m_hndl;			//画像ハンドル
	float m_speedX;		//X軸の移動速度
	float m_speedY;		//Y軸の移動速度
	bool m_isdraw;		//描画するかどうか
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

