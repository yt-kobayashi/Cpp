#include "stdafx.h"
#include <Windows.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <vector>
#include "BmpMem.h"

#define _CRTBG_MAP_ALLOC
#define BMP_SHARE_MEM _T("BMP_SHARED_MEMORY")
#define MEMORY_SIZE 3000 * 2000 * 4

using namespace std;
using namespace cv;

BmpMem::BmpMem()
{
}

BmpMem::~BmpMem()
{
}

int BmpMem::CreateMapObject(void) {
	try {
		// �}�b�s���O�I�u�W�F�N�g�쐬
		m_hMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, MEMORY_SIZE, BMP_SHARE_MEM);
		if (m_hMapping == NULL) {
			cout << "�}�b�v�h�t�@�C���I�u�W�F�N�g�̍쐬�Ɏ��s���܂���" << endl;
			getchar();
			return -1;
		}

		// ���L���������}�b�s���O
		m_lpBuff = (LPSTR)::MapViewOfFile(m_hMapping, FILE_MAP_WRITE, 0, 0, 0);
		if (m_lpBuff == NULL) {
			cout << "MapViewOfFile�G���[" << endl;
			getchar();
			return -1;
		}

		::ZeroMemory(m_lpBuff, MEMORY_SIZE);
	}
	catch (...) {
		cout << endl << "CreateMapObject Exception !" << endl;
		getchar();
	}

	return 0;
}

void BmpMem::OutMem(unsigned long* bmp_img) {
	try {
		memcpy(m_lpBuff, bmp_img, m_ImageWidth * m_ImageHeight * 4);
		cout << "�o�͂��������܂���" << endl;
	}
	catch (...) {
		cout << endl << "OutMem Exception !" << endl;
		getchar();
	}
}
void BmpMem::OutMem(vector<unsigned long>* imageBuffer) {
	try {
		memcpy(m_lpBuff, imageBuffer, (16 + (m_ImageWidth * m_ImageHeight)) * 4);
		cout << "vector�o�͂��������܂���" << endl;
	}
	catch (...) {
		cout << endl << "OutMem Exception !" << endl;
		getchar();
	}
}

void BmpMem::OutBmpData(cv::Mat* src) {
	m_ImageWidth = src->rows;
	m_ImageHeight = src->cols;
	IplImage IplImg;
	BITMAPINFO info;
	BITMAPFILEHEADER bmpHeader;

	try {
		IplImg = *src;

		HANDLE hHandle;
		unsigned long* bmpData;
		hHandle = GetProcessHeap();
		bmpData = (LPDWORD)HeapAlloc(hHandle, HEAP_ZERO_MEMORY, (16 + (m_ImageWidth * m_ImageHeight)) * 4);
		cout << "���L�������ɏo�͂��܂�" << endl;
		//iplTobmp(&IplImg, info, bmpHeader, bmpData, imageBuffer);
		iplTobmp(&IplImg, info, bmpHeader, bmpData);
		//cout << "���L�������ɏo�͂��܂�" << endl;
		OutMem(bmpData);
		HeapFree(hHandle, 0, bmpData);
		cout << "�o�͂��������܂���" << endl;
	}
	catch (...) {
		cout << endl << "OutBmpData Exception !" << endl;
		getchar();
	}
}

Mat BmpMem::InBmpData() {
	HANDLE mh_lpBuff = (LPSTR)::OpenFileMapping(FILE_MAP_ALL_ACCESS, false, BMP_SHARE_MEM);
	// ���L���������}�b�s���O
	LPSTR mp_lpBuff = (LPSTR)::MapViewOfFile(mh_lpBuff, FILE_MAP_WRITE, 0, 0, 0);
	if (mp_lpBuff == NULL) {
		cout << "MapViewOfFile�G���[" << endl;
		getchar();
	}
	unsigned long bmpInfo[16] = {};
	int bmpInfoInt[16] = {};
	memcpy(bmpInfo, mp_lpBuff, 16 * 4);
	cout << "�C���t�H����ǂݍ��݂܂���" << endl;
	int width = bmpInfo[6];
	int height = bmpInfo[7];
	for (int count = 0; count < 16; count++) {
		cout << count << " : " << bmpInfo[count] << endl;
		bmpInfoInt[count] = bmpInfo[count];
	}
	for (int count = 0; count < 16; count++) {
		cout << count << " : " << bmpInfoInt[count] << endl;
	}
	cv::Mat image;
	cv::Mat bmpImage(cvSize(bmpInfoInt[6], bmpInfoInt[7]), CV_8UC3, cv::Scalar(0));
	cout << "Mat�錾����" << endl;
	try {
		unsigned char b, g, r;
		unsigned long pixel;
		cout << "�ϐ��錾�������܂���" << endl;

		for (int countHeight = 0; countHeight < bmpInfoInt[7] - 1; countHeight++) {
			cout << countHeight << "�s�ڂ�ǂݍ��݂܂�" << endl;
			for (int countWidth = 0; countWidth < bmpInfoInt[6]; countWidth++) {
				CopyMemory(&pixel, (mp_lpBuff + ((16 + countWidth + ((bmpInfo[7] - countHeight - 1) * bmpInfo[6])) * 4)), sizeof(unsigned long));
				b = pixel;
				g = pixel >> 8;
				r = pixel >> 16;
				bmpImage.at<cv::Vec3b>(countHeight, countWidth)[0] = b;
				bmpImage.at<cv::Vec3b>(countHeight, countWidth)[1] = g;
				bmpImage.at<cv::Vec3b>(countHeight, countWidth)[2] = r;
			}
		cout << "�ǂݍ��݊������܂���" << endl;
		}
		cout << "�ǂݍ��݊������܂���" << endl;
	}
	catch (...) {
		cout << endl << "CloseMapObject Exception !" << endl;
		getchar();
	}
	return bmpImage;
}

