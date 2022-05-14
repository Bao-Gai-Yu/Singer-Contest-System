#pragma once
#include<string>
#include"singer.h"
#include"myList.h"
#include"myList.cpp"
using namespace std;

class contest {
public:
	contest* prev;//用于链表中，指向前一场比赛
	contest* next;//用于链表中，指向后一场比赛
	myList<singer> contestantList;//参赛者链表
	contest(string,int,int);
	void readContestantList(string);//获取参赛人
	void printContestantList();//输出参赛者列表
	void  display();//输出比赛信息

	string getContestName();
	void setContestName(string);
	int getContestantCount();
	int getFinished();

	void setContestantCount(int);
	void setFinished(int);

	friend ofstream& operator <<(ofstream&,contest&);
private:
	string contestName;//比赛名称
	int contestantCount;//参赛者人数
	int isFinished;//设置比赛是否已经结束，0表示进行中，1表示已结束
};