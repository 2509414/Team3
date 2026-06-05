#include"Collision.h"
#include"../../Comon.h"

bool CheckHitCircleTOCircle(VECTOR circlePos, int radius1, VECTOR circlePos2, int radius2) {

	if ((circlePos2.x - circlePos.x) * (circlePos2.x - circlePos.x) < (radius1 + radius2) * (radius1 + radius2) &&
		(circlePos2.y - circlePos.y) * (circlePos2.y - circlePos.y) < (radius1 + radius2) * (radius1 + radius2))
	{
		return true;
	}
	else return false;

}

//-------------------------------
//		矩形同士のあたり判定
//-------------------------------
int	ChenkHitSquareToSquare(VECTOR squarePos1, VECTOR squarePos2,
	int sizeX1, int sizeY1, int sizeX2, int sizeY2)
{
	int ret = 0;
	if (squarePos1.x - sizeX1 < squarePos2.x + sizeX2		// 四角の左端チェック
		&& squarePos1.x + sizeX1 > squarePos2.x - sizeX2	// 四角の右端チェック
		&& squarePos1.y - sizeY1 < squarePos2.y + sizeY2	// 四角の上端チェック
		&& squarePos1.y + sizeY1 > squarePos2.y - sizeY2)	// 四角の下端チェック
	{
		ret = 1;
	}
	return ret;
}


//-------------------------------
//		矩形と線分のあたり判定
//-------------------------------
bool CheckHitLinetoSquare(VECTOR squarePos, VECTOR lineStartPos, VECTOR lineEndPos,
	int sizeX, int sizeY)
{
	int pointsL, pointsR, pointsU, pointsD;

	pointsL = squarePos.x - sizeX;//矩形の左端
	pointsR = squarePos.x + sizeX;//矩形の右端
	pointsU = squarePos.y - sizeY;//矩形の上端
	pointsD = squarePos.y + sizeY;//矩形の下端

	VECTOR vec1, vec2[4];

	//直線のベクトル
	vec1.x = lineEndPos.x - lineStartPos.x;
	vec1.y = lineEndPos.y - lineStartPos.y;

	//直線の開始点から各点へのベクトル
	vec2[0].x = pointsL - lineStartPos.x;
	vec2[1].x = pointsR - lineStartPos.x;
	vec2[2].y = pointsU - lineStartPos.y;
	vec2[3].y = pointsD - lineStartPos.y;

	float cross[4];

	//外積
	cross[0] = vec1.x * vec2[0].y - vec1.y * vec2[0].x;
	cross[1] = vec1.x * vec2[1].y - vec1.y * vec2[1].x;
	cross[2] = vec1.x * vec2[2].y - vec1.y * vec2[2].x;
	cross[3] = vec1.x * vec2[3].y - vec1.y * vec2[3].x;

	//外積の結果が0だったら衝突している
	if (cross[0] == 0 || cross[1] == 0 || 
		cross[0] == 0 || cross[1] == 0)return true;
	
	//外積の結果がすべて同じ符号だったら衝突していない
	if ((cross[0] > 0 && cross[1] > 0 && cross[2] > 0 && cross[3] > 0) ||
		(cross[0] < 0 && cross[1] < 0 && cross[2] < 0 && cross[3] < 0))
	{
		return false;
	}
	//それ以外なら衝突している
	else return true;
}


class Line
{
public:

	float pointsL, pointsR, pointsT, pointsU;
	VECTOR StartLineL, StartLineR, StartLineT, StartLineU;
	VECTOR EndLineL, EndLineR, EndLineT, EndLineU;

	void SetpointsL(VECTOR pos, int size) {
		pointsL = pos.x - size;
	}void SetpointsR(VECTOR pos, int size) {
		pointsR = pos.x + size;
	}void SetpointsT(VECTOR pos, int size) {
		pointsT = pos.y - size;
	}void SetpointsU(VECTOR pos, int size) {
		pointsU = pos.y + size;
	}

	void startline() {
		StartLineL = { pointsL,pointsT };//左上
		StartLineR = { pointsR,pointsT };//右上
		StartLineT = { pointsL,pointsT };//左上
		StartLineU = { pointsL,pointsU };//左下
	}

	void endline() {

		EndLineL = { pointsL,pointsU };//左下
		EndLineR = { pointsR,pointsU };//右下
		EndLineT = { pointsR,pointsT };//右上
		EndLineU = { pointsR,pointsU };//右下
	}

};

class VEC:Line
{
public:
	
	VECTOR AB, AC, AD;
	VECTOR CD, CA, CB;

	void AtoB(VECTOR startpos,VECTOR endpos) {
		AB = { endpos.x - startpos.x, endpos.y - startpos.y };
	}
	void AtoC(){
		AC = {};

	}
	





};




bool CheckHitLinetoLine(VECTOR squarePos, VECTOR lineStartPos, VECTOR lineEndPos,
	int sizeX, int sizeY) {

	Line line;
	
	//点
	line.SetpointsL(squarePos, sizeX);
	line.SetpointsR(squarePos, sizeX);
	line.SetpointsT(squarePos, sizeY);
	line.SetpointsU(squarePos, sizeY);

	//直線の始点
	line.startline();
	//直線の終点
	line.endline();

	VEC LEFT,RIGHT,TOP,UNDER;

	LEFT.AtoB(lineStartPos,lineEndPos);




	return true;
}