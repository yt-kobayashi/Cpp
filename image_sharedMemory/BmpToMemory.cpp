// BmpToMemory.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <conio.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "BmpMem.h"

using namespace std;
using namespace cv;


int _tmain(int argc, _TCHAR* argv[])
{
	int key;
	Mat img;
	Mat returnImage;

	cout << "共有メモリのオープンに成功しました" << endl;
	//img = imread("06200.jpg", 1);
	//img = imread("TAMAMO.jpg", 1);
	//img = imread("Tamamo.bmp", 1);
	img = imread("5010661i.jpg", 1);
	//img = imread("rectangle_large_efbc1ff6c2d8e50618e00a4837099a7a.jpg.png", 1);
	if (img.empty()) {
		cout << "画像は読み込まれませんでした\nプログラムを終了します" << endl;
		return -1;
	}
	cout << "画像のオープンに成功しました" << endl;
	BmpMem *pBmp = new BmpMem;
	if (pBmp->CreateMapObject() == -1) {
		cout << "共有メモリのオープンに失敗しました" << endl;
		getchar();
		return -1;
	}
	pBmp->OutBmpData(&img);
	cout << "読み込みを開始します" << endl;
	returnImage = pBmp->InBmpData();
	cout << "読み込みが完了しました" << endl;
	//returnImage = pBmp->InBmpData();
	while (true) {
		cv::imshow("imagea", img);
		cv::imshow("image", returnImage);
		waitKey();

		Sleep(100);

		if (_kbhit() == TRUE) {
			break;
		}
	}

	pBmp->CloseMapObject();
	delete pBmp;

	_CrtDumpMemoryLeaks();

    return 0;
}

