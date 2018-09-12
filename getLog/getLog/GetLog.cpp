/*==================================================================================================
|
|   �T�v                :       GetLog�N���X�p���\�b�h
|   �쐬��              :       ���їR��
|	�쐬����			:		2018/09/12
|   �ړI                :       GetLog�N���X�̃��\�b�h��錾����
|
|   ���\�b�h����		:		�錾���Ɏ��s
|								GetLog(const string logFileName, const bool csvFlag)
|									����
|										- logFileName	:	���O�t�@�C����[�����I�Ɍ��ɓ������ǉ������]
|										- csvFlag		:	CSV�o�͂����邩[true : CSV�o��  false : TXT�o��]
|										��csvFlag�͐ݒ肵�Ȃ��Ă��悢[TXT�o��]
|						:		�t�@�C���o��
|								write(const double value)
|									����
|										- value			:	�o�͂��鐔�l
|									�߂�l
|										- done			:	�������݊���
|										- false			:	�������ݖ�����
|								write(const string value)
|									����
|										- value			:	�o�͂��镶����
|									�߂�l
|										- done			:	�������݊���
|										- false			:	�������ݖ�����
|						:		�o�̓t�@�C�����̎擾
|								getLogFileName()
|									�߂�l
|										- string�^�ŏo�̓t�@�C������Ԃ�
|
|   ����                :       �o�O�Ȃǂ̕s�������\������
|	�A����				:		eh15a036@oecu.jp	(���їR��)
|
==================================================================================================*/
#include "stdafx.h"
#include <stdio.h>							// �W�����o�͊֐�
#include <fstream>							// �t�@�C���֌W
#include <string>							// ������֌W
#include <time.h>							// ����
#include <iostream>							// �R���\�[���W�����o��
#include "GetLog.h"							// �N���X�w�b�_
using namespace std;

/*====================================================================================================
|		�N���X�̏�����
+-----------------------------------------------------------------------------------------------------
|		�w�肳�ꂽ���O�Ń��O�t�@�C�����쐬����
|		logFileName			:	���O�t�@�C���̖��O
|		csvFlag				:	CSV�t�@�C���o�̓t���O[true : CSV�t�@�C���o�� false : txt�t�@�C���o��]
|							:	csvFlag�͎w�肹���Ƃ��g�p�\
|							:	���̏ꍇ��txt�t�@�C���o�͂��s����
+-----------------------------------------------------------------------------------------------------
|		�쐬�������O�t�@�C���͈ȉ��̂悤�ɏo�͂����
|		logFileName = [�w�薼]yyyymmddhhmmss
|		�܂�CSV�t���O��true�ɂ���ƈȉ��̂̂悤�ɏo�͂����
|		logFileName = [�w�薼]yyyymmddhhmmss.csv
====================================================================================================*/
GetLog::GetLog(const string logFileName, const bool csvFlag) {
	//>>>>>>>>>>>>>>>>>>>> �ϐ��̐錾 <<<<<<<<<<<<<<<<<<<<<//
	writeLogFlag = true;			// �������݃t���OON
	//>>>>>>>>>>>>>>>>>>>> ���Ԃ̏o�� <<<<<<<<<<<<<<<<<<<<<//
	time_t t = time(NULL);			// time_t�^�̕ϐ�t��錾����
	struct tm tm;					// ����,���t���i�[�p
	/* ���t���ԏ��i�[ */
	localtime_s(&tm, &t);
	/* strftime(�o�̓t�@�C����, �o�̓t�@�C���̍ő�T�C�Y, �o�͕�����, ���ԓ��t���); */
	strftime(timeText, sizeof(timeText), "%Y%m%d%H%M%S", &tm);
	string timeString(timeText);	// ���ԕ�����
	//>>>>>>>>>>>>>>>>>>>> ���Ԃ̘A�� <<<<<<<<<<<<<<<<<<<<<//
	p_logFileName = logFileName + timeString;

	//>>>>>>>>>>>>>>>>>>>> �g���q�̘A�� <<<<<<<<<<<<<<<<<<<<<//
	if (csvFlag == true) {
		// CSV�t�@�C���o�͂̏ꍇ
		p_logFileName = p_logFileName + extensionCSV;
	}
	else {
		// txt�t�@�C���o�͂̏ꍇ
		p_logFileName = p_logFileName + extensionTXT;
	}

	p_csvFlag = csvFlag;
};
GetLog::GetLog(const string logFileName){
	//>>>>>>>>>>>>>>>>>>>> �ϐ��̐錾 <<<<<<<<<<<<<<<<<<<<<//
	writeLogFlag = true;			// �������݃t���OON
	//>>>>>>>>>>>>>>>>>>>> ���Ԃ̏o�� <<<<<<<<<<<<<<<<<<<<<//
	time_t t = time(NULL);			// time_t�^�̕ϐ�t��錾����
	struct tm tm;					// ����,���t���i�[�p
	/* ���t���ԏ��i�[ */
	localtime_s(&tm, &t);
	/* strftime(�o�̓t�@�C����, �o�̓t�@�C���̍ő�T�C�Y, �o�͕�����, ���ԓ��t���); */
	strftime(timeText, sizeof(timeText), "%Y%m%d%H%M%S", &tm);
	string timeString(timeText);	// ���ԕ�����
	//>>>>>>>>>>>>>>>>>>>> ���Ԃ̘A�� <<<<<<<<<<<<<<<<<<<<<//
	p_logFileName = logFileName + timeString + extensionTXT;

	p_csvFlag = false;
};
GetLog::~GetLog()
{
};

