/**************************************************
 *  File: cross.cpp
 *  Description: This file defines functions to calculate 
 *               the intersection points between different 
 *               geometric shapes, including lines, circles, 
 *               and rectangles. It also handles the logic 
 *               for determining whether shapes intersect 
 *               and where their intersection points lie.
 *  
 *  Author: 计算机23-1郑鑫业 2023217265 
 *  Date: 2024.10.6
********************/

// 包含所需要的一些库和头文件
#include "line.h"
#include "circle.h"
#include "rectangle.h"
#include <vector>

// 一个精度值，用于浮点数的精度的比较i
static const double E = 0.0000001;

// 使用std中的vector
using std::vector;

// 计算两条直线相交
vector<double> cross(Line &line1, Line &line2)
{
    // 定义返回结果
    vector<double> result;

    // 如果两条直线平行或者重合,返回空值
    if (line1.a * line2.b - line1.b * line2.a == 0)
    {
        return result;
    }

    // 用Cram法则求解
    double d = line1.a * line2.b - line1.b * line2.a;
    double dx = line2.b * (-line1.c) - line1.b * (-line2.c);
    double dy = line1.a * (-line2.c) - line2.a * (-line1.c);

    // 存入结果
    result.push_back(dx / d);
    result.push_back(dy / d);

    // 返回结果
    return result;
}

// 计算直线和圆的相交
vector<vector<double>> cross(Line &line, Circle &circle)
{
    // 定义返回结果
    vector<vector<double>> result;

    // 计算圆心到直线的距离
    double distance_to_center = fabs(line.a * circle.center.x + line.b * circle.center.y + line.c) / sqrt(pow(line.a, 2) + pow(line.b, 2));

    // 不相交，返回空vector
    if (distance_to_center > circle.radius)
    {
        return result;
    }

    // 接下来是相交的情况

    // 半个弦的长度
    double half_of_subtense = sqrt(pow(circle.radius, 2) - pow(distance_to_center, 2));

    // 情况1:直线和x轴平行
    if (fabs(line.a) < E && fabs(line.b) > E)
    {
        // 临时存放交点坐标
        vector<double> temp_vector;

        // 计算交点的纵坐标
        double y_pos = -line.c / line.b > circle.center.y
                           ? circle.center.y + distance_to_center
                           : circle.center.y - distance_to_center;

        // 添加第一个交点
        temp_vector.push_back(circle.center.x - half_of_subtense);
        temp_vector.push_back(y_pos);
        result.push_back(temp_vector);

        // 清空，以便放下一个点
        temp_vector.clear();

        // 添加第二个交点
        temp_vector.push_back(circle.center.x + half_of_subtense);
        temp_vector.push_back(y_pos);

        // 返回结果
        result.push_back(temp_vector);
        return result;
    }

    // 情况2:直线平行于y轴
    else if (fabs(line.a) > E && fabs(line.b) < E)
    {
        vector<double> temp_vector;

        // 计算交点的横坐标
        double x_pos = -line.c / line.a > circle.center.x
                           ? circle.center.x + distance_to_center
                           : circle.center.x - distance_to_center;
        // 添加第一个交点
        temp_vector.push_back(x_pos);
        temp_vector.push_back(circle.center.y + half_of_subtense);
        result.push_back(temp_vector);

        // 清空，以便放下一个点
        temp_vector.clear();

        // 添加第二个交点
        temp_vector.push_back(x_pos);
        temp_vector.push_back(circle.center.y - half_of_subtense);

        // 返回结果
        result.push_back(temp_vector);
        return result;
    }
    // 一般情况,直线和x轴y轴均不平行
    else if (fabs(line.a) > E && fabs(line.b) > E)
    {
        vector<double> temp_vector;

        // 存储弦中点的坐标
        vector<double> center_of_subtense;

        // 定义y轴
        Line y_axis(1.0, 0.0, 0.0);
        Line temp_line(-line.b, line.a, line.b * circle.center.x - line.a * circle.center.y);

        // 计算直线和中线的交点
        center_of_subtense = cross(line, temp_line);

        // 计算直线和y轴的交点
        vector<double> intersection_with_y_axis = cross(line, y_axis);

        // 计算交点的单位方向向量
        PointVec intersection_with_y(intersection_with_y_axis[0] - center_of_subtense[0],
                                     intersection_with_y_axis[1] - center_of_subtense[1]);

        double length = intersection_with_y.get_length();

        // 计算直线的方向单位向量
        PointVec unit_vector(intersection_with_y.x / length,
                             intersection_with_y.y / length);

        // 计算并添加两个交点
        temp_vector.push_back(-center_of_subtense[0] - unit_vector.x * half_of_subtense);
        temp_vector.push_back(center_of_subtense[1] + unit_vector.y * half_of_subtense);
        result.push_back(temp_vector);

        temp_vector.clear();

        temp_vector.push_back(-center_of_subtense[0] + unit_vector.x * half_of_subtense);
        temp_vector.push_back(center_of_subtense[1] - unit_vector.y * half_of_subtense);
        result.push_back(temp_vector);

        // 返回结果
        return result;
    }
}

