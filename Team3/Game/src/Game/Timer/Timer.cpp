#include<DxLib.h>
#include"Timer.h"



TIME g_timer;



void InitTime() {

	g_timer.m_cnt = 0;

	for (int i = 0; i < NUMBER; i++)
	{
		g_timer.m_graphHndl[i] = -1;
	}
	
	g_timer.m_time = 0;
	g_timer.hndl = -1;
	g_timer.Timehndl = -1;

	g_timer.m_cnt = 0;
	g_timer.m_minutes = 0;
	g_timer.m_seconds = 0;
	g_timer.count = 0;

}

void LoadTime()
{
	LoadDivGraph("Data/Textures/Number.png", NUMBER, 3, 4, NUMBER_SIZE_X, NUMBER_SIZE_Y,
		g_timer.m_graphHndl);

	LoadDivGraph("Data/Textures/white.png", 1, 1, 1, 32, 32, g_timer.m_white);


	g_timer.hndl = LoadGraph("Data/Textures/canma.png");

	g_timer.Timehndl  = LoadGraph("Data/Textures/Time.png");
}



void DrawCanma() {

	//DrawRotaGraph(STARTPOS_X+21, STARTPOS_Y,0.5, 0.0, g_timer.hndl, TRUE);

	DrawRotaGraph(STARTPOS_X + 21, STARTPOS_Y+10, 0.2, 0.0, g_timer.m_white[0], TRUE);
	DrawRotaGraph(STARTPOS_X + 21, STARTPOS_Y-10, 0.2, 0.0, g_timer.m_white[0], TRUE);


	//DrawRotaGraph(STARTPOS_X-60, STARTPOS_Y, 0.5, 0.0, g_timer.hndl, TRUE);	

	DrawRotaGraph(STARTPOS_X - 59, STARTPOS_Y + 10, 0.2, 0.0, g_timer.m_white[0], TRUE);
	DrawRotaGraph(STARTPOS_X - 59, STARTPOS_Y - 10, 0.2, 0.0, g_timer.m_white[0], TRUE);

	DrawRotaGraph(STARTPOS_X-200, STARTPOS_Y+38, 0.22, 0.0, g_timer.Timehndl, TRUE);
}
void DrawConma(){

	int tempScore = g_timer.m_cnt;
	for (int i = 0; i < DIGIT_NUMBER; i++)
	{
		// 下1桁を取り出す
		int num = tempScore % 10;

		if (num == 9) {
			DrawRotaGraph((STARTPOS_X - (i * NUMBER_SIZE_X / 2))+DISTANCE, STARTPOS_Y,
				0.5, 0.0, g_timer.m_graphHndl[num + 1], TRUE);
		}
		DrawRotaGraph((STARTPOS_X - (i * NUMBER_SIZE_X / 2))+DISTANCE, STARTPOS_Y,
			0.5, 0.0, g_timer.m_graphHndl[num], TRUE);
		// 下1桁を削除
		tempScore /= 10;
	}


}
void DrawSeconds() {
	int tempScore = g_timer.m_seconds;
	for (int i = 0; i < DIGIT_NUMBER; i++)
	{
		// 下1桁を取り出す
		int num = tempScore % 10;

		if (num == 9) {
			DrawRotaGraph(STARTPOS_X - (i * NUMBER_SIZE_X / 2), STARTPOS_Y,
				0.5, 0.0, g_timer.m_graphHndl[num + 1], TRUE);
		}
		DrawRotaGraph(STARTPOS_X - (i * NUMBER_SIZE_X / 2), STARTPOS_Y,
			0.5, 0.0, g_timer.m_graphHndl[num], TRUE);
		// 下1桁を削除
		tempScore /= 10;
	}
}


