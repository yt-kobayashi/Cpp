/*--------------------------------------------------------------------------------------------------
|   セクション名        :       LEEPMOTION構造体
|   目的                :       LeepMotionで計測したデータとXYステージに対する出力を扱う
|   メンバ変数          :       構造体の変数についての説明
|                       :       x               :   手の位置X
|                               y               :   手の位置Y
|                               z               :   手の位置Z
|                               setMovePowerX   :   XYステージの"X軸"に対する出力[%]
|                               setMovePowerY   :   YYステージの"Y軸"に対する出力[%]
|                               
--------------------------------------------------------------------------------------------------*/
struct LEEPMOTION{
    double x;
    double y;
    double z;
    double setMovePowerX;
    double setMovePowerY;
}
/*--------------------------------------------------------------------------------------------------
|   セクション名        :       OCULUS構造体
|   目的                :       Oculusで計測したデータとXYステージに対する出力を扱う
|   メンバ変数          :       構造体の変数についての説明
|                       :       x               :   頭の位置X
|                               y               :   頭の位置Y
|                               z               :   頭の位置Z
|                               yaw             :   頭の角度(ヨー角)
|                               roll            :   頭の角度(ロール角)
|                               pitch           :   頭の角度(ピッチ角)
|                               setMovePowerX   :   XYステージの"X軸"に対する出力[%]
|                               setMovePowerY   :   YYステージの"Y軸"に対する出力[%]
|                               
--------------------------------------------------------------------------------------------------*/
struct OCULUS{
    double x;
    double y;
    double z;
    double yaw;
    double roll;
    double pitch;
    double setMovePowerX;
    double setMovePowerY;
}
/*--------------------------------------------------------------------------------------------------
|   セクション名        :       OCULUS構造体
|   目的                :       Oculusで計測したデータとXYステージに対する出力を扱う
|   メンバ変数          :       構造体の変数についての説明
|                       :       setMovePowerX           :   XYステージの"X軸"に対する出力[%]
|                               setMovePowerY           :   YYステージの"Y軸"に対する出力[%]
|                               outMoveVoltageX         :   XYステージの"X軸"への実際の出力電圧[v]
|                               outMoveVoltageY         :   XYステージの"Y軸"への実際の出力電圧[v]
|                               movePositionX           :   XYステージの"X軸"の目標位置[m or mm]
|                               movePositionY           :   XYステージの"Y軸"の目標位置[m or mm]
|                               measurePositionVoltageX :   XYステージの"X軸"の目標位置[v]
|                               measurePositionVoltageY :   XYステージの"Y軸"の目標位置[v]
|                               positionX               :   XYステージの"X軸"の現在位置[m or mm]
|                               positionY               :   XYステージの"Y軸"の現在位置[m or mm]
|                               positionVoltageX        :   XYステージの"X軸"の現在位置[v]
|                               positionVoltageY        :   XYステージの"Y軸"の現在位置[v]
|                               
--------------------------------------------------------------------------------------------------*/
struct XYSTAGE{
    double setMovePowerX;
    double setMovePowerY;
    double movePositionX;
    double movePositionY;
    double outMoveVoltageX;
    double outMoveVoltageY;
    double measurePositionVoltageX;
    double measurePositionVoltageY;
    double positionX;
    double positionY;
    double positionVoltageX;
    double positionVoltageY;
}

/*--------------------------------------------------------------------------------------------------
|   セクション名        :       SENSORDATA構造体
|   目的                :       各種センサで計測したデータを扱う
|   メンバ変数          :       構造体の変数についての説明
|                       :       LEEPMOTION  :   LeepMotionの計測値とXYステージへの出力値
|                               OCULUS      :   Oculusの計測値とXYステージへの出力値
|                               XYSTAGE     :   XYステージの計測値とXYステージヘの出力値
|                               
--------------------------------------------------------------------------------------------------*/
struct SENSORDATA{
    LEEPMOTION leepMotion;
    OCULUS oculus;
    XYSTAGE xyStage;
}
