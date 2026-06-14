#include"Attack2.h"
#include "../Sound/Sound.h"
#include"../Player/Player2.h"



//定義関連
#define Attack2_SPEED (5)
#define Attack2_ACTIVE_TIME (30)

#define Attack2_Len (30)

#define ANIM_NUM (3)			//全画像枚数
#define X_SIZE (142)		//1枚分の大きさ（横）
#define Y_SIZE (320)		//1枚分の大きさ（縦）
#define X_NUM (3)				//横に何枚並んでいるか
#define Y_NUM (1)				//縦に何枚並んでいるか
#define ANIM_SPEED (0.5)		//アニメーションのスピード


//攻撃データ初期化関数
void Attack2::Init()
{
	for (int i = 0; i < ANIM_NUM; i++)
	{
		m_hndl[i] = -1;
	}

	m_isActive = 0;

	m_cooltime = 0.0f;

	anim_cnt = 0;
}

//	攻撃データ読み込み関数
void Attack2::Load()
{
	if (m_hndl[0] == -1)
	{
		LoadDivGraph("Data/Textures/Attack.png", ANIM_NUM,
			X_NUM, Y_NUM, X_SIZE, Y_SIZE, m_hndl);
	}
}

//	攻撃データ更新関数
void Attack2::Step()
{
	// クールタイム減少
	if (m_cooltime > 0.0f)
	{
		m_cooltime--;

	}
	//攻撃の移動処理
	if (m_isActive != 0)
	{
		anim_cnt += ANIM_SPEED;

		// ただ速度を足すだけ
		//m_pos.x += Attack2_Len;
		m_timer += 1.0f;
		//g_Attack2.m_timerがアクティブタイムより大きくなったら消す
		if (m_timer >= Attack2_ACTIVE_TIME)
		{
			m_timer = 0;
			m_isActive = 0;

		}
	}
	else
	{
		anim_cnt = 0;
	}
}
//	表示関数
void Attack2::Draw()
{

	int frame = (int)anim_cnt;
	if (frame < 4) {
		if (m_isActive == true)
		{
			for (int i = 0; i < 4; i++)
			{
				//画像描画　第１、２引数は画像の位置、第3引数は拡大縮小率、第４引数は回転率（ラジアン角指定）
				DrawRotaGraph((int)m_pos.x, (int)m_pos.y, 0.5f, 0.0, (int)m_hndl[frame], TRUE, !turn_flg);
			}
		}
	}
}

//	終了前の処理関数
void Attack2::Exit()
{
	for (int i = 0; i < ANIM_NUM; i++)
	{
		if (m_hndl[i] != -1)
		{
			DeleteGraph(m_hndl[i]);
			m_hndl[i] = -1;
		}
	}
}

void Attack2::Request(VECTOR pos, bool turn)
{
	// クールタイム中は発射不可
	if (m_cooltime > 0.0f)
	{
		return;
	}
	m_isActive = 1;
	m_timer = 0.0f;		//タイマーを0にセット
	PlaybackSound(0);
	m_cooltime = 30;	//0.5秒待つ

	turn_flg = turn;

	// 攻撃の移動方向や速度はプレイヤー側に設定をお願いする
	if (turn)
	{
		m_pos.x = pos.x + Attack2_Len;
	}
	else
	{
		m_pos.x = pos.x - Attack2_Len;
	}

	m_pos.y = pos.y + Attack2_Len;
}