/*==================================================================================================
|
|   概要                :       ログ取得用クラス
|   作成者              :       小林由尭
|	作成日時			:		2018/09/10
|   目的                :       各種ログの取得と準備の実装
|   使用法              :       1 : GetLogクラスを宣言する
|									引数
|										- logFileName	:	ログファイル名[自動的に後ろに日時が追加される]
|										- csvFlag		:	CSV出力をするか[true : CSV出力  false : TXT出力]
|										※csvFlagは設定しなくてもよい[TXT出力]
|								2 : writeValueで数値をログ出力する
|									writenValueで数値をログ出力したのちに改行する
|									writeTextで文字列をログ出力する
|									writenTextで文字列をログ出力したのちに改行する
|   注意                :       バグなどの不具合がある可能性あり
|								連絡先	:	eh15a036@oecu.jp	(小林由尭)
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
//#include <windows.h>						// WindowsAPI
//#include <stdio.h>							// 標準入出力関数
//#include <fstream>							// ファイル関係
//#include <string>							// 文字列関係
//#include <time.h>							// 時間
//#include <iostream>
//#include "GetLog.h"
////>>>>>>>>>>>>>>>>>>>> 名前空間の使用 <<<<<<<<<<<<<<<<<<<<<//
//using namespace std;

///*====================================================================================================
//|		GetLogクラスの宣言
//+-----------------------------------------------------------------------------------------------------
//|		ログファイルの作成,ログファイルの書き込みを行うクラスを宣言する
//|
//|		ログファイル名はプライベートとして宣言
//|		makeLogFileを実行した際にsetFileNameを呼ぶことでログファイル名を_logFileNameに格納
//|
//|		_logFileNameに保存されているファイル名に追記という形でログを出力する
//====================================================================================================*/
//class GetLog {
//private:
//	string p_logFileName;										// ログファイル名
//	bool p_csvFlag;												// CSV形式出力フラグ
//public:
//	GetLog(const string logFileName, const bool csvFlag);		// コンストラクタ	オブジェクト生成時に自動で呼ばれる
//	GetLog(const string logFileName);							// コンストラクタ	オブジェクト生成時に自動で呼ばれる
//	~GetLog();													// デストラクタ
//	bool writeLogFlag;											// 書き込みフラグ

//	string write(const double value);							// 数値書き込み用
//	string write(const string value);							// テキスト書き込み用
//	string GetLogFileName();									// ファイル名取得用
//};

///*====================================================================================================
//|		クラスの初期化
//+-----------------------------------------------------------------------------------------------------
//|		指定された名前でログファイルを作成する
//|		logFileName			:	ログファイルの名前
//|		csvFlag				:	CSVファイル出力フラグ[true : CSVファイル出力 false : txtファイル出力]
//|							:	csvFlagは指定せずとも使用可能
//|							:	この場合はtxtファイル出力が行われる
//+-----------------------------------------------------------------------------------------------------
//|		作成したログファイルは以下のように出力される
//|		logFileName = [指定名]yyyymmddhhmmss
//|		またCSVフラグをtrueにすると以下ののように出力される
//|		logFileName = [指定名]yyyymmddhhmmss.csv
//====================================================================================================*/
//inline GetLog::GetLog(const string logFileName, const bool csvFlag) {
//	writeLogFlag = true;			// 書き込みフラグON
//	//>>>>>>>>>>>>>>>>>>>> 変数の宣言 <<<<<<<<<<<<<<<<<<<<<//
//	string extensionCSV = ".csv";	// CSV拡張子
//	string extensionTXT = ".txt";	// txt拡張子
//	char timeText[41];				// 時間テキスト
//	string outPutFileName;			// 出力ファイル名
//	//>>>>>>>>>>>>>>>>>>>> 時間の出力 <<<<<<<<<<<<<<<<<<<<<//
//	time_t t = time(NULL);			// time_t型の変数tを宣言する
//	struct tm tm;					// 時間,日付情報格納用
//									/* 日付時間情報格納 */
//	localtime_s(&tm, &t);
//	/* strftime(出力ファイル名, 出力ファイルの最大サイズ, 出力文字列, 時間日付情報); */
//	strftime(timeText, sizeof(timeText), "%Y%m%d%H%M%S", &tm);
//	string timeString(timeText);	// 時間文字列
//	//>>>>>>>>>>>>>>>>>>>> 時間の連結 <<<<<<<<<<<<<<<<<<<<<//
//	outPutFileName = logFileName + timeString;

