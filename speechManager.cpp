//
// Created by USER on 12/07/2022.
//
#include "speechManager.h"

speechManger::speechManger() {
    competitionSession = 0;        //��ʼ�������Ľ���Ϊ0
    this->initContainer();         //���캯���ڲ����ó�Ա������ʼ��
}

speechManger::~speechManger() {}

void speechManger::showMenu() {
    cout << "**********************************" << endl;
    cout << "**********��ӭ�μ��ݽ�����**********" << endl;
    cout << "**********1����ʼ�ݽ�����***********" << endl;
    cout << "**********2���鿴�����¼***********" << endl;
    cout << "**********3����ձ�����¼***********" << endl;
    cout << "**********0���˳���������***********" << endl;
    cout << "**********************************" << endl;
}

void speechManger::exitSystem() {
    system("cls");
    cout << "��ӭ�´�ʹ��" << endl;
    system("pause");
    exit(0);
}

void speechManger::initContainer() {
    //�ĸ�����ȫ���ÿ��Գ�ʼ����һ�������ĳ�ʼ�������ÿ�
    v_competitorsRoundOne.clear();
    v_competitorsRoundTwo.clear();
    v_winners.clear();
    m_competitorsIdScore.clear();
}

void speechManger::createPlayer() {
    string nameSeed = "ABCDEFGHIJKL";
    speechPlayer person;
    for (int i = 0; i < nameSeed.size(); i++) {
        string name = "ѡ��";
        name += nameSeed[i];
        person.setName(name);
        v_competitorsRoundOne.push_back(i + 10001);                               //����Ҫ�����12��ѡ�ֵı�ŷ�������
        m_competitorsIdScore.insert(make_pair(v_competitorsRoundOne[i], person)); //����ŷ����ÿ��ѡ�֣����������map������
    }
}

void speechManger::showAllPlayers() {
    for (auto it: m_competitorsIdScore) {
        cout << "ѡ�ֱ�ţ�" << it.first << " ������" << it.second.getName();
        if (m_roundIndex == roundOne)
            cout << " ��һ�ֱ����÷֣�" << it.second.getScore(m_roundIndex) << endl;
        else
            cout << " ��һ�ֱ����÷֣�" << it.second.getScore(m_roundIndex) << " �ڶ��ֱ����÷�" << it.second.getScore(m_roundIndex)
                 << endl;
    }
}

void speechManger::startSpeech() {

    this->createPlayer();          //����ʮ������

    //��һ�ֱ���
    m_roundIndex = roundOne; //��������Ϊ1

    // 1����ǩ
    this->speechLot();
    // 2������
    this->speechContest();
    // 3����ʾ�������
    this->showQualifyingPlayers(v_competitorsRoundTwo);


    //�ڶ��ֱ���
    m_roundIndex = roundTwo;//�����������л�Ϊ2

    // 1����ǩ
    this->speechLot();

    // 2������
    this->speechContest();

    // 3����ʾ�������
    this->showQualifyingPlayers(v_winners);

    //���������������Ļ�ʤ�ߵ���Ϣ
    this->saveRecord();

    cout << "��������ѽ���" << endl;
    this->addSession();//�������Ľ�����1

    initContainer();//ȷ���ڲ�������ղ�����һ��������Ӱ��

    system("pause");
    system("cls");
}

void speechManger::speechLot() {
    cout << "��" << m_roundIndex << "�ֱ���ѡ�����ڳ�ǩ...\n----------------\n��ǩ���ݽ�˳������" << endl;
    if (m_roundIndex == roundOne) {
        random_shuffle(v_competitorsRoundOne.begin(), v_competitorsRoundOne.end()); //ϴ���㷨����˳��
        for (auto it: v_competitorsRoundOne)
            cout << it << " ";
        cout << endl;
    } else {
        random_shuffle(v_competitorsRoundTwo.begin(), v_competitorsRoundTwo.end());
        for (auto it: v_competitorsRoundTwo)
            cout << it << " ";
        cout << endl;
    }

    cout << "-------------------" << endl;
    system("pause");
    system("cls");
}

void speechManger::showQualifyingPlayers(vector<int> &v_temp) {
    cout << "��" << m_roundIndex << "�ֱ����Ľ������������£�" << endl;
    speechPlayer tempPerson;
    for (auto index: v_temp) {
        tempPerson = m_competitorsIdScore.at(index);
        tempPerson.showScore(m_roundIndex);
    }
}

