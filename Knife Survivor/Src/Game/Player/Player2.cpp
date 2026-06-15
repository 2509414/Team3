#include<DxLib.h>
#include "Player.h"
#include "../Knife/Knife2.h"
#include "Player2.h"
#include "../../Lib/Input.h"
#include "../../Lib/Collision.h"
#include "../Stage/Stage.h"
#include "../Sound/Sound.h"
#include "../Attack/Attack2.h"


//定義関連
#define WINDOW_SIZE_X (900.0f)	//ウィンドウのサイズ（横）
#define WINDOW_SIZE_Y (600.0f)	//ウィンドウのサイズ（縦）   
#define MOVE_SPEED (2)			//移動速度
#define MOVE_DASHSPEED (1)	//ダッシュスピード
#define MOVE_JUMPPW (-11)		//ジャンプパワー
#define GRAVITY (0.5f)			//重力
#define ANIM_NUM (6)			//全画像枚数
#define PLAYER_X_SIZE (320)		//1枚分の大きさ（横）
#define PLAYER_Y_SIZE (320)		//1枚分の大きさ（縦）
#define X_NUM (6)				//横に何枚並んでいるか
#define Y_NUM (1)				//縦に何枚並んでいるか
#define ANIM_SPEED (0.08)		//アニメーションのスピード
#define BOSSSCENE_POSX (5300)	//ボスシーンに入るX座標
#define MOVE_SQUATSPEED (0.5f);	//スロースピード
#define HP2_STARTPOS_X (815)	//HPを描画する基準点
#define HP2_END_X (515)			//HPを描画する終点

extern Stage_DATA g_stageData;
extern Player player1;
extern Knife2 knife2;
extern Attack2 attack2;
extern Player2 player2;

//プレイヤーデータ初期化関数
void Player2::Init(int Stagenum)
{
	//画像をロードしていないという意味で-1を入れる
	m_hndl[0] = -1;
	m_shndl[0] = -1;
	m_shothndl = -1;
	TurnFrag = 1;
	m_pos.x = 830;
	m_pos.y = 535;

	Knife = 1;
	itemcraft = 0;
	m_hp = 10;
	m_maxhp = 10;
	m_K_time = 0;
	m_A_time = 0;
	m_isSquat = false;
	m_isAttack = false;
	m_isAttack = false;
}

//	プレイヤーデータ読み込み関数
void Player2::Load()
{
	if (m_hndl[0] == -1)
	{
		LoadDivGraph("Data/Textures/キャラ.png", 4, 4, 1, PLAYER_X_SIZE, PLAYER_Y_SIZE, m_hndl);
	}

	if (m_shndl[0] == -1)
	{
		LoadDivGraph("Data/Textures/Squat.png", 4, 4, 1, PLAYER_X_SIZE, PLAYER_Y_SIZE, m_shndl);
	}
}

//	プレイヤーダッシュ関数
void Player2::Dash()
{
	if (IsKeyInput(KEY_DASH2))
	{
		m_pos.x += MOVE_DASHSPEED;
	}

	if (IsKeyInput(KEY_LDASH2))
	{
		m_pos.x -= MOVE_DASHSPEED;
	}
}

//	プレイヤージャンプ処理関数（処理内容）
void Player2::Jump()
{
	if (IsKeyInput(KEY_JUMP2) && m_JpActive == true)
	{
		PlaybackSound(5);
		playerSy = MOVE_JUMPPW;
		m_JpActive = false;
	}
	m_pos.y += playerSy;
	playerSy += GRAVITY;
}

