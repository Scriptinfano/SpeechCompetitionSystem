//
// Created by USER on 12/07/2022.
//
#include "speechManager.h"

speechManger::speechManger() {
    competitionSession = 0;        //初始化比赛的届数为0
    this->initContainer();         //构造函数内部调用成员函数初始化
}

speechManger::~speechManger() {}

void speechManger::showMenu() {
    cout << "**********************************" << endl;
    cout << "**********欢迎参加演讲比赛**********" << endl;
    cout << "**********1、开始演讲比赛***********" << endl;
    cout << "**********2、查看往届记录***********" << endl;
    cout << "**********3、清空比赛记录***********" << endl;
    cout << "**********0、退出比赛程序***********" << endl;
    cout << "**********************************" << endl;
}

void speechManger::exitSystem() {
    system("cls");
    cout << "欢迎下次使用" << endl;
    system("pause");
    exit(0);
}

void speechManger::initContainer() {
    //四个容器全部置空以初始化，一般容器的初始化都是置空
    v_competitorsRoundOne.clear();
    v_competitorsRoundTwo.clear();
    v_winners.clear();
    m_competitorsIdScore.clear();
}

void speechManger::createPlayer() {
    string nameSeed = "ABCDEFGHIJKL";
    speechPlayer person;
    for (int i = 0; i < nameSeed.size(); i++) {
        string name = "选手";
        name += nameSeed[i];
        person.setName(name);
        v_competitorsRoundOne.push_back(i + 10001);                               //将想要分配给12名选手的编号放入容器
        m_competitorsIdScore.insert(make_pair(v_competitorsRoundOne[i], person)); //将编号分配给每个选手，并将其放入map容器中
    }
}

void speechManger::showAllPlayers() {
    for (auto it: m_competitorsIdScore) {
        cout << "选手编号：" << it.first << " 姓名：" << it.second.getName();
        if (m_roundIndex == roundOne)
            cout << " 第一轮比赛得分：" << it.second.getScore(m_roundIndex) << endl;
        else
            cout << " 第一轮比赛得分：" << it.second.getScore(m_roundIndex) << " 第二轮比赛得分" << it.second.getScore(m_roundIndex)
                 << endl;
    }
}

void speechManger::startSpeech() {

    this->createPlayer();          //创建十二个人

    //第一轮比赛
    m_roundIndex = roundOne; //将轮数设为1

    // 1、抽签
    this->speechLot();
    // 2、比赛
    this->speechContest();
    // 3、显示晋级结果
    this->showQualifyingPlayers(v_competitorsRoundTwo);


    //第二轮比赛
    m_roundIndex = roundTwo;//将比赛轮数切换为2

    // 1、抽签
    this->speechLot();

    // 2、比赛
    this->speechContest();

    // 3、显示晋级结果
    this->showQualifyingPlayers(v_winners);

    //保存分数本届比赛的获胜者的信息
    this->saveRecord();

    cout << "本届比赛已结束" << endl;
    this->addSession();//将比赛的届数加1

    initContainer();//确保内部容器清空不对下一届比赛造成影响

    system("pause");
    system("cls");
}

