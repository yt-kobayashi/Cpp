/*==================================================================================================
|
|   概要                :       ログ取得用クラス使用のサンプル例
|   作成者              :       小林由尭
|	作成日時			:		2018/09/10
|   目的                :       ログ取得用クラス使用の使用例を示す
|
|   使用法
|		1	:	[ファイル名指定][CSVファイル出力指定]でgetCounterLogを宣言
|			:	[ファイル名指定][TXTファイル出力指定]でgetCounterLogTextを宣言
|			:	[ファイル名指定]のみでwriteTextを宣言
|		2	:	文章を出力する
|			:	数値を出力する
|		3	:	CSV出力とTXT出力
|			3.1	;	CSV出力
|			3.2	:	TXT出力
|   注意                :       バグなどの不具合がある可能性あり
|	連絡先				:		eh15a036@oecu.jp	(小林由尭)
|
==================================================================================================*/
/*====================================================================================================
|		ヘッダファイルと名前空間の使用
+-----------------------------------------------------------------------------------------------------
|		各ヘッダファイルの宣言を行う
|
|		std名前空間を使用する
====================================================================================================*/
//>>>>>>>>>>>>>>>>>>>> ヘッダファイル <<<<<<<<<<<<<<<<<<<<<//
#include "stdafx.h"
#include <windows.h>						// WindowsAPI
#include <stdio.h>							// 標準入出力関数
#include <fstream>							// ファイル関係
#include <string>							// 文字列関係
#include <time.h>							// 時間
#include <iostream>
#include "GetLog.h"
//>>>>>>>>>>>>>>>>>>>> 名前空間の使用 <<<<<<<<<<<<<<<<<<<<<//
using namespace std;

/*====================================================================================================
|		GetLogクラスの使用サンプル例
+-----------------------------------------------------------------------------------------------------
|		GetLogクラスの使用サンプル例として,ループの回数をCSVファイルとして出力する.
|
|		1	:	[ファイル名指定][CSVファイル出力指定]でgetCounterLogを宣言
|			:	[ファイル名指定][TXTファイル出力指定]でgetCounterLogTextを宣言
|			:	[ファイル名指定]のみでwriteTextを宣言
|		2	:	文章を出力する
|			:	数値を出力する
|		3	:	CSV出力とTXT出力
|			3.1	;	CSV出力
|			3.2	:	TXT出力
====================================================================================================*/
int main(int argc, char* argv[]) {
	//>>>>>>>>>>>>>>>>>>>> 変数の宣言 <<<<<<<<<<<<<<<<<<<<<//
	string logFirstName = "CounterLog";							// ログファイルの名前の先頭部分を設定する
	string logStat;												// ログを書き込んだ際に書き込みが"成功"か"失敗"かを示す
	string fileName;											// 日時を追加したファイル名を格納する
	//>>>>>>>>>>>>>>>>>>>> 1 : GetLogクラスの設定 <<<<<<<<<<<<<<<<<<<<<//
	GetLog getCounterLog(logFirstName, true);					// GetLogクラスでgetCounterLogを作成
	GetLog getCounterLogText("textLog", false);					// GetLogクラスでgetCounterLogを作成
	GetLog writeText("maker");									// GetLogクラスでwriteTextを作成

	//>>>>>>>>>>>>>>>>>>>> 2 : 文章と数値の出力 <<<<<<<<<<<<<<<<<<<<<//
	logStat = writeText.write("Test Project\nMaker,YoshitakaKoabyashi\n");
	logStat = writeText.write(2018);

	//>>>>>>>>>>>>>>>>>>>> 3 : ループの開始 <<<<<<<<<<<<<<<<<<<<<//
	for (int counter = 0; counter < 1000; counter++) {
		//>>>>>>>>>>>>>>>>>>>> 3.1 : CSV出力と状態確認 <<<<<<<<<<<<<<<<<<<<<//
		logStat = getCounterLog.write("Counter");
		cout << "書き込み : " << logStat << endl;
		logStat = getCounterLog.write(counter);
		cout << "書き込み : " << logStat << endl;
		logStat = getCounterLog.write("Remaining,");
		cout << "書き込み : " << logStat << endl;
		logStat = getCounterLog.write(1000 - counter);
		cout << "書き込み : " << logStat << endl;
		logStat = getCounterLog.write("\n");
		cout << "書き込み : " << logStat << endl;
		//>>>>>>>>>>>>>>>>>>>> 3.2 : TXT出力と状態確認 <<<<<<<<<<<<<<<<<<<<<//
		logStat = getCounterLogText.write("Counter");
		cout << "書き込み : " << logStat << endl;
		logStat = getCounterLogText.write(counter);
		cout << "書き込み : " << logStat << endl;
		logStat = getCounterLogText.write("Remaining,");
		cout << "書き込み : " << logStat << endl;
		logStat = getCounterLogText.write(1000 - counter);
		cout << "書き込み : " << logStat << endl;
		logStat = getCounterLogText.write("\n");
		cout << "書き込み : " << logStat << endl;
	}
	cout << getCounterLog.GetLogFileName() << "にCSV出力が完了しました." << endl;			// ログファイル名を返す
	cout << getCounterLogText.GetLogFileName() << "にTXT出力が完了しました." << endl;		// ログファイル名を返す
	cout << writeText.GetLogFileName() << "にTXT出力が完了しました." << endl;				// ログファイル名を返す

	getchar();	// 終了のために入力待ち

	return 0;
}