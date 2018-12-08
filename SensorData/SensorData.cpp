//#include "stdafx.h"
#include "pch.h"
#include <string>
#include "SensorData.h"

SensorData::SensorData()
{
	/*
	*	�\���̖��̃T�C�Y[byte]�̎擾
	*/
	DataSize = sizeof(SENSORDATA);
	OculusDataSize = sizeof(OCULUS);
	LeepMotionDataSize = sizeof(LEEPMOTION);
	XYStageDataSize = sizeof(XYSTAGE);

	/*
	*	�I�t�Z�b�g�l�̐ݒ�
	*/
	DataOffset = 0;
	OculusOffset = 0;
	LeepMotionOffset = OculusOffset + OculusDataSize;
	XYStageOffset = LeepMotionOffset + LeepMotionDataSize;
	
	/*
	*	SENSORDATA�\���̂̏�����[0�Z�b�g]
	*/
	memset(&Data, 0, DataSize);
}

SensorData::~SensorData()
{
}
