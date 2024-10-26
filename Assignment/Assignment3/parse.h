/**************************************************
 *  File: parse.h
 *  Description: This file defines a class Parse that is used to parse input strings.
 *               The class provides methods to parse symbols (letters) and numbers from the input.
 *  
 *  Date: 2024.10.15
***************************************************/

// 防止该头文件被重复包含
#ifndef PARSE_H
#define PARSE_H

#include <string> // 引入字符串库
using std::string; // 使用字符串类型

// 定义一个解析输入字符串的类 Parse
class Parse {
private:
    string message; // 存储输入字符串
    string::iterator position; // 用于跟踪当前解析的位置指针

public:
    // 构造函数，接受输入字符串并初始化位置指针
    explicit Parse(string _message) : message(_message), position(message.begin()) { }

    // 解析下一个符号（字母）
    string parse_next_symbol();
    // 解析下一个数字
    double parse_next_number();
};

// 定义解析下一个符号的成员函数
string Parse::parse_next_symbol() {
    string result; // 用于存储解析出的符号结果

    // 跳过所有不是 'C'、'P' 或 'G' 的字符
    while (*position != 'C' && *position != 'P' && *position != 'G') 
        ++position;

    // 继续读取直到遇到空格
    while (*position != ' ' && *position != '\0') { // 注意检查字符串尾部
        result.push_back(*position); // 将当前字符添加到结果字符串
        ++position; // 移动至下一个字符
    }

    return result; // 返回解析出的符号
}

// 定义解析下一个数字的成员函数
double Parse::parse_next_number() {
    string temp_string; // 用于存储解析出的数字字符串

    // 跳过所有不是数字或者负号的字符
    while ((*position < '0' || *position > '9') && *position != '-') 
        ++position;

    // 读取所有数字字符直到遇到空格或右括号 ')'
    while (*position != ' ' && *position != ')' && *position != '\0') {
        temp_string.push_back(*position); // 将当前字符添加到数字字符串
        ++position; // 移动至下一个字符
    }

    return stod(temp_string); // 将字符串转换为 double 并返回
}

#endif // 结束头文件保护
