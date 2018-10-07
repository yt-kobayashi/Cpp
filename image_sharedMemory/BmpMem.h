#pragma once
#include <Windows.h>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

class BmpMem
{
public:
	BmpMem();
	~BmpMem();
private:
	HANDLE m_hMapping;
	LPSTR m_lpBuff;
	int m_memSize;
	int m_ImageWidth;
	int m_ImageHeight;
	//BITMAPINFO& bmpInfo;

	// ���L�������Ƀf�[�^��������
	void OutMem(unsigned long*);
	void OutMem(std::vector<unsigned long>*);
	// IplImage����BMP(DIB)�֕ϊ�����
	//void iplTobmp(const IplImage* srcIplImage, BITMAPINFO& bmpInfo, unsigned long* bmpData);
	void iplTobmp(const IplImage* srcIplImage, BITMAPINFO& bmpInfo, BITMAPFILEHEADER& bmpHeader, unsigned long* bmpData);

public:
	// ���L�������̍쐬
	int CreateMapObject(void);
	// �r�b�g�}�b�v�f�[�^�̏�������
	void OutBmpData(cv::Mat *src);
	// �r�b�g�}�b�v�f�[�^�̓ǂݍ���
	//void InBmpData();
	cv::Mat InBmpData();
	// ���L�������I�u�W�F�N�g�̔j��
	void CloseMapObject(void);
};

