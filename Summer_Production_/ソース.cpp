#include <algorithm> //< std::maxを使用するため
#define NOMINMAX //< std::min/std::maxを正しく動作させるため。Windows負の遺産
#include "DxLib.h"
#include <stdlib.h>
#include <stdio.h>
#define PI    3.1415926535897932384626433832795f
// 画面サイズ設定
const int SCREEN_WIDTH = 640; //< スクリーン横の大きさ
const int SCREEN_HEIGHT = 480; //< スクリーン縦の大きさ

//
// 当たり判定を行う関数
int CheckHit(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
	float L1 = x1;      // 左
	float R1 = x1 + w1; // 右(左+横幅)
	float L2 = x2;      // 左
	float R2 = x2 + w2; // 右(左+横幅)

	if (R1 <= L2) return 0; //< 線上も当たらないことにする
	if (R2 <= L1) return 0; //< 線上も当たらないことにする

	float U1 = y1;      // 上
	float D1 = y1 + h1; // 下(上+縦幅)
	float U2 = y2;      // 上
	float D2 = y2 + h2; // 下(上+縦幅)

	if (D1 <= U2) return 0; //< 線上も当たらないことにする
	if (D2 <= U1) return 0; //< 線上も当たらないことにする

	// それ以外の場合は当たっている
	return 1;
}

//============================================================
// マップチップ定義
//============================================================
const int SIZE_MAP_X = 32;  //< マップチップXサイズ
const int SIZE_MAP_Y = 32;	//< マップチップYサイズ
const int NUM_CHIP_X = 1;  //< 横10種類
const int NUM_CHIP_Y = 1;   //< 縦4種類
const int NUM_CHIP_ALL = NUM_CHIP_X * NUM_CHIP_Y;
int sora[5];
int block[1];

// マップチップを使った背景
const int NUM_MAP_X = 20; // 32x20=640
const int NUM_MAP_Y = 15; // 32x15=480

int data[] =
{
	// 横20x15
	0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 0,
	0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 0,
	0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 0,
	0,  0,  0,  0,  0,   0,  0, 1, 1, 1,  1, 1,  0,  0,  0,   0,  0,  0,  0, 0,
	0,  0,  0,  0,  0,   0,  0, 0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 0,

	0,  0, 1, 1, 1,  1,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 0,
	0,  0,  0,  0,  0,   0,  0, 0,  0,  0,   0,  0,  0,  0, 1,  1, 1, 1,  0, 0,
	0,  0,  0,  0,  0,   0,  0, 0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 0,
	0,  0,  0,  0,  0,   0,  0, 0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 0,
	0,  0,  0,  0,  0,   0,  0, 1, 1, 1,  1, 1,  0,  0,  0,   0,  0,  0,  0, 0,

	0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 0,
	0,  0,  0, 0, 0,  0,  0,  0,  0,  0,   0,  0,  0,  0, 0,  0, 0,  0,  0, 0,
	0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 0,
	0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 0,
	2,  2,  2,  2,  2,    2, 2, 2, 2, 2, 0, 0, 0, 2,  2,  2,  2,  2,   2,  2,
};

//----------------------------------------
// マップの初期化
//----------------------------------------
void MAP_Init()
{
	/*LoadDivGraph("../background/sora.png", NUM_CHIP_ALL,
		NUM_CHIP_X, NUM_CHIP_Y,
		SIZE_MAP_X, SIZE_MAP_Y,
		block);*/
	sora[0] = LoadGraph("background/sora.png");
	sora[1] = LoadGraph("1-1/kara_block.png");
	sora[2] = LoadGraph("1-1/floor.png");
}



int startTime;
unsigned int color = GetColor(0, 0, 255);
bool flg = false;


//----------------------------------------
// マップの描画
//----------------------------------------

int karablock;


void MAP_Draw()
{
	// 背景描画
	for (int j = 0; j < NUM_MAP_Y; j++)
	{
		for (int i = 0; i < NUM_MAP_X; i++)
		{
			int no = data[i + j * NUM_MAP_X];
			DrawGraph(i * SIZE_MAP_X, j * SIZE_MAP_Y, sora[no], TRUE);
		}
	}
}




//============================================================
// キャラクター定義
//============================================================
const int CHARA_WIDTH = 32;
const int CHARA_HEIGHT = 32;

