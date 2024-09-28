// Name:SeeInfo.h

// 防止该头文件被重复使用
#pragma once

// 包含使用到的一些标准库
#include "librarys.h"

// 定义 SeeInfo 结构体，用于存储 see 指令的相关信息
typedef struct SeeInfo
{
    char time[5];       // 存储时间信息，格式为 "xxxx"，例如 "1022"
    char obj[30];       // 存储对象信息，例如 "ball"、"player hfut1 2"、"goal r" 或 "Line r"
    char distance[20];  // 存储对象与观察者的距离信息，格式为 "xxxx"，例如 "45"
    char direction[20]; // 存储对象相对于观察者的方向信息，格式为 "xxxx"，例如 "-20"
    char distChng[20];  // 存储对象距离的变化信息，格式为 "xxxx"，例如 "0.5"
    char dirChng[20];   // 存储对象方向的变化信息，格式为 "xxxx"，例如 "1"
    char bodyDir[20];   // 存储对象的身体方向信息，格式为 "xxxx"，例如 "22"
    char headDir[20];   // 存储对象的头部方向信息，格式为 "xxxx"，例如 "40"
    int len;            // 存储 see 信息的长度，即该 see 指令包含的对象数量
} SeeInfo;