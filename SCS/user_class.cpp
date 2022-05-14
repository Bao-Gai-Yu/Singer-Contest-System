#include<cstdlib>
#include"user_class.h"
#include"contest.h"
#include"singer.h"

basic::basic(){}

void mySort(myList<singer>& sL, int singerCnt, int sortChoice, int isGreater)
{
	for (int i = 1;i < singerCnt;++i)
	{
		int k = i;
		for (int j = i + 1;j <= singerCnt;++j)
		{
			bool flag = false;
			if (isGreater)
			{
				if ((*sL.getNode(k))[sortChoice] > (*sL.getNode(j))[sortChoice])
				{
					flag = true;
				}
			}
			else
			{
				if ((*sL.getNode(k))[sortChoice] < (*sL.getNode(j))[sortChoice])
				{
					flag = true;
				}
			}
			if (flag)
				k = j;
		}
		if (k != i)
		{
			sL.swapNodes(i, k);
		}
	}
}

void basic::showSingers(contest* c)//选择排序方式，输出对一场比赛排序后的歌手列表
{
	system("cls");
	cout << "请选择排序的依据：" << endl;
	cout << " 1：评委1打分\t 2：评委2打分\t 3：评委3打分\t 4：评委4打分\t 5：评委5打分" << endl;
	cout << " 6：评委6打分\t 7：评委7打分\t 8：评委8打分\t 9：评委9打分\t10：评委10打分" << endl;
	cout << "11：评委最高分\t12：评委最低分\t13：总得分\t14：平均得分\t15：观众投票数" << endl;
	cout << "16：综合得分" << endl;
	int sortChoice,isGreater;
	cout << "请输入您的选择：";
	cin >> sortChoice;
	while (sortChoice < 1 || sortChoice>16)
	{
		cout << "输入错误，请重新输入：";
		cin >> sortChoice;
	}
	cout << "请选择升序(1)和降序(0):";
	cin >> isGreater;
	while (isGreater != 1 && isGreater != 0)
	{
		cout << "输入错误，请重新输入";
		cin >> isGreater;
	}
	myList<singer>& sL = c->contestantList;
	int singerCnt = c->getContestantCount();
	mySort(sL, singerCnt, sortChoice, isGreater);
	system("cls");
	sL.printList();
	cout << "排序已完成，结果在上方" << endl;
	return;
}

void basic::search(contest* c)//查找功能。在一场比赛中查找某个歌手
{
	system("cls");
	cout << "请输入歌手的名字进行搜索（支持模糊搜索）：" << endl;
	string key;
	cin >> key;
	int singerCnt = c->getContestantCount();
	int idx = 0;
	for (int t = 1;t <= singerCnt;t++)
	{
		singer* cSinger = c->contestantList.getNode(t);
		string name = cSinger->getName();
		if (name.find(key)!=string::npos)
		{
			idx++;
			cout << "###########################################################" << endl;
			cout << "结果 " << idx << " :" << endl;
			cSinger->display();
		}
	}
	if (idx)
	{
		cout << "搜索已完成，共有" << idx << "条结果。" << endl;
	}
	else
	{
		cout << "没有查询到任何结果！" << endl;
	}
	cout << endl;
	return;
}

user::user(string uid,int contestCount)//普通用户的初始化
{
	id = uid;
	voted = new bool[contestCount + 1];
	for (int i = 0;i <= contestCount;i++)
		voted[i] = false;
}

user::~user()
{
	delete[] voted;
}

void user::voteSinger(int contestIndex,singer* vSinger)
{
	system("cls");
	if (voted[contestIndex])
	{
		cout << "该场比赛您已投票,您将不能再进行投票！" << endl;
		return;
	}
	else
	{
		cout << "您已为选中的歌手投上一票!" << endl;
		cout << "一定要正常退出，投票才会保存哦~" << endl<<endl;
		voted[contestIndex] = true;
		vSinger->setVotes(vSinger->getVotes() + 1);
		vSinger->countScores();
	}
	return;
}

void checkPromoted(myList<singer>& sL,int size)
{
	mySort(sL, size, 16, 0);//按照综合成绩(16)降序(0)排序。
	for (int i = 1;i <= size / 2;i++)
	{
		sL.getNode(i)->setPromoted(1);
	}
	for (int i = size / 2 + 1;i <= size;i++)
	{
		sL.getNode(i)->setPromoted(0);
	}
	return;
}