float x = (SCREEN_WIDTH - CHARA_WIDTH) / 2;		//< 画面の中心
float y = (SCREEN_HEIGHT - CHARA_HEIGHT) / 2;	//< 画面の中心
float yadd = 0.0f;
float gravity = 0.2f;
// 前回の位置
float old_x = 0.0f;
float old_y = 0.0f;

int mario0[9];
int mario1[9];

int motion = 0;
int act_motion[] = { 1,2,3,3, };
int act_index = 0;
const int MAX_MOTION_INDEX = 3; //

const int ACT_SPEED = 20;
int act_wait = ACT_SPEED;

const int ACT_NUM_X = 9;
const int ACT_NUM_Y = 1;
const int ACT_NUM_ALL2 = 1;
const int ACT_NUM_ALL = ACT_NUM_X * ACT_NUM_Y;

//const int ACT_NUM_ALL2 = ACT_NUM_X * ACT_NUM_Y;

const int ACT_DIR_SLIDE = ACT_NUM_X; //< 横のキャラ分スライドさせれば次の列を選択する

int act_dir = 0;
bool DashPad(void);




bool DashPad(void)
{
	int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (input & PAD_INPUT_A)
	{
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------
// キャラの初期化
//----------------------------------------
void CHARA_Init()
{
	LoadDivGraph("mario/mario.png", ACT_NUM_ALL, ACT_NUM_X, ACT_NUM_Y,
		CHARA_WIDTH, CHARA_HEIGHT,
		mario0);

	LoadDivGraph("mario/mariohanten.png", ACT_NUM_ALL, ACT_NUM_X, ACT_NUM_Y,
		CHARA_WIDTH, CHARA_HEIGHT,
		mario1);
}

//block
void Block_Init()
{
	//LoadDivGraph("../1-1/kara_block.png", ACT_NUM_ALL2, ACT_NUM_X, ACT_NUM_Y,
	//	CHARA_WIDTH, CHARA_HEIGHT, block);
}

//----------------------------------------
// キャラ移動
//----------------------------------------



void CHARA_Move()
{
	// 前回の位置を覚えておく(関数内宣言ではない)
	old_x = x;
	old_y = y;
	int Screen;
	unsigned int Cr;
	Cr = GetColor(255, 255, 255);
	int motion_index = act_motion[act_index];
	// キー情報を取得する
	int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	const float speed = 3.0f;
	const float speed2 = 5.0f;
	int num = 0;

	bool MarioGround = true;
	int Jump_count = 0;


	if(input& PAD_INPUT_A)
	{
		if(input&PAD_INPUT_LEFT)
		{
			x -= speed2;
		}
	}

	if (input & PAD_INPUT_A)
	{
		if (input & PAD_INPUT_RIGHT)
		{
			x += speed2;
		}
	}


	// ジャンプ処理
	if (input & PAD_INPUT_B && MarioGround == true)
	{
		MarioGround = false;
		yadd = -5.0f;
		Jump_count = 10;

	}

	if(Jump_count == 0)
	{
		yadd += 0.7f;
	}

	if (input & PAD_INPUT_B && MarioGround != true)
	{
			Jump_count--;		
	}

	


	if(MarioGround == false)
	{
		y += yadd;
	}



	Cr = GetColor(255, 255, 255);
	if(y > 467.0f)
	{
		MarioGround = true;
		DrawString(250, 240 - 32, "マリオが落ちた！!", Cr);

	}

	//デバック
	printfDx("jumpカウント%d / yadd %.1f\n bool:%d\n", Jump_count, yadd,MarioGround);
	printfDx("X%.1f Y%.1f \n", x, y);
	

	if (input & PAD_INPUT_RIGHT)
	{
		x += speed;
		act_dir = 1; //< 2列目を選ぶ(0スタート)
		num = 2;
		//DrawGraph(x, y, mario[motion_index + act_dir * ACT_DIR_SLIDE], TRUE);
	}

	if (input & PAD_INPUT_LEFT)

	{
		x -= speed;
		act_dir = 0; //< 1列目を選ぶ(0スタート)
		num = 1;

		//DrawGraph(x, y, mario1[motion_index + act_dir * ACT_DIR_SLIDE], TRUE);
	}

	switch (num)
	{
	case 1:
		DrawTurnGraph(x, y, mario0[motion_index + act_dir * ACT_DIR_SLIDE], TRUE);
		break;

	case 2:
		DrawGraph(x, y, mario1[motion_index + act_dir * ACT_DIR_SLIDE], TRUE);
		break;

	case 3:

		break;
	default:
		DrawGraph(x, y, mario0[0], TRUE);
		break;
	}

	// 重力加速度の処理
	y += yadd;
	yadd += gravity;
	// yadd を -30 ～ 30 に収める
	yadd = std::min(30.0f, std::max(-30.0f, yadd));
}

//----------------------------------------
// キャラアニメ更新
//----------------------------------------
void CHARA_Anim()
{
	if (--act_wait <= 0)
	{
		act_index++;
		act_wait = ACT_SPEED;
		act_index %= MAX_MOTION_INDEX;
	}
}

//----------------------------------------
// キャラ更新
//----------------------------------------
void CHARA_Update()
{
	// 移動処理とアニメ処理を行う
	CHARA_Move();

	CHARA_Anim();
}

//----------------------------------------
// キャラ描画
//----------------------------------------
//----------------------------------------

void CHARA_Draw()
{
	int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	int motion_index = act_motion[act_index];
	//条件付けて画像の切り替えしないといけない
}

void DrawBlock()
{
	int DrawGraph();
}
//============================================================
// 地形の当たり判定の処理
//============================================================
//============================================================
//============================================================
//============================================================
void MAP_HitCheck()
{
	// ブロックの当たり判定
	for (int j = 0; j < NUM_MAP_Y; j++)
	{
		for (int i = 0; i < NUM_MAP_X; i++)
		{
			int no = data[i + j * NUM_MAP_X];
			if (no >= 1 && no < 10)
			{
				// ①今まで使用している当たり判定をfloatにして処理を行う(※CheckHitの中を参照)
				if (CheckHit(i * SIZE_MAP_X, j * SIZE_MAP_Y, SIZE_MAP_X, SIZE_MAP_Y, x, y, CHARA_WIDTH, CHARA_HEIGHT))
				{
					// ②上から当たっているかチェック
					if (y >= old_y)
					{
						// ③地形よりも上から当たっているかチェックする
						// その場合のみYを補正
						// そうでない場合は横から当たっている
						if (j * SIZE_MAP_Y - CHARA_HEIGHT >= old_y)
						{
							// ④地形に上から当たっている
							old_y = j * SIZE_MAP_Y - CHARA_HEIGHT;
							y = old_y;
							yadd = 0.0f;
						}
						else
						{
							// ⑤地形の横から当たっている
							// マスクするためintを使用します (floatだと、割って掛けると同じ値になってしまう)
							int _x = std::max(x, old_x);
							_x /= SIZE_MAP_X;
							_x *= SIZE_MAP_X;
							x = _x;
							old_x = x;
						}
					}
					// 下から当たっているかチェック
					else if (y < old_y)
					{
						// 地形よりも下から当たっているかチェックする
						// その場合のみYを補正
						// そうでない場合は横から当たっている
						if ((j + 1) * SIZE_MAP_Y <= old_y)
						{
							old_y = (j + 1) * SIZE_MAP_Y;
							y = old_y;
							yadd = 0.0f;
						}
						else
						{
							// 地形の横から当たっている
							// マスクするためintを使用します (floatだと、割って掛けると同じ値になってしまう)
							int _x = std::max(x, old_x);
							_x /= SIZE_MAP_X;
							_x *= SIZE_MAP_X;
							x = _x;
							old_x = x;
						}
					}
				}
			}
		}
	}
}

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
	CHARA_Init();

	// マップ初期化
	MAP_Init();

	//------------------------------------------------------
	// メインループ部分
	//------------------------------------------------------
	while (ProcessMessage() == 0)
	{
		//裏画面消す
		ClearDrawScreen();

		// マップ描画
		MAP_Draw();

		// キャラ更新
		CHARA_Update();

		// ブロックの当たり判定
		MAP_HitCheck();

		//ブロック描画
		DrawBlock();

		// キャラ描画
		CHARA_Draw();

		//裏画面を表画面を入れ替える
		ScreenFlip();
	}



	//======================================================
	// DXライブラリ終了とプログラム終了
	//======================================================
	DxLib_End();
	return 0;
}