void BmpMem::CloseMapObject(void) {
	try {
		UnmapViewOfFile(m_lpBuff);
		CloseHandle(m_hMapping);
	}
	catch (...) {
		cout << endl << "CloseMapObject Exception !" << endl;
		getchar();
	}
}

// IplImage����BMP(DIB)�֕ϊ�����
// bmpData�̓|�C���^��n���Ă���
void BmpMem::iplTobmp(const IplImage* srcIplImage, BITMAPINFO& bmpInfo, BITMAPFILEHEADER& bmpHeader, unsigned long* bmpData) {
	int width = srcIplImage->width;
	int height = srcIplImage->height;


	// �r�b�g�}�b�v�̃w�b�_�[��0�ŏ�����
	ZeroMemory(&bmpHeader, sizeof(bmpHeader));
	bmpHeader.bfType = 'BM';								// �t�@�C���^�C�v
	bmpHeader.bfSize = (16 + width * height) * 4;			// �t�@�C���S�̂̃T�C�Y
	bmpHeader.bfReserved1 = 0;								// �\��̈�	���0
	bmpHeader.bfReserved2 = 0;								// �\��̈� ���0
	bmpHeader.bfOffBits = 16;								// �t�@�C���擪����摜�f�[�^�܂ł̃I�t�Z�b�g�l
	// bmpData[0-4]�Ƀw�b�_�����i�[
	bmpData[0] = bmpHeader.bfType;
	bmpData[1] = bmpHeader.bfSize;
	bmpData[2] = bmpHeader.bfReserved1;
	bmpData[3] = bmpHeader.bfReserved2;
	bmpData[4] = bmpHeader.bfOffBits;
	
	// �r�b�g�}�b�v�̃C���t�H��0�ŏ�����
	ZeroMemory(&bmpInfo, sizeof(bmpInfo));
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);	// Info�\���̂̃T�C�Y 40
	bmpInfo.bmiHeader.biWidth = width;						// �摜�̕�[pix]
	bmpInfo.bmiHeader.biHeight = height;					// �摜�̍���[pix]
	bmpInfo.bmiHeader.biPlanes = 1;							// �v���[���� ���1
	bmpInfo.bmiHeader.biBitCount = 32;						// 1��f������̃r�b�g��
	bmpInfo.bmiHeader.biCompression = BI_RGB;				// ���k�`��
	bmpInfo.bmiHeader.biSizeImage = 0;						// �摜�f�[�^�̃T�C�Y(byte) BI_RGB��0�ł���
	bmpInfo.bmiHeader.biXPelsPerMeter = 0;					// ��������1[m]������̉�f�� 0�ł���
	bmpInfo.bmiHeader.biYPelsPerMeter = 0;					// ��������1[m]������̉�f�� 0�ł���
	bmpInfo.bmiHeader.biClrUsed = 0;						// �J���[�e�[�u���̐F�� 0�ł���
	bmpInfo.bmiHeader.biClrImportant = 0;					// �\���ɕK�v�ȃJ���[�e�[�u���̐F�� 0�ł���
	// bmpData[5-15]�ɃC���t�H�����i�[
	bmpData[5] = bmpInfo.bmiHeader.biSize;
	bmpData[6] = bmpInfo.bmiHeader.biWidth;
	bmpData[7] = bmpInfo.bmiHeader.biHeight;
	bmpData[8] = bmpInfo.bmiHeader.biPlanes;
	bmpData[9] = bmpInfo.bmiHeader.biBitCount;
	bmpData[10] = bmpInfo.bmiHeader.biCompression;
	bmpData[11] = bmpInfo.bmiHeader.biSizeImage;
	bmpData[12] = bmpInfo.bmiHeader.biXPelsPerMeter;
	bmpData[13] = bmpInfo.bmiHeader.biYPelsPerMeter;
	bmpData[14] = bmpInfo.bmiHeader.biClrUsed;
	bmpData[15] = bmpInfo.bmiHeader.biClrImportant;
	cout << "�����o�͂��܂���" << endl;

	for (int count = 0; count < 16; count++) {
		cout << count << " : " << bmpData[count] << endl;
	}
	unsigned long pixel;
	unsigned char r, g, b;
	for (int countHeight = 0; countHeight < height; countHeight++) {
		for (int countWidth = 0; countWidth < width; countWidth++) {
			// Brue,Green,Red�̉�f�l���擾����
			b = srcIplImage->imageData[srcIplImage->widthStep * countHeight + countWidth * 3];
			g = srcIplImage->imageData[srcIplImage->widthStep * countHeight + countWidth * 3 + 1];
			r = srcIplImage->imageData[srcIplImage->widthStep * countHeight + countWidth * 3 + 2];
			//imageBuffer->push_back(b);
			//imageBuffer->push_back(g);
			//imageBuffer->push_back(r);
			// pixel������������
			pixel = 0x00000000;
			// r��16bit�V�t�g,g��8bit�V�t�g,b�͂��̂܂܂�pixel�Ɋi�[
			pixel = (r << 16) + (g << 8) + b;
			// pixel��bmpData�Ɋi�[
			bmpData[16 + countWidth + (height - countHeight - 1) * width] = pixel;
		}
		cout << countHeight << "�s�ڂ̉�f�f�[�^���i�[���܂�" << endl;
	}
	cout << "�摜���o�͂��܂���" << endl;
}