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
		// マッピングオブジェクト作成
		m_hMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, MEMORY_SIZE, BMP_SHARE_MEM);
		if (m_hMapping == NULL) {
			cout << "マップドファイルオブジェクトの作成に失敗しました" << endl;
			getchar();
			return -1;
		}

		// 共有メモリをマッピング
		m_lpBuff = (LPSTR)::MapViewOfFile(m_hMapping, FILE_MAP_WRITE, 0, 0, 0);
		if (m_lpBuff == NULL) {
			cout << "MapViewOfFileエラー" << endl;
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
		cout << "出力が完了しました" << endl;
	}
	catch (...) {
		cout << endl << "OutMem Exception !" << endl;
		getchar();
	}
}
void BmpMem::OutMem(vector<unsigned long>* imageBuffer) {
	try {
		memcpy(m_lpBuff, imageBuffer, (16 + (m_ImageWidth * m_ImageHeight)) * 4);
		cout << "vector出力が完了しました" << endl;
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
		cout << "共有メモリに出力します" << endl;
		//iplTobmp(&IplImg, info, bmpHeader, bmpData, imageBuffer);
		iplTobmp(&IplImg, info, bmpHeader, bmpData);
		//cout << "共有メモリに出力します" << endl;
		OutMem(bmpData);
		HeapFree(hHandle, 0, bmpData);
		cout << "出力が完了しました" << endl;
	}
	catch (...) {
		cout << endl << "OutBmpData Exception !" << endl;
		getchar();
	}
}

Mat BmpMem::InBmpData() {
	HANDLE mh_lpBuff = (LPSTR)::OpenFileMapping(FILE_MAP_ALL_ACCESS, false, BMP_SHARE_MEM);
	// 共有メモリをマッピング
	LPSTR mp_lpBuff = (LPSTR)::MapViewOfFile(mh_lpBuff, FILE_MAP_WRITE, 0, 0, 0);
	if (mp_lpBuff == NULL) {
		cout << "MapViewOfFileエラー" << endl;
		getchar();
	}
	unsigned long bmpInfo[16] = {};
	int bmpInfoInt[16] = {};
	memcpy(bmpInfo, mp_lpBuff, 16 * 4);
	cout << "インフォ部を読み込みました" << endl;
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
	cout << "Mat宣言完了" << endl;
	try {
		unsigned char b, g, r;
		unsigned long pixel;
		cout << "変数宣言完了しました" << endl;

		for (int countHeight = 0; countHeight < bmpInfoInt[7] - 1; countHeight++) {
			cout << countHeight << "行目を読み込みます" << endl;
			for (int countWidth = 0; countWidth < bmpInfoInt[6]; countWidth++) {
				CopyMemory(&pixel, (mp_lpBuff + ((16 + countWidth + ((bmpInfo[7] - countHeight - 1) * bmpInfo[6])) * 4)), sizeof(unsigned long));
				b = pixel;
				g = pixel >> 8;
				r = pixel >> 16;
				bmpImage.at<cv::Vec3b>(countHeight, countWidth)[0] = b;
				bmpImage.at<cv::Vec3b>(countHeight, countWidth)[1] = g;
				bmpImage.at<cv::Vec3b>(countHeight, countWidth)[2] = r;
			}
		cout << "読み込み完了しました" << endl;
		}
		cout << "読み込み完了しました" << endl;
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

// IplImageからBMP(DIB)へ変換する
// bmpDataはポインタを渡している
void BmpMem::iplTobmp(const IplImage* srcIplImage, BITMAPINFO& bmpInfo, BITMAPFILEHEADER& bmpHeader, unsigned long* bmpData) {
	int width = srcIplImage->width;
	int height = srcIplImage->height;


	// ビットマップのヘッダーを0で初期化
	ZeroMemory(&bmpHeader, sizeof(bmpHeader));
	bmpHeader.bfType = 'BM';								// ファイルタイプ
	bmpHeader.bfSize = (16 + width * height) * 4;			// ファイル全体のサイズ
	bmpHeader.bfReserved1 = 0;								// 予約領域	常に0
	bmpHeader.bfReserved2 = 0;								// 予約領域 常に0
	bmpHeader.bfOffBits = 16;								// ファイル先頭から画像データまでのオフセット値
	// bmpData[0-4]にヘッダ情報を格納
	bmpData[0] = bmpHeader.bfType;
	bmpData[1] = bmpHeader.bfSize;
	bmpData[2] = bmpHeader.bfReserved1;
	bmpData[3] = bmpHeader.bfReserved2;
	bmpData[4] = bmpHeader.bfOffBits;
	
	// ビットマップのインフォを0で初期化
	ZeroMemory(&bmpInfo, sizeof(bmpInfo));
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);	// Info構造体のサイズ 40
	bmpInfo.bmiHeader.biWidth = width;						// 画像の幅[pix]
	bmpInfo.bmiHeader.biHeight = height;					// 画像の高さ[pix]
	bmpInfo.bmiHeader.biPlanes = 1;							// プレーン数 常に1
	bmpInfo.bmiHeader.biBitCount = 32;						// 1画素あたりのビット数
	bmpInfo.bmiHeader.biCompression = BI_RGB;				// 圧縮形式
	bmpInfo.bmiHeader.biSizeImage = 0;						// 画像データのサイズ(byte) BI_RGBは0でも可
	bmpInfo.bmiHeader.biXPelsPerMeter = 0;					// 水平方向1[m]あたりの画素数 0でも可
	bmpInfo.bmiHeader.biYPelsPerMeter = 0;					// 垂直方向1[m]あたりの画素数 0でも可
	bmpInfo.bmiHeader.biClrUsed = 0;						// カラーテーブルの色数 0でも可
	bmpInfo.bmiHeader.biClrImportant = 0;					// 表示に必要なカラーテーブルの色数 0でも可
	// bmpData[5-15]にインフォ情報を格納
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
	cout << "情報を出力しました" << endl;

	for (int count = 0; count < 16; count++) {
		cout << count << " : " << bmpData[count] << endl;
	}
	unsigned long pixel;
	unsigned char r, g, b;
	for (int countHeight = 0; countHeight < height; countHeight++) {
		for (int countWidth = 0; countWidth < width; countWidth++) {
			// Brue,Green,Redの画素値を取得する
			b = srcIplImage->imageData[srcIplImage->widthStep * countHeight + countWidth * 3];
			g = srcIplImage->imageData[srcIplImage->widthStep * countHeight + countWidth * 3 + 1];
			r = srcIplImage->imageData[srcIplImage->widthStep * countHeight + countWidth * 3 + 2];
			//imageBuffer->push_back(b);
			//imageBuffer->push_back(g);
			//imageBuffer->push_back(r);
			// pixelを初期化する
			pixel = 0x00000000;
			// rは16bitシフト,gは8bitシフト,bはそのままでpixelに格納
			pixel = (r << 16) + (g << 8) + b;
			// pixelをbmpDataに格納
			bmpData[16 + countWidth + (height - countHeight - 1) * width] = pixel;
		}
		cout << countHeight << "行目の画素データを格納します" << endl;
	}
	cout << "画像を出力しました" << endl;
}