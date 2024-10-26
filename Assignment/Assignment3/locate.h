/**************************************************
 *  File: locate.h
 *  Description: This file defines a function to calculate the position of an unknown point
 *               based on its distances and angles from two known points. It includes a static
 *               unordered map to store the coordinates of specific points and a function to
 *               perform the calculation.
 *  
 *  Date: 2024.10.15
***************************************************/

// 防止该头文件被重复包含
#ifndef LOCATE_H
#define LOCATE_H

#include "PointVec.h" // 包含自定义的 PointVec 头文件
#include <unordered_map> // 用于存储点集的无序映射
#include <string> // 用于使用字符串类型
#include <cmath> // 用于数学计算（比如 sqrt）

using std::string;

// 定义一个静态，无序的映射，存储特定点的坐标
const static std::unordered_map<string, PointVec> point_set{ 
    {"C", PointVec(0.0, 0.0)},    // 中心点 C
    {"P1", PointVec(-52.5, -32.0)}, // 点 P1 的坐标
    {"P2", PointVec(-52.5, 32.0)}, // 点 P2 的坐标
    {"P3", PointVec(52.5, 32.0)},  // 点 P3 的坐标
    {"P4", PointVec(52.5, -32.0)}, // 点 P4 的坐标
    {"P5", PointVec(0.0, -32.0)},  // 点 P5 的坐标
    {"P6", PointVec(0.0, 32.0)},   // 点 P6 的坐标
    {"P7", PointVec(-30.0, -7.0)}, // 点 P7 的坐标
    {"P8", PointVec(-30.0, 7.0)},  // 点 P8 的坐标
    {"P9", PointVec(30.0, 7.0)},   // 点 P9 的坐标
    {"P10", PointVec(30.0, -7.0)}, // 点 P10 的坐标
    {"G1", PointVec(-52.5, 0.0)},  // 点 G1 的坐标
    {"G2", PointVec(52.5, 0.0)},   // 点 G2 的坐标
};

// 定义一个定位函数，根据传入的点和名称计算位置
PointVec locate(PointVec f, PointVec g, const string &s1, const string &s2) {
    // 从 point_set 中获取指定点的坐标
    PointVec p1 = point_set.find(s1)->second; // 获取第一个点的坐标
    PointVec p2 = point_set.find(s2)->second; // 获取第二个点的坐标

    // 计算点 p1 和 p2 之间的差值和距离
    double delta_x = p2.x - p1.x; // x 坐标差值
    double delta_y = p2.y - p1.y; // y 坐标差值
    double d = sqrt(delta_x * delta_x + delta_y * delta_y); // 计算两点间的距离

    // 利用公式计算未知点的中间值
    double a = (f.x * f.x - g.x * g.x + d * d) / (2.0 * d); // 中间变量 a
    double h = sqrt(f.x * f.x - a * a); // 中间变量 h

    // 计算符号（用于决定 h 的方向）
    int sign = g.y - f.y > 0 ? 1 : -1;

    // 计算方向的余弦和正弦值
    double cos_x = delta_x / d; // x 方向的余弦
    double sin_x = delta_y / d; // y 方向的正弦

    // 根据 p1 点以及 a 值计算临时点
    PointVec temp(p1.x + a * cos_x, p1.y + a * sin_x);
    
    // 根据临时点和 h 值计算最终结果坐标
    PointVec result(temp.x - h * sign * sin_x, temp.y + h * sign * cos_x);
    
    return result; // 返回计算结果
}

#endif // 结束头文件保护
