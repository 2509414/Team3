#include<DxLib.h>
#include"HitCheck.h"
#include "../Player/Player.h"
#include "../Player/Player2.h"
#include "../Knife/Knife.h"
#include "../Knife/Knife2.h"
#include "../Stage/Stage.h"
#include "../Scene/SceneGame.h"
#include "../../Lib/Collision.h"
#include "../Sound/Sound.h"
#include <corecrt_math.h>


#define PLSIZE (50)		//プレイヤーサイズ
#define ENSIZE (50)		//敵サイズ

extern Player player1;
extern Player2 player2;
extern Knife Knife1;
extern Knife2 knife2;

extern Knife_DATA g_knife;
extern Stage_DATA g_stageData;
extern GAME_SCENE g_gameScene;

void HitCheckPlayerToStage()
{
	//プレイヤーの画像サイズの半分
	int plHalfSizeX = 17;
	int plHalfSizeY = 25;

	//物体の画像サイズの半分
	int objHalfSizeX = 10;
	int	objHalfSizeY = 16;

	//ナイフのサイズ	
	int KnifeSizeX = 12;
	int KnifeSizeY = 5;
	//プレイヤーとナイフとマップチップの座標を取得
	VECTOR knifepos = Knife1.m_pos;
	VECTOR playerPos = player1.m_pos;
	VECTOR mapchipPos = g_stageData.m_stageData[0][0].m_pos;

	for (int y = 0; y < STAGE_Y; y++)
	{
		for (int x = 0; x < STAGE_X; x++)
		{
			//ブロック以外は無視
			if (g_stageData.m_mapData[y][x]/*g_stageData.m_stageData[y][x].m_state*/ == -1)
			{
				continue;
			}

			//ナイフがマップチップに触れたら消える処理
			//マップチップのデータが-1じゃなかったら
			if (g_stageData.m_mapData[y][x] != -1)
			{
				int hitknife = ChenkHitSquareToSquare(Knife1.m_pos, KnifeSizeX, KnifeSizeY, g_stageData.m_stageData[y][x].m_pos, objHalfSizeX, objHalfSizeY);

				if (hitknife != 0)
				{
					Knife1.m_isActive = 0;
				}
			}



			int hit = ChenkHitSquareToSquare(player1.m_pos, plHalfSizeX, plHalfSizeY, g_stageData.m_stageData[y][x].m_pos, objHalfSizeX, objHalfSizeY);

			if (hit != 0)
			{
				//縦横共に離れていないといけない距離を計算する
				float LenX = plHalfSizeX + objHalfSizeX;
				float LenY = plHalfSizeY + objHalfSizeY;

				//実際に離れている距離を縦横ともに計算する
				float distanceX = player1.m_pos.x - g_stageData.m_stageData[y][x].m_pos.x;
				distanceX = fabs(distanceX);

				float distanceY = player1.m_pos.y - g_stageData.m_stageData[y][x].m_pos.y;
				distanceY = fabs(distanceY);

				//上記2つの結果を引き算してめり込んだ距離を取得する
				float OverDistanceX = LenX - distanceX;
				float OverDistanceY = LenY - distanceY;

				//変数を２つ用意　上下左右どこにいるか分かるようにする
				int PosX, PosY;
				if (player1.m_pos.x < g_stageData.m_stageData[y][x].m_pos.x) PosX = -1;
				else PosX = 1;

				if (player1.m_pos.y < g_stageData.m_stageData[y][x].m_pos.y) PosY = -1;
				else PosY = 1;

				if (OverDistanceX < OverDistanceY)
				{
					//押し戻し予定位置に壁がない
					if (g_stageData.m_stageData[y][x + PosX].m_state == -1)
					{
						OverDistanceX *= PosX;
						player1.m_pos.x += OverDistanceX;
					}
					else
					{
						OverDistanceY *= PosY;
						player1.m_pos.y += OverDistanceY;

						if (OverDistanceY < 0)
						{
							player1.SetLand();
						}
					}
				}
				//押し戻し予定位置が無理だったので縦に押し戻す
				else
				{
					if (g_stageData.m_stageData[y + PosY][x].m_state == -1)
					{
						//頭をぶつけたらジャンプパワーを0にする
						//player1.playerSy = 0;

						OverDistanceY *= PosY;

						player1.m_pos.y += OverDistanceY;

						if (OverDistanceY < 0)
						{
							player1.SetLand();
						}
					}
					else
					{
						//正式な押し戻しの計算を行う
						OverDistanceX *= PosX;
						player1.m_pos.x += OverDistanceX;
					}
				}
				DrawFormatString(64, 64, GetColor(255, 255, 255), "X = %f, Y = %f", OverDistanceX, OverDistanceY);
			}
		}
	}

}