//	プレイヤーデータ更新関数
void Player2::Step()
{
	//必殺技状態かチェック
	if (m_attacktime >= 0)
	{
		m_isAttack = true;
	}
	else
	{
		m_isAttack = false;
	}

	if (m_isAttack == true)
	{
		m_attacktime--;
	}
	m_squattime--;
	m_hplength = 300 * m_hp / m_maxhp;

	m_K_time = knife2.GetCoul();
	m_A_time = attack2.GetCoul();
	m_Itemtime = GetCoul();

	//プレイヤー移動処理
	if (IsKeyInput(KEY_RIGHT2) && IsKeyInput(KEY_SQUAT2))
	{
		TurnFrag = 0;
		anim += ANIM_SPEED;
		if (anim >= 4)
		{
			anim = 0;
		}
		m_pos.x += MOVE_SQUATSPEED;
	}
	else if (IsKeyInput(KEY_RIGHT2))
	{
		TurnFrag = 0;
		anim += ANIM_SPEED;
		if (anim >= 4)
		{
			anim = 0;
		}
		m_pos.x += MOVE_SPEED;
	}

	if (IsKeyInput(KEY_LEFT2) && IsKeyInput(KEY_SQUAT2))
	{
		TurnFrag = 1;
		anim += ANIM_SPEED;
		if (anim >= 4)
		{
			anim = 0;
		}
		m_pos.x -= MOVE_SQUATSPEED;
	}
	else if (IsKeyInput(KEY_LEFT2))
	{
		TurnFrag = 1;
		anim += ANIM_SPEED;
		if (anim >= 4)
		{
			anim = 0;
		}
		m_pos.x -= MOVE_SPEED;
	}

	if (IsKeyInputTrg(KEY_KNIFE2))
	{
		// ナイフの移動方向を決める
		VECTOR v = { 0.0f, 0.0f, 0.0f };
		if (TurnFrag == 0) v.x = 5.0f;
		else v.x = -5.0f;
		knife2.Request(m_pos, v);
	}

	//しゃがみ状態だったら
	if (IsKeyInput(KEY_SQUAT2) == true)
	{
		m_squattime = 1;

		m_isSquat = true;
	}

	if (m_squattime < 0)
	{
		m_isSquat = false;
	}
	//アタック状態だったら
	if (IsKeyInputTrg(KEY_ATTACK2))
	{
		if (!attack2.m_isActive)
		{
			// 攻撃の移動方向を決める
			VECTOR v = { 0.0f, 0.0f, 0.0f };
			if (TurnFrag == 0) {
				/*m_pos.x += 10.0f;*/
				attack2.Request(m_pos, true);
			}
			else {
				/*m_pos.x += -10.0f;*/
				attack2.Request(m_pos, false);
			}
		}
	}

	//クリックした場所にブロックを置く
	if (IsKeyInputTrg(KEY_ITEMCRAFT))
	{
		//クリックした座標に一定時間ブロックを置く処理を書く
		const int BLOCK_LIFE = 240; // 4秒
		int mx, my;
		GetMousePoint(&mx, &my);


		int mapX = mx / OBJECT_SIZE_X;	//今の座標÷マップチップのサイズ(32)をして
		int mapY = my / OBJECT_SIZE_Y;	//格納する場所を決める

		//スコアが0以下またはすでにブロックが置かれている(-1じゃなっかたら）だったらブブー音を鳴らす
		if (g_stageData.m_mapData[mapY][mapX] != -1)
		{
			PlaybackSound(7);
		}
		//クリックした場所が-1(何も置かれてない)状態だったらブロックを置く
		if (g_stageData.m_mapData[mapY][mapX] == -1)
		{
			g_stageData.m_mapData[mapY][mapX] = 1;
			PlaybackSound(6);
			g_stageData.m_BlockTimer[mapY][mapX] = BLOCK_LIFE;
		}
	}
}
//	表示関数
void Player2::Draw()
{
	int frame = (int)anim;
	if (m_isSquat == false)
	{
		for (int i = 0; i < 4; i++)
		{
			//画像描画　第１、２引数は画像の位置、第3引数は拡大縮小率、第４引数は回転率（ラジアン角指定）
			DrawRotaGraph((int)m_pos.x, (int)m_pos.y, 0.2, 0.0, (int)m_hndl[frame], TRUE, TurnFrag);
		}
	}
	if (m_isSquat == true)
	{
		for (int i = 0; i < 4; i++)
		{
			//画像描画　第１、２引数は画像の位置、第3引数は拡大縮小率、第４引数は回転率（ラジアン角指定）
			DrawRotaGraph((int)m_pos.x, (int)m_pos.y + 10, 0.18, 0.0, (int)m_shndl[frame], TRUE, TurnFrag);
		}
	}
	//残りHPに応じて色を変える
	int color;

	if (m_hp >= 6)
	{
		color = GetColor(0, 255, 0);      // 緑
	}
	else if (m_hp >= 3)
	{
		color = GetColor(255, 255, 0);    // 黄
	}
	else
	{
		color = GetColor(255, 0, 0);      // 赤
	}

	DrawFormatString(825, 40, GetColor(0, 0, 255), "HP");
	//HPバー
	DrawLine(HP2_STARTPOS_X, 47, HP2_STARTPOS_X - m_hplength, 47, color, 15);

	if (m_attacktime > 0)
	{
		DrawFormatString(825, 100, GetColor(0, 0, 255), "必殺技");
	}
	//必殺技の時間を表示するバー
	DrawLine(815, 108, 815 - m_attacktime / 4, 108, GetColor(0, 0, 255), m_t = 3);

	if (player2.m_K_time > 0)
	{
		DrawFormatString(825, 80, GetColor(0, 0, 255), "ナイフ");
	}
	//ナイフクールタイムを表示するバー
	DrawLine(815, 88, 815 - player2.m_K_time, 88, GetColor(0, 0, 255), player2.m_t = 3);

	if (player2.m_A_time > 0)
	{
		DrawFormatString(825, 60, GetColor(0, 0, 255), "近接");
	}
	//近接攻撃クールタイムを表示するバー
	DrawLine(815, 68, 815 - player2.m_A_time * 3, 68, GetColor(0, 0, 255), player2.m_t = 3);

	DrawFormatString(m_pos.x - 9, m_pos.y - 50, GetColor(0, 0, 255), "2P");
}

