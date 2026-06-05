#pragma once

#include<DxLib.h>
#include<math.h>

#include <iostream>
#include "Lib/KeyInput/KeyInput.h"

#include "Game/Object/Player/Player.h"



//画面サイズ
#define WINDOW_SIZE_X (1280)
#define WINDOW_SIZE_Y (720)

#define PLSHOT_MAX (5)

// ステージの縦横の数
#define STAGE_X	(46)
#define STAGE_Y	(1006)


// プレイヤーのサイズ
#define PLAYER_SIZE_X (96)	// 画像サイズ横
#define PLAYER_SIZE_Y (84)	// 画像サイズ縦

// プレイヤーのサイズ
#define ENEMY_SIZE_X (96)	// 画像サイズ横
#define ENEMY_SIZE_Y (84)	// 画像サイズ縦

// 攻撃当たり判定サイズ
#define ATTACK_SIZE_X (48)	// 画像サイズ横
#define ATTACK_SIZE_Y (42)	// 画像サイズ縦

//プレイヤーの表示サイズ
#define PLAYER_SIZEX (48)	// 実際のサイズ横
#define PLAYER_SIZEY (42)	// 実際のサイズ縦

//弾のサイズ
#define SHOT_SIZEX (16)
#define SHOT_SIZEY (16)

// ステージに配置する物体のサイズ
#define OBJECT_SIZE_X		(32)
#define OBJECT_SIZE_Y		(32)



class Mouse_Data
{
public:

	int m_posX;
	int m_posY;

	VECTOR m_len;
	VECTOR m_arrow;
	VECTOR m_catch;
	VECTOR m_arrow_len;
	VECTOR m_catch_len;

	
	VECTOR m_mousepos;
	VECTOR m_nowpos;
	VECTOR m_prepos;
	int m_cnt;


	double m_angle_radian;

	//		マウス座標取得関数
	void GetMouse() {
		GetMousePoint(&m_posX, &m_posY);

		m_mousepos.x = (float)m_posX;
		m_mousepos.y = (float)m_posY;
	}

	void MouseOffset() {

		//オフセット
		VECTOR offsetPos = GetOffset();
		m_posX += (int)offsetPos.x;
		m_posY += (int)offsetPos.y;
	}

	//		プレイヤーからマウスへのベクトル
	void Player_Mouse_Vector(VECTOR pos) {
		VECTOR dir;
		dir.x = m_posX - pos.x;
		dir.y = m_posY - pos.y;
		dir.z = 0.0f;
		//上記方向ベクトルの長さの2乗を計算
		float length = (dir.x * dir.x) + (dir.y * dir.y);
		//長さの２乗になっているので2乗を取っ払う
		length = sqrtf(length);
		//1を長さで割る
		length = 1.0f / length;
		//上の計算結果を方向ベクトルに掛け算する	
		dir.x *= length;
		dir.y *= length;
		//=========================================================================

		m_len.x = dir.x;
		m_len.y = dir.y;
	}

	void Arrow() {

		m_arrow.x = m_len.x * 30;

		m_arrow.y = m_len.y * 30;
	}

	//角度取得(ラジアン)
	double Angle(VECTOR pos) {

		m_angle_radian = std::atan2(pos.y - m_posY, pos.x - m_posX);

		return m_angle_radian;
	}

	void GetPos() {

		m_cnt++;
		m_nowpos = m_mousepos;
	
		if (m_cnt == 1)
		{
			m_cnt = 0;
			m_prepos = m_mousepos;
		}

		DrawFormatString(16, 96, GetColor(255, 255, 255),
			"PreMouseX:%f,PreMouseY:%f",m_prepos.x,m_prepos.y );


		DrawFormatString(16, 112, GetColor(255, 255, 255),
			"NowMouseX:%f,NowMouseY:%f", m_nowpos.x, m_nowpos.y);

		

	}
	
};


class Shot
{
public:

	void Init() {
		m_hndl = -1;
		m_isActiv = false;
		m_pos = { 1,1,1 };
	}

	void Load() {

		if (m_hndl == -1)
		{
			m_hndl = LoadGraph("Data/Textures/shot00.png");
		}
	}
	
	void Step() {

		m_pos.x += (m_pow.x * m_speed);
		m_pos.y += (m_pow.y * m_speed);
	}

	void Draw() {

		VECTOR offsetPos = GetOffset();
		VECTOR drawShotPos;
		drawShotPos.x = m_pos.x - offsetPos.x;
		drawShotPos.y = m_pos.y - offsetPos.y;

		if (m_isActiv)
		{
			// 画像描画　第1, 2引数は画像の位置、第３引数は拡大縮小率、第４引数は回転率（ラジアン角指定）
			DrawRotaGraph((int)drawShotPos.x, (int)drawShotPos.y, 1.5, m_angle, m_hndl, TRUE);
		}
	}
	
	int m_speed;
	VECTOR m_pow;
	int m_hndl;
	VECTOR m_pos;
	bool m_isActiv;
	double m_angle;
	bool m_moveflag;
};


class Obj
{
public:
	


	void Init() {
		m_hndl = -1;
		m_isActive = false;
	}

	void Load() {
		if (m_hndl == -1)
		{
			m_hndl = LoadGraph("Data/Textures/shot00.png");
		}
	}

	void Step() {

	}

	void Draw() {

		//VECTOR offsetPos = GetOffset();
		//VECTOR drawShotPos;
		//drawShotPos.x = m_pos.x - offsetPos.x;
		//drawShotPos.y = m_pos.y - offsetPos.y;

		//if (m_isActive)
		//{
		//	// 画像描画　第1, 2引数は画像の位置、第３引数は拡大縮小率、第４引数は回転率（ラジアン角指定）
		//	DrawRotaGraph((int)drawShotPos.x, (int)drawShotPos.y, 1.0, m_hndl,0.0,0.0,0.0);
		//}

		if (m_isActive)
		{
			// 画像描画　第1, 2引数は画像の位置、第３引数は拡大縮小率、第４引数は回転率（ラジアン角指定）
			DrawRotaGraph((int)m_pos.x, (int)m_pos.y, 1.0, m_hndl, 0.0, 0.0, 0.0);
		}
	}

	VECTOR m_pos;
	bool m_isActive;
	int m_hndl;
};





//// ステージのタイプ
enum tagStageID {
	STAGEID_BLOCK,		// 床・壁
	STAGEID_BOX,		// 宝箱
	STAGEID_COIN,		//コイン
	STAGEID_MAGMA,		//マグマ
	STAGEID_WHITE,		//白ブロック
	STAGEID_RED,		//赤ブロック
	STAGEID_BLUE,		//青ブロック
	STAGEID_GOAL,
	STAGEID_SETTI,




	STAGEID_START,
	STAGEID_END,



	STAGEID_NUM
};
