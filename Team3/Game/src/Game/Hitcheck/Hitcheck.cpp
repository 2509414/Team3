#include "../Object/Player/Player.h"
#include "../Object/Stage/Stage.h"
#include "../../Comon.h"
#include "../../Lib/Collision/Collision.h"
#include"../../Lib/KeyInput/KeyInput.h"
#include "../Object/Enemy/Enemy.h"
#include"../../Lib/Effect/Effect.h"
#include"../Object/Player/Gimmick/Arrow.h"
#include "Hitcheck.h"

// プレイヤー情報が格納された構造体
extern PLAYER_DATA g_player;
// マップチップの情報が格納された構造体
// 2次元配列として使う
extern STAGE_DATA g_stage;

extern Shot g_plshot[PLSHOT_MAX];

Mouse_Data g_mouse_stage;


extern Enemy_DATA g_enemy;

extern Arrow g_arrow;


//-------------------------------
//		プレイヤーとステージオブジェクトの当たり判定
//-------------------------------
void HitCheckPlayerToStage()
{
	//プレイヤーの画像サイズの半分
	int plHalfSizeX = PLAYER_SIZEX / 2;
	int plHalfSizeY = PLAYER_SIZEY / 2;
	//物体の画像サイズの半分
	int objHlfSizeX = OBJECT_SIZE_X / 2;
	int objHlfSizeY = OBJECT_SIZE_Y / 2;


	bool isHit = false;


	VECTOR playerPos = g_player.m_pos;
	VECTOR mapchipPos = g_stage.m_stageData[0][0].m_pos;

	for (int y = 0; y < STAGE_Y; y++)
	{
		for (int x = 0; x < STAGE_X; x++)
		{
			if (g_stage.m_stageData[y][x].m_state != STAGEID_BLOCK)continue;

			int hit = ChenkHitSquareToSquare(g_player.m_pos, g_stage.m_stageData[y][x].m_pos,
				plHalfSizeX, plHalfSizeY, objHlfSizeX, objHlfSizeY);

			if (hit != 0)
			{
				isHit = true;
				//縦、横ともに本来離れていないといけない距離を計算する
				float lenX = (float)plHalfSizeX + objHlfSizeX;
				float lenY = (float)plHalfSizeY + objHlfSizeY;
				//実際に離れている距離を縦横ともに計算する
				float nowLenX = g_player.m_pos.x - g_stage.m_stageData[y][x].m_pos.x;
				nowLenX = fabsf(nowLenX);
				float nowLenY = g_player.m_pos.y - g_stage.m_stageData[y][x].m_pos.y;
				nowLenY = fabsf(nowLenY);
				//上記二つの結果を引き算して、めり込んだ距離を計算する
				float hitLenX = lenX - nowLenX;
				float hitLenY = lenY - nowLenY;
				//変数を二つ用意し、上下左右のどこにいるかわかるようにする
				int posX, posY;
				if (g_player.m_pos.x < g_stage.m_stageData[y][x].m_pos.x)posX = -1;
				else posX = 1;
				if (g_player.m_pos.y < g_stage.m_stageData[y][x].m_pos.y)posY = -1;
				else posY = 1;

				//めり込みが横のほうが小さいので横に押し戻し
				if (hitLenX < hitLenY)
				{
					//押し戻し予定位置に壁がない
					if (g_stage.m_stageData[y][x + posX].m_state != STAGEID_BLOCK)
					{
						//正式な押し戻しの計算を行う
						hitLenX *= posX;
						g_player.m_pos.x += hitLenX;

					}
					//押し戻し予定位置が無理だったので、縦に押し戻す
					else
					{
						//正式なもしも年の計算を行う
						hitLenY *= posY;
						g_player.m_pos.y += hitLenY;
						//押し戻し方向が上なら、地面と当たったはず
						if (hitLenY < 0)
						{
							SetLandPlayer();	//待機状態に移行させる
						}
						else {
							for (int i = 0; i < PLSHOT_MAX; i++)
							{
								if (!g_plshot[i].m_isActiv)continue;

								if (g_player.m_moveflag)
								{
									g_player.plshotmove = { 0 };
									g_player.m_moveflag = false;
								//	g_plshot[i].m_isActiv = false;
								}
							}
						}

					}
				}

				//めり込みが縦のほうが小さいので縦に押し戻し
				else
				{
					//押し戻し予定位置に壁がない
					if (g_stage.m_stageData[y + posY][x].m_state != STAGEID_BLOCK)
					{
						// 正式な押し戻しの計算を行う
						hitLenY *= posY;
						g_player.m_pos.y += hitLenY;
						// 押し戻し方向が上なら、地面と当たったはず
						if (hitLenY < 0)
						{
							SetLandPlayer();	// 待機状態に移行させる
						}
						else
						{
							for (int i = 0; i < PLSHOT_MAX; i++)
							{
								if (!g_plshot[i].m_isActiv)continue;

								if (g_player.m_moveflag)
								{
									g_player.plshotmove = { 0 };
									g_player.m_moveflag = false;
								//	g_plshot[i].m_isActiv = false;
								}
							}
						}
					}
					else
					{
						//正式な押し戻しの計算を行う
						hitLenX *= posX;
						g_player.m_pos.x += hitLenX;
					}
				}
			}
		}
	}
	// ブロックと一切あたっていない
	if (isHit == false)
	{
		g_player.soundflag = true;

		// 強制的にプレイヤーをジャンプ状態に
		SetJumpPlayer();
	}
}



