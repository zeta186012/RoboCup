// Name:printInfo.h

// 防止该头文件被重复使用
#pragma once

// 包含使用到的一些标准库
#include "librarys.h"

// 包含需要在printInfo函数中要使用到的SeeInfo和HearInfo的信息
#include "HearInfo.h"
#include "SeeInfo.h"

/**
 * 打印see和hear指向的信息
 * @param seeInfo 指向SeeInfo类型的指针，包含看到的信息
 * @param hearInfo 指向HearInfo类型的指针，包含听到的信息
 */
void printInfo(SeeInfo *seeInfo, HearInfo *hearInfo)
{
    // 创建一个文件流对象inFile
    fstream inFile;

    // 打开in.txt文件，并且以输出模式写入
    inFile.open("in.txt", ios::out);

    // 检查hearInfo的第一个元素是否为true，如果是的话，那么直接打印听到的信息
    if (hearInfo[0].isFirst == true)
    {
        // 输出结果到控制台
        cout << "在" << hearInfo[1].time << "周期hear从";

        // 写入结果到文件中
        inFile << "在" << hearInfo[1].time << "周期hear从";

        // 如果听到的信息包含方向，则打印方向
        if (hearInfo[1].isDirection != false)
        {
            // 输出结果到控制台
            cout << hearInfo[1].direction << "方向";

            // 写入结果到文件中
            inFile << hearInfo[1].direction << "方向";
        }
        else
        {
            // 如果听到的信息不包含方向，那么我们打印发送者就可以了

            // 输出结果到控制台
            cout << hearInfo[1].sender << " ";

            // 写入结果到文件中
            inFile << hearInfo[1].sender << " ";
        }

        // 输出结果到控制台
        cout << "听到了" << hearInfo[1].message << ";" << endl;

        // 写入结果到文件中
        inFile << "听到了" << hearInfo[1].message << ";" << endl;
    }

    // 声明循环变量i
    int i;

    // 输出结果到控制台
    cout << "在" << seeInfo[1].time << "周期see ";

    // 写入结果到文件中
    inFile << "在" << seeInfo[1].time << "周期see ";

    // 遍历每个看到的对象信息
    for (i = 1; i <= seeInfo[0].len; i++)
    {
        // 根据对象信息的特定位置字符，决定如何打印对象名称
        if (seeInfo[i].obj[12] == '1' || seeInfo[i].obj[12] == '2')
        {
            // 打印特殊对象的其余部分名称
            for (int q = 1; seeInfo[i].obj[q + 1] != '\0'; q++)
            {
                if (q == 12)
                    continue;
                // 输出结果到控制台
                cout << seeInfo[i].obj[q];

                // 写入结果到文件中
                inFile << seeInfo[i].obj[q];
            }
        }
        else
        {
            // 对于普通对象，直接打印对象名称
            for (int r = 1; seeInfo[i].obj[r + 1] != '\0'; r++)
            {
                // 输出结果到控制台
                cout << seeInfo[i].obj[r];

                // 写入结果到文件中
                inFile << seeInfo[i].obj[r];
            }
        }
        cout << " ";
        // 根据存在信息的情况，选择性地打印距离、方向等信息
        // 依次先输出结果到控制台，然后再把结果写入到文件中
        if (seeInfo[i].direction[0] != '\0')
        {
            if (string(seeInfo[i].obj) == "(Line r)")
            {
                cout << "和我的角度是" << seeInfo[i].direction << "度";
                inFile << "和我的角度是" << seeInfo[i].direction << "度";
            }
            else
            {
                cout << "距离我的Direction是" << seeInfo[i].direction;
                inFile << "距离我的Direction是" << seeInfo[i].direction;
            }

            if (seeInfo[i].distance[0] != '\0')
            {

                cout << ",Distance是" << seeInfo[i].distance;
                inFile << ",Distance是" << seeInfo[i].distance;

                if (seeInfo[i].distChng[0] != '\0')
                {
                    cout << ",DistChng是" << seeInfo[i].distChng;
                    inFile << ",DistChng是" << seeInfo[i].distChng;

                    if (seeInfo[i].dirChng[0] != '\0')
                    {
                        cout << ",DirChng是" << seeInfo[i].dirChng;
                        inFile << ",DirChng是" << seeInfo[i].dirChng;

                        if (seeInfo[i].bodyDir[0] != '\0')
                        {
                            cout << ",它的BodyDir是" << seeInfo[i].bodyDir;
                            inFile << ",它的BodyDir是" << seeInfo[i].bodyDir;

                            if (seeInfo[i].headDir[0] != '\0')
                            {
                                cout << "和HeadDir是" << seeInfo[i].headDir;
                                inFile << "和HeadDir是" << seeInfo[i].headDir;
                            }
                        }
                    }
                }
            }
        }
        cout << ";";
        inFile << ";";
    }
    cout << endl;
    cout << "结束";
    inFile << "结束";
}
