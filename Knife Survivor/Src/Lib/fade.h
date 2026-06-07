#pragma once
//初期化
void InitFade();
//フェード更新
void UpdateFade();
//フェード描画
void DrawFade();

//フェードインリクエスト
void RequestFadeIn();
//フェードアウトリクエスト
void RequestFadeOut();
//フェードインが終了しているか？
bool IsEndFadeIn();
//フェードアウトが終了しているかどうか？
bool IsEndFadeOut();
