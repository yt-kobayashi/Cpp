/*==================================================================================================
|
|   �T�v                :       ���O�擾�p�N���X
|   �쐬��              :       ���їR��
|	�쐬����			:		2018/09/10
|   �ړI                :       �e�탍�O�̎擾�Ə����̎���
|   �g�p�@              :       1 : GetLog�N���X��錾����
|									����
|										- logFileName	:	���O�t�@�C����[�����I�Ɍ��ɓ������ǉ������]
|										- csvFlag		:	CSV�o�͂����邩[true : CSV�o��  false : TXT�o��]
|										��csvFlag�͐ݒ肵�Ȃ��Ă��悢[TXT�o��]
|								2 : writeValue�Ő��l�����O�o�͂���
|									writenValue�Ő��l�����O�o�͂����̂��ɉ��s����
|									writeText�ŕ���������O�o�͂���
|									writenText�ŕ���������O�o�͂����̂��ɉ��s����
|   ����                :       �o�O�Ȃǂ̕s�������\������
|								�A����	:	eh15a036@oecu.jp	(���їR��)
|
==================================================================================================*/
/*====================================================================================================
|		�w�b�_�t�@�C���Ɩ��O��Ԃ̎g�p
+-----------------------------------------------------------------------------------------------------
|		�e�w�b�_�t�@�C���̐錾���s��
|
|		std���O��Ԃ��g�p����
====================================================================================================*/
//>>>>>>>>>>>>>>>>>>>> �w�b�_�t�@�C�� <<<<<<<<<<<<<<<<<<<<<//
#include "stdafx.h"
//#include <windows.h>						// WindowsAPI
//#include <stdio.h>							// �W�����o�͊֐�
//#include <fstream>							// �t�@�C���֌W
//#include <string>							// ������֌W
//#include <time.h>							// ����
//#include <iostream>
//#include "GetLog.h"
////>>>>>>>>>>>>>>>>>>>> ���O��Ԃ̎g�p <<<<<<<<<<<<<<<<<<<<<//
//using namespace std;

///*====================================================================================================
//|		GetLog�N���X�̐錾
//+-----------------------------------------------------------------------------------------------------
//|		���O�t�@�C���̍쐬,���O�t�@�C���̏������݂��s���N���X��錾����
//|
//|		���O�t�@�C�����̓v���C�x�[�g�Ƃ��Đ錾
//|		makeLogFile�����s�����ۂ�setFileName���ĂԂ��ƂŃ��O�t�@�C������_logFileName�Ɋi�[
//|
//|		_logFileName�ɕۑ�����Ă���t�@�C�����ɒǋL�Ƃ����`�Ń��O���o�͂���
//====================================================================================================*/
//class GetLog {
//private:
//	string p_logFileName;										// ���O�t�@�C����
//	bool p_csvFlag;												// CSV�`���o�̓t���O
//public:
//	GetLog(const string logFileName, const bool csvFlag);		// �R���X�g���N�^	�I�u�W�F�N�g�������Ɏ����ŌĂ΂��
//	GetLog(const string logFileName);							// �R���X�g���N�^	�I�u�W�F�N�g�������Ɏ����ŌĂ΂��
//	~GetLog();													// �f�X�g���N�^
//	bool writeLogFlag;											// �������݃t���O

//	string write(const double value);							// ���l�������ݗp
//	string write(const string value);							// �e�L�X�g�������ݗp
//	string GetLogFileName();									// �t�@�C�����擾�p
//};