void HitCheckPlShotToStage() {

	//弾の画像サイズの半分
	int plshotHalfSizeX = SHOT_SIZEX / 2;
	int plshotHalfSizeY = SHOT_SIZEY / 2;
	//物体の画像サイズの半分
	int objHlfSizeX = OBJECT_SIZE_X / 2;
	int objHlfSizeY = OBJECT_SIZE_Y / 2;

	bool isHit = false;

	VECTOR shotPos = g_plshot[0].m_pos;
	VECTOR mapchipPos = g_stage.m_stageData[0][0].m_pos;

	for (int i = 0; i < PLSHOT_MAX; i++)
	{
		if (!g_plshot[i].m_isActiv)continue;

		for (int y = 0; y < STAGE_Y; y++)
		{
			for (int x = 0; x < STAGE_X; x++)
			{
				if (g_stage.m_stageData[y][x].m_state != STAGEID_BLOCK)continue;

				int hit = ChenkHitSquareToSquare(g_plshot[i].m_pos, g_stage.m_stageData[y][x].m_pos,
					plshotHalfSizeX, plshotHalfSizeY, objHlfSizeX, objHlfSizeY);

				int posX, posY;
				if (g_plshot[i].m_pos.x < g_stage.m_stageData[y][x].m_pos.x)posX = -1;
				else posX = 1;
				if (g_plshot[i].m_pos.y < g_stage.m_stageData[y][x].m_pos.y)posY = -1;
				else posY = 1;



				if (hit != 0)
				{
					g_plshot[i].m_moveflag = false;
					g_player.m_moveflag = true;
					isHit = true;
				}
			}
		}
	}
}


void HitCheckPlShotToSpace() {

	//弾の画像サイズの半分
	int plshotHalfSizeX = SHOT_SIZEX / 2;
	int plshotHalfSizeY = SHOT_SIZEY / 2;
	//物体の画像サイズの半分
	int objHlfSizeX = OBJECT_SIZE_X / 2;
	int objHlfSizeY = OBJECT_SIZE_Y / 2;

	bool isHit = false;

	VECTOR shotPos = g_plshot[0].m_pos;
	VECTOR mapchipPos = g_stage.m_stageData[0][0].m_pos;

	for (int i = 0; i < PLSHOT_MAX; i++)
	{
		if (!g_plshot[i].m_isActiv)continue;

		for (int y = 0; y < STAGE_Y; y++)
		{
			for (int x = 0; x < STAGE_X; x++)
			{
				if (g_stage.m_stageData[y][x].m_state != -1)continue;

				int hit = ChenkHitSquareToSquare(g_plshot[i].m_pos, g_stage.m_stageData[y][x].m_pos,
					plshotHalfSizeX, plshotHalfSizeY, objHlfSizeX, objHlfSizeY);

				int posX, posY;
				if (g_player.m_pos.x < g_stage.m_stageData[y][x].m_pos.x)posX = -1;
				else posX = 1;
				if (g_player.m_pos.y < g_stage.m_stageData[y][x].m_pos.y)posY = -1;
				else posY = 1;




				if (hit != 0)
				{
					g_stage.m_stageData[y][x].m_state = STAGEID_SETTI;
					//g_player.seiseicapa--;
					g_plshot[i].m_isActiv = false;
					isHit = true;
				}
			}
		}
	}
}

void HitCheckPlShotToStage_2() {

	//弾の画像サイズの半分
	int plshotHalfSizeX = SHOT_SIZEX / 2;
	int plshotHalfSizeY = SHOT_SIZEY / 2;
	//物体の画像サイズの半分
	int objHlfSizeX = OBJECT_SIZE_X /2;
	int objHlfSizeY = OBJECT_SIZE_Y /2;

	bool isHit = false;

	VECTOR shotPos = g_plshot[0].m_pos;
	VECTOR mapchipPos = g_stage.m_stageData[0][0].m_pos;

	for (int i = 0; i < PLSHOT_MAX; i++)
	{

		
		if (!g_plshot[i].m_isActiv)continue;

		for (int y = 0; y < STAGE_Y; y++)
		{
			for (int x = 0; x < STAGE_X; x++)
			{
				if (g_stage.m_stageData[y][x].m_state != STAGEID_BOX)continue;

				int hit = ChenkHitSquareToSquare(g_plshot[i].m_pos, g_stage.m_stageData[y][x].m_pos,
					plshotHalfSizeX, plshotHalfSizeY, objHlfSizeX, objHlfSizeY);

				int posX, posY;
				if (g_plshot[i].m_pos.x < g_stage.m_stageData[y][x].m_pos.x)posX = -1;
				else posX = 1;
				if (g_plshot[i].m_pos.y < g_stage.m_stageData[y][x].m_pos.y)posY = -1;
				else posY = 1;

				if (hit != 0)
				{
					g_player.m_moveflag = true;
					g_plshot[i].m_moveflag = false;
					g_plshot[i].m_pos = g_stage.m_stageData[y][x].m_pos;
					
					isHit = true;
				}
			}
		}
	}
}




