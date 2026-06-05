#pragma once
#include"../../../../Comon.h"
#include"../../Player/Player.h"


class MOVEBLOCK
{
public:

	VECTOR m_pos;
	bool is_Active;
	bool turnflag;
	int  graphhndl;	
	int graph[1];
	VECTOR Movevec;
	VECTOR StratPos;
	VECTOR EndPos;
};



void InitBlock();
void LoadBlock();
void UpdateBlock();
void DrawBlock();
void ExitBlock();

void RequestMove(VECTOR StartPos, VECTOR EndPos, int num);






