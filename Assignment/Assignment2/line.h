/**************************************************
 *  File: line.h
 *  Description: This header file defines the Line 
 *               structure used to represent a line 
 *               in a 2D space, along with its 
 *               member functions for geometric 
 *               operations.
 *  
 *  Author：计算机23-1郑鑫业 2023217265 
 *  Date: 2024.10.6
********************/

// 防止该头文件被重复包含
#ifndef LINE_H
#define LINE_H

// 定义直线
struct Line
{
    // 系数
    double a;
    double b;
    double c;

    // 构造函数
    Line(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {};

    // 成员函数生明,用于判断两条直线是否相交的成员函数
    bool isCrossed(Line &&line);
};

#endif