void HitCheckPlshotToCoin() {

	//弾の画像サイズの半分
	int plshotHalfSizeX = SHOT_SIZEX;
	int plshotHalfSizeY = SHOT_SIZEY;
	//物体の画像サイズの半分
	int objHlfSizeX = OBJECT_SIZE_X;
	int objHlfSizeY = OBJECT_SIZE_Y;

	bool isHit = false;

	VECTOR shotPos = g_plshot[0].m_pos;
	VECTOR mapchipPos = g_stage.m_stageData[0][0].m_pos;

	for (int i = 0; i < PLSHOT_MAX; i++)
	{
		if (!g_plshot[i].m_isActiv)continue;

		for (int y = 0; y < STAGE_Y; y++)
		{
			for (int x = 0; x < STAGE_X; x++)
			{
				if (g_stage.m_stageData[y][x].m_state != STAGEID_COIN)continue;

				int hit = ChenkHitSquareToSquare(g_plshot[i].m_pos, g_stage.m_stageData[y][x].m_pos,
					plshotHalfSizeX, plshotHalfSizeY, objHlfSizeX, objHlfSizeY);

				int posX, posY;
				if (g_plshot[i].m_pos.x < g_stage.m_stageData[y][x].m_pos.x)posX = -1;
				else posX = 1;
				if (g_plshot[i].m_pos.y < g_stage.m_stageData[y][x].m_pos.y)posY = -1;
				else posY = 1;

				if (hit != 0)
				{

					

					g_stage.m_stageData[y][x].m_state = -1;

					g_player.m_coin++;
				
					isHit = true;
				}
			}
		}
	}
}











//-------------------------------
//		敵とステージオブジェクトの当たり判定
//-------------------------------
void HitCheckEnemyToStage()
{
	//敵の画像サイズの半分
	int enHalfSizeX = ENEMY_SIZE_X / 2;
	int enHalfSizeY = ENEMY_SIZE_Y / 2;
	//物体の画像サイズの半分
	int objHlfSizeX = OBJECT_SIZE_X / 2;
	int objHlfSizeY = OBJECT_SIZE_Y / 2;


	bool isHit = false;


	VECTOR enemyPos = g_player.m_pos;
	VECTOR mapchipPos = g_stage.m_stageData[0][0].m_pos;

	for (int y = 0; y < STAGE_Y; y++)
	{
		for (int x = 0; x < STAGE_X; x++)
		{
			if (g_stage.m_stageData[y][x].m_state != STAGEID_BLOCK)continue;

			int hit = ChenkHitSquareToSquare(g_enemy.m_pos, g_stage.m_stageData[y][x].m_pos,
				enHalfSizeX, enHalfSizeY, objHlfSizeX, objHlfSizeY);

			if (hit != 0)
			{
				isHit = true;
				//縦、横ともに本来離れていないといけない距離を計算する
				float lenX = (float)enHalfSizeX + objHlfSizeX;
				float lenY = (float)enHalfSizeY + objHlfSizeY;
				//実際に離れている距離を縦横ともに計算する
				float nowLenX = g_enemy.m_pos.x - g_stage.m_stageData[y][x].m_pos.x;
				nowLenX = fabsf(nowLenX);
				float nowLenY = g_enemy.m_pos.y - g_stage.m_stageData[y][x].m_pos.y;
				nowLenY = fabsf(nowLenY);
				//上記二つの結果を引き算して、めり込んだ距離を計算する
				float hitLenX = lenX - nowLenX;
				float hitLenY = lenY - nowLenY;
				//変数を二つ用意し、上下左右のどこにいるかわかるようにする
				int posX, posY;
				if (g_enemy.m_pos.x < g_stage.m_stageData[y][x].m_pos.x)posX = -1;
				else posX = 1;
				if (g_enemy.m_pos.y < g_stage.m_stageData[y][x].m_pos.y)posY = -1;
				else posY = 1;

				//めり込みが横のほうが小さいので横に押し戻し
				if (hitLenX < hitLenY)
				{
					//押し戻し予定位置に壁がない
					if (g_stage.m_stageData[y][x + posX].m_state != STAGEID_BLOCK)
					{
						//正式な押し戻しの計算を行う
						hitLenX *= posX;
						g_enemy.m_pos.x += hitLenX;
					}
					//押し戻し予定位置が無理だったので、縦に押し戻す
					else
					{
						//正式なもしも年の計算を行う
						hitLenY *= posY;
						g_enemy.m_pos.y += hitLenY;
						//押し戻し方向が上なら、地面と当たったはず
						if (hitLenY < 0)
						{
						//	SetLandPlayer();	//待機状態に移行させる
						}
					}
				}

				//めり込みが縦のほうが小さいので縦に押し戻し
				else
				{
					//押し戻し予定位置に壁がない
					if (g_stage.m_stageData[y + posY][x].m_state != STAGEID_BLOCK)
					{
						// 正式な押し戻しの計算を行う
						hitLenY *= posY;
						g_enemy.m_pos.y += hitLenY;
						// 押し戻し方向が上なら、地面と当たったはず
						if (hitLenY < 0)
						{
							//SetLandPlayer();	// 待機状態に移行させる
						}
					}
					else
					{
						//正式な押し戻しの計算を行う
						hitLenX *= posX;
						g_enemy.m_pos.x += hitLenX;
					}
				}

			}
		}
	}
	// ブロックと一切あたっていない
	if (isHit == false)
	{
		// 強制的にプレイヤーをジャンプ状態に
		SetJumpEnemy();
	}
}



//-------------------------------
//		プレイヤーとステージオブジェクトの当たり判定
//-------------------------------
void HitCheckPlayerToCoin()
{

	//弾の画像サイズの半分
	int plHalfSizeX = PLAYER_SIZEX / 2;
	int plHalfSizeY = PLAYER_SIZEY / 2;
	//物体の画像サイズの半分
	int objHlfSizeX = OBJECT_SIZE_X / 2;
	int objHlfSizeY = OBJECT_SIZE_Y / 2;

	bool isHit = false;

	for (int y = 0; y < STAGE_Y; y++)
	{
		for (int x = 0; x < STAGE_X; x++)
		{
			if (g_stage.m_stageData[y][x].m_state != STAGEID_COIN)continue;

			int hit = ChenkHitSquareToSquare(g_player.m_pos, g_stage.m_stageData[y][x].m_pos,
				plHalfSizeX, plHalfSizeY, objHlfSizeX, objHlfSizeY);

			if (hit )
			{
				g_stage.m_stageData[y][x].m_state = -1;
				g_player.m_coin++;


				isHit = true;
			}
		}
	}
}