void HitCheckPlayer2ToStage()
{
	//プレイヤーの画像サイズの半分
	int plHalfSizeX = 17;
	int plHalfSizeY = 25;

	//物体の画像サイズの半分
	int objHalfSizeX = 10;
	int	objHalfSizeY = 16;

	//ナイフのサイズ	
	int KnifeSizeX = 16;
	int KnifeSizeY = 5;
	//プレイヤーとナイフとマップチップの座標を取得
	VECTOR knifepos = knife2.m_pos;
	VECTOR playerPos = player2.m_pos;
	VECTOR mapchipPos = g_stageData.m_stageData[0][0].m_pos;

	for (int y = 0; y < STAGE_Y; y++)
	{
		for (int x = 0; x < STAGE_X; x++)
		{
			//ブロック以外は無視
			if (g_stageData.m_mapData[y][x]/*g_stageData.m_stageData[y][x].m_state*/ == -1)
			{
				continue;
			}

			//ナイフがマップチップに触れたら消える処理
			//マップチップのデータが-1じゃなかったら
			if (g_stageData.m_mapData[y][x] != -1)
			{
				int hitknife = ChenkHitSquareToSquare(knife2.m_pos, KnifeSizeX, KnifeSizeY, g_stageData.m_stageData[y][x].m_pos, objHalfSizeX, objHalfSizeY);

				if (hitknife != 0)
				{
					knife2.m_isActive = 0;
				}
			}

			//	ブロックにナイフが当たったらぶっ壊す処理
			if (g_stageData.m_mapData[y][x] == 2)
			{
				int hitbrock = ChenkHitSquareToSquare(knife2.m_pos, 20, 3, g_stageData.m_stageData[y][x].m_pos, 30, 21);

				if (hitbrock != 0)
				{
					g_stageData.m_mapData[y][x] = -1;
					knife2.m_isActive = 0;
					PlaybackSound(1);
				}
			}

			int hit = ChenkHitSquareToSquare(player2.m_pos, plHalfSizeX, plHalfSizeY, g_stageData.m_stageData[y][x].m_pos, objHalfSizeX, objHalfSizeY);

			if (hit != 0)
			{
				//縦横共に離れていないといけない距離を計算する
				float LenX = plHalfSizeX + objHalfSizeX;
				float LenY = plHalfSizeY + objHalfSizeY;

				//実際に離れている距離を縦横ともに計算する
				float distanceX = player2.m_pos.x - g_stageData.m_stageData[y][x].m_pos.x;
				distanceX = fabs(distanceX);

				float distanceY = player2.m_pos.y - g_stageData.m_stageData[y][x].m_pos.y;
				distanceY = fabs(distanceY);

				//上記2つの結果を引き算してめり込んだ距離を取得する
				float OverDistanceX = LenX - distanceX;
				float OverDistanceY = LenY - distanceY;

				//変数を２つ用意　上下左右どこにいるか分かるようにする
				int PosX, PosY;
				if (player2.m_pos.x < g_stageData.m_stageData[y][x].m_pos.x) PosX = -1;
				else PosX = 1;

				if (player1.m_pos.y < g_stageData.m_stageData[y][x].m_pos.y) PosY = -1;
				else PosY = 1;

				if (OverDistanceX < OverDistanceY)
				{
					//押し戻し予定位置に壁がない
					if (g_stageData.m_stageData[y][x + PosX].m_state == -1)
					{
						OverDistanceX *= PosX;
						player2.m_pos.x += OverDistanceX;
					}
					else
					{
						OverDistanceY *= PosY;
						player2.m_pos.y += OverDistanceY;

						if (OverDistanceY < 0)
						{
							player2.SetLand();
						}
					}
				}
				//押し戻し予定位置が無理だったので縦に押し戻す
				else
				{
					if (g_stageData.m_stageData[y + PosY][x].m_state == -1)
					{
						//頭をぶつけたらジャンプパワーを0にする
						player2.playerSy = 0;

						OverDistanceY *= PosY;

						player2.m_pos.y += OverDistanceY;

						if (OverDistanceY < 0)
						{
							player2.SetLand();
						}
					}
					else
					{
						//正式な押し戻しの計算を行う
						OverDistanceX *= PosX;
						player2.m_pos.x += OverDistanceX;
					}
				}
				DrawFormatString(64, 64, GetColor(255, 255, 255), "X = %f, Y = %f", OverDistanceX, OverDistanceY);
			}
		}
	}

}




