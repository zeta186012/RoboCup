// Name:main.cpp

// 包含使用到的一些头文件
#include "librarys.h"
#include "HearInfo.h"
#include "SeeInfo.h"
#include "initializeInfo.h"
#include "printInfo.h"


// 下面是测试时输入的字符串,如果你要测试，请直接复制粘贴下面给定的字符串进行测试，防止编码不同和字符串中中英文标点的差异而导致程序运行出现奇怪的结果
// 示例一：
// (hear 1022 -30 passto(23,24))(see 1022 ((ball) -20 20 1 -2) ((player hfut1 2) 45 23 0.5 1 22 40) ((goal r) 12 20) ((Line r) -30))
// 示例二：
// (see 2022 ((player hfut2 8) 40 23 1 6 21 33 ) ((goal r) 15 30) ((f r t 20) 5 24)) (hear 2022 -10 “pass ball”)
// 示例三：
// (see 2023 ((player hfut2 8) 10 20 1 2 6 8) ((player hfut1 9) 6 7 8 10 20 3) ((f r t 10) 15 20)) (hear 2023 10 “dash”)

int main(int argc, char *argv[])
{
    // 这是一个hear字符串
    char hearStr[4] = {'h', 'e', 'a', 'r'};

    // 这是一个see字符串
    char seeStr[3] = {'s', 'e', 'e'};

    // 这是输入指令的缓冲区
    char info[300];

    // 用于存储解析后的hear信息
    HearInfo hearInfo[300];

    // 用于存储解析后的see信息
    SeeInfo seeInfo[300];
    
        // k变量用于记录当前信息位置
        int k = 0;

        // count变量用于记录每个hear/see指令长度
        int count = 0;

        // 设置flag变量
        // 当flag为1时,为hear指令；当flag为0时，为see指令;当flag为-1时不是指令
        int flag = 1;

        // 设置子指令计数器
        int sc = 1;

        // 初始化缓冲区为空
        initializeInfo(info);

        // 添加分割线和相关提示
        cout << "----------------------------------------" << endl;
        cout << "请输入指令(直接回车结束运行):";

        // 开始从控制台读取指令
        cin.getline(info, 800);

        // 清除输入流的状态
        cin.clear();

        // 遍历输入的字符串
        while (info[k] != '\0')
        {
            // 跳过空格和括号
            if (info[k] == '(' || info[k] == ')' || info[k] == ' ')
            {
                k++;
                continue;
            }
            count = 0;
            // 检查是否为 hear 指令
            for (int k1 = k; info[k1] != ' '; k1++)
            {
                if (hearStr[count] != info[k1])
                {
                    flag = -1; // 不是hear指令
                    break;
                }
                else
                {
                    flag = 1; // 是hear指令
                    count++;
                }
            }

            // 如果不是 hear 指令，则检查是否为 see 指令
            if (flag != 1)
            {
                count = 0;

                for (int k2 = k; info[k2] != ' '; k2++)
                {
                    if (seeStr[count] != info[k2])
                    {
                        flag = -1; // 不是see指令
                        break;
                    }
                    else
                    {
                        flag = 0; // 是see指令
                        count++;
                    }
                }
            }

            // 如果既不是see指令，也不是hear指令，那么就继续处理下一个字符
            if (flag == -1)
            {
                k++;
                continue;
            }

            // 处理hear指令
            if (flag == 1)
            {
                // 跳过“hear”这个字符串
                k = k + 5;

                // 设置 hearInfo[0] 标识此条为第一条 hear 信息
                hearInfo[0].isFirst = true;

                // 解析 hear 指令的时间
                count = 0;
                for (int k3 = k; info[k3] != ' '; k3++)
                {
                    hearInfo[1].time[count] = info[k3];
                    count++;
                }

                // 添加一个字符串结束符
                hearInfo[1].time[count] = '\0';

                // 移动到下一个字符
                k = k + count + 1;

                // 接下来解析hear指令的发令者
                count = 0;

                if (info[k] >= 'a' && info[k] <= 'z')
                {
                    hearInfo[1].isDirection = false;
                    switch (info[k])
                    {
                    // 发令者是self
                    case 's':
                        hearInfo[1].sender = "self";
                        k = k + 5;
                        break;
                    // 发令者是referee
                    case 'r':
                        hearInfo[1].sender = "referee";
                        k = k + 8;
                        break;

                    // 发令者是online_coach
                    case 'o':
                        if (info[k + 13] == 'l')
                        {
                            hearInfo[1].sender = "online_coach_left";
                            k = k + 18;
                        }
                        else
                        {
                            hearInfo[1].sender = "online_coach_right";
                            k = k + 19;
                        }
                        break;

                    default:
                        cout << "指令格式错误!" << endl;
                        break;
                    }
                }

                else
                {
                    hearInfo[1].isDirection = true;
                    for (int k4 = k; info[k4] != ' '; k4++)
                    {
                        hearInfo[1].direction[count] = info[k4];
                        count++;
                    }

                    k = k + count + 1;
                }

                // 解析hear指令的消息部分
                count = 0;
                for (int k5 = k; info[k5] != '(' && info[k5] != ')'; k5++)
                {
                    hearInfo[1].message[count] = info[k5];
                    count++;
                }

                // 判断hear指令的消息中是否含有坐标信息
                if (info[k + count] == '(')
                {
                    for (; info[k + count - 1] != ')';)
                    {
                        hearInfo[1].message[count] = info[k + count];
                        count++;
                    }
                }
                k = k + count + 2;
            }

            count = 0;
            // 处理see指令
            if (flag == 0)
            {
                // 跳过“see”字符串
                k = k + 4;

                // 解析 see 指令的时间信息
                for (int j1 = k; info[j1] != ' '; j1++)
                {
                    seeInfo[1].time[count] = info[j1];
                    count++;
                }

                // 移动到下一个字符
                k = k + count + 1;

                // 解析 see 指令中的对象信息（例如球、球员、球门）
                while (info[k] == '(' && info[k + 1] == '(')
                {
                    count = 0;
                    k = k + 1;
                    for (int j2 = k; info[j2] != ')'; j2++)
                    {
                        seeInfo[sc].obj[count] = info[j2];
                        count++;
                    }

                    seeInfo[sc].obj[count] = ')';
                    k = k + count + 2;

                    // 解析对象的距离、方向等信息
                    count = 0;
                    while (info[k] != ')')
                    {
                        for (; info[k] != ' ' && info[k] != ')'; k++)
                            seeInfo[sc].direction[count++] = info[k]; // 距离
                        count = 0;
                        if (info[k] == ')')
                        {
                            k = k + 2;
                            break;
                        }
                        else
                            k++;
                        for (; info[k] != ' ' && info[k] != ')'; k++)
                            seeInfo[sc].distance[count++] = info[k]; // 方向
                        count = 0;
                        if (info[k] == ')')
                        {
                            k = k + 2;
                            break;
                        }
                        else
                            k++;
                        for (; info[k] != ' ' && info[k] != ')'; k++)
                            seeInfo[sc].distChng[count++] = info[k]; // 距离变化
                        count = 0;
                        if (info[k] == ')')
                        {
                            k = k + 2;
                            break;
                        }
                        else
                            k++;
                        for (; info[k] != ' ' && info[k] != ')'; k++)
                            seeInfo[sc].dirChng[count++] = info[k]; // 方向变化
                        count = 0;
                        if (info[k] == ')')
                        {
                            k = k + 2;
                            break;
                        }
                        else
                            k++;
                        for (; info[k] != ' ' && info[k] != ')'; k++)
                            seeInfo[sc].bodyDir[count++] = info[k]; // 身体方向
                        count = 0;
                        if (info[k] == ')')
                        {
                            k = k + 2;
                            break;
                        }
                        else
                            k++;
                        for (; info[k] != ')'; k++)
                            seeInfo[sc].headDir[count++] = info[k]; // 头部方向
                        count = 0;
                        if (info[k] == ')')
                        {
                            k = k + 2;
                            break;
                        }
                    }
                    // 增加子指令计数器
                    sc++;
                }

                // 设置子指令数量
                seeInfo[0].len = sc - 1;
            }
        }

        // 添加分割线
        cout << "----------------------------------------" << endl;
        // 打印解析的结果
        printInfo(seeInfo, hearInfo);
        cout << "----------------------------------------" << endl;
    

    return 0;
}