//	//>>>>>>>>>>>>>>>>>>>> 拡張子の連結 <<<<<<<<<<<<<<<<<<<<<//
//	if (csvFlag == true) {
//		// CSVファイル出力の場合
//		outPutFileName = outPutFileName + ".csv";
//	}
//	else {
//		// txtファイル出力の場合
//		outPutFileName = outPutFileName + extensionTXT;
//	}

//	p_logFileName = outPutFileName;
//	p_csvFlag = csvFlag;
//};
//inline GetLog::GetLog(const string logFileName){
//	writeLogFlag = true;			// 書き込みフラグON
//									//>>>>>>>>>>>>>>>>>>>> 変数の宣言 <<<<<<<<<<<<<<<<<<<<<//
//	string extensionCSV = ".csv";	// CSV拡張子
//	string extensionTXT = ".txt";	// txt拡張子
//	char timeText[41];				// 時間テキスト
//									//string timeString;				// 時間文字列
//	string outPutFileName;			// 出力ファイル名
//									//>>>>>>>>>>>>>>>>>>>> 時間の出力 <<<<<<<<<<<<<<<<<<<<<//
//	time_t t = time(NULL);			// time_t型の変数tを宣言する
//	struct tm tm;					// 時間,日付情報格納用
//									/* 日付時間情報格納 */
//	localtime_s(&tm, &t);
//	/* strftime(出力ファイル名, 出力ファイルの最大サイズ, 出力文字列, 時間日付情報); */
//	strftime(timeText, sizeof(timeText), "%Y%m%d%H%M%S", &tm);
//	string timeString(timeText);	// 時間文字列
//									//>>>>>>>>>>>>>>>>>>>> 時間の連結 <<<<<<<<<<<<<<<<<<<<<//
//	outPutFileName = logFileName + timeString;

//	//>>>>>>>>>>>>>>>>>>>> 拡張子の連結 <<<<<<<<<<<<<<<<<<<<<//
//	// txtファイル出力の場合
//	outPutFileName = outPutFileName + extensionTXT;

//	p_logFileName = outPutFileName;
//	p_csvFlag = false;
//};
//inline GetLog::~GetLog()
//{
//};

///*====================================================================================================
//|		ログファイルへの書き込み
//+-----------------------------------------------------------------------------------------------------
//|		指定された命令でログファイルに書き込む
//|		write				:	数値書き込み用非改行[成功 : done 失敗 : undone]
//|			double value	:	数値受け取り
//|			string text		:	テキスト受け取り
//|		オーバーライドで文字列と数値を１つのメソッドで扱える
//====================================================================================================*/
//inline string GetLog::write(const double value) {
//	string returnText;
//	if (writeLogFlag != 1) {
//		// 書き込みフラグOFFの処理
//		returnText = "undone";
//	}
//	else {
//		// 書き込みフラグONの処理
//		ofstream outputfile;								// ファイルストリームの使用
//		outputfile.open(p_logFileName, ios::app);			// ログファイルのオープン
//		outputfile << value;								// ログファイルに書き込み
//		//>>>>>>>>>>>>>>>>>>>> CSVファイル出力 <<<<<<<<<<<<<<<<<<<<<//
//		if (p_csvFlag == true) {
//			// 区切りを挿入
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
//		// 書き込みフラグOFFの処理
//		returnText = "undone";
//	}
//	else {
//		// 書き込みフラグONの処理
//		ofstream outputfile;								// ファイルストリームの使用
//		outputfile.open(p_logFileName, ios::app);			// ログファイルのオープン
//		//>>>>>>>>>>>>>>>>>>>> ファイル出力分岐 <<<<<<<<<<<<<<<<<<<<<//
//		// CSVファイル出力ではなく
//		if (value.find(",") != string::npos || p_csvFlag == false || value.rfind("\n") != string::npos ) {
//			writeText = value;
//		}
//		else {
//			writeText = value + ',';
//		}
//		outputfile << writeText;							// ログファイルに書き込み

//		returnText = "done";
//	}

//	return returnText;
//};

///*====================================================================================================
//| ログファイル名を返す
//+-----------------------------------------------------------------------------------------------------
//| 実行されればログファイル名を返す
//====================================================================================================*/
//inline string GetLog::GetLogFileName() {
//	return p_logFileName;
//}