//	終了前の処理関数
void Player2::Exit()
{
	//画像がロードされているようであれば、画像を破棄する
	if (m_hndl[0] != -1)
	{
		DeleteGraph(m_hndl[0]);
		//破棄した後はー１を入れることで未使用状態であると分かるようにする
		m_hndl[0] = -1;
	}

	m_isAttack = false;
	m_attacktime = 0.0f;
}

//	地面接地時処理
void Player2::SetLand()
{
	playerSy = 0.0f;
	m_JpActive = true;
}


bool Player2::HitCheckKnifeToPlayer1()
{
	//ナイフが出てなかったら判定しない
	if (knife2.m_isActive == 0)
	{
		return false;
	}

	bool hit = false;

	if (player1.m_isSquat == false)
	{
		// 立ち
		hit = ChenkHitSquareToSquare(knife2.m_pos, 15, 10, player1.m_pos, 12, 20);
	}
	else
	{
		// しゃがみ
		hit = ChenkHitSquareToSquare(knife2.m_pos, 15, 10, player1.m_pos, 12, 0);
	}

	//ヒットしたかつアタックフラグがオンだったら
	if (hit == true && m_isAttack == true)
	{
		//当たったらナイフの生存フラグを消す
		knife2.m_isActive = 0;
		PlaybackSound(1);
		player1.m_hp -= 2;

		return true;
	}
	//ヒットしたら
	else if (hit == true)
	{
		//当たったらナイフの生存フラグを消す
		knife2.m_isActive = 0;
		PlaybackSound(1);
		player1.m_hp -= 1;

		return true;
	}
	return false;
}

bool Player2::HitCheckAttackToPlayer1()
{

	//攻撃が出てなかったら判定しない
	if (attack2.m_isActive == 0)
	{
		hit_once = false;
		return false;
	}

	bool hit = ChenkHitSquareToSquare(attack2.m_pos, 5, 30, player1.m_pos, 30, 30);

	if (hit == true)
	{
		//当たったらナイフの生存フラグを消す！（これをしないと毎フレームHPが減って大変だぞ)

		if (!hit_once && m_isAttack == true)
		{
			PlaybackSound(1);
			player1.m_hp -= 2;
			hit_once = true;
			return true;
		}
		else if (!hit_once)
		{
			PlaybackSound(1);
			player1.m_hp -= 1;
			hit_once = true;
			return true;
		}
		return false;
	}
}

//ナイフとアイテムの判定(アイテムクラスを参照)
bool Player2::HitCheckAction2ToItem(Item& item)
{
	if (item.m_isdraw == true)
	{
		//falseだったら判定しない
		if (knife2.m_isActive == false)
		{
			return false;
		}

		bool knifehit = ChenkHitSquareToSquare(knife2.m_pos,15,2,item.m_pos,35,50);

		if (knifehit == true)
		{
			//HPが1じゃなかったら(８)の音 1だったら(10)の音を鳴らす　これで壊れると時だけ音を変えれる
			if (item.m_hp != 1)
			{
				PlaybackSound(8);
			}
			else
			{
				PlaybackSound(10);
			}
			//アクティブをfalseに
			knife2.m_isActive = false;

			//hpを減らす
			item.m_hp--;

			//0以下になったら
			if (item.m_hp <= 0)
			{

				//必殺技の時間をここで設定
				m_attacktime = 900;

				// アイテム消す
				item.m_isdraw = false;
			}
		}
		return true;
	}
	return false;
}