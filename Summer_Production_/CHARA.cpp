#include "main.h"
#include "CHARA.h"
//----------------------------------------
// キャラの初期化
//----------------------------------------
//---------------------------------------- int act_motion[] = { 1,1,1,1,1,3, };




// 前回の位置

void CHARA_Init()
{
	LoadDivGraph("mario/mario.png", ACT_NUM_ALL, ACT_NUM_X, ACT_NUM_Y,
		CHARA_WIDTH, CHARA_HEIGHT,
		mario);
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

	const float speed = 3.0f;

	// キー情報を取得する
	int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// キーで移動させる
	if (input & PAD_INPUT_RIGHT)
	{
		x += speed;
		act_dir = 0; //< 2列目を選ぶ(0スタート)
		//DrawRotaGraph2(ACT_NUM_X, ACT_NUM_Y, CHARA_WIDTH, CHARA_HEIGHT, 1.5f, PI / CHARA_HEIGHT, mario, TRUE);
	}
	if (input & PAD_INPUT_LEFT)
	{
		x -= speed;
		act_dir = 0; //< 1列目を選ぶ(0スタート)

		//DrawRotaGraph()

	}

	// ジャンプ処理
	if (input & PAD_INPUT_B)
	{
		yadd = -4.0f;
	}

	if (input & PAD_INPUT_A)
	{

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
void CHARA_Draw()
{
	int motion_index = act_motion[act_index];

	// 自分のキャラを表示する
	DrawGraph(x, y, mario[motion_index + act_dir * ACT_DIR_SLIDE], TRUE);
	//DrawRotaGraph();
}