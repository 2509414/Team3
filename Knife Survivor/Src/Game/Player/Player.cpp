#include<DxLib.h>
#include"Player.h"
#include "Player2.h"
#include "../../Lib/Input.h"
#include "../Knife/Knife.h"
#include "../../Lib/Collision.h"
#include "../Stage/Stage.h"
#include "../Sound/Sound.h"

//定義関連
#define WINDOW_SIZE_X (900.0f)	//ウィンドウのサイズ（横）
#define WINDOW_SIZE_Y (600.0f)	//ウィンドウのサイズ（縦）   
#define MOVE_SPEED (1)			//移動速度
#define MOVE_DASHSPEED (1.5)	//ダッシュスピード
#define MOVE_JUMPPW (-11)		//ジャンプパワー
#define GRAVITY (0.5f)			//重力
#define ANIM_NUM (6)			//全画像枚数
#define PLAYER_X_SIZE (320)		//1枚分の大きさ（横）
#define PLAYER_Y_SIZE (320)		//1枚分の大きさ（縦）
#define X_NUM (6)				//横に何枚並んでいるか
#define Y_NUM (1)				//縦に何枚並んでいるか
#define ANIM_SPEED (0.08)		//アニメーションのスピード
#define BOSSSCENE_POSX (5300)	//ボスシーンに入るX座標


extern Stage_DATA g_stageData;
extern Knife Knife1;
extern Player2 player2;

//プレイヤーデータ初期化関数
void Player::Init(int Stagenum)
{
	//画像をロードしていないという意味で-1を入れる
	m_hndl[0] = -1;
	m_shothndl = -1;
	TurnFrag = 0;
	m_pos.x = 150;
	m_pos.y = 519;
	g_isGameClear = false;
	m_isBossScene = false;
	Knife = 1;
	itemcraft = 0;
	m_hp = 10;

	if (Stagenum == 1)
	{
		m_pos.x = 4750;
	}

	if (Stagenum == 2)
	{
		m_pos.y = 423 ;
	}
}

//	プレイヤーデータ読み込み関数
void Player::Load()
{
	if (m_hndl[0] == -1)
	{
		LoadDivGraph("Data/Textures/キャラ.png", 4, 4, 1, PLAYER_X_SIZE, PLAYER_Y_SIZE, m_hndl);
	}
}

//	プレイヤーダッシュ関数
void Player::Dash()
{
	if (IsKeyInput(KEY_DASH))
	{
		m_pos.x += MOVE_DASHSPEED;
	}

	if (IsKeyInput(KEY_LDASH))
	{
		m_pos.x -= MOVE_DASHSPEED;
	}
}

//	プレイヤージャンプ処理関数（処理内容）
void Player::Jump()
{
	if (IsKeyInput(KEY_JUMP) && m_JpActive == true)
	{
		PlaybackSound(5);
		playerSy = MOVE_JUMPPW;
		m_JpActive = false;
	}

	m_pos.y += playerSy;
	playerSy += GRAVITY;

}

//	プレイヤーデータ更新関数
void Player::Step()
{


	//プレイヤー移動処理
	if (IsKeyInput(KEY_RIGHT))
	{
		TurnFrag = 0;
		anim += ANIM_SPEED;
		if (anim >= 4)
		{
			anim = 0;
		}
		m_pos.x += MOVE_SPEED;
	}

	if (IsKeyInput(KEY_LEFT))
	{
		TurnFrag = 1;
		anim += ANIM_SPEED;
		if (anim >= 4)
		{
			anim = 0;
		}
		m_pos.x -= MOVE_SPEED;
	}

	if (IsKeyInputTrg(KEY_KNIFE))
	{
		// ナイフの移動方向を決める
		VECTOR v = { 0.0f, 0.0f, 0.0f };
		if (TurnFrag == 0) v.x = 5.0f;
		else v.x = -5.0f;
		Knife1.Request(m_pos,v);
		PlaybackSound(0);
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
void Player::Draw()
{
	int frame = (int)anim;
	for (int i = 0; i < 4; i++)
	{
		//画像描画　第１、２引数は画像の位置、第3引数は拡大縮小率、第４引数は回転率（ラジアン角指定）
		DrawRotaGraph((int)m_pos.x, (int)m_pos.y, 0.2, 0.0, (int)m_hndl[frame], TRUE, TurnFrag);
	}
	DrawFormatString(75, 100, GetColor(255, 0, 0), "残りHP : %d", m_hp);
	DrawFormatString(m_pos.x - 9,m_pos.y -50, GetColor(255, 0, 0), "1P");

}

//	終了前の処理関数
void Player::Exit()
{
	//画像がロードされているようであれば、画像を破棄する
	if (m_hndl[0] != -1)
	{
		DeleteGraph(m_hndl[0]);
		//破棄した後はー１を入れることで未使用状態であると分かるようにする
		m_hndl[0] = -1;
	}
}

//	地面接地時処理
void Player::SetLand()
{
	playerSy = 0.0f;
	m_JpActive = true;
}

bool Player::HitCheckKnifeToPlayer2()
{
	//ナイフが出てなかったら判定しない
		if (Knife1.m_isActive== 0)
		{
			return false;
		}
		bool hit = ChenkHitSquareToSquare(Knife1.m_pos, 30, 30, player2.m_pos,30,30);
		
		if (hit == true)
		{
			//当たったらナイフの生存フラグを消す！（これをしないと毎フレームHPが減って大変だぞ)
			Knife1.m_isActive = 0;
			PlaybackSound(1);
			player2.m_hp -= 1;
			
			return true;
		}
		
	return false;
}
	
	

////オフセット値を取得
//VECTOR GetOffset()
//{
//
//	// プレイヤーの座標を基に理想の位置からどれだけ離れたかを計算する
//	VECTOR v;
//	// 理想の表示位置
//	v.x = WINDOW_SIZE_X / 2;
//	v.y = WINDOW_SIZE_Y ;
//	// 本来の座標から理想の表示位置までどれだけ離れたか
//	v.x = m_pos.x - v.x;
//	v.y = m_pos.y - v.y;
//	v.z = 0.0f;
//	// もしもオフセット値が限界を超えたら強制的に限界値へ===================
//	// 上下左右の限界値を計算
//	// プレイヤーはX=320,y=240からどれだけ離れているかを考える
//	// 左は今回プレイヤーが320まで来たら停止、上は240まで来たら停止なので、オフセットは共に0
//	float left = 0.0f;
//	float up = 0.0f;
//	// 右はステージ右端の40マス×32ドット=1280からウィンドウサイズの半分320を引いた960の位置が限界値
//	// ということは理想の位置320からのオフセットは960-320の640が限界となる
//	// 下の式は結果としてウィンドウサイズの半分を2回引き算しているので、まとめて表記している
//	float right = STAGE_X * OBJECT_SIZE_X - WINDOW_SIZE_X;
//	// こちらも上の式と同様の理論で作成
//	float down = STAGE_Y * OBJECT_SIZE_Y - WINDOW_SIZE_Y;
//
//	// 上で計算した上限を超えないようにする
//	if (v.x < left) v.x = left;
//	else if (v.x > right) v.x = right;
//	if (v.y < up) v.y = up;
//	else if (v.y > down) v.y = down;
//	//======================================================================
//
//	return v;
//}

VECTOR Player::GetPos()
{
	return m_pos;
}
