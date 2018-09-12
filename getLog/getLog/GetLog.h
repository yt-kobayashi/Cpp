/*==================================================================================================
|
|   概要                :       ログ取得用クラスヘッダ
|   作成者              :       小林由尭
|	作成日時			:		2018/09/12
|
|   使用法
|		1	:	ヘッダファイルとGetLog.cppをプロジェクトに追加する
|
|	連絡先				:		eh15a036@oecu.jp	(小林由尭)
|
==================================================================================================*/
#ifndef GETLOG_H
#define GETLOG_H

#pragma once
#include <string>
/*====================================================================================================
|		GetLogクラスの宣言
+-----------------------------------------------------------------------------------------------------
|		ログファイルの作成,ログファイルの書き込みを行うクラスを宣言する
|
|		_logFileNameに保存されているファイル名に追記という形でログを出力する
|
|		
====================================================================================================*/
class GetLog {
private:
	std::string p_logFileName;										// ログファイル名
	bool p_csvFlag;													// CSV形式出力フラグ
	std::string extensionCSV = ".csv";								// CSV拡張子
	std::string extensionTXT = ".txt";								// txt拡張子
	char timeText[41];												// 時間テキスト
public:
	GetLog(const std::string logFileName, const bool csvFlag);		// ログファイル名, ファイル出力分岐[csv or txt]指定
	GetLog(const std::string logFileName);							// ログファイル名指定
	~GetLog();														// デストラクタ
	bool writeLogFlag;												// 書き込みフラグ

	std::string write(const double value);							// 数値書き込み用
	std::string write(const std::string value);						// テキスト書き込み用
	std::string GetLogFileName();									// ファイル名取得用
};

#endif // GETLOG_H