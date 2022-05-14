#include"singer.h"
#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;

singer::singer()
{
	prev = NULL;
	next = NULL;
	number = "Nan";
	name ="Nan";
	for (int i = 0;i < 10;i++)
		score[i] = 0;
	maxScore = 0;
	minScore = 0;
	totalScore = 0;
	averageScore = 0;
	votes = 0;
}

void singer::setNumber(string numS)
{
	number = numS;
	return;
}

void singer::setName(string nameS)
{
	name = nameS;
	return;
}

void singer::setScore(int index,double sco)
{
	score[index] = sco;
	return;
}

void singer::countScores()
{
	totalScore = score[0];
	maxScore = score[0];
	minScore = score[0];
	for (int i = 1;i < 10;i++)
	{
		totalScore += score[i];
		if (score[i] > maxScore)
			maxScore = score[i];
		if (score[i] < minScore)
			minScore = score[i];
	}
	averageScore = (totalScore - maxScore - minScore) / 8;
	return;
}

void singer::setVotes(int v)
{
	votes = v;
	return;
}

void singer::display()
{
	cout << "\t编号：" << number <<endl;
	cout << endl;
	cout << "\t姓名：" << name << endl;
	cout << endl;
	cout << "\t最高分：" << maxScore <<"\t最低分："<<minScore << endl;
	cout << endl;
	for (int i = 0;i < 10;i++)
		cout << "\t评委" <<setw(2)<< i + 1 << "的打分为：\t\t" << score[i] << endl;
	cout << endl;
	cout << "\t总得分：" << totalScore << "\t平均分：" << averageScore << endl;
	cout << endl;
	cout << "\t用户投票数：\t" << votes << endl;

	return;
}

string singer::getNumber()const 
{
	return number;
}

string singer::getName()const
{
	return name;
}

double singer::getScore(int i)const
{
	if (i >= 1 && i <= 10)
		return score[i - 1];
	else
	{
		switch (i) {
		case 11:
			return maxScore;
		case 12:
			return minScore;
		case 13:
			return totalScore;
		case 14:
			return averageScore;
		case 15:
			return votes;
		}
	}
}

int singer::getVotes() const 
{
	return votes;
}

ofstream& operator <<(ofstream& OUT, const singer& s)//将歌手信息写入文件的运算符重载
{
	OUT << s.number << ' ' << s.name << endl;
	for (int i = 0;i < 10;i++)
	{
		if (i)
			OUT << ' ';
		OUT << s.score[i];
	}
	OUT << endl << s.votes << endl;
	return OUT;
}

double& singer::operator[](int i)
{
	if (i >= 1 && i <= 10)
		return score[i - 1];
	else
	{
		switch (i) {
		case 11:
			return maxScore;
		case 12:
			return minScore;
		case 13:
			return totalScore;
		case 14:
			return averageScore;
		case 15:
			return votes;
		}
	}
}