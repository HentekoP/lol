#pragma once
#include "main.h"
//============================================================
// �L�����N�^�[��`
//============================================================
#define  CHARA_WIDTH  32
#define  CHARA_HEIGHT  32
 
#define  float x = (SCREEN_WIDTH - CHARA_WIDTH) / 2;		//< ��ʂ̒��S
#define  float y = (SCREEN_HEIGHT - CHARA_HEIGHT) / 2;	//< ��ʂ̒��S
#define  float yadd  0.0f


int act_index = 0;
#define MAX_MOTION_INDEX  6 //< 0,1,2,1 ��4��� [0�`3]�܂łɂ��邽�߂ɗp��

#define ACT_SPEED  20


#define  ACT_NUM_X  9
#define ACT_NUM_Y  1
#define ACT_NUM_ALL2  1
#define ACT_NUM_ALL  ACT_NUM_X * ACT_NUM_Y

//const int ACT_NUM_ALL2 = ACT_NUM_X * ACT_NUM_Y;
#define ACT_DIR_SLIDE  ACT_NUM_X//< ���̃L�������X���C�h������Ύ��̗��I������
int act_motion[] = { 1,1,1,1,1,3 };
int act_dir = 0;
