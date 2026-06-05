#pragma once

//変数関連初期化
void InitFps();

//次のフレームに進めていいか
bool IsNextFrame();

//FPS更新処理
void StepFps();

//FPS表示関数
void PrintFps();