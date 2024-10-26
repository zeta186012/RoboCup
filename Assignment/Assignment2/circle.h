/**************************************************
 *  File: circle.h
 *  Description: This header file defines the Circle 
 *               structure used to represent a circle 
 *               in a 2D space, including its center 
 *               coordinates and radius. It also provides 
 *               a member function to check if a given 
 *               point lies within the circle.
 *  
 *  Date: 2024.10.6
********************/

// 防止该头文件被重复包含
#ifndef CIRCLE_H
#define CIRCLE_H

// 包含所需要的头文件
#include "point.h"

// 定义圆
struct Circle
{
    PointVec center; // 圆心
    double radius;   // 半径

    // 此构造函数传入点和半径来构造圆
    Circle(PointVec &&point, double _radius) : center(point), radius(_radius) {};

    // 此构造函数传入横纵坐标和半径来构造圆
    Circle(double _x, double _y, double _radius) : center(PointVec(_x, _y)), radius(_radius) {};

    // 成员函数声明,用于判断点是否在园内
    bool contains(PointVec &point);
};

// 成员函数的定义
bool Circle::contains(PointVec &point)
{
    // 计算点到圆心的距离
    double d = sqrt(pow(point.x - center.x, 2) + pow(point.y - center.y, 2));

    // 判断
    return d <= radius;
}

#endif