void admin::addContest(myList<contest>&c, int& contestCount)
{
	/*cout << "请输入新比赛的名称：";
	string newName;
	cin >> newName;
	cout << "请输入新比赛的参赛人数：";
	int newCount;
	cin >> newCount;
	for (int i = 1;i <= contestCount;i++)
	{
		string tmpName = c.getNode(i)->getContestName();
		if (newName == tmpName)
		{
			cout << "已存在同名比赛，添加失败！" << endl;
			return;
		}
	}
	contest* newC = new contest(newName,newCount,0);
	for (int i = 0;i < newCount;i++)
	{
		singer* tmp = new singer;
		newC->contestantList.addNode(*tmp);
	}
	c.addNode(*newC);
	contestCount++;*/
	system("cls");
	c.printList();
	cout << "请选择一个进行中的比赛进入下一阶段：";
	int selectKey;
	cin >> selectKey;
	while (selectKey < 1 || selectKey > contestCount)
	{
		cout << "输入错误，请重新输入：";
		cin >> selectKey;
	}
	contest* targetC = c.getNode(selectKey);
	int isF = targetC->getFinished();
	system("cls");
	if (isF)
	{
		cout << "当前比赛已结束，无法进入下一阶段。" << endl;
		cout << "比赛创建失败。" << endl;
	}
	else
	{
		targetC->setFinished(1);
		string newName;
		cout << "请输入新比赛的名称：";
		cin >> newName;
		while (1)
		{
			bool flag = true;
			for (int i = 1;i <= contestCount;i++)
			{
				string tmpName = c.getNode(i)->getContestName();
				if (i != selectKey && newName == tmpName)
				{
					cout << "已存在同名比赛，请重新输入：" << endl;
					flag = false;
				}
			}
			if (flag) {break;}
		}
		int newCount = targetC->getContestantCount() / 2;
		contest* newC = new contest(newName, newCount, 0);
		myList<singer>& sL=targetC->contestantList;
		checkPromoted(sL, targetC->getContestantCount());
		for (int i = 1;i <= targetC->getContestantCount();i++)
		{
			singer* tmp = targetC->contestantList.getNode(i);
			if (tmp->getPromoted())
			{
				singer* newTmp = new singer;
				newTmp->setNumber(tmp->getNumber());
				newTmp->setName(tmp->getName());
				newC->contestantList.addNode(*newTmp);
			}

		}
		c.addNode(*newC);
		contestCount++;
	}
	cout << "创建成功!"<<endl;
	return;
}

void admin::modifyContestData(myList<contest>& c, int& contestCount)
{
	system("cls");
	if (contestCount == 0)
	{
		cout << "当前没有比赛！" << endl;
		return;
	}
	c.printList();
	cout << "请选择您要修改的比赛：";
	int modifyKey;
	cin >> modifyKey;
	while (modifyKey < 1 || modifyKey > contestCount)
	{
		cout << "输入错误，请重新输入：";
		cin >> modifyKey;
	}
	contest* targetC = c.getNode(modifyKey);
	string nowName = targetC->getContestName();
	string newName;
	cout << "比赛原名称为[ " << nowName << " ]，请输入您要修改成的名称：";
	cin >> newName;
	for (int i = 1;i <= contestCount;i++)
	{
		string tmpName = c.getNode(i)->getContestName();
		if (i != modifyKey && newName == tmpName)
		{
			cout << "已存在同名比赛，无法修改！"<<endl;
			return;
		}
	}
	targetC->setContestName(newName);
	system("cls");
	cout << "已完成名称修改！" << endl;
	return;
}

void admin::deleteContest(myList<contest>& c, int& contestCount)
{
	system("cls");
	if (contestCount == 0)
	{
		cout << "当前没有比赛！" << endl;
		return;
	}
	c.printList();
	cout << "请选择您要删除的比赛：";
	int deleteKey;
	cin >> deleteKey;
	while (deleteKey<1 || deleteKey>contestCount)
	{
		cout << "输入错误，请重新输入：";
		cin >> deleteKey;
	}
	system("cls");
	string deleteName = c.getNode(deleteKey)->getContestName();
	cout << "您确定要删除[ " << deleteName << " ]吗？(y/n)： ";
	char confirm;
	cin >> confirm;
	if (confirm == 'y')
	{
		c.deleteNode(deleteKey);
		contestCount--;
		cout << "比赛[ " << deleteName << " ]已被删除！" << endl;
	}
	else
	{
		cout << "取消操作，没有任何比赛被删除。" << endl;
	}

	return;
}