void HitCheckPlayerToMagma() {

	//プレイヤーの画像サイズの半分
	int plHalfSizeX = PLAYER_SIZEX / 2;
	int plHalfSizeY = PLAYER_SIZEY / 2;
	//物体の画像サイズの半分
	int objHlfSizeX = OBJECT_SIZE_X / 2.5;
	int objHlfSizeY = OBJECT_SIZE_Y / 2.5;

	bool isHit = false;

	for (int y = 0; y < STAGE_Y; y++)
	{
		for (int x = 0; x < STAGE_X; x++)
		{
			if (g_stage.m_stageData[y][x].m_state != STAGEID_MAGMA)continue;

			int hit = ChenkHitSquareToSquare(g_player.m_pos, g_stage.m_stageData[y][x].m_pos,
				plHalfSizeX, plHalfSizeY, objHlfSizeX, objHlfSizeY);

			if (hit)
			{
				g_player.dead_flag = true;
				g_player.plshotmove = { 0 };
				
				isHit = true;
			}
		}
	}
}



void HitCheckArrowToStage() {

	//弾の画像サイズの半分
	int plshotHalfSizeX = SHOT_SIZEX / 2;
	int plshotHalfSizeY = SHOT_SIZEY / 2;
	//物体の画像サイズの半分
	int objHlfSizeX = OBJECT_SIZE_X / 2;
	int objHlfSizeY = OBJECT_SIZE_Y / 2;

	bool isHit = false;

	VECTOR ArrowPos = g_arrow.m_pos;
	VECTOR mapchipPos = g_stage.m_stageData[0][0].m_pos;


	for (int y = 0; y < STAGE_Y; y++)
	{
		for (int x = 0; x < STAGE_X; x++)
		{
			if (g_stage.m_stageData[y][x].m_state != STAGEID_BLOCK)continue;

			int hit = ChenkHitSquareToSquare(ArrowPos, g_stage.m_stageData[y][x].m_pos,
				plshotHalfSizeX, plshotHalfSizeY, objHlfSizeX, objHlfSizeY);

			int posX, posY;
			if (ArrowPos.x < g_stage.m_stageData[y][x].m_pos.x)posX = -1;
			else posX = 1;
			if (ArrowPos.y < g_stage.m_stageData[y][x].m_pos.y)posY = -1;
			else posY = 1;


			if (hit != 0)
			{
				g_arrow.m_moveflag = false;
				isHit = true;
			}
		}
	}
}


void HitCheckArrowToBox() {

	//弾の画像サイズの半分
	int plshotHalfSizeX = SHOT_SIZEX / 2;
	int plshotHalfSizeY = SHOT_SIZEY / 2;
	//物体の画像サイズの半分
	int objHlfSizeX = OBJECT_SIZE_X / 2;
	int objHlfSizeY = OBJECT_SIZE_Y / 2;

	bool isHit = false;

	VECTOR ArrowPos = g_arrow.m_pos;
	VECTOR mapchipPos = g_stage.m_stageData[0][0].m_pos;


	for (int y = 0; y < STAGE_Y; y++)
	{
		for (int x = 0; x < STAGE_X; x++)
		{
			if (g_stage.m_stageData[y][x].m_state != STAGEID_BOX)continue;

			int hit = ChenkHitSquareToSquare(ArrowPos, g_stage.m_stageData[y][x].m_pos,
				plshotHalfSizeX, plshotHalfSizeY, objHlfSizeX, objHlfSizeY);

			int posX, posY;
			if (ArrowPos.x < g_stage.m_stageData[y][x].m_pos.x)posX = -1;
			else posX = 1;
			if (ArrowPos.y < g_stage.m_stageData[y][x].m_pos.y)posY = -1;
			else posY = 1;


			if (hit != 0)
			{
				g_arrow.m_moveflag = false;
				isHit = true;
			}
		}
	}
}


void HitCheckPlshotToWhite(){

	//弾の画像サイズの半分
	int plshotHalfSizeX = SHOT_SIZEX / 2;
	int plshotHalfSizeY = SHOT_SIZEY / 2;
	//物体の画像サイズの半分
	int objHlfSizeX = OBJECT_SIZE_X / 2;
	int objHlfSizeY = OBJECT_SIZE_Y / 2;

	bool isHit = false;

	VECTOR shotPos = g_plshot[0].m_pos;
	VECTOR mapchipPos = g_stage.m_stageData[0][0].m_pos;

	for (int i = 0; i < PLSHOT_MAX; i++)
	{


		if (!g_plshot[i].m_isActiv)continue;

		for (int y = 0; y < STAGE_Y; y++)
		{
			for (int x = 0; x < STAGE_X; x++)
			{
				if (g_stage.m_stageData[y][x].m_state != STAGEID_WHITE)continue;

				int hit = ChenkHitSquareToSquare(g_plshot[i].m_pos, g_stage.m_stageData[y][x].m_pos,
					plshotHalfSizeX, plshotHalfSizeY, objHlfSizeX, objHlfSizeY);

			
				if (hit != 0)
				{
					g_player.m_moveflag = true;
					g_plshot[i].m_moveflag = false;
					g_plshot[i].m_pos = g_stage.m_stageData[y][x].m_pos;

					isHit = true;
				}
			}
		}
	}
}