///*====================================================================================================
//|		�N���X�̏�����
//+-----------------------------------------------------------------------------------------------------
//|		�w�肳�ꂽ���O�Ń��O�t�@�C�����쐬����
//|		logFileName			:	���O�t�@�C���̖��O
//|		csvFlag				:	CSV�t�@�C���o�̓t���O[true : CSV�t�@�C���o�� false : txt�t�@�C���o��]
//|							:	csvFlag�͎w�肹���Ƃ��g�p�\
//|							:	���̏ꍇ��txt�t�@�C���o�͂��s����
//+-----------------------------------------------------------------------------------------------------
//|		�쐬�������O�t�@�C���͈ȉ��̂悤�ɏo�͂����
//|		logFileName = [�w�薼]yyyymmddhhmmss
//|		�܂�CSV�t���O��true�ɂ���ƈȉ��̂̂悤�ɏo�͂����
//|		logFileName = [�w�薼]yyyymmddhhmmss.csv
//====================================================================================================*/
//inline GetLog::GetLog(const string logFileName, const bool csvFlag) {
//	writeLogFlag = true;			// �������݃t���OON
//	//>>>>>>>>>>>>>>>>>>>> �ϐ��̐錾 <<<<<<<<<<<<<<<<<<<<<//
//	string extensionCSV = ".csv";	// CSV�g���q
//	string extensionTXT = ".txt";	// txt�g���q
//	char timeText[41];				// ���ԃe�L�X�g
//	string outPutFileName;			// �o�̓t�@�C����
//	//>>>>>>>>>>>>>>>>>>>> ���Ԃ̏o�� <<<<<<<<<<<<<<<<<<<<<//
//	time_t t = time(NULL);			// time_t�^�̕ϐ�t��錾����
//	struct tm tm;					// ����,���t���i�[�p
//									/* ���t���ԏ��i�[ */
//	localtime_s(&tm, &t);
//	/* strftime(�o�̓t�@�C����, �o�̓t�@�C���̍ő�T�C�Y, �o�͕�����, ���ԓ��t���); */
//	strftime(timeText, sizeof(timeText), "%Y%m%d%H%M%S", &tm);
//	string timeString(timeText);	// ���ԕ�����
//	//>>>>>>>>>>>>>>>>>>>> ���Ԃ̘A�� <<<<<<<<<<<<<<<<<<<<<//
//	outPutFileName = logFileName + timeString;

//	//>>>>>>>>>>>>>>>>>>>> �g���q�̘A�� <<<<<<<<<<<<<<<<<<<<<//
//	if (csvFlag == true) {
//		// CSV�t�@�C���o�͂̏ꍇ
//		outPutFileName = outPutFileName + ".csv";
//	}
//	else {
//		// txt�t�@�C���o�͂̏ꍇ
//		outPutFileName = outPutFileName + extensionTXT;
//	}

//	p_logFileName = outPutFileName;
//	p_csvFlag = csvFlag;
//};
//inline GetLog::GetLog(const string logFileName){
//	writeLogFlag = true;			// �������݃t���OON
//									//>>>>>>>>>>>>>>>>>>>> �ϐ��̐錾 <<<<<<<<<<<<<<<<<<<<<//
//	string extensionCSV = ".csv";	// CSV�g���q
//	string extensionTXT = ".txt";	// txt�g���q
//	char timeText[41];				// ���ԃe�L�X�g
//									//string timeString;				// ���ԕ�����
//	string outPutFileName;			// �o�̓t�@�C����
//									//>>>>>>>>>>>>>>>>>>>> ���Ԃ̏o�� <<<<<<<<<<<<<<<<<<<<<//
//	time_t t = time(NULL);			// time_t�^�̕ϐ�t��錾����
//	struct tm tm;					// ����,���t���i�[�p
//									/* ���t���ԏ��i�[ */
//	localtime_s(&tm, &t);
//	/* strftime(�o�̓t�@�C����, �o�̓t�@�C���̍ő�T�C�Y, �o�͕�����, ���ԓ��t���); */
//	strftime(timeText, sizeof(timeText), "%Y%m%d%H%M%S", &tm);
//	string timeString(timeText);	// ���ԕ�����
//									//>>>>>>>>>>>>>>>>>>>> ���Ԃ̘A�� <<<<<<<<<<<<<<<<<<<<<//
//	outPutFileName = logFileName + timeString;

//	//>>>>>>>>>>>>>>>>>>>> �g���q�̘A�� <<<<<<<<<<<<<<<<<<<<<//
//	// txt�t�@�C���o�͂̏ꍇ
//	outPutFileName = outPutFileName + extensionTXT;

