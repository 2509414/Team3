#include <dxlib.h>
#include "../../../Lib/KeyInput/KeyInput.h"
#include "Player.h"
#include"../../../Comon.h"
#include"Gimmick/Plshot.h"
#include"../../../Lib/Effect/Effect.h"

// 各種定義
#define START_X (640.0f)	// スタート地点
#define START_Y (3000.0f)	// スタート地点
#define WALK_SPEED (5.0f)	// 歩き速度
#define GRAVITY (0.3f)		// 重力
#define GENSUI (0.1f)		//減衰
#define ANIM_SPEED (0.25f)	// アニメーション速度
#define JUMP_POW (8.0f)

#define BOOST_POW_X (5.0f)
#define BOOST_POW_Y (5.0f)


#define FRICTION (10)		//摩擦
#define BOOST_MAX (100)



#define SEISEI_MAX (5)

// それぞれの画像のパス
const char FILE_PATH[][128] = {
	"Data/Textures/Player/IDLE.png", "Data/Textures/Player/RUN.png",
	"Data/Textures/Player/JUMP.png","Data/Textures/Player/ATTACK 1.png",
	"Data/Textures/Player/ATTACK 1.png","Data/Textures/Player/DEFEND.png"
};
// 画像の全枚数
const int GRAPH_NUM[] = { 7, 8, 5, 6 ,6,6 };
// アニメーションをループさせるか
const bool IS_LOOP_ANIM[] = { true, true, false , false,false,false,false };

PLAYER_DATA g_player;
Mouse_Data g_mouse;

extern Shot g_plshot[PLSHOT_MAX];



int score() {
	
	int underrimit = (STAGE_Y-6) * OBJECT_SIZE_Y;
	int toprimit = g_player.goalpos;

	int lengh = underrimit - toprimit;

	float ret = ((g_player.m_pos.y- toprimit)/lengh);

	ret *= 100;
	ret = 100 - (int)ret;


	return ret;
}


void boostline() {

	VECTOR offsetPos = GetOffset();
	VECTOR drawPos_player;
	drawPos_player.x = g_player.m_pos.x - offsetPos.x;
	drawPos_player.y = g_player.m_pos.y - offsetPos.y;


	DrawLine(drawPos_player.x-g_player.m_shotcapa/10, drawPos_player.y-50,
		drawPos_player.x+g_player.m_shotcapa/10, drawPos_player.y - 50,
		GetColor(255, 255, 255), 2);
}




void plshotline(int num) {

	VECTOR offsetPos = GetOffset();
	VECTOR drawPos_player, drawPos_shot;
	drawPos_player.x = g_player.m_pos.x - offsetPos.x;
	drawPos_player.y = g_player.m_pos.y - offsetPos.y;

	for (int i = 0; i < PLSHOT_MAX; i++)
	{
		if (g_plshot[i].m_isActiv) {

			drawPos_shot.x = g_plshot[i].m_pos.x - offsetPos.x;
			drawPos_shot.y = g_plshot[i].m_pos.y - offsetPos.y;

			DrawLine(drawPos_player.x, drawPos_player.y,
				drawPos_shot.x, drawPos_shot.y,
				GetColor(255, 255, 255), 3);

			VECTOR dir;
			dir.x = drawPos_player.x - drawPos_shot.x;
			dir.y = drawPos_player.y - drawPos_shot.y;
			dir.z = 0.0f;
			//上記方向ベクトルの長さの2乗を計算
			float length = (dir.x * dir.x) + (dir.y * dir.y);
			//長さの２乗になっているので2乗を取っ払う
			length = sqrtf(length);

			if (length  >=   700  )
			{
				g_plshot[i].m_isActiv = false;
			}

		}
	}
}

void plshotmove(int  num ,VECTOR PlPos,VECTOR ShotPos) {

	VECTOR dir;

	dir.x = ShotPos.x - PlPos.x;
	dir.y = ShotPos.y - PlPos.y;

	//上記方向ベクトルの長さの2乗を計算
	float length = (dir.x * dir.x) + (dir.y * dir.y);
	//長さの２乗になっているので2乗を取っ払う
	length = sqrtf(length);

	//1を長さで割る
	length = 1.0f / length;
	//上の計算結果を方向ベクトルに掛け算する	
	dir.x *= length;
	dir.y *= length;
	//=========================================================================

	g_player.plshotmove.x += dir.x/1.3;
	g_player.plshotmove.y += dir.y/1.3;
}