void speechManger::speechContest() {
    cout << "----------��" << m_roundIndex << "�ֱ�����ʽ��ʼ----------" << endl;
    multimap<double, int, greater<double>> v_groupScore; //һ�����С���ڵ÷��������ʱ������key��ѡ�ֵ�ƽ���֣�value��ѡ�ֵı�ţ���ʹ����greater<double>()��Ϊν��ʹ�����ڲ�ִ���˽�������
    int num = 0;                                         //��¼��Ա����6����Ϊһ��
    vector<int> v_competingPersons;                      //������ڱ�����ѡ�ֵı�ŵ�����
    //��һ�ֱ���ʱ��v1�����е�Ԫ�ذ�������ڶ��ֱ���ʱ��v2�����е�Ԫ�ذ����
    if (m_roundIndex == roundOne)
        v_competingPersons = v_competitorsRoundOne;
    else
        v_competingPersons = v_competitorsRoundTwo;

    deque<double> d_judgesScores;                                                    //������ί��ֵ�����
    map<double, int, greater<double>> m_temporarySortingContainerForPromotedPlayers; //��ʱ�������ѡ�ֵ�����������������Խ���ѡ�ֵķ�������һ�����򣬵�һ�ֱ����Ľ���ѡ����һ���ǰ�����Ͷ����ǰ����

    for (auto it: v_competingPersons) {
        //ÿ��ѭ������ÿ���˵����ֹ���
        num++;
        //��ί���
        for (int i = 0; i < 10; i++) {
            //��ѭ����ʾ10����ί��һ���˴�ֵĹ���
            double score = (rand() % (int) (10 * (maxScore - minScore) + 1 + 10 * minScore)) / 10.2f;
            d_judgesScores.push_back(score);
        }
        sort(d_judgesScores.begin(), d_judgesScores.end(), greater<double>()); //���Ӵ�С��˳������
        d_judgesScores.pop_back();                                             //ȥ����ͷ�
        d_judgesScores.pop_front();                                            //ȥ����߷�
        double sum = accumulate(d_judgesScores.begin(), d_judgesScores.end(),
                                0.0f);                               //����ܷ֣��������������ۼӵĳ�ʼֵ��0.0f��ȷ��ʾ��ʼֵ��С�������ط��ص����;���
        double average = sum / (double) d_judgesScores.size();        //��ȡƽ������Ϊѡ�ֵ����ճɼ�
        m_competitorsIdScore.at(it).setScore(m_roundIndex, average); //��ѡ�ֵĳɼ�д��Ʒְ�
        v_groupScore.insert(make_pair(average, it));                 //��ѡ�ֵĳɼ�����С��÷��У�v_groupScore��map����������ڲ��洢�ķ������н�������

        //��Ϊ�μӵ�һ�ֱ���������12���˺Ͳμӵڶ��ֱ���������6����������num%6��ʱ�������������Բ���Ҫ���ǵڶ����������˵��������������������ε�����

        if (num % 6 == 0) //�ڵ�һ�ֱ����и���6���˻��12����������� ���� �ڵڶ��ֱ����и�������6����������������if����ִ�У���ʾҪ��С��÷ֽ��л��ܣ�ȡ��ǰ����
        {

            //���ݱ����������ֱ�չʾ��һ�ֱ���������С��ĳɼ��͵ڶ��ֱ����������˵ĳɼ�
            if (m_roundIndex == roundOne)
                cout << "��" << num / 6 << "С��ı����������£�" << endl;
            else
                cout << "�ڶ��ֱ����У�6���˵ĳɼ����£�" << endl;

            for (auto it: v_groupScore) {
                cout << "��ţ�" << it.second << " ������" << m_competitorsIdScore[it.second].getName() << " �ɼ���"
                     << m_competitorsIdScore[it.second].getScore(m_roundIndex) << endl;
            }

            //�ó�С�������֮�󣬽�ǰ����ȡ����������ǵ�һ�ֱ�������ȡ���������˷���v_competitorsOfRoundOne�����У�����ǵڶ��ֱ�������ȡ���������˷���v_winners������
            int count = 0; //��ѭ��ȡ��ǰ������ʹ��count���������ﵽ3ʱֹͣѭ����ȡ��v_groupScore��ǰ����Ԫ��
            for (auto it = v_groupScore.begin(); it != v_groupScore.end() && count < 3; it++, count++) {
                if (m_roundIndex == roundOne)                    //��һ�ֱ����н�С���ڵ�ǰ��������v_competitorsRoundTwo������
                    v_competitorsRoundTwo.push_back(it->second); //����һ�غ�������С�������ǰ����������ڶ��ֱ�����������
                else                                             //�����ڵڶ��ֱ���ʱ������ѡ��ǰ���������ʤ�����������
                    v_winners.push_back(it->second);
            }

            /*�ڵ�һ�ֱ����У���һ���ǰ�����͵ڶ����ǰ��������һ������ʱ����Ȼ��һ���ǰ�����͵ڶ����ǰ�������ǰ��Ӵ�С��˳�����еģ����Ƿ���һ��֮��û�а��մӴ�С��˳���������
            �����ڵ�һ�ֱ�����12����ȫ���������֮�󣬶Ա������ѡ�ֱ�ŵ�����v_competitorsRoundTwo����һ�����򣬰�ѡ�ַ����Ӵ�С��˳��Ա�Ž�����������*/
            if (m_roundIndex == roundOne && num == 12) {
                for (auto index: v_competitorsRoundTwo) {
                    m_temporarySortingContainerForPromotedPlayers.insert(
                            make_pair(m_competitorsIdScore.at(index).getScore(m_roundIndex), index));
                }
                v_competitorsRoundTwo.clear(); //���û�жԷ�����������Ľ�����ѡ�ֱ�ŵ�����v_competitorsRoundTwo���Ա㽫�ź����˵�map�����е��������°����
                for (auto pairOfPlayers: m_temporarySortingContainerForPromotedPlayers) {
                    v_competitorsRoundTwo.push_back(pairOfPlayers.second);
                }
            }

            v_groupScore.clear(); // v_groupScoreֻ��һ����ʱ������չʾ��һ��С��ĳɼ�����ɽ�������֮��Ҫ������գ��Ա�洢��һС��ĳɼ�
            m_temporarySortingContainerForPromotedPlayers.clear();
        }

        d_judgesScores.clear(); // d_judgesScores��һ���˵Ĵ�ֽ���������˵�ƽ�����Ѿ���¼�����Լ��ڲ��������У���������ʮ�������������ã�Ӧ������գ�����һ��ѭ���и��µ��˴洢ʮ����ί�ĳɼ�
    }
    cout << "----------��" << m_roundIndex << "�ֱ�������----------" << endl;
    system("pause");
}

