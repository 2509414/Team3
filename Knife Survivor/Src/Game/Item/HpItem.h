#pragma once
#include "../Player/Player.h"
#include "../Player/Player2.h"


class HpItem
{
public:
	int m_drawtime;		//描画するまでの時間
	int m_hndl;			//画像ハンドル
	bool m_isdraw;		//描画するかどうか
	VECTOR m_pos;		// 座標

public:

	// 初期化
	void Init();

	// 読み込み
	void Load();

	// 更新
	void Step();

	// 描画
	void Draw();

	// 終了処理
	void Exit();

};