//-------------------------------
//		プレイヤーとステージオブジェクトの当たり判定
//-------------------------------
void HitCheckPlayerToWhite()
{
	//プレイヤーの画像サイズの半分
	int plHalfSizeX = PLAYER_SIZEX / 2;
	int plHalfSizeY = PLAYER_SIZEY / 2;
	//物体の画像サイズの半分
	int objHlfSizeX = OBJECT_SIZE_X / 2;
	int objHlfSizeY = OBJECT_SIZE_Y / 2;


	bool isHit = false;


	VECTOR playerPos = g_player.m_pos;
	VECTOR mapchipPos = g_stage.m_stageData[0][0].m_pos;

	for (int y = 0; y < STAGE_Y; y++)
	{
		for (int x = 0; x < STAGE_X; x++)
		{
			if (g_stage.m_stageData[y][x].m_state != STAGEID_WHITE)continue;

			int hit = ChenkHitSquareToSquare(g_player.m_pos, g_stage.m_stageData[y][x].m_pos,
				plHalfSizeX, plHalfSizeY, objHlfSizeX, objHlfSizeY);

			if (hit != 0)
			{
				isHit = true;
				//縦、横ともに本来離れていないといけない距離を計算する
				float lenX = (float)plHalfSizeX + objHlfSizeX;
				float lenY = (float)plHalfSizeY + objHlfSizeY;
				//実際に離れている距離を縦横ともに計算する
				float nowLenX = g_player.m_pos.x - g_stage.m_stageData[y][x].m_pos.x;
				nowLenX = fabsf(nowLenX);
				float nowLenY = g_player.m_pos.y - g_stage.m_stageData[y][x].m_pos.y;
				nowLenY = fabsf(nowLenY);
				//上記二つの結果を引き算して、めり込んだ距離を計算する
				float hitLenX = lenX - nowLenX;
				float hitLenY = lenY - nowLenY;
				//変数を二つ用意し、上下左右のどこにいるかわかるようにする
				int posX, posY;
				if (g_player.m_pos.x < g_stage.m_stageData[y][x].m_pos.x)posX = -1;
				else posX = 1;
				if (g_player.m_pos.y < g_stage.m_stageData[y][x].m_pos.y)posY = -1;
				else posY = 1;


				//押し戻し予定位置に壁がない
				if (g_stage.m_stageData[y + posY][x].m_state != STAGEID_WHITE)
				{
					// 正式な押し戻しの計算を行う
					hitLenY *= posY;
					

					// 押し戻し方向が上なら、地面と当たったはず
					if (hitLenY < 0)
					{
						g_player.m_pos.y += hitLenY;
						
						if (!g_player.m_moveflag)
						{


							g_player.checkpoint.x = g_stage.m_stageData[y][x].m_pos.x;
							g_player.checkpoint.y = g_stage.m_stageData[y-1][x].m_pos.y;


							SetLandPlayer();	// 待機状態に移行させる
						}
					
					}
				}
			}

		}
}

	// ブロックと一切あたっていない
	if (isHit == false)
	{
		g_player.soundflag_1 = true;

		// 強制的にプレイヤーをジャンプ状態に
		SetJumpPlayer();
	}
}





