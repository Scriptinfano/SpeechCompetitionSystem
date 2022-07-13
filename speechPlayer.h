#pragma once

#include <iostream>
#include <string>

using namespace std;
enum roundIndexUnion
{
    roundOne = 1,
    roundTwo
}; //������ʾ�������ε�ö�ٱ�������roundIndexUnion

class speechPlayer
{
private:
    string m_name;
    double *m_score; //��������ֵ÷�
public:
    void operator=(speechPlayer &m_speechPlayer)
    {
        m_name = m_speechPlayer.getName();
        m_score[0] = m_speechPlayer.getScore(roundOne);
        m_score[1] = m_speechPlayer.getScore(roundTwo);
    }

    speechPlayer(string name = "")
    {
        m_name = name;
        m_score = new double[2];
        m_score[0] = 0;
        m_score[1] = 0;
    }

    speechPlayer(const speechPlayer &p) //�����еĹ��캯����ʹ��new��������ڴ�ʱһ��Ҫ�Զ��忽�����캯�������������
    {
        m_name = p.m_name;
        m_score = new double[2];
        m_score[0] = p.m_score[0];
        m_score[1] = p.m_score[1];
    }

    ~speechPlayer() { delete[] m_score; }

    void setName(string name) { m_name = name; }

    void setScore(enum roundIndexUnion roundIndex, double score)
    {
        if (roundIndex == roundOne)
            m_score[0] = score;
        else if (roundIndex == roundTwo)
            m_score[1] = score;
        else
        {
            cerr << "setScore()�������ݴ����˳�����" << endl;
            exit(0);
        }
    }

    void setScoreOne(double scoreOne)
    {
        m_score[0] = scoreOne;
    }

    void setScoreTwo(double scoreTwo)
    {
        m_score[1] = scoreTwo;
    }

    void setAll(string name, double scoreOne, double scoreTwo)
    {
        m_name = name;
        m_score[0] = scoreOne;
        m_score[1] = scoreTwo;
    }

    string getName() { return m_name; }

    void showScore(enum roundIndexUnion roundIndex)
    {
        if (roundIndex == roundOne)
            cout << m_name << "ѡ�ֵĵ�һ�ֱ����ĵ÷�:" << m_score[0] << endl;
        else
            cout << m_name << "ѡ�ֵ����ֵ÷ֱַ�Ϊ:" << m_score[0] << " " << m_score[1] << endl;
    }

    double getScore(enum roundIndexUnion roundIndex) //��������Ҫ������һ�ֱ����ķ���
    {
        if (roundIndex == roundOne)
            return m_score[0];
        else if (roundIndex == roundTwo)
            return m_score[1];
        else
            return -1.0;
    }
};