// 计算直线和矩形的相交
vector<vector<double>> cross(Line &line, Rectangle &rectange)
{
    // 定义返回结果
    vector<vector<double>> result;

    // 临时存放交点坐标
    vector<double> temp_vector;

    // 情况1:直线和x轴平行
    if (fabs(line.a) < E && fabs(line.b) > E)
    {
        // 计算交点的纵坐标
        double y_pos = -line.c / line.b;

        // 检查交点是否在矩形边界内
        if (y_pos >= rectange.point1.y || y_pos <= rectange.point2.y)
        {
            return result;
        }

        // 添加交点坐标
        temp_vector.push_back(rectange.point1.x);
        temp_vector.push_back(y_pos);
        result.push_back(temp_vector);

        temp_vector.clear();

        temp_vector.push_back(rectange.point2.x);
        temp_vector.push_back(y_pos);
        result.push_back(temp_vector);

        // 返回结果
        return result;
    }
    // 情况2:直线和y轴平行
    else if (fabs(line.a) > E && fabs(line.b) < E)
    {
        // 计算交点的横坐标
        double x_pos = -line.c / line.a;
        if (x_pos <= rectange.point1.x || x_pos >= rectange.point2.x)
        {
            return result;
        }

        // 添加交点坐标
        temp_vector.push_back(x_pos);
        temp_vector.push_back(rectange.point1.y);
        result.push_back(temp_vector);

        temp_vector.clear();

        temp_vector.push_back(x_pos);
        temp_vector.push_back(rectange.point2.y);
        result.push_back(temp_vector);

        // 返回结果
        return result;
    }
    // 一般情况,直线和x轴y轴均不平行
    else if (fabs(line.a) > E && fabs(line.b) > E)
    {
        // 直线与矩形上边所在直线的交点
        double x1 = (-line.c - line.b * rectange.point1.y) / line.a;

        // 直线与矩形下边所在直线的交点
        double x2 = (-line.c - line.b * rectange.point2.y) / line.a;

        // 直线与矩形左边所在直线的交点
        double y1 = (-line.c - line.a * rectange.point1.x) / line.b;

        // 直线与矩形右边所在直线的交点
        double y2 = (-line.c - line.a * rectange.point2.x) / line.b;

        // 检查交点是否在矩形上边
        if (x1 > rectange.point1.x && x1 < rectange.point2.x)
        {
            temp_vector.push_back(x1);
            temp_vector.push_back(rectange.point1.y);
            result.push_back(temp_vector);
            temp_vector.clear();
        }
        // 检查交点是否在矩形下边
        if (x2 > rectange.point1.x && x2 < rectange.point2.x)
        {
            temp_vector.push_back(x2);
            temp_vector.push_back(rectange.point2.y);
            result.push_back(temp_vector);
            temp_vector.clear();
        }
        // 检查交点是否在矩形左边
        if (y1 > rectange.point2.y && y1 < rectange.point1.y)
        {
            temp_vector.push_back(rectange.point1.x);
            temp_vector.push_back(y1);
            result.push_back(temp_vector);
            temp_vector.clear();
        }
        // 检查交点是否在矩形上边
        if (y2 > rectange.point2.y && y2 < rectange.point1.y)
        {
            temp_vector.push_back(rectange.point2.x);
            temp_vector.push_back(y2);
            result.push_back(temp_vector);
        }
        // 返回结果
        return result;
    }
}
