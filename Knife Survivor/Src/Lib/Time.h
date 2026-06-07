#pragma once

//タイマー初期化
void TimerInit(int LimitTime);

//タイマー開始
void TimerStart();

//残り時間（秒）を返す
int TimerGetSec();

//時間切れか判定する
bool TimeUp();
