#include <algorithm> //< std::max���g�p���邽��
#define NOMINMAX //< std::min/std::max�𐳂������삳���邽�߁BWindows���̈�Y
#include "DxLib.h"
#include <stdlib.h>
#include <stdio.h>
#define PI    3.1415926535897932384626433832795f
// ��ʃT�C�Y�ݒ�
const int SCREEN_WIDTH = 640; //< �X�N���[�����̑傫��
const int SCREEN_HEIGHT = 480; //< �X�N���[���c�̑傫��

//
// �����蔻����s���֐�
int CheckHit(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
	float L1 = x1;      // ��
	float R1 = x1 + w1; // �E(��+����)
	float L2 = x2;      // ��
	float R2 = x2 + w2; // �E(��+����)

	if (R1 <= L2) return 0; //< �����������Ȃ����Ƃɂ���
	if (R2 <= L1) return 0; //< �����������Ȃ����Ƃɂ���

	float U1 = y1;      // ��
	float D1 = y1 + h1; // ��(��+�c��)
	float U2 = y2;      // ��
	float D2 = y2 + h2; // ��(��+�c��)

	if (D1 <= U2) return 0; //< �����������Ȃ����Ƃɂ���
	if (D2 <= U1) return 0; //< �����������Ȃ����Ƃɂ���

	// ����ȊO�̏ꍇ�͓������Ă���
	return 1;
}

//============================================================
// �}�b�v�`�b�v��`
//============================================================
const int SIZE_MAP_X = 32;  //< �}�b�v�`�b�vX�T�C�Y
const int SIZE_MAP_Y = 32;	//< �}�b�v�`�b�vY�T�C�Y
const int NUM_CHIP_X = 1;  //< ��10���
const int NUM_CHIP_Y = 1;   //< �c4���
const int NUM_CHIP_ALL = NUM_CHIP_X * NUM_CHIP_Y;
int sora[5];
int block[1];

// �}�b�v�`�b�v���g�����w�i
const int NUM_MAP_X = 20; // 32x20=640
const int NUM_MAP_Y = 15; // 32x15=480