//
//void HitCheckWireToStage() {
//
//	//物体の画像サイズの半分
//	int objHlfSizeX = OBJECT_SIZE_X / 2;
//	int objHlfSizeY = OBJECT_SIZE_Y / 2;
//
//	VECTOR shotPos = g_plshot[0].m_pos;
//	VECTOR mapchipPos = g_stage.m_stageData[0][0].m_pos;
//
//	g_mouse_stage.GetMouse();
//
//
//	VECTOR offsetPos = GetOffset();
//	VECTOR drawPos_player, drawPos_arrow;
//
//
//
//	drawPos_arrow.x = g_mouse_stage.m_posX + offsetPos.x;
//	drawPos_arrow.y = g_mouse_stage.m_posY + offsetPos.y;
//
//	VECTOR mouse_pos = { drawPos_arrow.x ,drawPos_arrow.y,0 };
//
//	for (int i = 0; i < PLSHOT_MAX; i++)
//	{
//		if (!g_plshot[i].m_isActiv)continue;
//
//		for (int y = 0; y < STAGE_Y; y++)
//		{
//			for (int x = 0; x < STAGE_X; x++)
//			{
//				if (g_stage.m_stageData[y][x].m_state != STAGEID_BLOCK)continue;
//
//				bool hit = CheckHitLinetoSquare(g_stage.m_stageData[y][x].m_pos,g_player.m_pos,g_plshot[i].m_pos,
//												objHlfSizeX,objHlfSizeY);
//				
//				/*bool hit = CheckHitLinetoSquare(g_stage.m_stageData[y][x].m_pos, g_player.m_pos,mouse_pos,
//					objHlfSizeX, objHlfSizeY);*/
//
//				if (hit)
//				{
//					DrawFormatString(WINDOW_SIZE_X/2,WINDOW_SIZE_Y/2,GetColor(255,255,255),"衝突");
//
//				/*	g_player.m_moveflag = true;
//					g_plshot[i].m_moveflag = false;
//					g_plshot[i].m_isActiv = false;*/
//
//				}
//			}
//		}
//	}
//}
//
//-------------------------------
//		プレイヤーとステージオブジェクトの当たり判定
//-------------------------------
void HitCheckPlayerToRed()
{
	//プレイヤーの画像サイズの半分
	int plHalfSizeX = PLAYER_SIZEX / 2;
	int plHalfSizeY = PLAYER_SIZEY / 2;
	//物体の画像サイズの半分
	int objHlfSizeX = OBJECT_SIZE_X / 2;
	int objHlfSizeY = OBJECT_SIZE_Y / 2;


	bool isHit = false;


	VECTOR playerPos = g_player.m_pos;
	VECTOR mapchipPos = g_stage.m_stageData[0][0].m_pos;

	for (int y = 0; y < STAGE_Y; y++)
	{
		for (int x = 0; x < STAGE_X; x++)
		{
			if (g_stage.m_stageData[y][x].m_state != STAGEID_RED)continue;

			int hit = ChenkHitSquareToSquare(g_player.m_pos, g_stage.m_stageData[y][x].m_pos,
				plHalfSizeX, plHalfSizeY, objHlfSizeX, objHlfSizeY);

			if (hit != 0)
			{
				g_player.dead_flag = true;
			
				isHit = true;
				//縦、横ともに本来離れていないといけない距離を計算する
				float lenX = (float)plHalfSizeX + objHlfSizeX;
				float lenY = (float)plHalfSizeY + objHlfSizeY;
				//実際に離れている距離を縦横ともに計算する
				float nowLenX = g_player.m_pos.x - g_stage.m_stageData[y][x].m_pos.x;
				nowLenX = fabsf(nowLenX);
				float nowLenY = g_player.m_pos.y - g_stage.m_stageData[y][x].m_pos.y;
				nowLenY = fabsf(nowLenY);
				//上記二つの結果を引き算して、めり込んだ距離を計算する
				float hitLenX = lenX - nowLenX;
				float hitLenY = lenY - nowLenY;
				//変数を二つ用意し、上下左右のどこにいるかわかるようにする
				int posX, posY;
				if (g_player.m_pos.x < g_stage.m_stageData[y][x].m_pos.x)posX = -1;
				else posX = 1;
				if (g_player.m_pos.y < g_stage.m_stageData[y][x].m_pos.y)posY = -1;
				else posY = 1;

				//めり込みが横のほうが小さいので横に押し戻し
				if (hitLenX < hitLenY)
				{
					//押し戻し予定位置に壁がない
					if (g_stage.m_stageData[y][x + posX].m_state != STAGEID_RED)
					{
						//正式な押し戻しの計算を行う
						hitLenX *= posX;
						g_player.m_pos.x += hitLenX;
					}
					//押し戻し予定位置が無理だったので、縦に押し戻す
					else
					{
						//正式なもしも年の計算を行う
						hitLenY *= posY;
						g_player.m_pos.y += hitLenY;
						//押し戻し方向が上なら、地面と当たったはず
						if (hitLenY < 0)
						{
							SetLandPlayer();	//待機状態に移行させる
						}
					}
				}

				//めり込みが縦のほうが小さいので縦に押し戻し
				else
				{
					//押し戻し予定位置に壁がない
					if (g_stage.m_stageData[y + posY][x].m_state != STAGEID_RED)
					{
						// 正式な押し戻しの計算を行う
						hitLenY *= posY;
						g_player.m_pos.y += hitLenY;
						// 押し戻し方向が上なら、地面と当たったはず
						if (hitLenY < 0)
						{
							SetLandPlayer();	// 待機状態に移行させる
						}
					}
					else
					{
						//正式な押し戻しの計算を行う
						hitLenX *= posX;
						g_player.m_pos.x += hitLenX;
					}
				}
			}
		}
	}
	// ブロックと一切あたっていない
	if (isHit == false)
	{
		g_player.soundflag_2 = true;

		// 強制的にプレイヤーをジャンプ状態に
		SetJumpPlayer();
	}
}




void HitCheckPlshotToRed() {

	//弾の画像サイズの半分
	int plshotHalfSizeX = SHOT_SIZEX / 2;
	int plshotHalfSizeY = SHOT_SIZEY / 2;
	//物体の画像サイズの半分
	int objHlfSizeX = OBJECT_SIZE_X / 2;
	int objHlfSizeY = OBJECT_SIZE_Y / 2;

	bool isHit = false;

	VECTOR shotPos = g_plshot[0].m_pos;
	VECTOR mapchipPos = g_stage.m_stageData[0][0].m_pos;

	for (int i = 0; i < PLSHOT_MAX; i++)
	{

		if (!g_plshot[i].m_isActiv)continue;

		for (int y = 0; y < STAGE_Y; y++)
		{
			for (int x = 0; x < STAGE_X; x++)
			{
				if (g_stage.m_stageData[y][x].m_state != STAGEID_RED)continue;

				int hit = ChenkHitSquareToSquare(g_plshot[i].m_pos, g_stage.m_stageData[y][x].m_pos,
					plshotHalfSizeX, plshotHalfSizeY, objHlfSizeX, objHlfSizeY);


				if (hit != 0)
				{
					//g_plshot[i].m_isActiv = false;


					g_player.m_moveflag = true;
					g_plshot[i].m_moveflag = false;
					g_plshot[i].m_pos = g_stage.m_stageData[y][x].m_pos;





					isHit = true;
				}
			}
		}
	}
}












