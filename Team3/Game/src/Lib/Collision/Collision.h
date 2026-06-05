#pragma once
#include <DxLib.h>



bool CheckHitCircleTOCircle(VECTOR circlePos, int radius1, VECTOR circlePos2, int radius2);




//		矩形同士のあたり判定
//	squarePos	:	各矩形の中心位置
//	sizeX,Y	:	各矩形の縦と横のサイズ(中心からの距離)
//	@return		:	0=ヒットなし、1=ヒット
int		ChenkHitSquareToSquare(VECTOR squarePos1, VECTOR squarePos2,
	int sizeX1, int sizeY1, int sizeX2, int sizeY2);


//線分と矩形の当たり判定

bool CheckHitLinetoSquare(VECTOR squarePos, VECTOR lineStartPos,VECTOR lineEndPos,
	int sizeX, int sizeY );


//線分と線分の当たり判定

bool CheckHitLinetoLine(VECTOR squarePos, VECTOR lineStartPos, VECTOR lineEndPos,
	int sizeX, int sizeY);