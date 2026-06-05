#pragma once
#include <DxLib.h>

#define PLAYER_MAX_ANIMNUM	(8)	// 一番多いアニメーション枚数

// プレイヤーの状態
enum tagPlayerState {
	PLSTATE_IDLE,		// 待機
	PLSTATE_WALK,		// 移動
	PLSTATE_JUMP,		// ジャンプ
	PLSTATE_SHOT,		//ショット
	PLSTATE_ATTACK,		//攻撃


	PLSTATE_NUM
};

// プレイヤー操作構造体
typedef struct {
	int m_hndl[PLSTATE_NUM][PLAYER_MAX_ANIMNUM];	// 自機画像ハンドル
	VECTOR m_pos;									// 表示位置
	float m_animCount;								// アニメーション番号
	int m_state;									// プレイヤーの状態
	float m_jumpPow;								// ジャンプ力
	float m_boostpow;
	float m_attackflame;							//攻撃時間
	float m_shotcapa;									//残弾数

	
	int m_life;										// 体力
	bool m_isTurn;									// 画像を反転させるか
	bool m_isActive;								// 生存フラグ
	int m_Gunhndl;									//銃画像ハンドル
	bool Gun_turn_flag;								//銃反転フラグ
	bool m_shot_flag;								//ショットフラグ

	bool m_land_flag;								//地面に立っているかフラグ
	bool m_jump_flag;								//ジャンプフラグ

	int m_mode;//モード
	
	bool m_moveflag;
	VECTOR plshotmove;
	
	bool boostflag;
	int boost_cnt;
	VECTOR boost_pow;

	bool dead_flag;

	int m_coin;

	int seiseicapa;

	VECTOR checkpoint;

	bool goalflag;

	int goalpos;

	int soundhndl;
	int landsound;
	int damagesound;

	bool soundflag;
	bool soundflag_1;
	bool soundflag_2;
	bool soundflag_3;
	bool soundflag_4;

}PLAYER_DATA;


//	プレイヤーデータ初期化関数
void InitPlayer();
//	プレイヤーデータ読み込み関数
void LoadPlayer();
//	プレイヤーデータ更新関数
void StepPlayer();
//	プレイヤー表示関数
void DrawPlayer();
//	終了前の処理関数
void ExitPlayer();

// 各種行動時に実行する内容
void IdlePlayerExec();
void WalkPlayerExec();
void JumpPlayerExec();
void ShotPlayerExec();
void AttackPlayerExec();


// よく行われる行動の処理
// 歩き処理
// @return : 歩きが成立したか
bool WalkPlayer();
// ジャンプ処理
// @return : ジャンプが成立したか
bool JumpPlayer();

// ショット処理
// @return : ショットが成立したか
bool ShotPlayer();

// 攻撃処理
// @return : 攻撃が成立したか
bool AttackPlayer();



////		地面接地時処理
void SetLandPlayer();
////		落下時処理
void SetJumpPlayer();


//オフセット取得
VECTOR GetOffset();

void plshotline(int num);

void plshotmove(int num,VECTOR PlPos,VECTOR ShotPos);

int score();

void boostline();