//-------------------------------
//		プレイヤーデータ初期化関数
//-------------------------------
void InitPlayer()
{
	// プレイヤー本体の初期化
	for (int i = 0; i < PLSTATE_NUM; i++)
	{
		for (int j = 0; j < PLAYER_MAX_ANIMNUM; j++)
		{
			g_player.m_hndl[i][j] = -1;
		}
	}
	g_player.m_pos.x = OBJECT_SIZE_X * (STAGE_X / 2);
	g_player.m_pos.y = OBJECT_SIZE_Y * (STAGE_Y - 6);

	g_player.m_animCount = 0.0f;
	g_player.m_state = PLSTATE_IDLE;
	g_player.m_jumpPow = 0.0f;
	g_player.m_life = 3;
	g_player.m_isTurn = false;
	g_player.m_isActive = true;

	g_player.m_Gunhndl = -1;

	g_player.Gun_turn_flag = false;
	g_player.m_shotcapa = BOOST_MAX;
	g_player.m_land_flag = true;
	g_player.m_jump_flag = false;
	g_player.m_shot_flag = false;
	g_player.boostflag = false;

	g_player.m_coin = 0;
	g_player.boost_pow = {0};
	g_player.plshotmove = { 0 };

	g_player.dead_flag = false;

	g_player.seiseicapa = SEISEI_MAX;

	g_player.goalflag = false;

	g_player.checkpoint = { WINDOW_SIZE_X / 2 ,OBJECT_SIZE_Y * (STAGE_Y - 10) ,0};

	//g_player.m_moveflag = true;

	g_player.m_pos.y += 15;

	g_player.soundhndl = -1;
	g_player.landsound = -1;
	g_player.damagesound = -1;

	g_player.soundflag = false;
	g_player.soundflag_1 = false;
	g_player.soundflag_2 = false;
	g_player.soundflag_3 = false;
	g_player.soundflag_4 = false;

}


//-------------------------------
//		プレイヤーデータ読み込み関数
//-------------------------------
void LoadPlayer()
{
	// プレイヤーの画像をロード
	// 全画像統一感のあるルールなので成せる業
	for (int i = 0; i < PLSTATE_NUM; i++)
	{
		LoadDivGraph(FILE_PATH[i], GRAPH_NUM[i], GRAPH_NUM[i], 1, PLAYER_SIZE_X, PLAYER_SIZE_Y, g_player.m_hndl[i]);
	}

	g_player.m_Gunhndl = LoadGraph("Data/Textures/gun.png");

	if (g_player.soundhndl == -1)
	{
		g_player.soundhndl = LoadSoundMem("Data/Sounds/shot.mp3");
	}
	if (g_player.landsound == -1)
	{
		g_player.landsound = LoadSoundMem("Data/Sounds/land.mp3");
	}
	if (g_player.damagesound == -1)
	{
		g_player.damagesound = LoadSoundMem("Data/Sounds/Damage.mp3");
	}


}


//-------------------------------
//		プレイヤーデータ更新関数
//-------------------------------
void StepPlayer()
{
	// 各状態に合わせて関数呼び出し
	switch (g_player.m_state)
	{
	case PLSTATE_IDLE:
		IdlePlayerExec();
		break;
	case PLSTATE_WALK:
		WalkPlayerExec();
		break;
	case PLSTATE_JUMP:
		JumpPlayerExec();
		break;
	case PLSTATE_ATTACK:
		AttackPlayerExec();
		break;
	case PLSTATE_SHOT:
		ShotPlayerExec();
		break;
	}

	// アニメーション更新
	g_player.m_animCount += ANIM_SPEED;
	if (g_player.m_animCount >= GRAPH_NUM[g_player.m_state])
	{
		// 最後まで来たらループするか、停止するかで値を変更
		if (IS_LOOP_ANIM[g_player.m_state])
			g_player.m_animCount = 0.0f;
		else
			g_player.m_animCount = GRAPH_NUM[g_player.m_state] - 1.0f;
	}



	if (!g_player.m_land_flag)
	{
		if (IsKeyInput(KEY_ATTACK) == false)
		{
			g_player.plshotmove.y += GRAVITY;
		}
		else
		{
			if (g_player.boostflag)
			{
				g_player.plshotmove.y *= 0.98;
			}
			else
			{
				g_player.plshotmove.y += GRAVITY;
			}
		}
		g_player.m_pos.y -= g_player.m_jumpPow;
	}

	if (IsKeyInput(KEY_ATTACK) == true)
	{

		if (g_player.boostflag)
		{
			g_player.m_pos.x += g_player.boost_pow.x;
			g_player.m_pos.y += g_player.boost_pow.y;
		}

		if (g_player.m_shotcapa <= 0)
		{
			g_player.boostflag = false;
			g_player.m_shotcapa = 0;
		}
		else
		{
			g_player.boostflag = true;
			g_player.m_shotcapa--;
		}
	}
	/*else
	{
		if (g_player.m_shotcapa >= BOOST_MAX)
		{
			g_player.m_shotcapa = BOOST_MAX;
		}
		else
		{
			g_player.m_shotcapa+=0.5;
		}
	}*/

	//ジップ処理========================================
		
	g_player.m_pos.x += g_player.plshotmove.x;
	g_player.m_pos.y += g_player.plshotmove.y;
	
		
	if (IsKeyInput(KEY_SHOT) == false)
	{
		if (fabs(g_player.plshotmove.x)>0.1 )
		{
			g_player.plshotmove.x *= 0.98;

		}
	}

	if (IsKeyInputTrg(KEY_SHOT) == true)
	{	
		PlaySoundMem(g_player.soundhndl, DX_PLAYTYPE_BACK);
	}

	/*if (IsKeyInput(KEY_SHOT) == true)
	{
		g_player.m_jumpPow += GRAVITY;
	}
	*/
	//======================================================
		if (IsKeyInputTrg(KEY_RE) == true)
		{
			g_player.m_pos.x = g_player.checkpoint.x;
			g_player.m_pos.y = g_player.checkpoint.y;
		}
}


