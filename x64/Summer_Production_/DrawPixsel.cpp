#include "DxLib.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);

	int i;
	int mario[9]; //9���̉摜������

	if (DxLib_Init() == -1)        // �c�w���C�u��������������
	{
		return -1;        // �G���[���N�����璼���ɏI��
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

	// �ǂݍ��񂾉摜�̃O���t�B�b�N�n���h�����폜
	ScreenFlip();
	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;
}

