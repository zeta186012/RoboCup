/**************************************************
 *  File: point.h
 *  Description: This header file defines the PointVec 
 *               structure used to represent a point or 
 *               vector in 2D space. It includes member 
 *               functions to initialize the point's 
 *               coordinates and to compute its length 
 *               using the Pythagorean theorem.
 *  
 *  Date: 2024.10.6
********************/

// 防止该头文件被重复包含
#ifndef POINT_H
#define POINT_H

// 包含所需要的库
#include <cmath>

// 定义点坐标,也可以用来表示向量
struct PointVec
{
    double x;
    double y;

    // 构造函数
    PointVec(double _x, double _y) : x(_x), y(_y) {};

    // 成员函数声明,用于计算向量的模
    double get_length();
};

// 成员函数定义
inline double PointVec::get_length()
{
    return sqrt(pow(x, 2) + pow(y, 2));
}

#endif