//	p_logFileName = outPutFileName;
//	p_csvFlag = false;
//};
//inline GetLog::~GetLog()
//{
//};

///*====================================================================================================
//|		���O�t�@�C���ւ̏�������
//+-----------------------------------------------------------------------------------------------------
//|		�w�肳�ꂽ���߂Ń��O�t�@�C���ɏ�������
//|		write				:	���l�������ݗp����s[���� : done ���s : undone]
//|			double value	:	���l�󂯎��
//|			string text		:	�e�L�X�g�󂯎��
//|		�I�[�o�[���C�h�ŕ�����Ɛ��l���P�̃��\�b�h�ň�����
//====================================================================================================*/
//inline string GetLog::write(const double value) {
//	string returnText;
//	if (writeLogFlag != 1) {
//		// �������݃t���OOFF�̏���
//		returnText = "undone";
//	}
//	else {
//		// �������݃t���OON�̏���
//		ofstream outputfile;								// �t�@�C���X�g���[���̎g�p
//		outputfile.open(p_logFileName, ios::app);			// ���O�t�@�C���̃I�[�v��
//		outputfile << value;								// ���O�t�@�C���ɏ�������
//		//>>>>>>>>>>>>>>>>>>>> CSV�t�@�C���o�� <<<<<<<<<<<<<<<<<<<<<//
//		if (p_csvFlag == true) {
//			// ��؂��}��
//			outputfile << ",";
//		}
//		returnText = "done";
//	}

//	return returnText;
//};
//inline string GetLog::write(const string value) {
//	string returnText;
//	string writeText;
//	if (writeLogFlag != 1) {
//		// �������݃t���OOFF�̏���
//		returnText = "undone";
//	}
//	else {
//		// �������݃t���OON�̏���
//		ofstream outputfile;								// �t�@�C���X�g���[���̎g�p
//		outputfile.open(p_logFileName, ios::app);			// ���O�t�@�C���̃I�[�v��
//		//>>>>>>>>>>>>>>>>>>>> �t�@�C���o�͕��� <<<<<<<<<<<<<<<<<<<<<//
//		// CSV�t�@�C���o�͂ł͂Ȃ�
//		if (value.find(",") != string::npos || p_csvFlag == false || value.rfind("\n") != string::npos ) {
//			writeText = value;
//		}
//		else {
//			writeText = value + ',';
//		}
//		outputfile << writeText;							// ���O�t�@�C���ɏ�������

//		returnText = "done";
//	}

//	return returnText;
//};

///*====================================================================================================
//| ���O�t�@�C������Ԃ�
//+-----------------------------------------------------------------------------------------------------
//| ���s�����΃��O�t�@�C������Ԃ�
//====================================================================================================*/
//inline string GetLog::GetLogFileName() {
//	return p_logFileName;
//}

/*====================================================================================================
|		GetLog�N���X�̎g�p�T���v����
+-----------------------------------------------------------------------------------------------------
|		GetLog�N���X�̎g�p�T���v����Ƃ���,���[�v�̉񐔂�CSV�t�@�C���Ƃ��ďo�͂���.
====================================================================================================*/
//int main(int argc, char* argv[]) {
//	//>>>>>>>>>>>>>>>>>>>> �ϐ��̐錾 <<<<<<<<<<<<<<<<<<<<<//
//	string logFirstName = "CounterLog";							// ���O�t�@�C���̖��O�̐擪������ݒ肷��
//	string logStat;												// ���O���������񂾍ۂɏ������݂�"����"��"���s"��������
//	string fileName;											// ������ǉ������t�@�C�������i�[����
//	LARGE_INTEGER freq;											// ���Ԍv���p�P��
//	if (!QueryPerformanceFrequency(&freq)) {return 0;}			// �P�ʂ̎擾
//	LARGE_INTEGER start, end, otw;								// ���Ԍv���̊J�n���ԂƏI�����ԗp
//	//>>>>>>>>>>>>>>>>>>>> GetLog�N���X�̐ݒ� <<<<<<<<<<<<<<<<<<<<<//
//	if (!QueryPerformanceCounter(&start)){
//		printf("���Ԍv�����s\n");
//	}
//	GetLog getCounterLog(logFirstName, true);					// GetLog�N���X��getCounterLog���쐬
//	GetLog getCounterLogText("textLog", false);					// GetLog�N���X��getCounterLog���쐬
//	GetLog writeText("maker");									// GetLog�N���X��writeText���쐬
//	if (!QueryPerformanceCounter(&end)){
//		printf("���Ԍv�����s\n");
//	}
//	logStat = getCounterLog.write("�N���X�錾����");
//	cout << "�������� : " << logStat << endl;
//	logStat = getCounterLog.write((double)(end.QuadPart - start.QuadPart) / freq.QuadPart);
//	logStat = getCounterLog.write("sec.\n");
//	otw = end;

