#pragma once
#include<DxLib.h>

//エフェクトデータ初期化
void InitItemEffect();
//エフェクトデータロード
void LoadItemEffect();
//エフェクトデータ更新
void UpdateItemEffect();
//エフェクトデータ表示
void DrawItemEffect();
//終了前の処理
void ExitItemEffect();

void RequestItemExplosion(VECTOR pos);
