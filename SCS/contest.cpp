#include"contest.h"
#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;

contest::contest(string cName="Nan", int cnt=0,int cFinished=0) :contestantList()
{
	prev = NULL;
	next = NULL;
	contestName = cName;
	contestantCount = cnt;
	isFinished = cFinished;
}

void contest::readContestantList(string cName)//读入一场比赛的歌手数据
{
	ifstream singerInput;
	singerInput.open("Data/SingerLists/"+cName + ".dat");		//歌手信息的存储文件名为  比赛名+".dat"
	for (int i = 0;i < contestantCount;i++)
	{
		singer* tmpSinger = new singer;
		string tmpNum, tmpName;
		singerInput >> tmpNum >> tmpName;	//读入歌手编号，姓名
		tmpSinger->setNumber(tmpNum);
		tmpSinger->setName(tmpName);
		for (int i = 0;i < 10;i++)			//读入评委打分
		{
			double tmpSco;
			singerInput >> tmpSco;
			tmpSinger->setScore(i, tmpSco);
		}
		int tmpVote;
		singerInput >> tmpVote;				//读入选手获得的观众投票数
		tmpSinger->setVotes(tmpVote);

		tmpSinger->countScores();			//计算选手的最高分，最低分，总分，平均分，以及综合得分。
		
		int tmpPromoted;
		singerInput >> tmpPromoted;
		tmpSinger->setPromoted(tmpPromoted);
		contestantList.addNode	(*tmpSinger);
	}
	singerInput.close();
	return;
}

void contest::printContestantList()
{	
	contestantList.printList();
	return;
}

void contest::display()
{
	cout << setw(29) << contestName << setw(23) << "比赛状态：";
	if (isFinished)
		cout << "已结束！" << endl;
	else
		cout << "进行中！" << endl;
}

string contest::getContestName()
{
	return contestName;
}

void contest::setContestName(string newName)
{
	contestName = newName;
	return;
}

int contest::getContestantCount()
{
	return contestantCount;
}

int contest::getFinished()
{
	return isFinished;
}

void contest::setContestantCount(int newCount)
{
	contestantCount = newCount;
	return;
}

void contest::setFinished(int newF)
{
	isFinished = newF;
	return;
}

ofstream& operator <<(ofstream& OUT,contest& c)	//将比赛信息写入文件的运算符重载
{
	OUT << c.contestName << ' ' << c.contestantCount << ' ' << c.isFinished;
	return OUT;
}