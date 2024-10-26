/**************************************************
 *  File: rectangle.h
 *  Description: This header file defines the Rectangle 
 *               structure used to represent a rectangle 
 *               in 2D space. It includes member functions 
 *               for initializing the rectangle's vertices 
 *               and checking if a point lies within its 
 *               boundaries.
 *  
 *  Date: 2024.10.6
********************/

// 防止该头文件被重复包含
#ifndef RECTANGLE_H
#define RECTANGLE_H

// 包含所需要的头文件
#include "point.h"

// 定义矩形
struct Rectangle
{
    // 左上顶点的位置
    PointVec point1;

    // 右下顶点的位置
    PointVec point2;

    // 此构造函数使用右值引用初始化矩形
    Rectangle(PointVec &&p1, PointVec &&p2) : point1(p1), point2(p2) {};

    // 此构造函数使用坐标初始化矩形
    Rectangle(double _x1, double _y1, double _x2, double _y2) : point1(PointVec(_x1, _y1)), point2(PointVec(_x2, _y2)) {};

    // 成员函数声明,用于判断点是否在矩形内
    bool contains(PointVec &point);
};

// 成员函数定义
bool Rectangle::contains(PointVec &point)
{
    return (point.x >= point1.x && point.x <= point2.x) || (point.y >= point2.y && point.y <= point1.y);
}

#endif