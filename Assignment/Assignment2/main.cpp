/**************************************************
 *  File: main.cpp
 *  Description: This file contains the main function
 *               which demonstrates the usage of
 *               geometric operations on lines, circles,
 *               and rectangles. It calculates the
 *               intersection points of different
 *               shapes and checks if certain points
 *               are contained within a circle or
 *               rectangle.
 *
 *  Date: 2024.10.6
 ********************/

// 包含所需要的一些库和头文件
#include "cross.cpp"
#include <iostream>
#include <iomanip>

// 使用标准命名空间中的cin和cout
using std::cout;
using std::endl;

// 主函数
int main()
{
     // 定义两条直线
     // y = -1
     // x = -1
     Line l1(0.0, 1.0, 1.0);
     Line l2(1.0, 0.0, 1.0);

     // 定义一个圆
     Circle c1(PointVec(0.0, 0.0), 2.0);
     // 定义一个矩形
     Rectangle r1(PointVec(-3.0, 2.0), PointVec(3.0, -2.0));

     // 定义两个点
     PointVec p1(0.0, 0.0);
     PointVec p2(10.0, 10.0);

     // 定义两个结果容器
     vector<vector<double>> result1;
     vector<double> result2;

     // 求两条直线的交点
     result2 = cross(l1, l2);
     cout << "-------------------------------------" << endl;
     cout << "直线l1(0.0,1.0,1.0)与l2(1.0,0.0,1.0)的交点为:("
          << result2[0] << "," << result2[1] << ")" << endl;
     cout << "-------------------------------------" << endl;

     // 计算直线和圆的交点
     result1 = cross(l1, c1);
     cout << "直线l1与圆c1(0.0,0.0,2.0)的交点为:("
          << result1[0][0] << "," << result1[0][1] << ")和("
          << result1[1][0] << "," << result1[1][1] << ")" << endl;
     cout << "-------------------------------------" << endl;

     // 计算直线和举行的交点
     result1 = cross(l1, r1);
     cout << "直线l1与矩形r1(-3.0,2.0,3.0,-2.0)的交点为:("
          << result1[0][0] << "," << result1[0][1] << ")和("
          << result1[1][0] << "," << result1[1][1] << ")" << endl;
     cout << "-------------------------------------" << endl;

     // 使用std中的boolalpha
     cout << std::boolalpha

          // 判断p1这个点是否在圆中
          << "p1(0.0,0.0)是否在圆c1(0.0,0.0,2.0)中:" << c1.contains(p1) << endl
          << "-------------------------------------" << endl

          // 判断p2这个点是否在圆中
          << "p2(10.0,10.0)是否在圆c1中:" << c1.contains(p2) << endl
          << "-------------------------------------" << endl

          // 判断p1这个点否在矩形中
          << "p1是否在矩形r1(-3.0,2.0,3.0,-2.0)中:" << r1.contains(p1) << endl
          << "-------------------------------------" << endl

          // 判断p2这个点否在矩形中
          << "p2是否在矩形r1中:" << r1.contains(p2) << endl
          << "-------------------------------------" << endl;
     return 0;
}
