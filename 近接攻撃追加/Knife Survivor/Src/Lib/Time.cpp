#include <DxLib.h>
#include "time.h"

/*static*/ int g_LimitTime = 0;	//制限時間
/*static*/ int g_StartTime = 0; //開始時間

//タイマー初期化
void TimerInit(int LimitTime)
{
	g_LimitTime = LimitTime * 1000;
}

//タイマー開始
void TimerStart()
{
	g_StartTime = GetNowCount();
}

//残り時間
int TimerGetSec()
{
	int now = GetNowCount();

	int elapsed = now - g_StartTime; //経過した時間
	int remaining = g_LimitTime - elapsed;	//残り時間

	//残り時間が0より小さくなったら
	if (remaining < 0)
	{
		//0に固定する
		remaining = 0;
	}
	return remaining / 1000;	//秒にして返す
}

//時間切れかどうか
bool TimeUp()
{
	//残り時間が0より小さかったら
	return TimerGetSec() <= 0;
}