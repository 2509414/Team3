#include<DxLib.h>
#include"../../Game/Object/Player/Player.h"
#include"../../Comon.h"

//定義関連
#define ANIM_NUM (4)		//全画像枚数
#define X_SIZE (104)	    //1枚分の大きさ（横）
#define Y_SIZE (134)		//1枚分の大きさ（縦）
#define X_NUM (4)		//横に何枚並んでいるか
#define Y_NUM (1)			//縦に何枚並んでいるか
#define ANIM_SPEED (0.3f)	//アニメーション速度
#define EFFECT_MAX (5)		//エフェクトの最大同時表示数

//エフェクトデータに必要な構造体
typedef struct {
	float m_animCnt;		//どの画像を表示するか
	VECTOR m_pos;			//表示位置
	bool m_isActive;		//生存フラグ
}EFFECT_DATA;

//エフェクトマネージャー構造体
typedef struct {
	int m_hndl[ANIM_NUM];					//画像ハンドル
	EFFECT_DATA m_effectData[EFFECT_MAX];	//エフェクトデータ
	
} EFFECT_MANEGER;

EFFECT_MANEGER g_Effect = { 0 };

extern Mouse_Data g_mouse;

extern PLAYER_DATA g_player;


//		エフェクトデータ初期化関数
void InitEffect()
{
	//g_Effect.m_soundhndl = -1;

	//エフェクトに使う画像のハンドルをすべて初期化
	for (int i = 0; i < ANIM_NUM; i++)
	{
		g_Effect.m_hndl[i] = -1;
	}

	//エフェクトデータもすべて初期化
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		g_Effect.m_effectData[i].m_isActive = false;
		g_Effect.m_effectData[i].m_animCnt = 0.0f;
	}
}
//		エフェクトデータ読み込み
void LoadEffect()
{
	if (g_Effect.m_hndl[0] == -1)
	{
		LoadDivGraph("Data/Textures/explosion.png", ANIM_NUM, X_NUM, Y_NUM, X_SIZE, Y_SIZE, g_Effect.m_hndl);
	}
	/*if (g_Effect.m_soundhndl == -1)
	{
		LoadSoundMem("Data/Sounds/se_explore.mp3");
	}*/
}
//		エフェクトデータ更新関数
void StepEffect()
{
	//	すべてのエフェクトをチェックする必要あり
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		//表示されているエフェクトだけ更新する
		if (g_Effect.m_effectData[i].m_isActive == true)
		{
			//カウントを一つずつ増やす　　
			g_Effect.m_effectData[i].m_animCnt += ANIM_SPEED;

			//１番最後の画像を超えたらエフェクトを消す
			if (g_Effect.m_effectData[i].m_animCnt >= ANIM_NUM)
			{
				g_Effect.m_effectData[i].m_isActive = false;
			}
		}
	}
}

//		エフェクトデータ表示関数
void DrawEffect()
{
	VECTOR offsetPos = GetOffset();
	VECTOR drawPos;

	//	すべてのエフェクトをチェックする必要あり
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		int anmNum = g_Effect.m_effectData[i].m_animCnt;

		//フラグがオンのエフェクトだけ表示する
		if (g_Effect.m_effectData[i].m_isActive == true)
		{
			drawPos.x = g_Effect.m_effectData[i].m_pos.x - offsetPos.x;
			drawPos.y = g_Effect.m_effectData[i].m_pos.y - offsetPos.y;

			int animNum = g_Effect.m_effectData[i].m_animCnt;

			DrawRotaGraph((int)drawPos.x, (int)drawPos.y, 0.5, -g_mouse.Angle(g_player.m_pos), g_Effect.m_hndl[animNum], TRUE,g_player.Gun_turn_flag);
		}
	}
}

//		終了前の処理関数
void ExitEffect()
{
	/*if (g_Effect.m_soundhndl != -1)
	{
		DeleteSoundMem(g_Effect.m_soundhndl);
		g_Effect.m_soundhndl = -1;
	}*/
	//すべてのエフェクト画像を消す
	for (int i = 0; i < ANIM_NUM; i++)
	{
		DeleteGraph(g_Effect.m_hndl[i]);
		g_Effect.m_hndl[i] = -1;
	}
}

//エフェクトの呼び出し
void RequestEffect(VECTOR pos) {

	VECTOR offsetPos = GetOffset();
	VECTOR drawPos[EFFECT_MAX];

	//すべてのエフェクトをチェックする必要あり
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		//まだ使用されていないエフェクトを使う
		if (g_Effect.m_effectData[i].m_isActive == false)
		{
			pos.x -= offsetPos.x;
			pos.y -= offsetPos.y;

			//エフェクト表示に必要な情報をセット
			g_Effect.m_effectData[i].m_isActive = true;
			g_Effect.m_effectData[i].m_pos = pos;
			g_Effect.m_effectData[i].m_animCnt = 0.0f;
			//PlaySoundMem(g_Effect.m_soundhndl, DX_PLAYTYPE_BACK);
			break;
		}
	}
}