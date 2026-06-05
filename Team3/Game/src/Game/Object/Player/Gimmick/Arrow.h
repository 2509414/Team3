#include <DxLib.h>


struct Arrow
{

	int m_graphHndl;
	VECTOR m_pos;
	bool isActive;
	VECTOR m_pow;
	bool m_moveflag;
	VECTOR m_len;
	float m_angle;

};



//		矢印初期化関数
void InitArrow();
//		矢印データ読み込み
void LoadArrow();
//		矢印データ更新関数
void StepARROW();
//		矢印データ表示関数
void DrawArrow(VECTOR Plpos );
