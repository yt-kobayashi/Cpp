#pragma once
/*--------------------------------------------------------------------------------------------------
|	概要
|		各機器毎の計測値,出力値を管理するクラス
|	注意
|		各機器にメンバ変数を追加する際には変更は必要ない.
|		構造体自体を追加した際には
|		1:SENSORDATAでの構造体宣言
|		2:構造体のサイズの取得用メンバ変数の追加と,取得処理の追加
|		3:構造体のメモリ上のオフセットメンバ変数の追加と,オフセット設定処理の追加
|		の3つを追加する必要がある.
|		追加しなかった場合はプログラム上で実装すること.
|
|	追加方法
|		1:ADDDATA構造体を追加した場合は"SensorData.h"内のSENSORDATA構造体に追加する.
|			struct SENSORDATA {
|				OCULUS Oculus;
|				LEEPMOTION LeepMotion;
|				XYSTAGE XYStage;
|			--------以下を追記--------
|				ADDDATA AddData;
|			--------------------------
|			};
|		2:構造体のサイズとオフセットの取得用メンバ変数の追加
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
|				-----以下を追加------
|				int AddDataDataSize;
|				int AddDataOffset;
|				---------------------
|			 	SensorData();
|				~SensorData();
|			};
|		構造体サイズ取得処理の追加をする際には"SensorData.cpp"内のSensorData::SensorData()に以下を
|		追記する.
|			AddDataDataSize = sizeof(ADDDATA);
|			AddDataOffset = "ひとつ前の構造体のオフセット" + "ひとつ前の構造体サイズ";
|
--------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------
|	概要
|		Oculus用の構造体
--------------------------------------------------------------------------------------------------*/
struct OCULUS {
	double X;						// 頭部X位置[mm]
	double Y;						// 頭部Y位置[mm]
	double Z;						// 頭部Z位置[mm]
	double Yaw;						// 頭部Yaw角度[deg]
	double Roll;					// 頭部Roll角度[deg]
	double Pitch;					// 頭部Pitch角度[deg]
	double MovePositionX;			// XYステージ移動X目標位置[mm]
	double MovePositionY;			// XYステージ移動Y目標位置[mm]
	long SetMovePowerX;				// XYステージX軸への出力[%]
	long SetMovePowerY;				// XYステージY軸への出力[%]
};

/*--------------------------------------------------------------------------------------------------
|	概要
|		LeepMotion用の構造体	
|
|	注意
|		角度の単位不明
--------------------------------------------------------------------------------------------------*/
struct LEEPMOTION {
	double X;						// 手X位置[mm]
	double Y;						// 手Y位置[mm]
	double Z;						// 手Z位置[mm]
	double Yaw;						// 手Yaw角度
	double Roll;					// 手Roll角度
	double Pitch;					// 手Pitch角度
	long SetMovePowerX;				// XYステージX軸への出力[%]
	long SetMovePowerY;				// XYステージY軸への出力[%]
};

/*--------------------------------------------------------------------------------------------------
|	概要
|		XYステージ用の構造体	
--------------------------------------------------------------------------------------------------*/
struct XYSTAGE {
	double PositionX;				// XYステージX位置[mm] 
	double PositionVoltageX;		// XYステージX位置[V]
	double PositionY;				// XYステージY位置[mm] 
	double PositionVoltageY;		// XYステージY位置[V]
	double MovePositionX;			// XYステージ移動X目標位置[mm]
	double MovePositionVoltageX;	// XYステージ移動X目標位置[V]
	double MovePositionY;			// XYステージ移動Y目標位置[mm]
	double MovePositionVoltageY;	// XYステージ移動Y目標位置[V]
	long SetMovePowerX;				// XYステージX軸への出力[%]
	long SetMovePowerY;				// XYステージY軸への出力[%]
	double OutputVoltageX;			// XYステージX軸への出力電圧[V]
	double OutputVoltageY;			// XYステージY軸への出力電圧[V]
};

/*--------------------------------------------------------------------------------------------------
|	概要
|		各センサデータ用の構造体	
--------------------------------------------------------------------------------------------------*/
struct SENSORDATA {
	OCULUS Oculus;					// Oculusの計測データ
	LEEPMOTION LeepMotion;			// LeepMotionの計測データ
	XYSTAGE XYStage;				// XYステージの計測データ
};

class SensorData
{
public:
	SENSORDATA Data;			// 各センサデータ用の構造体
	int DataSize;				// 各センサデータ用の構造体サイズ
	int DataOffset;				// 各センサデータ用の構造体の先頭からのオフセット
	int OculusDataSize;			// Oculus用の構造体サイズ
	int OculusOffset;			// Oculus用の構造体オフセット
	int LeepMotionDataSize;		// LeepMotion用の構造体サイズ
	int LeepMotionOffset;		// LeepMotion用の構造体オフセット
	int XYStageDataSize;		// XYステージ用の構造体サイズ
	int XYStageOffset;			// XYステージ用の構造体オフセット
 	SensorData();
	~SensorData();
};

