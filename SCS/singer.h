#pragma once
#include<string>
#include"myList.h"
using namespace std;
class singer {
public:
	singer* prev;//用在链表中，指向其前一个元素
	singer* next;//用在链表中，指向其后一个元素
	singer();
	void setNumber(string);//设置编号
	void setName(string);//设置姓名
	void setScore(int, double);//设置评委i+1的打分(0-9)
	void countScores();//计算最高最低分，总得分，平均分
	void setVotes(int);//设置观众投票数
	void setPromoted(int);
	void display();//输出歌手信息
	string getNumber()const;//返回编号
	string getName()const;//返回姓名
	double getScore(int)const;//int 为1-10，则返回评委1-10打分，11返回最高分，12返回最低分，13返回总分，14返回平均分，15返回投票数
	int getVotes()const;//返回观众投票数
	int getPromoted()const;//返回是否晋级
	friend void checkPromoted(myList<singer>&,int);
	friend ofstream& operator <<(ofstream&, const singer&);
	double& operator [](int);
private:
	string number;//歌手编号
	string name;//歌手姓名
	double score[10];//十个评委打分
	double maxScore;//评委最高分
	double minScore;//评委最低分
	double totalScore;//评委总得分（“不”去掉最高最低分的）
	double averageScore;//平均得分（去掉最高最低后的）
	double votes;//获得的用户投票数
	double finalScore;//综合得分
	int isPromtoted;//设置该选手是否晋级,0表示未晋级，1表示已晋级
};