#pragma once


#include <DxLib.h>
#include "../../../Comon.h"

#define ANIM_NUM (7)
#define X_NUM	 (7)
#define Y_NUM	 (1)
#define X_SIZE	 (66)
#define Y_SIZE	 (62)
#define ANIM_SPEED (0.1f)


// ステージオブジェクト構造体
struct OBJECT_DATA {
	VECTOR m_pos;	// 座標
	int m_state;	// // ステージデータ　0=床・壁　1=宝箱　2= コイン  -1=何もなし
	float m_animCnt;
};

// ステージデータ構造体
struct STAGE_DATA {
	OBJECT_DATA m_stageData[STAGE_Y][STAGE_X];
	int m_graphHndl[STAGEID_NUM];		// 画像ハンドル
	int m_animHndl[ANIM_NUM];
	int m_magma_cnt;
	int m_magma[1];
	int m_white[1];
	int m_blue[1];
	int m_red[1];



	int m_cnt;
};


//		ステージ初期化
void InitStage();
//		ステージロード
void LoadStage();
//		ステージ更新
void UpdateStage();
//		ステージ描画
void DrawStage();
//		ステージ破棄
void ExitStage();
