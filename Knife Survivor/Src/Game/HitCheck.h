#pragma once
#include"DxLib.h"


//プレイヤーとアイテムボックスの判定
bool HitCheckPlayerToItem();

//プレイヤーとアイテムクラフトボックスの判定
bool HitCheckPlayerToItemCraft();

//プレイヤーとステージマップチップの当たり判定
void HitCheckPlayerToStage();
void HitCheckPlayer2ToStage();