/*====================================================================================================
|		���O�t�@�C���ւ̏�������
+-----------------------------------------------------------------------------------------------------
|		�w�肳�ꂽ���߂Ń��O�t�@�C���ɏ�������
|		write				:	���l�������ݗp����s[���� : done ���s : undone]
|			double value	:	���l�󂯎��
|			string text		:	�e�L�X�g�󂯎��
|		�I�[�o�[���C�h�ŕ�����Ɛ��l���P�̃��\�b�h�ň�����
====================================================================================================*/
string GetLog::write(const double value) {
	string returnText;						// �߂�l
	if (writeLogFlag != 1) {
		// �������݃t���OOFF�̏���
		returnText = "undone";
	}
	else {
		// �������݃t���OON�̏���
		ofstream outputfile;								// �t�@�C���X�g���[���̎g�p
		outputfile.open(p_logFileName, ios::app);			// ���O�t�@�C���̃I�[�v��
		outputfile << value;								// ���O�t�@�C���ɏ�������
		//>>>>>>>>>>>>>>>>>>>> CSV�t�@�C���o�� <<<<<<<<<<<<<<<<<<<<<//
		if (p_csvFlag == true) {
			// ��؂��}��
			outputfile << ",";
		}
		returnText = "done";
	}

	return returnText;
};
string GetLog::write(const string value) {
	string returnText;						// �߂�l
	string writeText;						// �������ݕ�����
	if (writeLogFlag != 1) {
		// �������݃t���OOFF�̏���
		returnText = "undone";
	}
	else {
		// �������݃t���OON�̏���
		ofstream outputfile;								// �t�@�C���X�g���[���̎g�p
		outputfile.open(p_logFileName, ios::app);			// ���O�t�@�C���̃I�[�v��
		//>>>>>>>>>>>>>>>>>>>> �t�@�C���o�͕��� <<<<<<<<<<<<<<<<<<<<<//
		// "','���Ȃ���" "TXT�o�͂ł��邩" "'\n'�����݂��邩" �Ŏ��s
		if (value.find(",") != string::npos || p_csvFlag == false || value.rfind("\n") != string::npos ) {
			writeText = value;
		}
		else {
			writeText = value + ',';
		}
		outputfile << writeText;							// ���O�t�@�C���ɏ�������

		returnText = "done";
	}

	return returnText;
};

/*====================================================================================================
| ���O�t�@�C������Ԃ�
+-----------------------------------------------------------------------------------------------------
| ���s�����΃��O�t�@�C������Ԃ�
====================================================================================================*/
string GetLog::GetLogFileName() {
	return p_logFileName;
}
