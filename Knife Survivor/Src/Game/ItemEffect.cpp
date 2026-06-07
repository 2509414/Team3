#include<DxLib.h>
#include "Player.h"

//定義
#define ANIMITEM_NUM (5)		//エフェクトの画像枚数
#define EFFECTITEM_MAX (1)		//エフェクトの最大同時表示数
#define ANIMITEM_SPEED (0.10f)	//アニメーション速度

//エフェクト表示用構造体
typedef struct
{
	VECTOR m_pos;	//表示位置
	float m_animCnt;//どの画像を表示するか
	int m_isActive;	//エフェクト表示フラグ
}ITEMEFFECT_DATA;

//エフェクトマネージャー
typedef struct
{
	int m_hndl[ANIMITEM_NUM];	//画像ハンドル
	ITEMEFFECT_DATA m_Itemeffect[EFFECTITEM_MAX];
}ITEMEFFECT_MANAGER;

static ITEMEFFECT_MANAGER g_Itemeffect = { 0 };

//初期化
void InitItemEffect()
{
	for (int i = 0; i < ANIMITEM_NUM;i++)
	{
		g_Itemeffect.m_hndl[i] = -1;
	}

	for(int i = 0; i < EFFECTITEM_MAX;i++)
	{
		g_Itemeffect.m_Itemeffect[i].m_animCnt = 0.0f;
		g_Itemeffect.m_Itemeffect[i].m_isActive = false;
	}
}

//エフェクトデータ読み込み
void LoadItemEffect()
{
	//画像がロードされてなかったらロード
	if (g_Itemeffect.m_hndl[0] == -1)
	{
		LoadDivGraph("Data/Textures/ItemEffect.png", 4, 4, 1, 32, 32, g_Itemeffect.m_hndl);
	}
}

//エフェクト更新関数
 void UpdateItemEffect()
{
	for (int i = 0; i < EFFECTITEM_MAX;i++)
	{
		//表示されているエフェクトだけを更新
		if (g_Itemeffect.m_Itemeffect[i].m_isActive == 1)
		{	
			//カウントを少しずつ増やすことによって表示させる画像を変える
			g_Itemeffect.m_Itemeffect[i].m_animCnt += ANIMITEM_SPEED;
			//一番最後の画像が表示されたらフラグを消す
			if (g_Itemeffect.m_Itemeffect[i].m_animCnt >= ANIMITEM_NUM)
			{
				g_Itemeffect.m_Itemeffect[i].m_isActive = 0;
			}
		}
	}

}

//表示関数
void DrawItemEffect()
{
	
	for (int i = 0; i < EFFECTITEM_MAX;i++)
	{
		//フラグがオンのエフェクトだけ表示
		if (g_Itemeffect.m_Itemeffect[i].m_isActive == 1)
		{
			DrawRotaGraph((int)g_Itemeffect.m_Itemeffect[i].m_pos.x, (int)g_Itemeffect.m_Itemeffect[i].m_pos.y , 1.0, 0.0, g_Itemeffect.m_hndl[(int)g_Itemeffect.m_Itemeffect[i].m_animCnt], TRUE);
		}
	}
}

//終了前の処理
void ExitItemEffect()
{
	if (g_Itemeffect.m_hndl[0] != -1)
	{
		//全ての画像データを削除
		for (int i = 0; i < ANIMITEM_NUM;i++)
		{
			DeleteGraph(g_Itemeffect.m_hndl[i]);
			g_Itemeffect.m_hndl[i] = -1;
		}
	}
}

//エフェクト呼び出し（リクエスト）
void RequestItemExplosion(VECTOR pos)
{
	for (int i = 0; i < EFFECTITEM_MAX;i++)
	{
		if (g_Itemeffect.m_Itemeffect[i].m_isActive == 0)
		{
			//エフェクト表示に必要な情報をセット
			g_Itemeffect.m_Itemeffect[i].m_isActive = 1;
			g_Itemeffect.m_Itemeffect[i].m_pos = pos;
			g_Itemeffect.m_Itemeffect[i].m_animCnt = 0.0f;
			break;
		}
	}
}