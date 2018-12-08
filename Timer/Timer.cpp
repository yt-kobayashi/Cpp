#include "pch.h"
#include "Timer.h"


Timer::Timer()
{
	//>>>>>>>>>>>>>>>>>>>> �P�ʎ擾 <<<<<<<<<<<<<<<<<<<<<//
	if (!QueryPerformanceFrequency(&freq)) {
		return;
	}
	//>>>>>>>>>>>>>>>>>>>> �P�ʐݒ� <<<<<<<<<<<<<<<<<<<<<//
	SetUnit("ms");
}
Timer::Timer(std::string unitString)
{
	//>>>>>>>>>>>>>>>>>>>> �P�ʎ擾 <<<<<<<<<<<<<<<<<<<<<//
	if (!QueryPerformanceFrequency(&freq)) {
		return;
	}
	//>>>>>>>>>>>>>>>>>>>> �P�ʐݒ� <<<<<<<<<<<<<<<<<<<<<//
	SetUnit(unitString);
}


Timer::~Timer()
{
}

void Timer::SetUnit(std::string unitString) {
	//>>>>>>>>>>>>>>>>>>>> �P�ʌW���ݒ� <<<<<<<<<<<<<<<<<<<<<//
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
	//>>>>>>>>>>>>>>>>>>>> �P�ʐݒ� <<<<<<<<<<<<<<<<<<<<<//
	unit = unitString;
}

double Timer::StartTimer() {
	// �J�n�����擾
	if (!QueryPerformanceCounter(&start)) {
		return 0.0;
	}

	// �J�n�����̎Z�o�ƒP�ʂ̓K��
	returnTime = (double)(start.QuadPart * unitNum / freq.QuadPart);
	
	// ���Ԃ�Ԃ�
	return returnTime;
}

double Timer::EndTimer() {
	// �I�������擾
	if (!QueryPerformanceCounter(&end)) {
		return 0.0;
	}

	// �o�ߎ��Ԃ̎Z�o�ƒP�ʂ̓K��
	returnTime = (double)(((end.QuadPart - start.QuadPart) * unitNum) / freq.QuadPart);
	
	// ���Ԃ�Ԃ�
	return returnTime;
}
