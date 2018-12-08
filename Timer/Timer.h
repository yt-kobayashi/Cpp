#pragma once
/*==================================================================================================
|
|   概要                :       時間計測制御用クラス
|   作成者              :       小林由尭
|   目的                :       時間計測の制御をクラスとして提供することで簡単に時間計測を扱えるよう
|								にする
|   使用法              :       Timer.cppとTimer.hをプロジェクトに追加して使用する
|
==================================================================================================*/
#include <Windows.h>
#include <string>

class Timer
{
private:
	double unitNum;								// 単位係数
	std::string unit;							// 単位設定 ミリ秒:ms 秒:s 分:min 時間:h
	LARGE_INTEGER freq, start, end;				// 周波数,開始時間,終了時間
	double returnTime;							// 返す為の一時変数
public:
	// コントラクタ
	Timer();
	Timer(std::string unitString);
	// デストラクタ
	~Timer();
	// 単位設定
	void SetUnit(std::string unitString);
	// タイマー関係
	double StartTimer();
	double EndTimer();
};

