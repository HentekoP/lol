#include "CHARA.h"
#include "Map.h"
#include "CHARA.h"
#include "main.h"
#include "DxLib.h"
#include <algorithm> //< std::max���g�p���邽��
#define NOMINMAX //< std::min/std::max�𐳂������삳���邽�߁BWindows���̈�Y

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
	void CHARA_Init();

	// �}�b�v������
 void	  MAP_Init();

	//------------------------------------------------------
	// ���C�����[�v����
	//------------------------------------------------------
	while (ProcessMessage() == 0)
	{
		//����ʏ���
		ClearDrawScreen();

		// �}�b�v�`��
		void MAP_Draw();

		// �L�����X�V
	void CHARA_Update();

		// �u���b�N�̓����蔻��
		void MAP_HitCheck();

		//�u���b�N�`��
		void DrawBlock();

		// �L�����`��
		void CHARA_Draw();

		//����ʂ�\��ʂ����ւ���
		ScreenFlip();
	}

	//======================================================
	// DX���C�u�����I���ƃv���O�����I��
	//======================================================
	DxLib_End();
	return 0;
}