void speechManger::speechLot() {
    cout << "第" << m_roundIndex << "轮比赛选手正在抽签...\n----------------\n抽签后演讲顺序如下" << endl;
    if (m_roundIndex == roundOne) {
        random_shuffle(v_competitorsRoundOne.begin(), v_competitorsRoundOne.end()); //洗牌算法打乱顺序
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
    cout << "第" << m_roundIndex << "轮比赛的晋级者名单如下：" << endl;
    speechPlayer tempPerson;
    for (auto index: v_temp) {
        tempPerson = m_competitorsIdScore.at(index);
        tempPerson.showScore(m_roundIndex);
    }
}

void speechManger::speechContest() {
    cout << "----------第" << m_roundIndex << "轮比赛正式开始----------" << endl;
    multimap<double, int, greater<double>> v_groupScore; //一个存放小组内得分情况的临时容器，key是选手的平均分，value是选手的编号，因使用了greater<double>()作为谓词使容器内部执行了降序排列
    int num = 0;                                         //记录人员数，6个人为一组
    vector<int> v_competingPersons;                      //存放正在比赛的选手的编号的容器
    //第一轮比赛时将v1容器中的元素搬进来，第二轮比赛时将v2容器中的元素搬进来
    if (m_roundIndex == roundOne)
        v_competingPersons = v_competitorsRoundOne;
    else
        v_competingPersons = v_competitorsRoundTwo;

    deque<double> d_judgesScores;                                                    //保存评委打分的容器
    map<double, int, greater<double>> m_temporarySortingContainerForPromotedPlayers; //临时保存晋级选手的容器，用这个容器对晋级选手的分数进行一个排序，第一轮比赛的晋级选手是一组的前三名和二组的前三名

    for (auto it: v_competingPersons) {
        //每个循环代表每个人的评分过程
        num++;
        //评委打分
        for (int i = 0; i < 10; i++) {
            //该循环表示10个评委给一个人打分的过程
            double score = (rand() % (int) (10 * (maxScore - minScore) + 1 + 10 * minScore)) / 10.2f;
            d_judgesScores.push_back(score);
        }
        sort(d_judgesScores.begin(), d_judgesScores.end(), greater<double>()); //按从大到小的顺序排列
        d_judgesScores.pop_back();                                             //去掉最低分
        d_judgesScores.pop_front();                                            //去掉最高分
        double sum = accumulate(d_judgesScores.begin(), d_judgesScores.end(),
                                0.0f);                               //获得总分，第三个参数是累加的初始值，0.0f明确表示初始值是小数，返回返回的类型就是
        double average = sum / (double) d_judgesScores.size();        //获取平均分作为选手的最终成绩
        m_competitorsIdScore.at(it).setScore(m_roundIndex, average); //将选手的成绩写入计分板
        v_groupScore.insert(make_pair(average, it));                 //将选手的成绩放入小组得分中，v_groupScore是map容器，会对内部存储的分数进行降序排列

        //因为参加第一轮比赛的人数12个人和参加第二轮比赛的人数6个人在下面num%6的时候都能整除，所以不需要考虑第二轮人数变了的情况下重新设置输出名次的条件

        if (num % 6 == 0) //在第一轮比赛中给第6个人或第12个人评完分数 或者 在第二轮比赛中给晋级的6个人评完分数后，这个if语句会执行，表示要对小组得分进行汇总，取出前三名
        {

            //根据比赛的轮数分别展示第一轮比赛中两个小组的成绩和第二轮比赛中六个人的成绩
            if (m_roundIndex == roundOne)
                cout << "第" << num / 6 << "小组的比赛名次如下：" << endl;
            else
                cout << "第二轮比赛中，6个人的成绩如下：" << endl;

            for (auto it: v_groupScore) {
                cout << "编号：" << it.second << " 姓名：" << m_competitorsIdScore[it.second].getName() << " 成绩："
                     << m_competitorsIdScore[it.second].getScore(m_roundIndex) << endl;
            }

            //得出小组的名次之后，将前三名取出来，如果是第一轮比赛，则将取出的三个人放入v_competitorsOfRoundOne容器中，如果是第二轮比赛，则将取出的三个人放入v_winners容器中
            int count = 0; //用循环取得前三名，使用count来计数，达到3时停止循环，取出v_groupScore的前三个元素
            for (auto it = v_groupScore.begin(); it != v_groupScore.end() && count < 3; it++, count++) {
                if (m_roundIndex == roundOne)                    //第一轮比赛中将小组内的前三名放入v_competitorsRoundTwo容器中
                    v_competitorsRoundTwo.push_back(it->second); //将第一回合中两个小组产生的前三名都放入第二轮比赛的容器中
                else                                             //这是在第二轮比赛时将六名选手前三名放入获胜者容器的情况
                    v_winners.push_back(it->second);
            }

            /*在第一轮比赛中，第一组的前三名和第二组的前三名放在一个容器时，虽然第一组的前三名和第二组的前三名都是按从大到小的顺序排列的，但是放在一起之后并没有按照从大到小的顺序进行排列
            所以在第一轮比赛的12个人全部评完分数之后，对保存晋级选手编号的容器v_competitorsRoundTwo进行一个排序，按选手分数从大到小的顺序对编号进行重新排序。*/
            if (m_roundIndex == roundOne && num == 12) {
                for (auto index: v_competitorsRoundTwo) {
                    m_temporarySortingContainerForPromotedPlayers.insert(
                            make_pair(m_competitorsIdScore.at(index).getScore(m_roundIndex), index));
                }
                v_competitorsRoundTwo.clear(); //清空没有对分数进行排序的仅保存选手编号的容器v_competitorsRoundTwo，以便将排好序了的map容器中的数据重新搬进来
                for (auto pairOfPlayers: m_temporarySortingContainerForPromotedPlayers) {
                    v_competitorsRoundTwo.push_back(pairOfPlayers.second);
                }
            }

            v_groupScore.clear(); // v_groupScore只是一个临时容器，展示完一个小组的成绩和完成晋级工作之后要立即清空，以便存储下一小组的成绩
            m_temporarySortingContainerForPromotedPlayers.clear();
        }

        d_judgesScores.clear(); // d_judgesScores在一个人的打分结束后，这个人的平均分已经记录在了自己内部的数组中，该容器中十个分数不再有用，应立即清空，在下一个循环中给新的人存储十个评委的成绩
    }
    cout << "----------第" << m_roundIndex << "轮比赛结束----------" << endl;
    system("pause");
}

void speechManger::saveRecord() {
    ofstream fileOut;
    fileOut.open(fileAddress, ios::out | ios::app);//以追加写的方式将比赛的结果写入文件
    for (auto winnerIndex: v_winners) {
        fileOut << winnerIndex << "," << m_competitorsIdScore.at(winnerIndex).getScore(roundTwo) << ",";
    }
    fileOut << endl;//写完一整条记录后换行，以便下次书写记录不会将记录写在上一条记录的后面
    fileOut.close();
    cout << "记录已保存" << endl;

}

void speechManger::loadRecord() {
    ifstream fileIn(fileAddress, ios::in);
    if (!fileIn.is_open())//打开失败
    {
        fileIsEmpty = true;//表示文件为空
        cout << "文件不存在" << endl;
        fileIn.close();
        return;
    }
    //文件清空的情况
    char ch;
    fileIn >> ch;
    if (fileIn.eof())//表示读到了文件尾
    {
        cout << "文件为空" << endl;
        fileIsEmpty = true;
        fileIn.close();
        return;
    }
    //文件不为空的情况
    fileIsEmpty = false;
    fileIn.putback(ch);//将上面读取的字符读回来
    string winnersData;
    vector<string> v_winnersData;//v_winnerData只存放一届比赛的信息，每个元素是获胜者的编号或者成绩
    competitionSession=0;//

    while (fileIn >> winnersData) {
        //每个循环读取一届比赛的信息
        //文件中的数据是字符串，中间夹杂逗号，将逗号分离出来
        int position = -1;//表示逗号在字符串的位置
        int startPosition = 0;//find()函数查找的起始位置

        //下面这个循环v_winnerData只存放一届比赛的信息，每个元素是获胜者的编号或者成绩
        while (true) {
            //此循环将一届比赛的信息（一段字符串，其中含有逗号）中的逗号剔除，然后将子串放入 v_winnersData

            position = winnersData.find(",", startPosition);//find函数返回字符串中字串的起始位置，第二个参数是开始查找的位置
            if (position == -1) break;//若未找到逗号则退出循环
            //subWinnerData字符串是选手的编号或者得分，是winnersData的子字符串
            string subWinnerData = winnersData.substr(startPosition,
                                                      position - startPosition);//substr(pos,n);pos是开始位置，n是获取字串的长度
            startPosition = position + 1;
            v_winnersData.push_back(subWinnerData);
        }
        competitionSession++;
        this->m_winnersRecorder.insert(make_pair(competitionSession, v_winnersData));//将届数和每届的数据放入map容器便于管理存储
        v_winnersData.clear();
    }
    fileIn.close();
}

void speechManger::viewPastRecords() {
    this->loadRecord();
    cout << "往届比赛的信息如下：" << endl;

    for (auto item: m_winnersRecorder) {
        int i = 0;//vector<string>容器的内部索引值
        cout << "第" << item.first << "届比赛：" << endl;
        //0 A姓名 1 A成绩 2 B姓名 3 B成绩 4 C姓名 5 C成绩
        cout << "冠军--- 姓名：" << item.second.at(i) << " 成绩：" << item.second.at(i + 1) << endl;
        cout << "亚军--- 姓名：" << item.second.at(i + 2) << " 成绩：" << item.second.at(i + 3) << endl;
        cout << "季军--- 姓名：" << item.second.at(i + 4) << "成绩：" << item.second.at(i + 5) << endl;
        cout << endl;

    }


}