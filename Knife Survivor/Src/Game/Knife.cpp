#include<DxLib.h>
#include "../Lib/Input.h"
#include"Knife.h"
#include "Player.h"
#include"../Game/Knife.h"
//定義関連
#define KNIFE_SPEED (5)
#define KNIFE_ACTIVE_TIME (6)

//ナイフデータ初期化関数
void Knife::Init()
{
	m_hndl = -1;

	//弾の初期化
	m_isActive = 0;
}

//	ナイフデータ読み込み関数
void Knife::Load()
{
	if (m_hndl == -1)
	{
		m_hndl = LoadGraph("Data/Textures/ナイフ.png");
	}
}

//	ナイフデータ更新関数
void Knife::Step()
{
	//ナイフの移動処理
	
		if (m_isActive != 0)
		{
			// ただ速度を足すだけ
			m_pos.x += m_speed.x;
			m_pos.y += m_speed.y;

			//経過時間を加算
			m_timer += 0.1;

			//g_knife.m_timerがアクティブタイムより大きくなったら消す
			if (m_timer > KNIFE_ACTIVE_TIME)
			{
				m_isActive = 0;
			}
		}
}
//	表示関数
void Knife::Draw()
{
	
	if (m_isActive != 0)
	{
		// 移動速度を見れば、画像反転させるべきかどうかわかるはず
		bool isTurn;
		if (m_speed.x < 0.0f) isTurn = true;
		else isTurn = false;
		DrawRotaGraph((int)m_pos.x, (int)m_pos.y, 1.0, 0.0,m_hndl, TRUE, isTurn);
	}
}

//	終了前の処理関数
void Knife::Exit()
{
	if (m_hndl != -1)
	{
		DeleteGraph(m_hndl);
		m_hndl = -1;
	}
}

void Knife::Request(VECTOR pos, VECTOR speed)
{
	m_isActive = 1;

	m_timer = 0.0f;	//タイマーを0にセット
	// ナイフの移動方向や速度はプレイヤー側に設定をお願いする
	m_speed = speed;
	m_pos = pos;
}