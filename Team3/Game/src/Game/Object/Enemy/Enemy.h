#pragma once
#include <DxLib.h>

#define ENEMY_MAX_ANIMNUM	(8)	// 一番多いアニメーション枚数

// プレイヤーの状態
enum tagEnemyState {
	ENSTATE_IDLE,		// 待機
	ENSTATE_WALK,		// 移動
	ENSTATE_SHOT,		//ショット
	ENSTATE_DETH,		//死亡
	ENSTATE_JUMP,		//ジャンプ

	ENSTATE_NUM
};

// エネミー操作構造体
typedef struct {
	int m_hndl[ENSTATE_NUM][ENEMY_MAX_ANIMNUM];	// 自機画像ハンドル
	VECTOR m_pos;									// 表示位置
	float m_animCount;								// アニメーション番号
	int m_state;									// エネミーの状態
	float m_attackflame;							//攻撃時間
	float m_shotPowX;								//ショットベクトルX
	float m_shotPowY;								//ショットベクトルY
	int m_life;										// 体力
	bool m_isTurn;									// 画像を反転させるか
	bool m_isActive;								// 生存フラグ
	bool m_land_flag;								//地面に立っているかフラグ
	bool m_move;
	bool m_shot_flag;

}Enemy_DATA;


//	プレイヤーデータ初期化関数
void InitEnemy();
//	プレイヤーデータ読み込み関数
void LoadEnemy();
//	プレイヤーデータ更新関数
void StepEnemy();
//	プレイヤー表示関数
void DrawEnemy();
//	終了前の処理関数
void ExitEnemy();

// 各種行動時に実行する内容
void IdleEnemyExec();
void WalkEnemyExec();
void ShotEnemyExec();
void DethEnemyExec();
void JumpEnemyExec();



// よく行われる行動の処理
// 歩き処理
// @return : 歩きが成立したか
bool WalkEnemy();
// ジャンプ処理
// @return : ジャンプが成立したか
bool JumpEnemy();

// ショット処理
// @return : ショットが成立したか
bool ShotEnemy();

// ショット処理
// @return : ショットが成立したか
bool DethEnemy();



////		地面接地時処理
void SetLandEnemy();
////		落下時処理
void SetJumpEnemy();
