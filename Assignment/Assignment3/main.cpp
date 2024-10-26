/**************************************************
 *  File: main.cpp
 *  Description: This file implements the main program logic for reading input data,
 *               parsing it, and using the locate function to determine the position
 *               of an unknown point based on distances and angles from two known points.
 *               The program reads input from standard input, processes each line,
 *               and outputs the calculated coordinates.
 *  
 *  Date: 2024.10.15
***************************************************/

#include "locate.h" // 包含定位函数的头文件
#include "parse.h" // 包含解析字符串的头文件
#include <iostream> // 引入输入输出流
using std::cin; // 使用 std::cin
using std::cout; // 使用 std::cout
using std::endl; // 使用 std::endl

int main() {
    string message; // 存储输入的消息
    string temp_string1, temp_string2; // 分别存储第一个点和第二个点的标识

    // 循环读取标准输入的每一行
    while (std::getline(cin, message)) { // 一次读入一行
        // 创建一个解析对象，并将消息传入。使用 std::move 避免拷贝，提升效率
        Parse parser(std::move(message)); 
        
        // 解析第一个点的标识名称
        temp_string1 = parser.parse_next_symbol(); 
        double fx = parser.parse_next_number(); // 解析第一个点的距离
        double fy = parser.parse_next_number(); // 解析第一个点的极角

        // 创建第一个点的 PointVec 对象
        PointVec f(fx, fy);

        // 解析第二个点的标识名称
        temp_string2 = parser.parse_next_symbol(); 
        double gx = parser.parse_next_number(); // 解析第二个点的距离
        double gy = parser.parse_next_number(); // 解析第二个点的极角

        // 创建第二个点的 PointVec 对象
        PointVec g(gx, gy);

        // 调用 locate 函数计算结果
        PointVec result = locate(f, g, temp_string1, temp_string2); 
        
        // 输出结果，显示计算出的坐标
        cout << "px=" << result.x << ", py=" << result.y << endl; 
    }
    return 0; // 返回 0 表示程序正常结束
}