//	//logStat = getCounterLog.writeText("Test Project\nMaker,YoshitakaKoabyashi\n");
//	logStat = writeText.write("Test Project\nMaker,YoshitakaKoabyashi\n");
//	logStat = writeText.write(2018);
//	//>>>>>>>>>>>>>>>>>>>> ���[�v�̊J�n <<<<<<<<<<<<<<<<<<<<<//
//	if (!QueryPerformanceCounter(&otw)) {
//		printf("���Ԍv�����s\n");
//	}
//	for (int counter = 0; counter < 1000; counter++) {
//		//>>>>>>>>>>>>>>>>>>>> ���O�̏o�͂Ə�Ԋm�F <<<<<<<<<<<<<<<<<<<<<//
//		//>>>>>>>>>>>>>>>>>>>> CSV�o�͂Ə�Ԋm�F <<<<<<<<<<<<<<<<<<<<<//
//		logStat = getCounterLog.write("Counter");
//		cout << "�������� : " << logStat << endl;
//		logStat = getCounterLog.write(counter);
//		cout << "�������� : " << logStat << endl;
//		logStat = getCounterLog.write("Remaining,");
//		cout << "�������� : " << logStat << endl;
//		logStat = getCounterLog.write(1000 - counter);
//		cout << "�������� : " << logStat << endl;
//		//>>>>>>>>>>>>>>>>>>>> TXT�o�͂Ə�Ԋm�F <<<<<<<<<<<<<<<<<<<<<//
//		logStat = getCounterLogText.write("Counter");
//		cout << "�������� : " << logStat << endl;
//		logStat = getCounterLogText.write(counter);
//		cout << "�������� : " << logStat << endl;
//		logStat = getCounterLogText.write("Remaining,");
//		cout << "�������� : " << logStat << endl;
//		logStat = getCounterLogText.write(1000 - counter);
//		cout << "�������� : " << logStat << endl;
//		logStat = getCounterLogText.write("\n");
//		cout << "�������� : " << logStat << endl;

//		//>>>>>>>>>>>>>>>>>>>> ���Ԍv�� <<<<<<<<<<<<<<<<<<<<<//
//		if (!QueryPerformanceCounter(&end)) {
//			printf("���Ԍv�����s\n");
//		}
//		logStat = getCounterLog.write("1���[�v��������");
//		cout << "�������� : " << logStat << endl;
//		logStat = getCounterLog.write((double)(end.QuadPart - otw.QuadPart) / freq.QuadPart);
//		logStat = getCounterLog.write("sec.\n");
//		otw = end;
//	}
//	cout << getCounterLog.GetLogFileName() << "�ɏo�͂��������܂���." << endl;		// ���O�t�@�C������Ԃ�
//	
//	if (!QueryPerformanceCounter(&end)){
//		printf("���Ԍv�����s\n");
//	}
//	cout << "���s���� : " << (double)(end.QuadPart - start.QuadPart) / freq.QuadPart << "sec.\n";
//	logStat = getCounterLog.write("���s���� : ");
//	logStat = getCounterLog.write((double)(end.QuadPart - start.QuadPart) / freq.QuadPart);
//	logStat = getCounterLog.write("sec.\n");
//	cout << "�������� : " << logStat << endl;

//	getchar();

//	return 0;
//}