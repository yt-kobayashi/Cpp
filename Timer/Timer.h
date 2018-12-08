#pragma once
/*==================================================================================================
|
|   �T�v                :       ���Ԍv������p�N���X
|   �쐬��              :       ���їR��
|   �ړI                :       ���Ԍv���̐�����N���X�Ƃ��Ē񋟂��邱�ƂŊȒP�Ɏ��Ԍv����������悤
|								�ɂ���
|   �g�p�@              :       Timer.cpp��Timer.h���v���W�F�N�g�ɒǉ����Ďg�p����
|
==================================================================================================*/
#include <Windows.h>
#include <string>

class Timer
{
private:
	double unitNum;								// �P�ʌW��
	std::string unit;							// �P�ʐݒ� �~���b:ms �b:s ��:min ����:h
	LARGE_INTEGER freq, start, end;				// ���g��,�J�n����,�I������
	double returnTime;							// �Ԃ��ׂ̈ꎞ�ϐ�
public:
	// �R���g���N�^
	Timer();
	Timer(std::string unitString);
	// �f�X�g���N�^
	~Timer();
	// �P�ʐݒ�
	void SetUnit(std::string unitString);
	// �^�C�}�[�֌W
	double StartTimer();
	double EndTimer();
};

