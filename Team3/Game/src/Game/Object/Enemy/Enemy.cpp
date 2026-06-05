#include <dxlib.h>
#include "../../../Lib/KeyInput/KeyInput.h"
#include "../../Object/Player/Player.h"
#include"../../../Comon.h"
#include"../../../Lib/Effect/Effect.h"
#include"Enemy.h"

// 各種定義
#define START_X (100.0f)	// スタート地点
#define START_Y (0.0f)	// スタート地点
#define MOVE_SPEED (3.0f)	// 歩き速度
#define GRAVITY (0.3f)		// 重力
#define ANIM_SPEED (0.25f)	// アニメーション速度
#define ATTACK_FRAME (10.0f)//攻撃フレーム


// それぞれの画像のパス
const char FILE_PATH[][128] = {"Data/Textures/Player/RUN.png"
	
};
// 画像の全枚数
const int GRAPH_NUM[] = {8};
// アニメーションをループさせるか
const bool IS_LOOP_ANIM[] = {true};

Enemy_DATA g_enemy;

//-------------------------------
//		プレイヤーデータ初期化関数
//-------------------------------
void InitEnemy()
{
	// プレイヤー本体の初期化
	for (int i = 0; i < ENSTATE_NUM; i++)
	{
		for (int j = 0; j < ENEMY_MAX_ANIMNUM; j++)
		{
			g_enemy.m_hndl[i][j] = -1;
		}
	}

	g_enemy.m_animCount = 0.0f;
	g_enemy.m_attackflame = 0.0f;
	g_enemy.m_isActive = true;
	g_enemy.m_isTurn = false;
	g_enemy.m_land_flag = false;
	g_enemy.m_life = 1;
	g_enemy.m_move = false;
	g_enemy.m_shotPowX = 0.0f;
	g_enemy.m_shotPowY = 0.0f;
	g_enemy.m_shot_flag = false;


}


//-------------------------------
//		プレイヤーデータ読み込み関数
//-------------------------------
void LoadEnemy()
{
	// プレイヤーの画像をロード
	// 全画像統一感のあるルールなので成せる業
	for (int i = 0; i < PLSTATE_NUM; i++)
	{
		LoadDivGraph(FILE_PATH[i], GRAPH_NUM[i], GRAPH_NUM[i], 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, g_enemy.m_hndl[i]);
	}
}


//-------------------------------
//		プレイヤーデータ更新関数
//-------------------------------
void StepEnemy()
{
	// 各状態に合わせて関数呼び出し
	switch (g_enemy.m_state)
	{
	case ENSTATE_IDLE:
		IdlePlayerExec();
		break;
	case ENSTATE_WALK:
		WalkPlayerExec();
		break;
	case ENSTATE_SHOT:
		ShotPlayerExec();
		break;
	case ENSTATE_DETH:
		DethEnemyExec();
		break;
	}

	// アニメーション更新
	g_enemy.m_animCount += ANIM_SPEED;
	if (g_enemy.m_animCount >= GRAPH_NUM[g_enemy.m_state])
	{
		// 最後まで来たらループするか、停止するかで値を変更
		if (IS_LOOP_ANIM[g_enemy.m_state])
			g_enemy.m_animCount = 0.0f;
		else
			g_enemy.m_animCount = GRAPH_NUM[g_enemy.m_state] - 1.0f;
	}

}


//-------------------------------
//		プレイヤー表示関数
//-------------------------------
void DrawEnemy()
{
	if (!g_enemy.m_isActive) return;
	// プレイヤー表示
	int animID = (int)g_enemy.m_animCount;
	// オフセット値を考慮して描画場所を決める
	VECTOR offsetPos = GetOffset();
	VECTOR drawPos;
	drawPos.x = g_enemy.m_pos.x - offsetPos.x;
	drawPos.y = g_enemy.m_pos.y - offsetPos.y;
	DrawRotaGraph((int)drawPos.x, drawPos.y, 1.0, 0.0,
		g_enemy.m_hndl[g_enemy.m_state][animID], TRUE, g_enemy.m_isTurn);
}


