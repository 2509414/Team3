#include"display.h"
#include"../../Comon.h"
#include"Fps.h"

void Init_Data() {

	InitFps();
}

void Step_Data() {

	StepFps();
}

//デバッグデータ表示
void Draw_Data() {
	
	PrintFps();
}

