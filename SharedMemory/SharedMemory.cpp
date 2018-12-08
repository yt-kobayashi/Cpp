//#include "stdafx.h"
#include "pch.h"
#include <Windows.h>
#include <string>
#include <atlstr.h>
#include <tchar.h>
#include "SharedMemory.h"

using namespace std;

/***************************************************
*	コントラクタ
*	オーバーロード 4
*	オブジェクトを宣言した時点で実行される
***************************************************/
//>>>>>>>>>>>>>>>>>>>> デフォルト <<<<<<<<<<<<<<<<<<<<<//
SharedMemory::SharedMemory()
{
	SetFileName("sharedMemory");
	SetFileSize(1024);
}
//>>>>>>>>>>>>>>>>>>>> ファイル名指定 <<<<<<<<<<<<<<<<<<<<<//
SharedMemory::SharedMemory(const string fileName)
{
	SetFileName(fileName);
	SetFileSize(1024);
}
//>>>>>>>>>>>>>>>>>>>> ファイルサイズ指定 <<<<<<<<<<<<<<<<<<<<<//
SharedMemory::SharedMemory(const int fileSize)
{
	SetFileName("DefaultName");
	SetFileSize(fileSize);
}
//>>>>>>>>>>>>>>>>>>>> ファイル名,サイズ指定 <<<<<<<<<<<<<<<<<<<<<//
SharedMemory::SharedMemory(const string fileName, const int fileSize)
{
	SetFileName(fileName);
	SetFileSize(fileSize);
}

/***************************************************
*	デストラクタ
***************************************************/
SharedMemory::~SharedMemory()
{
}

