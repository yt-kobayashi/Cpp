//#include "stdafx.h"
#include "pch.h"
#include <string>
#include "SensorData.h"

SensorData::SensorData()
{
	/*
	*	構造体毎のサイズ[byte]の取得
	*/
	DataSize = sizeof(SENSORDATA);
	OculusDataSize = sizeof(OCULUS);
	LeepMotionDataSize = sizeof(LEEPMOTION);
	XYStageDataSize = sizeof(XYSTAGE);

	/*
	*	オフセット値の設定
	*/
	DataOffset = 0;
	OculusOffset = 0;
	LeepMotionOffset = OculusOffset + OculusDataSize;
	XYStageOffset = LeepMotionOffset + LeepMotionDataSize;
	
	/*
	*	SENSORDATA構造体の初期化[0セット]
	*/
	memset(&Data, 0, DataSize);
}

SensorData::~SensorData()
{
}
