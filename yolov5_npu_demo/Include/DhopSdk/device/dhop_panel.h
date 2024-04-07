/*******************************************************************************
 * panel.h
 *
 * Copyright (C) 2015-2030 ZheJiang Dahua Technology CO.,LTD.
 *
 * Description: 控制面板操作
 *
 *******************************************************************************/

#ifndef __DHOP_DEVICE_PANEL_H__
#define __DHOP_DEVICE_PANEL_H__

#ifdef __cplusplus
extern "C"{
#endif

/*******************************************************************************/


#include "dhop_type_def.h"

typedef enum
{
    DHOP_DEVICE_PANEL_ALARM_OUT_LOW = 0,    //低电平
    DHOP_DEVICE_PANEL_ALARM_OUT_HIGH,       //高电平
} DHOP_PANEL_AlarmOut_Mode;                 //alarmOut模式

typedef enum
{
    DHOP_DEVICE_PANEL_LIGHT_OFF = 0,        //关灯
    DHOP_DEVICE_PANEL_LIGHT_ON,             //开灯
} DHOP_PANEL_Light_Mode;                    //light模式

typedef enum
{
    DHOP_DEVICE_PANEL_ALARM_IN_LOW = 0,     //低电平
    DHOP_DEVICE_PANEL_ALARM_IN_HIGH,        //高电平
    DHOP_DEVICE_PANEL_ALARM_IN_SHORT_CIRCUIT,//短路
    DHOP_DEVICE_PANEL_ALARM_IN_OPEN_CIRCUIT //断路
} DHOP_PANEL_AlarmIn_Mode;                  //报警输入模式，根据GBT31070.2-2018要求，需支持4态报警

typedef enum
{
    DHOP_DEVICE_PANEL_ANTI_DISMANTLE_ALARM_PRESSED = 0, //防拆按键按下
    DHOP_DEVICE_PANEL_ANTI_DISMANTLE_ALARM_RELEASED,    //防拆按键弹起
} DHOP_PANEL_AntiDismantle_Alarm_Mode;                  //防拆报警模式

typedef enum
{
    DHOP_DEVICE_PANEL_PROXIMITY_ALARM_NEARBY = 0,   //有物体靠近
    DHOP_DEVICE_PANEL_PROXIMITY_ALARM_FARAWAY,      //物体离开
} DHOP_PANEL_Proximity_Alarm_Mode;                  //靠近感应报警

typedef enum
{
    DHOP_DEVICE_PANEL_BTN_PRESSED = 0,      //按键按下
    DHOP_DEVICE_PANEL_BTN_RELEASED,         //按键弹起
} DHOP_PANEL_Btn_Mode;                      //按键模式

typedef enum
{
    DHOP_DEVICE_PANEL_CMD_ALARM_IN_REGISTER_CB = 0x0,              //注册alarmin回调
    DHOP_DEVICE_PANEL_CMD_ALARM_IN_GET_MODE,                       //获取alarmin当前mode
    DHOP_DEVICE_PANEL_CMD_ALARM_IN_GET_VOLTAGE,                    //获取alarmin引脚电压值
    DHOP_DEVICE_PANEL_CMD_ANTI_DISMANTLE_ALARM_REGISTER_CB = 0x10, //注册防拆回调
    DHOP_DEVICE_PANEL_CMD_GET_ANTI_DISMANTLE_ALARM_STATUS,         //获取防拆报警状态
    DHOP_DEVICE_PANEL_CMD_PROXIMITY_ALARM_REGISTER_CB = 0x20,      //注册接近感应回调
    DHOP_DEVICE_PANEL_CMD_GET_PROXIMITY_ALARM_STATUS,              //获取接近感应报警状态
    DHOP_DEVICE_PANEL_CMD_BUTTON_REGISTER_CB = 0x30,               //注册按键回调
    DHOP_DEVICE_PANEL_CMD_ALARM_OUT_SET = 0x40,                    //设置alarmout模式
    DHOP_DEVICE_PANEL_CMD_LIGHT_SET = 0x50,                        //设置灯模式
    DHOP_DEVICE_PANEL_CMD_MAX
} DHOP_PANEL_CmdType;                                       //面板外设命令类型


/*******************************************************************************/

#if (__SIZEOF_POINTER__ == 4)                       // 32位系统下结构体定义
typedef struct
{
    DH_Uint32           alarmInIndex;               //alarmin的编号
    DH_Uint32           mode;                       //alarmin模式，参见DHOP_PANEL_AlarmIn_Mode
    DH_Void*            pPriv;                      //用户自定义数据
    DH_Uint32           reserved[5];
} DHOP_PANEL_AlarmInCbParam;                        //alarmIn回调参数

typedef struct
{
    DH_Uint32           AlarmIndex;                 //防拆按键编号
    DH_Uint32           mode;                       //模式，参见DHOP_PANEL_AntiDismantle_Alarm_Mode
    DH_Void*            pPriv;                      //用户自定义数据
    DH_Uint32           reserved[5];
} DHOP_PANEL_AntiDismantleAlarmCbParam;             //防拆回调参数

typedef struct
{
    DH_Uint32           sensorIndex;                //传感器编号
    DH_Uint32           mode;                       //模式，参见DHOP_PANEL_Proximity_Alarm_Mode
    DH_Void*            pPriv;                      //用户自定义数据
    DH_Uint32           reserved[5];
} DHOP_PANEL_ProximityCbParam;                      //接近感应回调参数

typedef struct
{
    DH_Uint32           btnIndex;                   //按键编号
    DH_Uint32           mode;                       //按键模式，参见DHOP_PANEL_Btn_Mode
    DH_Void*            pPriv;                      //用户自定义数据
    DH_Uint32           reserved[5];
} DHOP_PANEL_BtnCbParam;                            //按键回调参数

typedef struct
{
    union
    {
        // alarmin回调函数指针,对应DHOP_DEVICE_PANEL_CMD_ALARM_IN_REGISTER_CB的参数，选择此命令，调用者必填
        struct
        {
            DH_Void     (*alarmInCb)(DHOP_PANEL_AlarmInCbParam *param);
            //用户自定义数据，回调时原样返回
            DH_Void*    pPriv;
        } alarmInEvt;

        //alarmin模式，取值参见DHOP_PANEL_AlarmIn_Mode，对应DHOP_DEVICE_PANEL_CMD_ALARM_IN_GET_MODE的参数，选择此命令，调用者无需填写，接口内部赋值
        DH_Uint32       alarmInMode;

        //alarmin引脚电压，单位为mV，例如3.3v对应值3300，对应DHOP_DEVICE_PANEL_CMD_ALARM_IN_GET_VOLTAGE的参数，选择此命令，调用者无需填写，接口内部赋值
        DH_Uint32       alarmInVoltage;

        //防拆回调函数指针,对应DHOP_DEVICE_PANEL_CMD_ANTI_DISMANTLE_ALARM_REGISTER_CB的参数
        struct
        {
            DH_Void     (*antiDismantleAlarmCb)(DHOP_PANEL_AntiDismantleAlarmCbParam *param);
            //用户自定义数据，回调时原样返回
            DH_Void*    pPriv;
        } antiDismantleAlarmEvt;

        //防拆报警状态，对应DHOP_DEVICE_PANEL_CMD_GET_ANTI_DISMANTLE_ALARM_STATUS的参数，取值范围参见DHOP_PANEL_AntiDismantle_Alarm_Mode，
        DH_Uint32 antiDismantleAlarmStatus;

        //接近感应回调函数指针,对应DHOP_DEVICE_PANEL_CMD_PROXIMITY_ALARM_REGISTER_CB的参数
        struct
        {
            DH_Void     (*proximityAlarmCb)(DHOP_PANEL_ProximityCbParam *param);
            //用户自定义数据，回调时原样返回
            DH_Void*    pPriv;
        } proximityAlarmEvt;

        //接近报警状态，对应DHOP_DEVICE_PANEL_CMD_GET_PROXIMITY_ALARM_STATUS命令，取值范围参见DHOP_PANEL_Proximity_Alarm_Mode
        DH_Uint32 proximityAlarmStatus;

        //按键回调函数指针，对应DHOP_DEVICE_PANEL_CMD_BUTTON_REGISTER_CB的参数
        struct
        {
            DH_Void     (*btnCb)(DHOP_PANEL_BtnCbParam *param);
            //用户自定义数据，回调时原样返回
            DH_Void*    pPriv;
        } btnEvt;

        //alarmout模式，取值参见DHOP_PANEL_AlarmOut_Mode，对应DHOP_DEVICE_PANEL_CMD_ALARM_OUT_SET的参数，选择此命令，调用者必填
        DH_Uint32       alarmOutMode;   
        
        //灯模式，取值参见DHOP_PANEL_Light_Mode，对应DHOP_DEVICE_PANEL_CMD_LIGHT_SET的参数
        DH_Uint32       lightMode;

        DH_Uint32       res[8];
    } param;

    DH_Uint32 reserved[8];
} DHOP_PANEL_CmdArgs;       //面板外设命令参数
#endif

#if (__SIZEOF_POINTER__ == 8)                       // 64位系统下结构体定义
typedef struct
{
    DH_Uint32           alarmInIndex;               //alarmin的编号
    DH_Uint32           mode;                       //alarmin模式，参见DHOP_PANEL_AlarmIn_Mode
    DH_Void*            pPriv;                      //用户自定义数据
    DH_Uint32           reserved[4];
} DHOP_PANEL_AlarmInCbParam;                        //alarmIn回调参数

typedef struct
{
    DH_Uint32           AlarmIndex;                 //防拆按键编号
    DH_Uint32           mode;                       //模式，参见DHOP_PANEL_AntiDismantle_Alarm_Mode
    DH_Void*            pPriv;                      //用户自定义数据
    DH_Uint32           reserved[4];
} DHOP_PANEL_AntiDismantleAlarmCbParam;             //防拆回调参数

typedef struct
{
    DH_Uint32           sensorIndex;                //传感器编号
    DH_Uint32           mode;                       //模式，参见DHOP_PANEL_Proximity_Alarm_Mode
    DH_Void*            pPriv;                      //用户自定义数据
    DH_Uint32           reserved[4];
} DHOP_PANEL_ProximityCbParam;                      //接近感应回调参数

typedef struct
{
    DH_Uint32           btnIndex;                   //按键编号
    DH_Uint32           mode;                       //按键模式，参见DHOP_PANEL_Btn_Mode
    DH_Void*            pPriv;                      //用户自定义数据
    DH_Uint32           reserved[4];
} DHOP_PANEL_BtnCbParam;                            //按键回调参数

typedef struct
{
    union
    {
        // alarmin回调函数指针,对应DHOP_DEVICE_PANEL_CMD_ALARM_IN_REGISTER_CB的参数，选择此命令，调用者必填
        struct
        {
            DH_Void     (*alarmInCb)(DHOP_PANEL_AlarmInCbParam *param);
            //用户自定义数据，回调时原样返回
            DH_Void*    pPriv;
        } alarmInEvt;

        //alarmin模式，取值参见DHOP_PANEL_AlarmIn_Mode，对应DHOP_DEVICE_PANEL_CMD_ALARM_IN_GET_MODE的参数，选择此命令，调用者无需填写，接口内部赋值
        DH_Uint32       alarmInMode;

        //alarmin引脚电压，单位为mV，例如3.3v对应值3300，对应DHOP_DEVICE_PANEL_CMD_ALARM_IN_GET_VOLTAGE的参数，选择此命令，调用者无需填写，接口内部赋值
        DH_Uint32       alarmInVoltage;

        //防拆回调函数指针,对应DHOP_DEVICE_PANEL_CMD_ANTI_DISMANTLE_ALARM_REGISTER_CB的参数
        struct
        {
            DH_Void     (*antiDismantleAlarmCb)(DHOP_PANEL_AntiDismantleAlarmCbParam *param);
            //用户自定义数据，回调时原样返回
            DH_Void*    pPriv;
        } antiDismantleAlarmEvt;

        //防拆报警状态，对应DHOP_DEVICE_PANEL_CMD_GET_ANTI_DISMANTLE_ALARM_STATUS的参数，取值范围参见DHOP_PANEL_AntiDismantle_Alarm_Mode，
        DH_Uint32 antiDismantleAlarmStatus;

        //接近感应回调函数指针,对应DHOP_DEVICE_PANEL_CMD_PROXIMITY_ALARM_REGISTER_CB的参数
        struct
        {
            DH_Void     (*proximityAlarmCb)(DHOP_PANEL_ProximityCbParam *param);
            //用户自定义数据，回调时原样返回
            DH_Void*    pPriv;
        } proximityAlarmEvt;

        //接近报警状态，对应DHOP_DEVICE_PANEL_CMD_GET_PROXIMITY_ALARM_STATUS命令，取值范围参见DHOP_PANEL_Proximity_Alarm_Mode
        DH_Uint32 proximityAlarmStatus;

        //按键回调函数指针，对应DHOP_DEVICE_PANEL_CMD_BUTTON_REGISTER_CB的参数
        struct
        {
            DH_Void     (*btnCb)(DHOP_PANEL_BtnCbParam *param);
            //用户自定义数据，回调时原样返回
            DH_Void*    pPriv;
        } btnEvt;

        //alarmout模式，取值参见DHOP_PANEL_AlarmOut_Mode，对应DHOP_DEVICE_PANEL_CMD_ALARM_OUT_SET的参数，选择此命令，调用者必填
        DH_Uint32       alarmOutMode;   

        //灯模式，取值参见DHOP_PANEL_Light_Mode，对应DHOP_DEVICE_PANEL_CMD_LIGHT_SET的参数
        DH_Uint32       lightMode;

        DH_Uint32       res[8];
    } param;

    DH_Uint32 reserved[8];
} DHOP_PANEL_CmdArgs;       //面板外设命令参数
#endif

/*******************************************************************************/


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif // __DHOP_DEVICE_PANEL_H__


