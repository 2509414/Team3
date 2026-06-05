#pragma once
#include<DxLib.h>

//		エフェクトデータ初期化関数
void InitEffect();
//		エフェクトデータ読み込み
void LoadEffect();
//		エフェクトデータ更新関数
void StepEffect();
//		エフェクトデータ表示関数
void DrawEffect();
//		終了前の処理関数
void ExitEffect();
//エフェクトの呼び出し
void RequestEffect(VECTOR pos);