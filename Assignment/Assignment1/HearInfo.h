// Name:HearInfo.h

// 防止该头文件被重复使用
#pragma once

// 包含使用到的一些标准库
#include "librarys.h"

// 定义 HearInfo 结构体，用于存储 hear 指令的相关信息
typedef struct HearInfo
{
    char time[5];         // 存储时间信息，格式为 "xxxx"，例如 "1022"
    bool isDirection;     // 标识是否包含方向信息，true 表示包含方向信息，false 表示不包含
    bool isFirst;         // 标识是否为第一条 hear 指令，true 表示是第一条，false 表示不是
    char direction[10];   // 存储方向信息，格式为 "xxx"，例如 "-30"
    string sender;        // 存储发送者信息，例如 "self"、"referee"、"online_coach_left" 或 "online_coach_right"
    char message[MAXLEN]; // 存储消息信息，格式为 "xxxxxxxxx"，例如 "passto(23,24)"
} HearInfo;