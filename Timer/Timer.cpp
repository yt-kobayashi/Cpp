#include "pch.h"
#include "Timer.h"


Timer::Timer()
{
	//>>>>>>>>>>>>>>>>>>>> 単位取得 <<<<<<<<<<<<<<<<<<<<<//
	if (!QueryPerformanceFrequency(&freq)) {
		return;
	}
	//>>>>>>>>>>>>>>>>>>>> 単位設定 <<<<<<<<<<<<<<<<<<<<<//
	SetUnit("ms");
}
Timer::Timer(std::string unitString)
{
	//>>>>>>>>>>>>>>>>>>>> 単位取得 <<<<<<<<<<<<<<<<<<<<<//
	if (!QueryPerformanceFrequency(&freq)) {
		return;
	}
	//>>>>>>>>>>>>>>>>>>>> 単位設定 <<<<<<<<<<<<<<<<<<<<<//
	SetUnit(unitString);
}


Timer::~Timer()
{
}

void Timer::SetUnit(std::string unitString) {
	//>>>>>>>>>>>>>>>>>>>> 単位係数設定 <<<<<<<<<<<<<<<<<<<<<//
	if (unitString == "ms"){
		unitNum = 1000;
	}
	else if (unitString == "s") {
		unitNum = 1;
	}
	else if (unitString == "min") {
		unitNum = 1 / 60.0;
	}
	else if (unitString == "h") {
		unitNum = 1 / 3600.0;
	}
	//>>>>>>>>>>>>>>>>>>>> 単位設定 <<<<<<<<<<<<<<<<<<<<<//
	unit = unitString;
}

double Timer::StartTimer() {
	// 開始時刻取得
	if (!QueryPerformanceCounter(&start)) {
		return 0.0;
	}

	// 開始時刻の算出と単位の適応
	returnTime = (double)(start.QuadPart * unitNum / freq.QuadPart);
	
	// 時間を返す
	return returnTime;
}

double Timer::EndTimer() {
	// 終了時刻取得
	if (!QueryPerformanceCounter(&end)) {
		return 0.0;
	}

	// 経過時間の算出と単位の適応
	returnTime = (double)(((end.QuadPart - start.QuadPart) * unitNum) / freq.QuadPart);
	
	// 時間を返す
	return returnTime;
}
