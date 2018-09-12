/*==================================================================================================
|
|   �T�v                :       ���O�擾�p�N���X�w�b�_
|   �쐬��              :       ���їR��
|	�쐬����			:		2018/09/12
|
|   �g�p�@
|		1	:	�w�b�_�t�@�C����GetLog.cpp���v���W�F�N�g�ɒǉ�����
|
|	�A����				:		eh15a036@oecu.jp	(���їR��)
|
==================================================================================================*/
#ifndef GETLOG_H
#define GETLOG_H

#pragma once
#include <string>
/*====================================================================================================
|		GetLog�N���X�̐錾
+-----------------------------------------------------------------------------------------------------
|		���O�t�@�C���̍쐬,���O�t�@�C���̏������݂��s���N���X��錾����
|
|		_logFileName�ɕۑ�����Ă���t�@�C�����ɒǋL�Ƃ����`�Ń��O���o�͂���
|
|		
====================================================================================================*/
class GetLog {
private:
	std::string p_logFileName;										// ���O�t�@�C����
	bool p_csvFlag;													// CSV�`���o�̓t���O
	std::string extensionCSV = ".csv";								// CSV�g���q
	std::string extensionTXT = ".txt";								// txt�g���q
	char timeText[41];												// ���ԃe�L�X�g
public:
	GetLog(const std::string logFileName, const bool csvFlag);		// ���O�t�@�C����, �t�@�C���o�͕���[csv or txt]�w��
	GetLog(const std::string logFileName);							// ���O�t�@�C�����w��
	~GetLog();														// �f�X�g���N�^
	bool writeLogFlag;												// �������݃t���O

	std::string write(const double value);							// ���l�������ݗp
	std::string write(const std::string value);						// �e�L�X�g�������ݗp
	std::string GetLogFileName();									// �t�@�C�����擾�p
};

#endif // GETLOG_H