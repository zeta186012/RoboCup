/**************************************************
 *  File: pointvec.h
 *  Description: This file defines a struct PointVec that is used to store points in a 2D plane.
 *               The struct can represent points in Cartesian coordinates (x, y).
 *               It includes a constructor for initializing PointVec objects.
 *  
 *  Date: 2024.10.15
***************************************************/

// 防止该头文件被重复包含
#ifndef POINTVEC_H
#define POINTVEC_H

#include <ostream> // 引入输出流库，用于输出 PointVec 对象

// 定义一个存储点的结构体 PointVec，可以表示直角坐标或极坐标
struct PointVec {
    double x; // x 坐标
    double y; // y 坐标

    // 构造函数，用于初始化 PointVec 对象的 x 和 y 坐标
    PointVec(double _x, double _y) : x(_x), y(_y) { };
};

// 可以在这里添加重载输出运算符（如有需要）

#endif // 结束头文件保护
