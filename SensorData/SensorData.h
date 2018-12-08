#pragma once
/*--------------------------------------------------------------------------------------------------
|	�T�v
|		�e�@�했�̌v���l,�o�͒l���Ǘ�����N���X
|	����
|		�e�@��Ƀ����o�ϐ���ǉ�����ۂɂ͕ύX�͕K�v�Ȃ�.
|		�\���̎��̂�ǉ������ۂɂ�
|		1:SENSORDATA�ł̍\���̐錾
|		2:�\���̂̃T�C�Y�̎擾�p�����o�ϐ��̒ǉ���,�擾�����̒ǉ�
|		3:�\���̂̃�������̃I�t�Z�b�g�����o�ϐ��̒ǉ���,�I�t�Z�b�g�ݒ菈���̒ǉ�
|		��3��ǉ�����K�v������.
|		�ǉ����Ȃ������ꍇ�̓v���O������Ŏ������邱��.
|
|	�ǉ����@
|		1:ADDDATA�\���̂�ǉ������ꍇ��"SensorData.h"����SENSORDATA�\���̂ɒǉ�����.
|			struct SENSORDATA {
|				OCULUS Oculus;
|				LEEPMOTION LeepMotion;
|				XYSTAGE XYStage;
|			--------�ȉ���ǋL--------
|				ADDDATA AddData;
|			--------------------------
|			};
|		2:�\���̂̃T�C�Y�ƃI�t�Z�b�g�̎擾�p�����o�ϐ��̒ǉ�
|			class SensorData
|			{
|			public:
|				SENSORDATA Data;
|				int DataSize;
|				int DataOffset;
|				int OculusDataSize;
|				int OculusOffset;
|				int LeepMotionDataSize;
|				int LeepMotionOffset;
|				int XYStageDataSize;
|				int XYStageOffset;
|				-----�ȉ���ǉ�------
|				int AddDataDataSize;
|				int AddDataOffset;
|				---------------------
|			 	SensorData();
|				~SensorData();
|			};
|		�\���̃T�C�Y�擾�����̒ǉ�������ۂɂ�"SensorData.cpp"����SensorData::SensorData()�Ɉȉ���
|		�ǋL����.
|			AddDataDataSize = sizeof(ADDDATA);
|			AddDataOffset = "�ЂƂO�̍\���̂̃I�t�Z�b�g" + "�ЂƂO�̍\���̃T�C�Y";
|
--------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------
|	�T�v
|		Oculus�p�̍\����
--------------------------------------------------------------------------------------------------*/
struct OCULUS {
	double X;						// ����X�ʒu[mm]
	double Y;						// ����Y�ʒu[mm]
	double Z;						// ����Z�ʒu[mm]
	double Yaw;						// ����Yaw�p�x[deg]
	double Roll;					// ����Roll�p�x[deg]
	double Pitch;					// ����Pitch�p�x[deg]
	double MovePositionX;			// XY�X�e�[�W�ړ�X�ڕW�ʒu[mm]
	double MovePositionY;			// XY�X�e�[�W�ړ�Y�ڕW�ʒu[mm]
	long SetMovePowerX;				// XY�X�e�[�WX���ւ̏o��[%]
	long SetMovePowerY;				// XY�X�e�[�WY���ւ̏o��[%]
};

/*--------------------------------------------------------------------------------------------------
|	�T�v
|		LeepMotion�p�̍\����	
|
|	����
|		�p�x�̒P�ʕs��
--------------------------------------------------------------------------------------------------*/
struct LEEPMOTION {
	double X;						// ��X�ʒu[mm]
	double Y;						// ��Y�ʒu[mm]
	double Z;						// ��Z�ʒu[mm]
	double Yaw;						// ��Yaw�p�x
	double Roll;					// ��Roll�p�x
	double Pitch;					// ��Pitch�p�x
	long SetMovePowerX;				// XY�X�e�[�WX���ւ̏o��[%]
	long SetMovePowerY;				// XY�X�e�[�WY���ւ̏o��[%]
};

/*--------------------------------------------------------------------------------------------------
|	�T�v
|		XY�X�e�[�W�p�̍\����	
--------------------------------------------------------------------------------------------------*/
struct XYSTAGE {
	double PositionX;				// XY�X�e�[�WX�ʒu[mm] 
	double PositionVoltageX;		// XY�X�e�[�WX�ʒu[V]
	double PositionY;				// XY�X�e�[�WY�ʒu[mm] 
	double PositionVoltageY;		// XY�X�e�[�WY�ʒu[V]
	double MovePositionX;			// XY�X�e�[�W�ړ�X�ڕW�ʒu[mm]
	double MovePositionVoltageX;	// XY�X�e�[�W�ړ�X�ڕW�ʒu[V]
	double MovePositionY;			// XY�X�e�[�W�ړ�Y�ڕW�ʒu[mm]
	double MovePositionVoltageY;	// XY�X�e�[�W�ړ�Y�ڕW�ʒu[V]
	long SetMovePowerX;				// XY�X�e�[�WX���ւ̏o��[%]
	long SetMovePowerY;				// XY�X�e�[�WY���ւ̏o��[%]
	double OutputVoltageX;			// XY�X�e�[�WX���ւ̏o�͓d��[V]
	double OutputVoltageY;			// XY�X�e�[�WY���ւ̏o�͓d��[V]
};

/*--------------------------------------------------------------------------------------------------
|	�T�v
|		�e�Z���T�f�[�^�p�̍\����	
--------------------------------------------------------------------------------------------------*/
struct SENSORDATA {
	OCULUS Oculus;					// Oculus�̌v���f�[�^
	LEEPMOTION LeepMotion;			// LeepMotion�̌v���f�[�^
	XYSTAGE XYStage;				// XY�X�e�[�W�̌v���f�[�^
};

class SensorData
{
public:
	SENSORDATA Data;			// �e�Z���T�f�[�^�p�̍\����
	int DataSize;				// �e�Z���T�f�[�^�p�̍\���̃T�C�Y
	int DataOffset;				// �e�Z���T�f�[�^�p�̍\���̂̐擪����̃I�t�Z�b�g
	int OculusDataSize;			// Oculus�p�̍\���̃T�C�Y
	int OculusOffset;			// Oculus�p�̍\���̃I�t�Z�b�g
	int LeepMotionDataSize;		// LeepMotion�p�̍\���̃T�C�Y
	int LeepMotionOffset;		// LeepMotion�p�̍\���̃I�t�Z�b�g
	int XYStageDataSize;		// XY�X�e�[�W�p�̍\���̃T�C�Y
	int XYStageOffset;			// XY�X�e�[�W�p�̍\���̃I�t�Z�b�g
 	SensorData();
	~SensorData();
};

