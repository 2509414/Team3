#include<DxLib.h>
#include"controller.h"

//アイテムデータ初期化関数
void Controller::Init()
{
	m_hndl = -1;
}

//	アイテムデータ読み込み関数
void Controller::Load()
{
	if (m_hndl == -1)
	{
		m_hndl = LoadGraph("Data/Textures/controller.png");
	}
}


//アイテムデータ更新関数
void Controller::Step()
{
	
}

//表示関数
void Controller::Draw()
{
	DrawGraph(270, 100, m_hndl, TRUE);
}

//破棄関数
void Controller::Exit()
{
	DeleteGraph(m_hndl);
	m_hndl = -1;
}