/*==================================================================================================
|
|   概要                :       GetLogクラス用メソッド
|   作成者              :       小林由尭
|	作成日時			:		2018/09/12
|   目的                :       GetLogクラスのメソッドを宣言する
|
|   メソッド説明		:		宣言時に実行
|								GetLog(const string logFileName, const bool csvFlag)
|									引数
|										- logFileName	:	ログファイル名[自動的に後ろに日時が追加される]
|										- csvFlag		:	CSV出力をするか[true : CSV出力  false : TXT出力]
|										※csvFlagは設定しなくてもよい[TXT出力]
|						:		ファイル出力
|								write(const double value)
|									引数
|										- value			:	出力する数値
|									戻り値
|										- done			:	書き込み完了
|										- false			:	書き込み未完了
|								write(const string value)
|									引数
|										- value			:	出力する文字列
|									戻り値
|										- done			:	書き込み完了
|										- false			:	書き込み未完了
|						:		出力ファイル名の取得
|								getLogFileName()
|									戻り値
|										- string型で出力ファイル名を返す
|
|   注意                :       バグなどの不具合がある可能性あり
|	連絡先				:		eh15a036@oecu.jp	(小林由尭)
|
==================================================================================================*/
#include "stdafx.h"
#include <stdio.h>							// 標準入出力関数
#include <fstream>							// ファイル関係
#include <string>							// 文字列関係
#include <time.h>							// 時間
#include <iostream>							// コンソール標準入出力
#include "GetLog.h"							// クラスヘッダ
using namespace std;

/*====================================================================================================
|		クラスの初期化
+-----------------------------------------------------------------------------------------------------
|		指定された名前でログファイルを作成する
|		logFileName			:	ログファイルの名前
|		csvFlag				:	CSVファイル出力フラグ[true : CSVファイル出力 false : txtファイル出力]
|							:	csvFlagは指定せずとも使用可能
|							:	この場合はtxtファイル出力が行われる
+-----------------------------------------------------------------------------------------------------
|		作成したログファイルは以下のように出力される
|		logFileName = [指定名]yyyymmddhhmmss
|		またCSVフラグをtrueにすると以下ののように出力される
|		logFileName = [指定名]yyyymmddhhmmss.csv
====================================================================================================*/
GetLog::GetLog(const string logFileName, const bool csvFlag) {
	//>>>>>>>>>>>>>>>>>>>> 変数の宣言 <<<<<<<<<<<<<<<<<<<<<//
	writeLogFlag = true;			// 書き込みフラグON
	//>>>>>>>>>>>>>>>>>>>> 時間の出力 <<<<<<<<<<<<<<<<<<<<<//
	time_t t = time(NULL);			// time_t型の変数tを宣言する
	struct tm tm;					// 時間,日付情報格納用
	/* 日付時間情報格納 */
	localtime_s(&tm, &t);
	/* strftime(出力ファイル名, 出力ファイルの最大サイズ, 出力文字列, 時間日付情報); */
	strftime(timeText, sizeof(timeText), "%Y%m%d%H%M%S", &tm);
	string timeString(timeText);	// 時間文字列
	//>>>>>>>>>>>>>>>>>>>> 時間の連結 <<<<<<<<<<<<<<<<<<<<<//
	p_logFileName = logFileName + timeString;

	//>>>>>>>>>>>>>>>>>>>> 拡張子の連結 <<<<<<<<<<<<<<<<<<<<<//
	if (csvFlag == true) {
		// CSVファイル出力の場合
		p_logFileName = p_logFileName + extensionCSV;
	}
	else {
		// txtファイル出力の場合
		p_logFileName = p_logFileName + extensionTXT;
	}

	p_csvFlag = csvFlag;
};
GetLog::GetLog(const string logFileName){
	//>>>>>>>>>>>>>>>>>>>> 変数の宣言 <<<<<<<<<<<<<<<<<<<<<//
	writeLogFlag = true;			// 書き込みフラグON
	//>>>>>>>>>>>>>>>>>>>> 時間の出力 <<<<<<<<<<<<<<<<<<<<<//
	time_t t = time(NULL);			// time_t型の変数tを宣言する
	struct tm tm;					// 時間,日付情報格納用
	/* 日付時間情報格納 */
	localtime_s(&tm, &t);
	/* strftime(出力ファイル名, 出力ファイルの最大サイズ, 出力文字列, 時間日付情報); */
	strftime(timeText, sizeof(timeText), "%Y%m%d%H%M%S", &tm);
	string timeString(timeText);	// 時間文字列
	//>>>>>>>>>>>>>>>>>>>> 時間の連結 <<<<<<<<<<<<<<<<<<<<<//
	p_logFileName = logFileName + timeString + extensionTXT;

	p_csvFlag = false;
};
GetLog::~GetLog()
{
};

/*====================================================================================================
|		ログファイルへの書き込み
+-----------------------------------------------------------------------------------------------------
|		指定された命令でログファイルに書き込む
|		write				:	数値書き込み用非改行[成功 : done 失敗 : undone]
|			double value	:	数値受け取り
|			string text		:	テキスト受け取り
|		オーバーライドで文字列と数値を１つのメソッドで扱える
====================================================================================================*/
string GetLog::write(const double value) {
	string returnText;						// 戻り値
	if (writeLogFlag != 1) {
		// 書き込みフラグOFFの処理
		returnText = "undone";
	}
	else {
		// 書き込みフラグONの処理
		ofstream outputfile;								// ファイルストリームの使用
		outputfile.open(p_logFileName, ios::app);			// ログファイルのオープン
		outputfile << value;								// ログファイルに書き込み
		//>>>>>>>>>>>>>>>>>>>> CSVファイル出力 <<<<<<<<<<<<<<<<<<<<<//
		if (p_csvFlag == true) {
			// 区切りを挿入
			outputfile << ",";
		}
		returnText = "done";
	}

	return returnText;
};
string GetLog::write(const string value) {
	string returnText;						// 戻り値
	string writeText;						// 書き込み文字列
	if (writeLogFlag != 1) {
		// 書き込みフラグOFFの処理
		returnText = "undone";
	}
	else {
		// 書き込みフラグONの処理
		ofstream outputfile;								// ファイルストリームの使用
		outputfile.open(p_logFileName, ios::app);			// ログファイルのオープン
		//>>>>>>>>>>>>>>>>>>>> ファイル出力分岐 <<<<<<<<<<<<<<<<<<<<<//
		// "','がないか" "TXT出力であるか" "'\n'が存在するか" で実行
		if (value.find(",") != string::npos || p_csvFlag == false || value.rfind("\n") != string::npos ) {
			writeText = value;
		}
		else {
			writeText = value + ',';
		}
		outputfile << writeText;							// ログファイルに書き込み

		returnText = "done";
	}

	return returnText;
};

/*====================================================================================================
| ログファイル名を返す
+-----------------------------------------------------------------------------------------------------
| 実行されればログファイル名を返す
====================================================================================================*/
string GetLog::GetLogFileName() {
	return p_logFileName;
}