int data[] =
{
	// ��20x15
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
// �}�b�v�̏�����
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
// �}�b�v�̕`��
//----------------------------------------

int karablock;


void MAP_Draw()
{
	// �w�i�`��
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
// �L�����N�^�[��`
//============================================================
const int CHARA_WIDTH = 32;
const int CHARA_HEIGHT = 32;

float x = (SCREEN_WIDTH - CHARA_WIDTH) / 2;		//< ��ʂ̒��S
float y = (SCREEN_HEIGHT - CHARA_HEIGHT) / 2;	//< ��ʂ̒��S
float yadd = 0.0f;
float gravity = 0.2f;
// �O��̈ʒu
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

const int ACT_DIR_SLIDE = ACT_NUM_X; //< ���̃L�������X���C�h������Ύ��̗��I������

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
// �L�����̏�����
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
// �L�����ړ�
//----------------------------------------



void CHARA_Move()
{
	// �O��̈ʒu���o���Ă���(�֐����錾�ł͂Ȃ�)
	old_x = x;
	old_y = y;
	int Screen;
	unsigned int Cr;
	Cr = GetColor(255, 255, 255);
	int motion_index = act_motion[act_index];
	// �L�[�����擾����
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


	// �W�����v����
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
		DrawString(250, 240 - 32, "�}���I���������I!", Cr);

	}

	//�f�o�b�N
	printfDx("jump�J�E���g%d / yadd %.1f\n bool:%d\n", Jump_count, yadd,MarioGround);
	printfDx("X%.1f Y%.1f \n", x, y);
	

	if (input & PAD_INPUT_RIGHT)
	{
		x += speed;
		act_dir = 1; //< 2��ڂ�I��(0�X�^�[�g)
		num = 2;
		//DrawGraph(x, y, mario[motion_index + act_dir * ACT_DIR_SLIDE], TRUE);
	}

	if (input & PAD_INPUT_LEFT)

	{
		x -= speed;
		act_dir = 0; //< 1��ڂ�I��(0�X�^�[�g)
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

	// �d�͉����x�̏���
	y += yadd;
	yadd += gravity;
	// yadd �� -30 �` 30 �Ɏ��߂�
	yadd = std::min(30.0f, std::max(-30.0f, yadd));
}

//----------------------------------------
// �L�����A�j���X�V
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
// �L�����X�V
//----------------------------------------
void CHARA_Update()
{
	// �ړ������ƃA�j���������s��
	CHARA_Move();

	CHARA_Anim();
}

//----------------------------------------
// �L�����`��
//----------------------------------------
//----------------------------------------

void CHARA_Draw()
{
	int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	int motion_index = act_motion[act_index];
	//�����t���ĉ摜�̐؂�ւ����Ȃ��Ƃ����Ȃ�
}

void DrawBlock()
{
	int DrawGraph();
}
//============================================================
// �n�`�̓����蔻��̏���
//============================================================
//============================================================
//============================================================
//============================================================
void MAP_HitCheck()
{
	// �u���b�N�̓����蔻��
	for (int j = 0; j < NUM_MAP_Y; j++)
	{
		for (int i = 0; i < NUM_MAP_X; i++)
		{
			int no = data[i + j * NUM_MAP_X];
			if (no >= 1 && no < 10)
			{
				// �@���܂Ŏg�p���Ă��铖���蔻���float�ɂ��ď������s��(��CheckHit�̒����Q��)
				if (CheckHit(i * SIZE_MAP_X, j * SIZE_MAP_Y, SIZE_MAP_X, SIZE_MAP_Y, x, y, CHARA_WIDTH, CHARA_HEIGHT))
				{
					// �A�ォ�瓖�����Ă��邩�`�F�b�N
					if (y >= old_y)
					{
						// �B�n�`�����ォ�瓖�����Ă��邩�`�F�b�N����
						// ���̏ꍇ�̂�Y��␳
						// �����łȂ��ꍇ�͉����瓖�����Ă���
						if (j * SIZE_MAP_Y - CHARA_HEIGHT >= old_y)
						{
							// �C�n�`�ɏォ�瓖�����Ă���
							old_y = j * SIZE_MAP_Y - CHARA_HEIGHT;
							y = old_y;
							yadd = 0.0f;
						}
						else
						{
							// �D�n�`�̉����瓖�����Ă���
							// �}�X�N���邽��int���g�p���܂� (float���ƁA�����Ċ|����Ɠ����l�ɂȂ��Ă��܂�)
							int _x = std::max(x, old_x);
							_x /= SIZE_MAP_X;
							_x *= SIZE_MAP_X;
							x = _x;
							old_x = x;
						}
					}
					// �����瓖�����Ă��邩�`�F�b�N
					else if (y < old_y)
					{
						// �n�`���������瓖�����Ă��邩�`�F�b�N����
						// ���̏ꍇ�̂�Y��␳
						// �����łȂ��ꍇ�͉����瓖�����Ă���
						if ((j + 1) * SIZE_MAP_Y <= old_y)
						{
							old_y = (j + 1) * SIZE_MAP_Y;
							y = old_y;
							yadd = 0.0f;
						}
						else
						{
							// �n�`�̉����瓖�����Ă���
							// �}�X�N���邽��int���g�p���܂� (float���ƁA�����Ċ|����Ɠ����l�ɂȂ��Ă��܂�)
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
	// �E�C���h�E�ݒ��DX���C�u�����̏�����
	//======================================================

	// Windows���[�h�ɂ���
	ChangeWindowMode(TRUE);
	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
	// DX���C�u����������
	if (DxLib_Init() == -1)
	{
		//�������Ɏ��s
		return -1;
	}
	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);
	//======================================================
	// �Q�[������
	//======================================================
	//------------------------------------------------------
	// �Q�[������������
	//------------------------------------------------------

	// �L�����̃��[�h
	CHARA_Init();

	// �}�b�v������
	MAP_Init();

	//------------------------------------------------------
	// ���C�����[�v����
	//------------------------------------------------------
	while (ProcessMessage() == 0)
	{
		//����ʏ���
		ClearDrawScreen();

		// �}�b�v�`��
		MAP_Draw();

		// �L�����X�V
		CHARA_Update();

		// �u���b�N�̓����蔻��
		MAP_HitCheck();

		//�u���b�N�`��
		DrawBlock();

		// �L�����`��
		CHARA_Draw();

		//����ʂ�\��ʂ����ւ���
		ScreenFlip();
	}



	//======================================================
	// DX���C�u�����I���ƃv���O�����I��
	//======================================================
	DxLib_End();
	return 0;
}