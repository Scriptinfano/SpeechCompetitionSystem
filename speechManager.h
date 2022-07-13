#pragma once

#include <iostream>
#include <vector>
#include <map>
#include "speechPlayer.h"
#include <string>
#include <deque>
#include <numeric>
#include <fstream>

const static string fileAddress = "D:\\ClionProjects\\speechCompetitionManageSystem\\winnersData.csv";//文件读写路径

const double maxScore = 100; //规定评委打分的最高分
const double minScore = 0;   //规定评委打分的最低分
using namespace std;

//设计演讲比赛的管理类
class speechManger {
public:
    //成员函数
    speechManger();

    ~speechManger();

    void showMenu();                                 //显示主菜单
    void exitSystem();                               //退出系统
    void initContainer();                            //将内部的容器清空
    void createPlayer();                             //创建出十二个选手
    void showAllPlayers();                           //显示每个选手当前时刻所得的分数
    void startSpeech();                              //开始比赛，控制整个比赛的流程，每个环节使用其他函数执行比赛的具体细节
    void speechLot();                                //比赛流程中的抽签
    void speechContest();                            //执行比赛的具体细节
    void showQualifyingPlayers(vector<int> &v_temp); //显示晋级的选手的具体信息
    void saveRecord();                               //将获胜者的数据保存到文件中
    void loadRecord();                               //将文件中保存的往届比赛的记录读取到内存中的容器里
    void viewPastRecords();                          //查看往届记录
    void addSession() { competitionSession++; }//增加比赛的届数，在比赛结束后调用该接口
    int getCompetitionSession() { return competitionSession; }

    //公有成员变量如下：
    bool fileIsEmpty;//表示文件是否为空

    //成员变量
private:
    int competitionSession;//比赛的届数

    vector<int> v_competitorsRoundOne;           //保存第一轮比赛选手编号的容器
    vector<int> v_competitorsRoundTwo;           //第一轮晋级的选手的编号的容器
    vector<int> v_winners;                       //胜出的前三名选手的编号的容器
    map<int, speechPlayer> m_competitorsIdScore; //存放编号以及对应具体选手的容器
    roundIndexUnion m_roundIndex;                //代表比赛的轮数
    map<int, vector<string>> m_winnersRecorder;  //存放往届胜利者的容器，int代表的是第几届比赛的数据也是map容器的key值，内部的vector<string>容器存放具体的获胜者信息
};