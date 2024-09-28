// Name:initializeInfo.h

// 防止该头文件被重复使用
#pragma once

// 包含使用到的一些标准库
#include "librarys.h"

/**
 * 初始化信息数组
 *
 * 将信息数组的每个元素设置为NULL字符
 *
 * @param info 信息数组，用于存储字符信息
 */
void initializeInfo(char info[])
{
    for (int i = 0; info[i] != 0; i++)
        info[i] = '\0';
}