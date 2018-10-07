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

	// 共有メモリにデータ書き込み
	void OutMem(unsigned long*);
	void OutMem(std::vector<unsigned long>*);
	// IplImageからBMP(DIB)へ変換する
	//void iplTobmp(const IplImage* srcIplImage, BITMAPINFO& bmpInfo, unsigned long* bmpData);
	void iplTobmp(const IplImage* srcIplImage, BITMAPINFO& bmpInfo, BITMAPFILEHEADER& bmpHeader, unsigned long* bmpData);

public:
	// 共有メモリの作成
	int CreateMapObject(void);
	// ビットマップデータの書き込み
	void OutBmpData(cv::Mat *src);
	// ビットマップデータの読み込み
	//void InBmpData();
	cv::Mat InBmpData();
	// 共有メモリオブジェクトの破棄
	void CloseMapObject(void);
};

