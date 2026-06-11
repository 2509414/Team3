#include<DxLib.h>
#include"Item.h"

extern Player player1;
extern Player2 player2;


//アイテムデータ初期化関数
void Item::Init()
{
	m_hndl = -1;
	m_pos = { 100.0f,500.0f,0.0f };
	m_hp = GetRand(3) + 1;
	m_speedX = 3.0f;
	m_speedY = 2.0f;
	m_isdraw = false;
	m_differenceHP = 0;
	m_differenceHP2 = 0;
}

//	アイテムデータ読み込み関数
void Item::Load()
{
	if (m_hndl == -1)
	{
		m_hndl = LoadGraph("Data/Textures/Item.png");
	}
}


//アイテムデータ更新関数
void Item::Step()
{
	//playerのHPの差を格納
	m_differenceHP  = player1.m_hp - player2.m_hp;
	m_differenceHP2 = player2.m_hp - player1.m_hp;

	//HPの差が5以上だったらフラグをオンにする
	if (m_differenceHP >= 5 || m_differenceHP2 >= 5)
	{
		m_isdraw = true;
	}

	// 移動
	m_pos.x += m_speedX;
	m_pos.y += m_speedY;

	// ランダムで方向変更
	if (GetRand(100) == 0)
	{
		m_speedX = GetRand(10) - 5;
		m_speedY = GetRand(10) - 5;
	}

	// 画面端まで行ったらマイナスをかけて反転移動させる
	if (m_pos.x < 32 || m_pos.x > 870)
	{
		m_speedX *= -1;
	}

	if (m_pos.y < 0 || m_pos.y > 545)
	{
		m_speedY *= -1;
	}

	//破棄処理
	if (m_hp == 0)
	{
		Item::Exit();
	}
}

//表示関数
void Item::Draw()
{
	if (m_isdraw == true)
	{
		DrawGraph(m_pos.x, m_pos.y, m_hndl, TRUE);
		DrawFormatString(450, 300, GetColor(255, 255, 0), "あと%d回で割れる！", m_hp);
	}
}

//破棄関数
void Item::Exit()
{
	if (m_hp == 0)
	{
		DeleteGraph(m_hndl);
		m_pos = { -100,-100,-100 };
		m_isdraw = false;
	}
}