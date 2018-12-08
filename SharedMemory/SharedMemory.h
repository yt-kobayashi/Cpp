#pragma once
/*==================================================================================================
|
|   概要                :       マップドファイル制御用クラス
|   作成者              :       小林由尭
|   目的                :       マップドファイルの制御をクラスとして提供することで簡単にマップド
|								ファイルを扱えるようにする
|   使用法              :       SharedMemory.cppとSharedMemory.hをプロジェクトに追加して使用する
|
==================================================================================================*/
#include <Windows.h>
#include <string>

class SharedMemory
{
private:
	TCHAR mappedFileName[128];			// マップドファイル名
	int mappedFileSize;					// マップドファイルサイズ
	HANDLE mappedFileHandle;			// マップドファイル用ハンドル
	intptr_t mappedFilePointer;			// マップドファイル用ポインタ
public:
	// コントラクタ
	SharedMemory();
	SharedMemory(const std::string fileName);
	SharedMemory(const int fileSize);
	SharedMemory(const std::string fileName, const int fileSize);
	// デストラクタ
	~SharedMemory();
	// 設定メソッド
	bool SetFileName(const std::string fileName);
	bool SetFileSize(const int fileSize);
	// マップドファイル制御メソッド
	bool CreateMappedFile();
	bool OpenMappedFile();
	bool UnmapMappedFile();
	bool CloseMappedFile();
	// マップドファイル入出力メソッド
	bool ReadMappedFile(void* variablePointer, const int offset, const int dataSize);
	bool WriteMappedFile(void* variablePointer, const int offset, const int dataSize);
	bool WriteFlushMappedFile(void* variablePointer, const int offset, const int dataSize, const bool flush);
	// プライベート変数アクセッサ
	std::string ReadFileName();
	int ReadFileSize();
	HANDLE ReadFileHandle();
	intptr_t ReadFilePointer();
};