/*====================================================================================================
|		GetLogクラスの使用サンプル例
+-----------------------------------------------------------------------------------------------------
|		GetLogクラスの使用サンプル例として,ループの回数をCSVファイルとして出力する.
====================================================================================================*/
//int main(int argc, char* argv[]) {
//	//>>>>>>>>>>>>>>>>>>>> 変数の宣言 <<<<<<<<<<<<<<<<<<<<<//
//	string logFirstName = "CounterLog";							// ログファイルの名前の先頭部分を設定する
//	string logStat;												// ログを書き込んだ際に書き込みが"成功"か"失敗"かを示す
//	string fileName;											// 日時を追加したファイル名を格納する
//	LARGE_INTEGER freq;											// 時間計測用単位
//	if (!QueryPerformanceFrequency(&freq)) {return 0;}			// 単位の取得
//	LARGE_INTEGER start, end, otw;								// 時間計測の開始時間と終了時間用
//	//>>>>>>>>>>>>>>>>>>>> GetLogクラスの設定 <<<<<<<<<<<<<<<<<<<<<//
//	if (!QueryPerformanceCounter(&start)){
//		printf("時間計測失敗\n");
//	}
//	GetLog getCounterLog(logFirstName, true);					// GetLogクラスでgetCounterLogを作成
//	GetLog getCounterLogText("textLog", false);					// GetLogクラスでgetCounterLogを作成
//	GetLog writeText("maker");									// GetLogクラスでwriteTextを作成
//	if (!QueryPerformanceCounter(&end)){
//		printf("時間計測失敗\n");
//	}
//	logStat = getCounterLog.write("クラス宣言時間");
//	cout << "書き込み : " << logStat << endl;
//	logStat = getCounterLog.write((double)(end.QuadPart - start.QuadPart) / freq.QuadPart);
//	logStat = getCounterLog.write("sec.\n");
//	otw = end;

//	//logStat = getCounterLog.writeText("Test Project\nMaker,YoshitakaKoabyashi\n");
//	logStat = writeText.write("Test Project\nMaker,YoshitakaKoabyashi\n");
//	logStat = writeText.write(2018);
//	//>>>>>>>>>>>>>>>>>>>> ループの開始 <<<<<<<<<<<<<<<<<<<<<//
//	if (!QueryPerformanceCounter(&otw)) {
//		printf("時間計測失敗\n");
//	}
//	for (int counter = 0; counter < 1000; counter++) {
//		//>>>>>>>>>>>>>>>>>>>> ログの出力と状態確認 <<<<<<<<<<<<<<<<<<<<<//
//		//>>>>>>>>>>>>>>>>>>>> CSV出力と状態確認 <<<<<<<<<<<<<<<<<<<<<//
//		logStat = getCounterLog.write("Counter");
//		cout << "書き込み : " << logStat << endl;
//		logStat = getCounterLog.write(counter);
//		cout << "書き込み : " << logStat << endl;
//		logStat = getCounterLog.write("Remaining,");
//		cout << "書き込み : " << logStat << endl;
//		logStat = getCounterLog.write(1000 - counter);
//		cout << "書き込み : " << logStat << endl;
//		//>>>>>>>>>>>>>>>>>>>> TXT出力と状態確認 <<<<<<<<<<<<<<<<<<<<<//
//		logStat = getCounterLogText.write("Counter");
//		cout << "書き込み : " << logStat << endl;
//		logStat = getCounterLogText.write(counter);
//		cout << "書き込み : " << logStat << endl;
//		logStat = getCounterLogText.write("Remaining,");
//		cout << "書き込み : " << logStat << endl;
//		logStat = getCounterLogText.write(1000 - counter);
//		cout << "書き込み : " << logStat << endl;
//		logStat = getCounterLogText.write("\n");
//		cout << "書き込み : " << logStat << endl;

//		//>>>>>>>>>>>>>>>>>>>> 時間計測 <<<<<<<<<<<<<<<<<<<<<//
//		if (!QueryPerformanceCounter(&end)) {
//			printf("時間計測失敗\n");
//		}
//		logStat = getCounterLog.write("1ループ処理時間");
//		cout << "書き込み : " << logStat << endl;
//		logStat = getCounterLog.write((double)(end.QuadPart - otw.QuadPart) / freq.QuadPart);
//		logStat = getCounterLog.write("sec.\n");
//		otw = end;
//	}
//	cout << getCounterLog.GetLogFileName() << "に出力が完了しました." << endl;		// ログファイル名を返す
//	
//	if (!QueryPerformanceCounter(&end)){
//		printf("時間計測失敗\n");
//	}
//	cout << "実行時間 : " << (double)(end.QuadPart - start.QuadPart) / freq.QuadPart << "sec.\n";
//	logStat = getCounterLog.write("実行時間 : ");
//	logStat = getCounterLog.write((double)(end.QuadPart - start.QuadPart) / freq.QuadPart);
//	logStat = getCounterLog.write("sec.\n");
//	cout << "書き込み : " << logStat << endl;

//	getchar();

//	return 0;
//}