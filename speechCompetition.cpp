/*演讲比赛管理系统
 * 一、比赛规则：
 * 1、12个人参加，比赛有2轮，第一轮为淘汰赛，第二轮为决赛
 * 2、每个选手有对应的编号
 * 3、比赛方式为分组比赛，每组6个人
 * 4、第一轮分为两个小组，整体按照选手编号进行抽签后顺序演讲
 * 5、十个评委分别给每个选手打分，去除最高分和最低分，求的平均分为本轮选手的成绩
 * 6、当小组演讲完之后，淘汰组内排名最后的三个选手，前三名晋级，进入下一轮比赛
 * 7、第二轮为决赛，前三名胜出
 * 8、每轮比赛过后需要显示晋级选手的信息
 *
 * 二、程序功能
 * 1、开始演讲比赛：完成整届比赛的流程，每个比赛阶段需要给用户一个提示，用户按任意键后开始下一个阶段
 * 2、查看往届记录：查看之前比赛的前三名结果，每次比赛都会记录到文件中，文件用.csv后缀名保存
 * 3、清空比赛记录：将文件中的数据清空
 * 4、退出比赛程序：可退出当前程序
 * */
#include "speechManager.h"
#include <cstdlib>
#include <ctime>

int main() {
    //初始化随机数发生器
    srand((unsigned int) time(NULL));
    //设置cout输出小数的格式
    cout.setf(ios::fixed);
    cout.precision(2);

    //初始化管理器对象
    speechManger manager;
    // manager.showAllPlayers();//此为测试代码
    while (true) {
        manager.showMenu();
        cout << "输入您的选择：";
        int choice = 0;
        cin >> choice;
        switch (choice) {
            case 1: //开始比赛
                manager.startSpeech();
                break;
            case 2: //查看记录
                manager.viewPastRecords();
                break;
            case 3: //清空记录
                break;
            case 0: //退出系统
                manager.exitSystem();
                break;
            default: {
                cout << "请输入1，2，3，0中的任意一个数字完成选择操作" << endl;
                system("pause");
                system("cls");
                break;
            }
        }
    }
}