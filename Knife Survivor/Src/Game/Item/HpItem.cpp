#include<DxLib.h>
#include"HpItem.h"

extern Player player1;
extern Player2 player2;
extern int Stagenum;
//アイテムデータ初期化関数
void HpItem::Init()
{
	m_hndl = -1;
	m_pos = { 400.0f,450.0f,0.0f };
	m_isdraw = false;
	m_drawtime = 0;
}

//	アイテムデータ読み込み関数
void HpItem::Load()
{
	if (m_hndl == -1)
	{
		m_hndl = LoadGraph("Data/Textures/HpItem.png");
	}
}


//アイテムデータ更新関数
void HpItem::Step()
{
	//ドロータイムが0より大きかったら
	if (m_drawtime >= 0)
	{
		m_drawtime--;
	}
	else
	{
		m_isdraw = false;
	}

	if (m_isdraw == false)
	{
		//変数に乱数を取得する
		int isHpItemDraw = GetRand(500);
		//0だったら描画
		if (isHpItemDraw == 0)
		{
			m_isdraw = true;
			m_pos.x = GetRand(900);
			m_pos.y = GetRand(600);
			m_drawtime = 600;
		}
	}
}

//表示関数
void HpItem::Draw()
{
	if (m_isdraw == true && Stagenum == 3)
	{
		DrawGraph(m_pos.x, m_pos.y, m_hndl, TRUE);
		DrawFormatString(m_pos.x -45,m_pos.y -20 , GetColor(0, 0, 0), "触れるとHPが回復する");
	}
	else if(m_isdraw == true)
	{
		DrawGraph(m_pos.x, m_pos.y, m_hndl, TRUE);
	}
}

//破棄関数
void HpItem::Exit()
{
	if (m_isdraw == false)
	{
		DeleteGraph(m_hndl);
		m_pos = { -100,-100,-100 };
	}
}