//-------------------------------
//		プレイヤー表示関数
//-------------------------------
void DrawPlayer()
{
	if (!g_player.m_isActive) return;
	// プレイヤー表示
	int animID = (int)g_player.m_animCount;
	// オフセット値を考慮して描画場所を決める
	VECTOR offsetPos = GetOffset();
	VECTOR drawPos;
	drawPos.x = g_player.m_pos.x -offsetPos.x;
	drawPos.y = g_player.m_pos.y -offsetPos.y;
	DrawRotaGraph((int)drawPos.x, drawPos.y, 1.5, 0.0,
		g_player.m_hndl[g_player.m_state][animID], TRUE, g_player.m_isTurn);


	if (g_player.m_pos.x > g_mouse.m_posX)g_player.Gun_turn_flag = false;
	else g_player.Gun_turn_flag = true;

	//矢印
	VECTOR drawPosArrow;
	drawPosArrow.x = g_mouse.m_arrow_len.x - offsetPos.x;
	drawPosArrow.y = g_mouse.m_arrow_len.y - offsetPos.y;
	
	DrawRotaGraph((int)drawPosArrow.x, (int)drawPosArrow.y, 0.05, g_mouse.Angle(g_player.m_pos),
		g_player.m_Gunhndl, TRUE, 0, g_player.Gun_turn_flag);

	boostline();


}


//-------------------------------
//		終了前の処理関数
//-------------------------------
void ExitPlayer()
{
	for (int i = 0; i < PLSTATE_NUM; i++)
	{
		for (int j = 0; j < PLAYER_MAX_ANIMNUM; j++)
		{
			DeleteGraph(g_player.m_hndl[i][j]);
			g_player.m_hndl[i][j] = -1;
		}
	}
}


//-------------------------------
//		待機中に実行するもの
//-------------------------------
void IdlePlayerExec()
{
	// 行動の優先順位が高いものから実行
	
	// 歩き状態へ
	if (WalkPlayer() == true)
	{
		g_player.m_animCount = 0;
		g_player.m_state = PLSTATE_WALK;
	}
	// ジャンプ状態へ
	else if (JumpPlayer() == true)
	{
		g_player.m_animCount = 0;
		g_player.m_state = PLSTATE_JUMP;
	}
	// 攻撃状態へ
	else if (AttackPlayer() == true)
	{
		g_player.m_animCount = 0;
		g_player.m_state = PLSTATE_ATTACK;
	}
	// ショット状態へ
	else if (ShotPlayer() == true)
	{
		g_player.m_animCount = 0;
		g_player.m_state = PLSTATE_SHOT;
	}
	else
	{
		// ここまで来たら待機のまま
	}

}


//-------------------------------
//		移動中に実行するもの
//-------------------------------
void WalkPlayerExec()
{

	// 行動の優先順位が高いものから実行
	// 

	
	// ジャンプ状態へ
	if (JumpPlayer() == true)
	{
		g_player.m_animCount = 0;
		g_player.m_state = PLSTATE_JUMP;
	}
	// 攻撃状態へ
	else if (AttackPlayer() == true)
	{
		g_player.m_animCount = 0;
		g_player.m_state = PLSTATE_ATTACK;
	}
	// ショット状態へ
	else if (ShotPlayer() == true)
	{
		g_player.m_animCount = 0;
		g_player.m_state = PLSTATE_SHOT;
	}
	// 歩き状態のまま
	else if (WalkPlayer() == true)
	{

	}
	// 待機状態へ
	else
	{
		g_player.m_animCount = 0;
		g_player.m_state = PLSTATE_IDLE;
	}
}

