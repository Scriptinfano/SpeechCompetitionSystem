#pragma once

#include <iostream>
#include <vector>
#include <map>
#include "speechPlayer.h"
#include <string>
#include <deque>
#include <numeric>
#include <fstream>

const static string fileAddress = "D:\\ClionProjects\\speechCompetitionManageSystem\\winnersData.csv";//�ļ���д·��

const double maxScore = 100; //�涨��ί��ֵ���߷�
const double minScore = 0;   //�涨��ί��ֵ���ͷ�
using namespace std;

//����ݽ������Ĺ�����
class speechManger {
public:
    //��Ա����
    speechManger();

    ~speechManger();

    void showMenu();                                 //��ʾ���˵�
    void exitSystem();                               //�˳�ϵͳ
    void initContainer();                            //���ڲ����������
    void createPlayer();                             //������ʮ����ѡ��
    void showAllPlayers();                           //��ʾÿ��ѡ�ֵ�ǰʱ�����õķ���
    void startSpeech();                              //��ʼ�����������������������̣�ÿ������ʹ����������ִ�б����ľ���ϸ��
    void speechLot();                                //���������еĳ�ǩ
    void speechContest();                            //ִ�б����ľ���ϸ��
    void showQualifyingPlayers(vector<int> &v_temp); //��ʾ������ѡ�ֵľ�����Ϣ
    void saveRecord();                               //����ʤ�ߵ����ݱ��浽�ļ���
    void loadRecord();                               //���ļ��б������������ļ�¼��ȡ���ڴ��е�������
    void viewPastRecords();                          //�鿴�����¼
    void addSession() { competitionSession++; }//���ӱ����Ľ������ڱ�����������øýӿ�
    int getCompetitionSession() { return competitionSession; }

    //���г�Ա�������£�
    bool fileIsEmpty;//��ʾ�ļ��Ƿ�Ϊ��

    //��Ա����
private:
    int competitionSession;//�����Ľ���

    vector<int> v_competitorsRoundOne;           //�����һ�ֱ���ѡ�ֱ�ŵ�����
    vector<int> v_competitorsRoundTwo;           //��һ�ֽ�����ѡ�ֵı�ŵ�����
    vector<int> v_winners;                       //ʤ����ǰ����ѡ�ֵı�ŵ�����
    map<int, speechPlayer> m_competitorsIdScore; //��ű���Լ���Ӧ����ѡ�ֵ�����
    roundIndexUnion m_roundIndex;                //�������������
    map<int, vector<string>> m_winnersRecorder;  //�������ʤ���ߵ�������int������ǵڼ������������Ҳ��map������keyֵ���ڲ���vector<string>������ž���Ļ�ʤ����Ϣ
};