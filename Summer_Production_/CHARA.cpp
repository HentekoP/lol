#include "main.h"
#include "CHARA.h"
//----------------------------------------
// �L�����̏�����
//----------------------------------------
//---------------------------------------- int act_motion[] = { 1,1,1,1,1,3, };




// �O��̈ʒu

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
// �L�����ړ�
//----------------------------------------
void CHARA_Move()
{
	// �O��̈ʒu���o���Ă���(�֐����錾�ł͂Ȃ�)
	old_x = x;
	old_y = y;

	const float speed = 3.0f;

	// �L�[�����擾����
	int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// �L�[�ňړ�������
	if (input & PAD_INPUT_RIGHT)
	{
		x += speed;
		act_dir = 0; //< 2��ڂ�I��(0�X�^�[�g)
		//DrawRotaGraph2(ACT_NUM_X, ACT_NUM_Y, CHARA_WIDTH, CHARA_HEIGHT, 1.5f, PI / CHARA_HEIGHT, mario, TRUE);
	}
	if (input & PAD_INPUT_LEFT)
	{
		x -= speed;
		act_dir = 0; //< 1��ڂ�I��(0�X�^�[�g)

		//DrawRotaGraph()

	}

	// �W�����v����
	if (input & PAD_INPUT_B)
	{
		yadd = -4.0f;
	}

	if (input & PAD_INPUT_A)
	{

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
void CHARA_Draw()
{
	int motion_index = act_motion[act_index];

	// �����̃L������\������
	DrawGraph(x, y, mario[motion_index + act_dir * ACT_DIR_SLIDE], TRUE);
	//DrawRotaGraph();
}