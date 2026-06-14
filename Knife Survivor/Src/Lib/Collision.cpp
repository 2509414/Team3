#include<DxLib.h>

//ŽlŠp“¯Žm‚Ì‚ ‚½‚è”»’è
bool ChenkHitSquareToSquare(VECTOR SquarePos1, int sizeX1, int sizeY1, VECTOR SquarePos2, int sizeX2, int sizeY2)
{
	if (SquarePos1.x + sizeX1 > SquarePos2.x - sizeX2 &&
		SquarePos1.x - sizeX1 < SquarePos2.x + sizeX2 &&
		SquarePos1.y + sizeY1 > SquarePos2.y - sizeY2 &&
		SquarePos1.y - sizeY1 < SquarePos2.y + sizeY2
		)
	{
		return true;
	}
	else return false;
}
