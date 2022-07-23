#pragma once
#include "main.h"
//============================================================
// キャラクター定義
//============================================================
#define  CHARA_WIDTH  32
#define  CHARA_HEIGHT  32
 
#define  float x = (SCREEN_WIDTH - CHARA_WIDTH) / 2;		//< 画面の中心
#define  float y = (SCREEN_HEIGHT - CHARA_HEIGHT) / 2;	//< 画面の中心
#define  float yadd  0.0f


int act_index = 0;
#define MAX_MOTION_INDEX  6 //< 0,1,2,1 の4種類 [0～3]までにするために用意

#define ACT_SPEED  20


#define  ACT_NUM_X  9
#define ACT_NUM_Y  1
#define ACT_NUM_ALL2  1
#define ACT_NUM_ALL  ACT_NUM_X * ACT_NUM_Y

//const int ACT_NUM_ALL2 = ACT_NUM_X * ACT_NUM_Y;
#define ACT_DIR_SLIDE  ACT_NUM_X//< 横のキャラ分スライドさせれば次の列を選択する
int act_motion[] = { 1,1,1,1,1,3 };
int act_dir = 0;
