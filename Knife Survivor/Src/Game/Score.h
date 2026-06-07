#pragma once
//スコアの初期化
void InitScore();

//スコアの画像ロード
void LoadScore();

//スコアの更新
void StepScore();

//スコアの描画
void DrawScore();

//スコア加算用関数
void AddScore();

//スコアの画像破棄
void ExitScore();

//今のスコアを取得
int GetScore();

//スコアを減らす
void ReduceScore(int n);