void ShotPlayerExec() {

	// 地面に着いたら待機状態へ
	if (g_player.m_land_flag)
	{
		g_player.m_animCount = 0;
		g_player.m_state = PLSTATE_IDLE;
	}
	else
	{
		// ジャンプ状態へ
		if (JumpPlayer() == true)
		{
			g_player.m_animCount = 0;
			g_player.m_state = PLSTATE_JUMP;
		}
		// 攻撃状態へ
		if (AttackPlayer() == true)
		{
			g_player.m_animCount = 0;
			g_player.m_state = PLSTATE_ATTACK;
		}
		//ショット状態へ
		if (ShotPlayer() == true)
		{
			g_player.m_animCount = 0;
			g_player.m_state = PLSTATE_SHOT;
		}
		// ジャンプ中も左右移動だけは実行
		if (WalkPlayer() == false)
		{

		}
	}
}

//-------------------------------
//		ジャンプ中に実行するもの
//-------------------------------
void JumpPlayerExec()
{

	// 地面に着いたら待機状態へ
	if (g_player.m_land_flag)
	{
		g_player.m_animCount = 0;
		g_player.m_state = PLSTATE_IDLE;
	}
	else
	{
		
		// 攻撃状態へ
		if (AttackPlayer() == true)
		{
			g_player.m_animCount = 0;
			g_player.m_state = PLSTATE_ATTACK;
		}
		//ショット状態へ
		else if (ShotPlayer() == true)
		{
			g_player.m_animCount = 0;
			g_player.m_state = PLSTATE_SHOT;
		}
		// ジャンプ中も左右移動だけは実行
		if (WalkPlayer() == false)
		{

		}
	}
}



//-------------------------------
//		ショット中に実行するもの
//-------------------------------
void AttackPlayerExec()
{



	// 地面に着いたら待機状態へ
	if (g_player.m_land_flag)
	{
		g_player.m_animCount = 0;
		g_player.m_state = PLSTATE_IDLE;
	}
	//ショット状態へ
	else if (ShotPlayer() == true)
	{
		g_player.m_animCount = 0;
		g_player.m_state = PLSTATE_SHOT;
	}
	// 攻撃状態へ
	if (AttackPlayer() == true)
	{
		g_player.m_animCount = 0;
		g_player.m_state = PLSTATE_ATTACK;
	}
		// ジャンプ中も左右移動だけは実行
	if (WalkPlayer() == false)
	{

	}
}




//-------------------------------
//		歩き処理
//-------------------------------
bool WalkPlayer()
{
	// 移動方向ボタンが押されていたら座標変更
	if (IsKeyInput(KEY_D) == true)
	{
		g_player.m_pos.x += WALK_SPEED;
		g_player.m_isTurn = false;

		return true;
	}
	else if (IsKeyInput(KEY_A) == true)
	{
		g_player.m_pos.x -= WALK_SPEED;
		g_player.m_isTurn = true;


		return true;
	}
	// ここに来たら歩き不成立
	return false;
}





//攻撃処理
bool AttackPlayer() {

	g_mouse.GetMouse();
	g_mouse.MouseOffset();
	g_mouse.Player_Mouse_Vector(g_player.m_pos);
	g_mouse.Arrow();

	g_mouse.m_arrow_len.x = (g_mouse.m_arrow.x + g_player.m_pos.x);
	g_mouse.m_arrow_len.y = (g_mouse.m_arrow.y + g_player.m_pos.y);

	VECTOR offset = GetOffset();
	VECTOR drawpos;

	drawpos.x = g_mouse.m_arrow_len.x + offset.x;
	drawpos.y = g_mouse.m_arrow_len.y + offset.y;

	

	if (IsKeyInput(KEY_ATTACK) == true) {
		if (g_player.m_shotcapa <= 0)return false;

		RequestEffect(drawpos);

		g_player.boost_pow.x = g_mouse.m_len.x * BOOST_POW_X;
		g_player.boost_pow.y = g_mouse.m_len.y * BOOST_POW_Y;

		g_player.boostflag = true;
		return true;
	}
	else return false;
}


