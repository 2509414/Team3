#pragma once
#define MAP_CHIP_SIZE (32)		//マップチップの縦横のサイズ
#define MAP_CHIP_X		(10)		// マップチップの画像枚数(横)
#define MAP_CHIP_Y		(1)	// マップチップの画像枚数(縦)
#define STAGE_WIDTH		(184)	// ステージの横に敷き詰められるマップチップの数
#define STAGE_HEIGHT	(19)	// ステージの縦に敷き詰められるマップチップの数
#define STAGE_Y			(150)
#define	STAGE_X			(184)
#define OBJECT_SIZE_X (32)
#define OBJECT_SIZE_Y (32)
//ステージオブジェクト構造体
typedef struct
{
	VECTOR m_pos;	//座標
	int m_state;	
}OBJECT_DATA;

//マップのデータを管理する構造体
typedef struct
{
	OBJECT_DATA m_stageData[STAGE_Y][STAGE_X];
	int m_mapData[STAGE_HEIGHT][STAGE_WIDTH];		// マップのデータ格納
	int m_BlockTimer[STAGE_HEIGHT][STAGE_WIDTH];	//設置したブロックのタイマー
	int m_hndl[MAP_CHIP_X * MAP_CHIP_Y];			//マップチップの画像ハンドル
}Stage_DATA;

//初期化処理
void InitStage();

//終了処理
void ExitStage();

//マップチップ画像の読込み
void LoadStageGraph();

//ステージデータの読込み
void LoadStageData(int Stagenum);

//ステージの描画
void DrawStage();

void UpdateStage();

