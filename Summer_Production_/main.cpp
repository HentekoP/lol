#include "CHARA.h"
#include "Map.h"
#include "CHARA.h"
#include "main.h"
#include "DxLib.h"
#include <algorithm> //< std::maxを使用するため
#define NOMINMAX //< std::min/std::maxを正しく動作させるため。Windows負の遺産

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	//======================================================
	// ウインドウ設定とDXライブラリの初期化
	//======================================================

	// Windowsモードにする
	ChangeWindowMode(TRUE);
	// 画面サイズの設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
	// DXライブラリ初期化
	if (DxLib_Init() == -1)
	{
		//初期化に失敗
		return -1;
	}
	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);
	//======================================================
	// ゲーム部分
	//======================================================
	//------------------------------------------------------
	// ゲーム初期化部分
	//------------------------------------------------------

	// キャラのロード
	void CHARA_Init();

	// マップ初期化
 void	  MAP_Init();

	//------------------------------------------------------
	// メインループ部分
	//------------------------------------------------------
	while (ProcessMessage() == 0)
	{
		//裏画面消す
		ClearDrawScreen();

		// マップ描画
		void MAP_Draw();

		// キャラ更新
	void CHARA_Update();

		// ブロックの当たり判定
		void MAP_HitCheck();

		//ブロック描画
		void DrawBlock();

		// キャラ描画
		void CHARA_Draw();

		//裏画面を表画面を入れ替える
		ScreenFlip();
	}

	//======================================================
	// DXライブラリ終了とプログラム終了
	//======================================================
	DxLib_End();
	return 0;
}