#include<DxLib.h>

//		“_‚ÆŽlŠp‚Ì“–‚½‚è”»’è
//	dotPos		:	“_‚ÌÀ•W
//	squarePos	:	ŽlŠpŒ`‚Ì’†SˆÊ’u
//	sizeX,Y		:	ŽlŠpŒ`‚Ìc‚Æ‰¡‚ÌƒTƒCƒYi’†S‚©‚ç‚Ì‹——£j
//	@return		:	0=ƒqƒbƒg‚È‚µ 1=ƒqƒbƒg

//“_‚ÆŽlŠp‚Ì“–‚½‚è”»’è
//bool ChenkHitDotToSquare(VECTOR dotPos, VECTOR SquarePos, int sizeX, int sizeY)
//{
//	bool ret = false;
//	if (dotPos.x > SquarePos.x - sizeX &&
//		dotPos.x < SquarePos.x + sizeX &&
//		dotPos.y > SquarePos.y - sizeX &&
//		dotPos.y < SquarePos.y + sizeX)
//	{
//		ret = true;
//	}
//
//	return ret;
//}

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

//‰~“¯Žm‚Ì‚ ‚½‚è”»’è
//bool ChenkHitCircleToSircle(VECTOR circlePos1, int radius1, VECTOR circlePos2, int radius2)
//{
//	//ŽO•½•û‚Ì’è—‚Ì’ê•Ó‚Æ‚‚³‚ðŒvŽZ‚·‚é
//
//	int x = (int)(circlePos1.x - circlePos2.x);
//	x *= x;
//	int y = (int)(circlePos1.y - circlePos2.y);
//	y *= y;
//
//	//‚»‚ê‚¼‚ê‚Ì”¼Œa‚ð‘«‚µ‚½‚à‚Ì‚Ì2æ‚ðŒvŽZ
//	int rad = radius1 + radius2;
//	rad *= rad;
//
//	if (x + y < rad)
//	{
//
//		return true;
//	}
//	else return false;
//	
//}