void HitCheckPlayerToBlue()
{
	//プレイヤーの画像サイズの半分
	int plHalfSizeX = PLAYER_SIZEX / 2;
	int plHalfSizeY = PLAYER_SIZEY / 2;
	//物体の画像サイズの半分
	int objHlfSizeX = OBJECT_SIZE_X / 2;
	int objHlfSizeY = OBJECT_SIZE_Y / 2;


	bool isHit = false;


	VECTOR playerPos = g_player.m_pos;
	VECTOR mapchipPos = g_stage.m_stageData[0][0].m_pos;

	for (int y = 0; y < STAGE_Y; y++)
	{
		for (int x = 0; x < STAGE_X; x++)
		{
			if (g_stage.m_stageData[y][x].m_state != STAGEID_BLUE)continue;

			int hit = ChenkHitSquareToSquare(g_player.m_pos, g_stage.m_stageData[y][x].m_pos,
				plHalfSizeX, plHalfSizeY, objHlfSizeX, objHlfSizeY);

			if (hit != 0)
			{

				isHit = true;
				//縦、横ともに本来離れていないといけない距離を計算する
				float lenX = (float)plHalfSizeX + objHlfSizeX;
				float lenY = (float)plHalfSizeY + objHlfSizeY;
				//実際に離れている距離を縦横ともに計算する
				float nowLenX = g_player.m_pos.x - g_stage.m_stageData[y][x].m_pos.x;
				nowLenX = fabsf(nowLenX);
				float nowLenY = g_player.m_pos.y - g_stage.m_stageData[y][x].m_pos.y;
				nowLenY = fabsf(nowLenY);
				//上記二つの結果を引き算して、めり込んだ距離を計算する
				float hitLenX = lenX - nowLenX;
				float hitLenY = lenY - nowLenY;
				//変数を二つ用意し、上下左右のどこにいるかわかるようにする
				int posX, posY;
				if (g_player.m_pos.x < g_stage.m_stageData[y][x].m_pos.x)posX = -1;
				else posX = 1;
				if (g_player.m_pos.y < g_stage.m_stageData[y][x].m_pos.y)posY = -1;
				else posY = 1;

				//めり込みが横のほうが小さいので横に押し戻し
				if (hitLenX < hitLenY)
				{
					//押し戻し予定位置に壁がない
					if (g_stage.m_stageData[y][x + posX].m_state != STAGEID_BLUE)
					{
						//正式な押し戻しの計算を行う
						hitLenX *= posX;
						g_player.m_pos.x += hitLenX;
					}
					//押し戻し予定位置が無理だったので、縦に押し戻す
					else
					{
						//正式なもしも年の計算を行う
						hitLenY *= posY;
						g_player.m_pos.y += hitLenY;
						//押し戻し方向が上なら、地面と当たったはず
						if (hitLenY < 0)
						{
							SetLandPlayer();	//待機状態に移行させる
						}
					}
				}

				//めり込みが縦のほうが小さいので縦に押し戻し
				else
				{
					//押し戻し予定位置に壁がない
					if (g_stage.m_stageData[y + posY][x].m_state != STAGEID_BLUE)
					{
						// 正式な押し戻しの計算を行う
						hitLenY *= posY;
						g_player.m_pos.y += hitLenY;
						// 押し戻し方向が上なら、地面と当たったはず
						if (hitLenY < 0)
						{
							SetLandPlayer();	// 待機状態に移行させる
						}
					}
					else
					{
						//正式な押し戻しの計算を行う
						hitLenX *= posX;
						g_player.m_pos.x += hitLenX;
					}
				}
			}

		}
	}
	// ブロックと一切あたっていない
	if (isHit == false)
	{
		g_player.soundflag_3 = true;

		// 強制的にプレイヤーをジャンプ状態に
		SetJumpPlayer();
	}
}

void HitCheckPlayerToGoal()
{	//プレイヤーの画像サイズの半分
	int plHalfSizeX = PLAYER_SIZEX / 2;
	int plHalfSizeY = PLAYER_SIZEY / 2;
	//物体の画像サイズの半分
	int objHlfSizeX = OBJECT_SIZE_X / 2.5;
	int objHlfSizeY = OBJECT_SIZE_Y / 2.5;

	bool isHit = false;

	for (int y = 0; y < STAGE_Y; y++)
	{
		for (int x = 0; x < STAGE_X; x++)
		{
			if (g_stage.m_stageData[y][x].m_state != STAGEID_GOAL)continue;

			int hit = ChenkHitSquareToSquare(g_player.m_pos, g_stage.m_stageData[y][x].m_pos,
				plHalfSizeX, plHalfSizeY, objHlfSizeX, objHlfSizeY);

			if (hit)
			{
				g_player.goalflag = true;

				isHit = true;
			}
		}
	}
}




void HitCheckPlshotToBlue() {

	//弾の画像サイズの半分
	int plshotHalfSizeX = SHOT_SIZEX / 2;
	int plshotHalfSizeY = SHOT_SIZEY / 2;
	//物体の画像サイズの半分
	int objHlfSizeX = OBJECT_SIZE_X / 2;
	int objHlfSizeY = OBJECT_SIZE_Y / 2;

	bool isHit = false;

	VECTOR shotPos = g_plshot[0].m_pos;
	VECTOR mapchipPos = g_stage.m_stageData[0][0].m_pos;

	for (int i = 0; i < PLSHOT_MAX; i++)
	{


		if (!g_plshot[i].m_isActiv)continue;

		for (int y = 0; y < STAGE_Y; y++)
		{
			for (int x = 0; x < STAGE_X; x++)
			{
				if (g_stage.m_stageData[y][x].m_state != STAGEID_BLUE)continue;

				int hit = ChenkHitSquareToSquare(g_plshot[i].m_pos, g_stage.m_stageData[y][x].m_pos,
					plshotHalfSizeX, plshotHalfSizeY, objHlfSizeX, objHlfSizeY);


				if (hit != 0)
				{
					/*if (g_player.m_moveflag == false)
					{
						g_stage.m_stageData[y][x].m_state = -1;
					}*/


					g_player.m_moveflag = true;
					g_plshot[i].m_moveflag = false;
					g_plshot[i].m_pos = g_stage.m_stageData[y][x].m_pos;

				


					isHit = true;
				}
			}
		}
	}
}