void DrawMinutets() {
	int tempScore = g_timer.m_minutes;
	for (int i = 0; i < DIGIT_NUMBER; i++)
	{
		// 下1桁を取り出す
		int num = tempScore % 10;

		if (num == 9) {
			DrawRotaGraph((STARTPOS_X - (i * NUMBER_SIZE_X / 2))-DISTANCE, STARTPOS_Y,
				0.5, 0.0, g_timer.m_graphHndl[num + 1], TRUE);
		}
		DrawRotaGraph((STARTPOS_X - (i * NUMBER_SIZE_X / 2))-DISTANCE, STARTPOS_Y,
			0.5, 0.0, g_timer.m_graphHndl[num], TRUE);
		// 下1桁を削除
		tempScore /= 10;
	}
}



int Time() {

	g_timer.m_cnt++;
	if (g_timer.m_cnt >= 100)
	{
		g_timer.m_seconds++;
		g_timer.m_cnt = 0;

		if (g_timer.m_seconds >= 60)
		{
			g_timer.m_minutes++;
			g_timer.m_seconds = 0;
		}
	}

	return g_timer.m_seconds;
}



void ExitTime()
{
	/*for (int i = 0; i < NUMBER; i++)
	{
		if (g_timer.m_graphHndl[i] != -1)
		{
			DeleteGraph(g_timer.m_graphHndl[i]);
			g_timer.m_graphHndl[i] = -1;
		}
	}

	if (g_timer.hndl != -1)
	{
		DeleteGraph(g_timer.hndl);
		g_timer.hndl = -1;
	}*/
}


void ResultTimer() {

	DrawRotaGraph(STARTPOS_X - 200, RESULT_POSY+35, 0.22, 0.0, g_timer.Timehndl, TRUE);

	DrawRotaGraph(STARTPOS_X+21, RESULT_POSY,0.6, 0.0, g_timer.hndl, TRUE);	

	DrawRotaGraph(STARTPOS_X-60, RESULT_POSY, 0.6, 0.0, g_timer.hndl, TRUE);


	int Conma = g_timer.m_cnt;
	for (int i = 0; i < DIGIT_NUMBER; i++)
	{
		// 下1桁を取り出す
		int num = Conma % 10;

		if (num == 9) {
			DrawRotaGraph((STARTPOS_X - (i * NUMBER_SIZE_X / 2)) + DISTANCE, RESULT_POSY,
				0.5, 0.0, g_timer.m_graphHndl[num + 1], TRUE);
		}
		DrawRotaGraph((STARTPOS_X - (i * NUMBER_SIZE_X / 2)) + DISTANCE, RESULT_POSY,
			0.5, 0.0, g_timer.m_graphHndl[num], TRUE);
		// 下1桁を削除
		Conma /= 10;
	}

	int Seco = g_timer.m_seconds;
	for (int i = 0; i < DIGIT_NUMBER; i++)
	{
		// 下1桁を取り出す
		int num = Seco % 10;

		if (num == 9) {
			DrawRotaGraph(STARTPOS_X - (i * NUMBER_SIZE_X / 2), RESULT_POSY,
				0.5, 0.0, g_timer.m_graphHndl[num + 1], TRUE);
		}
		DrawRotaGraph(STARTPOS_X - (i * NUMBER_SIZE_X / 2), RESULT_POSY,
			0.5, 0.0, g_timer.m_graphHndl[num], TRUE);
		// 下1桁を削除
		Seco /= 10;
	}

	int Min = g_timer.m_minutes;
	for (int i = 0; i < DIGIT_NUMBER; i++)
	{
		// 下1桁を取り出す
		int num = Min % 10;

		if (num == 9) {
			DrawRotaGraph((STARTPOS_X - (i * NUMBER_SIZE_X / 2)) - DISTANCE, RESULT_POSY,
				0.5, 0.0, g_timer.m_graphHndl[num + 1], TRUE);
		}
		DrawRotaGraph((STARTPOS_X - (i * NUMBER_SIZE_X / 2)) - DISTANCE, RESULT_POSY,
			0.5, 0.0, g_timer.m_graphHndl[num], TRUE);
		// 下1桁を削除
		Min /= 10;
	}
	
}