//-------------------------------
//		終了前の処理関数
//-------------------------------
void ExitEnemy()
{
	for (int i = 0; i < PLSTATE_NUM; i++)
	{
		for (int j = 0; j < PLAYER_MAX_ANIMNUM; j++)
		{
			DeleteGraph(g_enemy.m_hndl[i][j]);
			g_enemy.m_hndl[i][j] = -1;
		}
	}
}






//-------------------------------
//		待機中に実行するもの
//-------------------------------
void IdleEnemyExec()
{


	// 行動の優先順位が高いものから実行
	// 歩き状態へ
	if (WalkEnemy() == true)
	{
		g_enemy.m_animCount = 0;
		g_enemy.m_state = PLSTATE_WALK;
	}
	// ショット状態へ
	else if (ShotEnemy() == true)
	{
		g_enemy.m_animCount = 0;
		g_enemy.m_state = PLSTATE_SHOT;
	}
	// デス状態へ
	else if (DethEnemy() == true)
	{
		g_enemy.m_animCount = 0;
		g_enemy.m_state = ENSTATE_DETH;
	}
	else
	{
		// ここまで来たら待機のまま
	}

}




//-------------------------------
//		移動に実行するもの
//-------------------------------
void WalkEnemyExec()
{


	// 行動の優先順位が高いものから実行
	// ショット状態へ
	if (ShotEnemy() == true)
	{
		g_enemy.m_animCount = 0;
		g_enemy.m_state = PLSTATE_SHOT;
	}
	// デス状態へ
	else if (DethEnemy() == true)
	{
		g_enemy.m_animCount = 0;
		g_enemy.m_state = ENSTATE_DETH;
	}
	// 歩き状態のまま
	else if (WalkEnemy() == true)
	{

	}
	// 待機状態へ
	else
	{
		g_enemy.m_animCount = 0;
		g_enemy.m_state = ENSTATE_IDLE;
	}
}


//-------------------------------
//		移動に実行するもの
//-------------------------------
void ShotEnemyExec()
{
	// 行動の優先順位が高いものから実行
	// デス状態へ
	if (DethEnemy() == true)
	{
		g_enemy.m_animCount = 0;
		g_enemy.m_state = ENSTATE_DETH;
	}
	// 歩き状態へ
	if (WalkEnemy() == true)
	{
		g_enemy.m_animCount = 0;
		g_enemy.m_state = PLSTATE_WALK;
	}
	// ショット状態のまま
	else if (ShotEnemy() == true)
	{

	}
	// 待機状態へ
	else
	{
		g_enemy.m_animCount = 0;
		g_enemy.m_state = ENSTATE_IDLE;
	}
}


//-------------------------------
//		ジャンプ中に実行するもの
//-------------------------------
void JumpEnemyExec()
{
	// 地面に着いたら待機状態へ
	if (g_enemy.m_land_flag)
	{
		g_enemy.m_animCount = 0;
		g_enemy.m_state = ENSTATE_IDLE;
	}
	else
	{
		if (DethEnemy() == true)
		{
			g_enemy.m_animCount = 0;
			g_enemy.m_state = ENSTATE_DETH;
		}
	}
}



//-------------------------------
//		デス中に実行するもの
//-------------------------------
void DethEnemyExec()
{
	if (DethEnemy() == true)
	{
		g_enemy.m_animCount = 0;
		g_enemy.m_state = ENSTATE_DETH;
	}
}




//-------------------------------
//		歩き処理
//-------------------------------
bool WalkEnemy()
{
	if (g_enemy.m_move)
	{
		return true;
	}
	// ここに来たら歩き不成立
	return false;
}

//ショット処理
bool ShotEnemy() {
	if (g_enemy.m_shot_flag)
	{
		return true;
	}
}


//デス処理
bool DethEnemy() {
	if (g_enemy.m_life<=0)
	{
		return true;
	}
}



//-------------------------------
//		地面接地時処理
//-------------------------------
void SetLandEnemy(void)
{
	g_enemy.m_land_flag = true;
}


//-------------------------------
//		落下時処理
//-------------------------------
void SetJumpEnemy(void)
{
	g_enemy.m_land_flag = false;
	g_enemy.m_state = ENSTATE_JUMP;

}