void HitCheckPlshotToSetti() {

	//弾の画像サイズの半分
	int plshotHalfSizeX = SHOT_SIZEX / 2;
	int plshotHalfSizeY = SHOT_SIZEY / 2;
	//物体の画像サイズの半分
	int objHlfSizeX = OBJECT_SIZE_X / 2;
	int objHlfSizeY = OBJECT_SIZE_Y / 2;

	bool isHit = false;

	VECTOR shotPos = g_plshot[0].m_pos;
	VECTOR mapchipPos = g_stage.m_stageData[0][0].m_pos;

	for (int i = 0; i < PLSHOT_MAX; i++)
	{

		if (!g_plshot[i].m_isActiv)continue;

		for (int y = 0; y < STAGE_Y; y++)
		{
			for (int x = 0; x < STAGE_X; x++)
			{
				if (g_stage.m_stageData[y][x].m_state != STAGEID_SETTI)continue;

				int hit = ChenkHitSquareToSquare(g_plshot[i].m_pos, g_stage.m_stageData[y][x].m_pos,
					plshotHalfSizeX, plshotHalfSizeY, objHlfSizeX, objHlfSizeY);


				if (hit != 0)
				{
					if (g_player.m_moveflag == false)
					{
						g_stage.m_stageData[y][x].m_state = -1;
					}

					g_player.m_moveflag = true;
					g_plshot[i].m_moveflag = false;
					g_plshot[i].m_pos = g_stage.m_stageData[y][x].m_pos;

					isHit = true;
				}
			}
		}
	}
}



void HitCheckPlayerToSetti()
{
	//プレイヤーの画像サイズの半分
	int plHalfSizeX = PLAYER_SIZEX / 2;
	int plHalfSizeY = PLAYER_SIZEY / 2;
	//物体の画像サイズの半分
	int objHlfSizeX = OBJECT_SIZE_X / 2;
	int objHlfSizeY = OBJECT_SIZE_Y / 2;


	bool isHit = false;


	VECTOR playerPos = g_player.m_pos;
	VECTOR mapchipPos = g_stage.m_stageData[0][0].m_pos;

	for (int y = 0; y < STAGE_Y; y++)
	{
		for (int x = 0; x < STAGE_X; x++)
		{
			if (g_stage.m_stageData[y][x].m_state != STAGEID_SETTI)continue;

			int hit = ChenkHitSquareToSquare(g_player.m_pos, g_stage.m_stageData[y][x].m_pos,
				plHalfSizeX, plHalfSizeY, objHlfSizeX, objHlfSizeY);

			if (hit != 0)
			{

				isHit = true;
				//縦、横ともに本来離れていないといけない距離を計算する
				float lenX = (float)plHalfSizeX + objHlfSizeX;
				float lenY = (float)plHalfSizeY + objHlfSizeY;
				//実際に離れている距離を縦横ともに計算する
				float nowLenX = g_player.m_pos.x - g_stage.m_stageData[y][x].m_pos.x;
				nowLenX = fabsf(nowLenX);
				float nowLenY = g_player.m_pos.y - g_stage.m_stageData[y][x].m_pos.y;
				nowLenY = fabsf(nowLenY);
				//上記二つの結果を引き算して、めり込んだ距離を計算する
				float hitLenX = lenX - nowLenX;
				float hitLenY = lenY - nowLenY;
				//変数を二つ用意し、上下左右のどこにいるかわかるようにする
				int posX, posY;
				if (g_player.m_pos.x < g_stage.m_stageData[y][x].m_pos.x)posX = -1;
				else posX = 1;
				if (g_player.m_pos.y < g_stage.m_stageData[y][x].m_pos.y)posY = -1;
				else posY = 1;

				//めり込みが横のほうが小さいので横に押し戻し
				if (hitLenX < hitLenY)
				{
					//押し戻し予定位置に壁がない
					if (g_stage.m_stageData[y][x + posX].m_state != STAGEID_SETTI)
					{
						//正式な押し戻しの計算を行う
						hitLenX *= posX;
						g_player.m_pos.x += hitLenX;
					}
					//押し戻し予定位置が無理だったので、縦に押し戻す
					else
					{
						//正式なもしも年の計算を行う
						hitLenY *= posY;
						g_player.m_pos.y += hitLenY;
						//押し戻し方向が上なら、地面と当たったはず
						if (hitLenY < 0)
						{
							SetLandPlayer();	//待機状態に移行させる
						}
					}
				}

				//めり込みが縦のほうが小さいので縦に押し戻し
				else
				{
					//押し戻し予定位置に壁がない
					if (g_stage.m_stageData[y + posY][x].m_state != STAGEID_SETTI)
					{
						// 正式な押し戻しの計算を行う
						hitLenY *= posY;
						g_player.m_pos.y += hitLenY;
						// 押し戻し方向が上なら、地面と当たったはず
						if (hitLenY < 0)
						{
							SetLandPlayer();	// 待機状態に移行させる
						}
					}
					else
					{
						//正式な押し戻しの計算を行う
						hitLenX *= posX;
						g_player.m_pos.x += hitLenX;
					}
				}
			}
		}
	}
	// ブロックと一切あたっていない
	if (isHit == false)
	{
		g_player.soundflag_4 = true;
		// 強制的にプレイヤーをジャンプ状態に
		SetJumpPlayer();
	}
}