void admin::addSingerData(contest* c)
{
	singer* tmp=new singer;
	myList<singer>& sL = c->contestantList;
	string newNum, newName;
	cout << "请输入新增歌手的编号：";
	cin >> newNum;
	tmp->setNumber(newNum);
	cout << "请输入新增歌手的姓名：";
	cin >> newName;
	tmp->setName(newName);
	for (int i = 0;i < 10;i++)
	{
		double s;
		cout << "请输入第" << i + 1 << "个评委打分：";
		cin >> s;
		tmp->setScore(i, s);
	}
	int newVote;
	cout << "请输入新增歌手的观众投票数：";
	cin >> newVote;
	tmp->setVotes(newVote);
	
	tmp->countScores();
	c->setContestantCount( c->getContestantCount() + 1 );
	sL.addNode(*tmp);
	system("cls");
	cout << "新增歌手数据完成！" << endl<<endl;
	return;
}

void admin::modifySingerData(contest* c)
{
	system("cls");
	int singerCnt = c->getContestantCount();
	myList<singer>& sL = c->contestantList;
	for (int i = 1;i <= singerCnt;i++)
	{
		singer* tmp = sL.getNode(i);
		cout << "->" << i << endl;
		cout << "\t编号：" << tmp->getNumber() << "\t姓名:" << tmp->getName() << endl;
	}
	cout << "->0" << endl << "\t退出修改操作" << endl;
	cout << "请输入您欲修改的选手前的序号（非选手编号）：";
	int modifyKey;
	cin >> modifyKey;
	while (modifyKey<0 || modifyKey>singerCnt)
	{
		cout << "输入错误，请重新输入：";
		cin >> modifyKey;
	}
	system("cls");
	if (modifyKey == 0)
	{
		cout << "没有任何歌手数据被修改！" << endl;
	}
	else
	{
		singer& mS = *sL.getNode(modifyKey);
		char c;
		cout << "请问您要修改歌手编号与姓名吗(输入y表示确定):";
		cin >> c;
		if (c == 'y')
		{
			cout << "歌手原编号为：[ " << mS.getNumber()<<" ]  您想修改为：";
			string newNum;
			cin >> newNum;
			mS.setNumber(newNum);
			cout << "歌手原姓名为：[ " << mS.getName() << " ]  您想修改为：";
			string newName;
			cin >> newName;
			mS.setName(newName);
		}
		cout << "请问您要修改评委打分吗(输入y表示确定):";
		cin >> c;
		if (c == 'y')
		{
			for (int i = 1;i <= 10;i++)
			{
				cout << "评委" << i << "的原打分为：[ " << mS.getScore(i) << " ]  您想修改为：";
				double newS;
				cin >> newS;
				mS.setScore(i-1, newS);
			}
		}
		cout << "请问您要修改观众投票数吗(输入y表示确定):";
		cin >> c;
		if (c == 'y')
		{
			cout << "歌手的原观众投票数为：[ " << mS.getVotes() << " ]  您想修改为：";
			int newVote;
			cin >> newVote;
			mS.setVotes(newVote);
		}
		mS.countScores();
		system("cls");
		cout << "歌手信息已修改成功！" << endl;
	}
	return;
}

void admin::deleteSingerData(contest* c)
{
	system("cls");
	int singerCnt = c->getContestantCount();
	if (singerCnt == 0)
	{
		cout << "暂无歌手数据，无法删除！" << endl;
		return;
	}
	myList<singer>& sL = c->contestantList;
	for (int i = 1;i <= singerCnt;i++)
	{
		singer* tmp=sL.getNode(i);
		cout << "->" << i << endl;
		cout << "\t编号：" << tmp->getNumber() << "\t姓名:" << tmp->getName() << endl;
	}
	cout << "->0" << endl << "\t退出删除操作" << endl;
	cout << "请输入您欲删除的选手前的序号（非选手编号）：";
	int deleteKey;
	cin >> deleteKey;
	while (deleteKey<0 || deleteKey>singerCnt)
	{
		cout << "输入错误，请重新输入：";
		cin >> deleteKey;
	}
	system("cls");
	if (deleteKey == 0)
	{
		cout << "没有任何歌手数据被删除！" << endl;
	}
	else
	{
		sL.deleteNode(deleteKey);
		c->setContestantCount(c->getContestantCount() - 1);
		cout << "已成功删除歌手数据！"<<endl;
	}
	return;
}