void speechManger::saveRecord() {
    ofstream fileOut;
    fileOut.open(fileAddress, ios::out | ios::app);//��׷��д�ķ�ʽ�������Ľ��д���ļ�
    for (auto winnerIndex: v_winners) {
        fileOut << winnerIndex << "," << m_competitorsIdScore.at(winnerIndex).getScore(roundTwo) << ",";
    }
    fileOut << endl;//д��һ������¼���У��Ա��´���д��¼���Ὣ��¼д����һ����¼�ĺ���
    fileOut.close();
    cout << "��¼�ѱ���" << endl;

}

void speechManger::loadRecord() {
    ifstream fileIn(fileAddress, ios::in);
    if (!fileIn.is_open())//��ʧ��
    {
        fileIsEmpty = true;//��ʾ�ļ�Ϊ��
        cout << "�ļ�������" << endl;
        fileIn.close();
        return;
    }
    //�ļ���յ����
    char ch;
    fileIn >> ch;
    if (fileIn.eof())//��ʾ�������ļ�β
    {
        cout << "�ļ�Ϊ��" << endl;
        fileIsEmpty = true;
        fileIn.close();
        return;
    }
    //�ļ���Ϊ�յ����
    fileIsEmpty = false;
    fileIn.putback(ch);//�������ȡ���ַ�������
    string winnersData;
    vector<string> v_winnersData;//v_winnerDataֻ���һ���������Ϣ��ÿ��Ԫ���ǻ�ʤ�ߵı�Ż��߳ɼ�
    competitionSession=0;//

    while (fileIn >> winnersData) {
        //ÿ��ѭ����ȡһ���������Ϣ
        //�ļ��е��������ַ������м���Ӷ��ţ������ŷ������
        int position = -1;//��ʾ�������ַ�����λ��
        int startPosition = 0;//find()�������ҵ���ʼλ��

        //�������ѭ��v_winnerDataֻ���һ���������Ϣ��ÿ��Ԫ���ǻ�ʤ�ߵı�Ż��߳ɼ�
        while (true) {
            //��ѭ����һ���������Ϣ��һ���ַ��������к��ж��ţ��еĶ����޳���Ȼ���Ӵ����� v_winnersData

            position = winnersData.find(",", startPosition);//find���������ַ������ִ�����ʼλ�ã��ڶ��������ǿ�ʼ���ҵ�λ��
            if (position == -1) break;//��δ�ҵ��������˳�ѭ��
            //subWinnerData�ַ�����ѡ�ֵı�Ż��ߵ÷֣���winnersData�����ַ���
            string subWinnerData = winnersData.substr(startPosition,
                                                      position - startPosition);//substr(pos,n);pos�ǿ�ʼλ�ã�n�ǻ�ȡ�ִ��ĳ���
            startPosition = position + 1;
            v_winnersData.push_back(subWinnerData);
        }
        competitionSession++;
        this->m_winnersRecorder.insert(make_pair(competitionSession, v_winnersData));//��������ÿ������ݷ���map�������ڹ���洢
        v_winnersData.clear();
    }
    fileIn.close();
}

void speechManger::viewPastRecords() {
    this->loadRecord();
    cout << "�����������Ϣ���£�" << endl;

    for (auto item: m_winnersRecorder) {
        int i = 0;//vector<string>�������ڲ�����ֵ
        cout << "��" << item.first << "�������" << endl;
        //0 A���� 1 A�ɼ� 2 B���� 3 B�ɼ� 4 C���� 5 C�ɼ�
        cout << "�ھ�--- ������" << item.second.at(i) << " �ɼ���" << item.second.at(i + 1) << endl;
        cout << "�Ǿ�--- ������" << item.second.at(i + 2) << " �ɼ���" << item.second.at(i + 3) << endl;
        cout << "����--- ������" << item.second.at(i + 4) << "�ɼ���" << item.second.at(i + 5) << endl;
        cout << endl;

    }


}