//ショット処理
bool ShotPlayer() {

	g_mouse.GetMouse();
	g_mouse.MouseOffset();
	g_mouse.Player_Mouse_Vector(g_player.m_pos);
	g_mouse.Arrow();

	g_mouse.m_arrow_len.x = (g_mouse.m_arrow.x + g_player.m_pos.x);
	g_mouse.m_arrow_len.y = (g_mouse.m_arrow.y + g_player.m_pos.y);

	VECTOR offset = GetOffset();
	VECTOR drawpos;

	drawpos.x = g_mouse.m_arrow_len.x + offset.x;
	drawpos.y = g_mouse.m_arrow_len.y + offset.y;

	if (IsKeyInputTrg(KEY_SHOT) == true)
	{
		RequestPLShot(g_player.m_pos);
		return true;
		//g_player.m_shotcapa--;
	}
	else return false;
}

//-------------------------------
//		ジャンプ処理
//-------------------------------
bool JumpPlayer()
{
	// ひとまずボタンが押されたらジャンプ力を再設定
	if (IsKeyInputTrg(KEY_JUMP) == true)
	{
		g_player.plshotmove.y -= JUMP_POW;
		return true;
	}
	else return false;
}

//-------------------------------
//		地面接地時処理
//-------------------------------
void SetLandPlayer(void)
{

	if (g_player.soundflag&&
		g_player.soundflag_1&&
		g_player.soundflag_2&&
		g_player.soundflag_3&&
		g_player.soundflag_4)
	{
 		PlaySoundMem(g_player.landsound, DX_PLAYTYPE_BACK);

		g_player.soundflag = false;
		g_player.soundflag_1 = false;
		g_player.soundflag_2 = false;
		g_player.soundflag_3 = false;
		g_player.soundflag_4 = false;
	}

	


	g_player.m_land_flag = true;
	g_player.m_shotcapa = BOOST_MAX;
	g_player.seiseicapa = SEISEI_MAX;
	
	if (IsKeyInput(KEY_SHOT)== false) {
		//g_player.plshotmove.x *= 0.0f;
		g_player.plshotmove.y = 0.0f;
		g_player.m_jumpPow = 0.0f;
	}

	if (IsKeyInput(KEY_ATTACK) == true) {
		g_player.m_shot_flag = true;
	}

	if (!g_player.m_moveflag)
	{
		g_player.plshotmove.x *= 0.7;

		if (IsKeyInput(KEY_D) == false && IsKeyInput(KEY_A) == false) {
			g_player.m_state = PLSTATE_IDLE;
		}
		else if (IsKeyInput(KEY_D) == true || IsKeyInput(KEY_A) == true) {
			g_player.m_state = PLSTATE_WALK;
		}
	}
}


//-------------------------------
//		落下時処理
//-------------------------------
void SetJumpPlayer(void)
{
	g_player.m_land_flag = false;


	if (!g_player.m_shot_flag)
	{
		g_player.m_state = PLSTATE_JUMP;
	}
	g_player.m_jump_flag = true;
}


//-------------------------------
//		オフセット値を取得する
//-------------------------------
VECTOR GetOffset()
{
	// プレイヤーの座標を基に理想の位置からどれだけ離れたかを計算する
	VECTOR v;
	// 理想の表示位置
	v.x = WINDOW_SIZE_X / 2;
	v.y = WINDOW_SIZE_Y / 1.3;
	// 本来の座標から理想の表示位置までどれだけ離れたか
	v.x = g_player.m_pos.x - v.x;
	v.y = g_player.m_pos.y - v.y;
	v.z = 0.0f;

	// もしもオフセット値が限界を超えたら強制的に限界値へ===================
	// 上下左右の限界値を計算
	// プレイヤーはX=320,y=240からどれだけ離れているかを考える
	// 左は今回プレイヤーが320まで来たら停止、上は240まで来たら停止なので、オフセットは共に0
	float left = 0.0f;
	float up = 0.0f;
	// 右はステージ右端の40マス×32ドット=1280からウィンドウサイズの半分320を引いた960の位置が限界値
	// ということは理想の位置320からのオフセットは960-320の640が限界となる
	// 下の式は結果としてウィンドウサイズの半分を2回引き算しているので、まとめて表記している
	float right = STAGE_X * OBJECT_SIZE_X - WINDOW_SIZE_X;
	// こちらも上の式と同様の理論で作成
	float down = STAGE_Y * OBJECT_SIZE_Y - WINDOW_SIZE_Y;

	// 上で計算した上限を超えないようにする
	if (v.x < left) v.x = left;
	else if (v.x > right) v.x = right;
	if (v.y < up) v.y = up;
	else if (v.y > down) v.y = down;
	//======================================================================

	return v;
}

