#include<DxLib.h>
#include"Knife.h"
#include "Knife2.h"
#include "../Sound/Sound.h"

//定義関連
#define KNIFE_SPEED (5)
#define KNIFE_ACTIVE_TIME (360)

//ナイフデータ初期化関数
void Knife2::Init()
{
	m_hndl = -1;

	m_isActive = 0;

	m_cooltime = 0.0f;
}

//	ナイフデータ読み込み関数
void Knife2::Load()
{
	if (m_hndl == -1)
	{
		m_hndl = LoadGraph("Data/Textures/ナイフ.png");
	}
}

//	ナイフデータ更新関数
void Knife2::Step()
{
	// クールタイム減少
	if (m_cooltime > 0.0f)
	{
		m_cooltime--;

	}
	//ナイフの移動処理
	if (m_isActive != 0)
	{
		// ただ速度を足すだけ
		m_pos.x += m_speed.x;
		m_pos.y += m_speed.y;
		m_timer += 1.0f;
		//g_knife.m_timerがアクティブタイムより大きくなったら消す
		if (m_timer > KNIFE_ACTIVE_TIME)
		{
			m_isActive = 0;

		}
	}
}
//	表示関数
void Knife2::Draw()
{
	if (m_isActive != 0)
	{
		// 移動速度を見れば、画像反転させるべきかどうかわかるはず
		bool isTurn;
		if (m_speed.x < 0.0f) isTurn = true;
		else isTurn = false;
		DrawRotaGraph((int)m_pos.x, (int)m_pos.y, 1.0, 0.0, m_hndl, TRUE, isTurn);
	}

	//クールタイムが0より大きかったら残り何カウントか知らせる
	if (m_cooltime > 0)
	{
		DrawFormatString(600, 75, GetColor(0, 0, 255), "Knife クールタイム : %.1f", m_cooltime);
	}
}

//	終了前の処理関数
void Knife2::Exit()
{
	if (m_hndl != -1)
	{
		DeleteGraph(m_hndl);
		m_hndl = -1;
	}
}

void Knife2::Request(VECTOR pos, VECTOR speed)
{
	// クールタイム中は発射不可
	if (m_cooltime > 0.0f)
	{
		return;
	}
	m_isActive = 1;
	m_timer = 0.0f;		//タイマーを0にセット
	PlaybackSound(0);
	m_cooltime = 180;	//投げた瞬間から3秒待つ


	// ナイフの移動方向や速度はプレイヤー側に設定をお願いする
	m_speed = speed;
	m_pos = pos;
}