/***************************************************
*	メンバメソッド
***************************************************/
//>>>>>>>>>>>>>>>>>>>> ファイル名の指定 <<<<<<<<<<<<<<<<<<<<<//
bool SharedMemory::SetFileName(const string fileName) {
	bool state;		// 成功・失敗判定

	// ファイル名の長さチェック
	if (128 < fileName.length()) {
		// 長さ超過
		printf_s("マップドファイル名が長すぎます\n");
		printf_s("マップドファイル名は128文字以内で宣言してください\n");
		// 失敗判定
		state = false;
	}
	else {
		// 長さ適合
		// ファイル名をNULL埋め
		memset(mappedFileName, NULL, 128);
		// CString型にString型を返還
		CString tempString = fileName.c_str();
		// TCHAR型にファイル名をコピー
		_tcscpy_s(mappedFileName, tempString);
		// 成功判定
		state = true;
	}

	// 判定を返す
	return state;
}
//>>>>>>>>>>>>>>>>>>>> ファイルサイズの指定 <<<<<<<<<<<<<<<<<<<<<//
bool SharedMemory::SetFileSize(const int fileSize) {
	bool state;		// 成功・失敗判定

	// ファイルサイズのチェック
	if (2000000000 < fileSize) {
		// サイズ超過
		printf_s("マップドファイルサイズが大きすぎます\n");
		printf_s("マップドファイルサイズを2GB以下で宣言してください\n");
		// 失敗判定
		state = false;
	}
	else {
		// サイズ適合
		mappedFileSize = fileSize;
		// 成功判定
		state = true;
	}

	// 判定を返す
	return state;
}
//>>>>>>>>>>>>>>>>>>>> マップドファイルの作成 <<<<<<<<<<<<<<<<<<<<<//
bool SharedMemory::CreateMappedFile() {
	// 作成メソッドの実行のアナウンス
	printf_s("Run at Create MappedFile\n");
	bool state;		// 成功・失敗判定

	// マップドファイルの作成
	mappedFileHandle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, mappedFileSize, mappedFileName);
	// マップドファイルの作成の成功・失敗判定
	// 失敗時にはハンドルにNULLが返る
	if (mappedFileHandle == NULL) {
		// 失敗時
		printf_s("Create MappedFile : Fail|失敗\n");
		// 失敗判定
		state = false;
	}
	else {
		// 成功時
		// 成功アナウンス
		printf_s("Create MappedFile : Success|成功\n");
		// マップドファイルのビューの取得(メモリアドレスの設定)
		mappedFilePointer = (intptr_t)MapViewOfFile(mappedFileHandle, FILE_MAP_ALL_ACCESS, 0, 0, mappedFileSize);
		// ビューの取得の成功・失敗判定
		// 失敗時にはNULLポインタが返る(ヌルポ・ッガ！)
		if (mappedFilePointer == NULL) {
			// 失敗時
			// 失敗アナウンス
			printf_s("Get Pointer for MappedFile : Fail|失敗\n");
			// 失敗判定
			state = false;
		}
		else {
			// 成功時
			// 成功アナウンス
			printf_s("Get Pointer for MappedFile : Success|成功\n");
			// 成功判定
			state = true;
		}
	}

	// 判定を返す
	return state;
}
//>>>>>>>>>>>>>>>>>>>> マップドファイルのオープン <<<<<<<<<<<<<<<<<<<<<//
bool SharedMemory::OpenMappedFile() {
	// オープンメソッドの実行のアナウンス
	printf_s("Run at Open MappedFile\n");
	bool state;		// 成功・失敗判定

	// マップドファイルのオープン
	mappedFileHandle = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, mappedFileName);
	// マップドファイルのオープンの成功・失敗判定
	// 失敗時にはハンドルにNULLが返る
	if (mappedFileHandle == NULL) {
		// 失敗時
		printf_s("Open MappedFile : Fail|失敗\n");
		// 失敗判定
		state = false;
	}
	else {
		// 成功時
		// 成功アナウンス
		printf_s("Open MappedFile : Success|成功\n");
		// マップドファイルのビューの取得(メモリアドレスの設定)
		mappedFilePointer = (intptr_t)MapViewOfFile(mappedFileHandle, FILE_MAP_ALL_ACCESS, 0, 0, mappedFileSize);
		// ビューの取得の成功・失敗判定
		// 失敗時にはNULLポインタが返る(ヌルポ・ッガ！)
		if (mappedFilePointer == NULL) {
			// 失敗時
			// 失敗アナウンス
			printf_s("Get Pointer for MappedFile : Fail|失敗\n");
			// 失敗判定
			state = false;
		}
		else {
			// 成功時
			// 成功アナウンス
			printf_s("Get Pointer for MappedFile : Success|成功\n");
			// 成功判定
			state = true;
		}
	}

	// 判定を返す
	return state;
}
//>>>>>>>>>>>>>>>>>>>> マップドファイルのビューのアンマップ <<<<<<<<<<<<<<<<<<<<<//
bool SharedMemory::UnmapMappedFile() {
	// アンマップメソッドのアナウンス
	printf_s("Run at Unmap MappedFile\n");
	bool state;		// 成功・失敗判定

	// マップドファイルのビューのチェック
	if (mappedFilePointer == NULL) {
		// 失敗時(ビューの取得をしていない)
		// 失敗アナウンス
		printf_s("Get Pointer for MappedFile : Fail|失敗\n");
		// 失敗判定
		state = false;
	}
	else {
		// 成功時
		// 成功アナウンス
		printf_s("Get Pointer for MappedFile : Success|成功\n");
		// ビューのアンマップの成功・失敗判定
		if (!UnmapViewOfFile((LPCVOID)mappedFilePointer)) {
			// 失敗時
			// 失敗アナウンス
			printf_s("Unmap View of File : Fail|失敗\n");
			// 失敗判定
			state = false;
		}
		else {
			// 成功時
			// 成功アナウンス
			printf_s("Unmap View of File : Success|成功\n");
			// 成功判定
			state = true;
		}
	}

	// 判定を返す
	return state;
}
//>>>>>>>>>>>>>>>>>>>> マップドファイルの終了 <<<<<<<<<<<<<<<<<<<<<//
bool SharedMemory::CloseMappedFile() {
	bool state;		// 成功・失敗判定
	// 終了メソッドのアナウンス
	printf_s("Run at CloseMappedFile\n");
	// ハンドルを閉じる
	CloseHandle(mappedFileHandle);
	// 成功判定
	state = true;
	// 判定を返す
	return state;
}
//>>>>>>>>>>>>>>>>>>>> マップドファイルからデータの読み取り <<<<<<<<<<<<<<<<<<<<<//
bool SharedMemory::ReadMappedFile(void* variablePointer, const int offset, const int dataSize) {
	bool state;		// 成功・失敗判定

	// マップドファイルのチェック
	if (mappedFileHandle == NULL || mappedFilePointer == NULL) {
		// 失敗時
		// 失敗アナウンス
		printf_s("共有メモリを作成するか,オープンしてください\n");
		// 失敗判定
		state = false;
	}
	else {
		// 成功時
		// オーバーアクセスのチェック
		if (mappedFileSize < offset + dataSize) {
			// 失敗時
			// 失敗アナウンス
			printf_s("読み込み先がマップドファイルのサイズをオーバーしています\n");
			printf_s("オーバーしない範囲で読み込みを行ってください\n");
			// 失敗判定
			state = false;
		}
		else {
			// 成功時
			// マップドファイルからデータを読み取る
			CopyMemory(variablePointer, (PVOID)(mappedFilePointer + offset), dataSize);
			// 成功判定
			state = true;
		}
	}

	// 判定を返す
	return state;
}
//>>>>>>>>>>>>>>>>>>>> マップドファイルからデータの書き込み <<<<<<<<<<<<<<<<<<<<<//
bool SharedMemory::WriteMappedFile(void* variablePointer, const int offset, const int dataSize) {
	bool state;		// 成功・失敗判定

	// マップドファイルのチェック
	if (mappedFileHandle == NULL || mappedFilePointer == NULL) {
		// 失敗時
		// 失敗アナウンス
		printf_s("共有メモリを作成するか,オープンしてください\n");
		// 失敗判定
		state = false;
	}
	else {
		// 成功時
		// オーバーアクセスのチェック
		if (mappedFileSize < offset + dataSize) {
			// 失敗時
			// 失敗アナウンス
			printf_s("書き込み先がマップドファイルのサイズをオーバーしています\n");
			printf_s("オーバーしない範囲で書き込みを行ってください\n");
			// 失敗判定
			state = false;
		}
		else {
			// 成功時
			// マップドファイルへデータを出力する
			CopyMemory((PVOID)(mappedFilePointer + offset), variablePointer, dataSize);
			// 成功判定
			state = true;
		}
	}

	// 判定を返す
	return state;
}
//>>>>>>>>>>>>>>>>>>>> マップドファイルからデータの即時書き込み <<<<<<<<<<<<<<<<<<<<<//
bool SharedMemory::WriteFlushMappedFile(void* variablePointer, const int offset, const int dataSize, const bool flush) {
	bool state;		// 成功・失敗判定

	// 書き込みの成功・失敗判定
	if (!WriteMappedFile(variablePointer, offset, dataSize)) {
		// 失敗時
		// 失敗判定
		state = false;
	}
	else {
		// 成功時
		// 即時書き込み
		if (!flush) {
			// 失敗時
			// 失敗判定
			state = false;
		}
		else {
			// 成功時
			// 即時書き込み
			if (!FlushViewOfFile((LPCVOID)mappedFilePointer, mappedFileSize)) {
				// 失敗判定
				state = false;
			}
			else {
				// 成功判定
				state = true;
			}
		}
	}

	// 判定を返す
	return state;
}
//>>>>>>>>>>>>>>>>>>>> マップドファイル名を返す <<<<<<<<<<<<<<<<<<<<<//
string SharedMemory::ReadFileName(){
	// マップドファイル名をTCHARからCStringAに変換する
	CStringA tempString = mappedFileName;
	// CStringAからstringに変換する
	string fileName = tempString.GetBuffer(0);
	// ファイル名を返す
	return fileName;
}
//>>>>>>>>>>>>>>>>>>>> マップドファイルサイズを返す <<<<<<<<<<<<<<<<<<<<<//
int SharedMemory::ReadFileSize(){
	return mappedFileSize;
}
//>>>>>>>>>>>>>>>>>>>> マップドファイルハンドルを返す <<<<<<<<<<<<<<<<<<<<<//
HANDLE SharedMemory::ReadFileHandle(){
	return mappedFileHandle;
}
//>>>>>>>>>>>>>>>>>>>> マップドファイルのビューを返す <<<<<<<<<<<<<<<<<<<<<//
intptr_t SharedMemory::ReadFilePointer(){
	return mappedFilePointer;
}