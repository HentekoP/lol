#include "DxLib.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);

	int i;
	int mario[9]; //9枚の画像がある

	if (DxLib_Init() == -1)        // ＤＸライブラリ初期化処理
	{
		return -1;        // エラーが起きたら直ちに終了
	}

	LoadDivGraph("../char/mario.png", 9, 9, 1, 32, 32, mario);
	ScreenFlip();
	i = 0;
	while (CheckHitKeyAll() == 0)

	{
		
		
		i++;
		if (i == 4) i = 0; {
			DrawGraph(0, 0, mario[i], FALSE);
			
			ScreenFlip();
		}

		


	}

	// 読み込んだ画像のグラフィックハンドルを削除
	ScreenFlip();
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;
}

