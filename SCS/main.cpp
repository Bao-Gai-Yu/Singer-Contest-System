#include<iostream>
#include<cstdlib>
#include<fstream>
#include"myList.h"
#include"user_class.h"
#include"contest.h"
#include"singer.h"
using namespace std;

void readData(int&, myList<contest>&);
void writeData(int&, myList<contest>&);

int main()
{
	myList<contest> contestList;//创建存储不同场次的比赛的链表
	int contestCount;//存储比赛场次数
	readData(contestCount, contestList);//文件读入数据

	cout << "################################################" << endl;
	cout << "#                                              #" << endl;
	cout << "#   欢迎使用歌手比赛管理系统                   #" << endl;
	cout << "#                                              #" << endl;
	cout << "#   请选择用户类别：                           #" << endl;
	cout << "#       1 - 普通用户                           #" << endl;
	cout << "#       2 - 管理员                             #" << endl;
	cout << "#                                              #" << endl;
	cout << "################################################" << endl;
	char choice;
	cin >> choice;
	while (choice != '1' && choice != '2')
	{
		cout << "输入错误，请重新输入：";
		cin >> choice;
	}
	if (choice == '1')		//普通用户的操作
	{
		string uid;
		cout << "请输入你的ID：";
		cin >> uid;
		user currentUser(uid, contestCount);
		system("cls");
		cout << "欢迎您，亲爱的 " << uid << " !" << endl;
		if (contestCount == 0)
		{
			cout << "当前没有比赛哦~" << endl;
			system("pause");
		}
		else
		{
			cout << "当前共有"<<contestCount<<"场比赛" << endl;
			while (1)
			{

				contestList.printList();
				cout << "###########################################################" << endl;
				cout << "请输入您要查看的场次前的数字（1-" << contestCount << ")" << endl;
				cout << "输入0表示退出系统\n\t(注意！不正常退出系统的话，您的任何操作不会被记录！)"<<endl;
				cout << "您的选择是：";
				int contestChoice;
				cin >> contestChoice;
				while ((contestChoice<0 || contestChoice > contestCount ))
				{
					cout << "输入错误，请重新输入：";
					cin >> contestChoice;
				}
				if (contestChoice == 0)
				{
					system("cls");
					break;
				}
				else
				{
					system("cls");
					while (1)
					{
						contest* currentContest = contestList.getNode(contestChoice);
						myList<singer>* currentSingerList = &(currentContest->contestantList);
						int singerNum = currentContest->getContestantCount();
						cout <<endl<< "当前正在查看的比赛为：" << currentContest->getContestName() << endl;
						cout << "###########################" << endl;
						cout << "#                         #" << endl;
						cout << "#  操作：                 #" << endl;
						cout << "#     1.查看选手信息      #" << endl;
						cout << "#     2.为选手投票        #" << endl;
						cout << "#     3.返回比赛选择      #" << endl;
						cout << "#                         #" << endl;
						cout << "###########################" << endl;
						char inContestChoice;
						cout << "您要进行的操作是：";
						cin >> inContestChoice;
						while (inContestChoice < '1' || inContestChoice > '3')
						{
							cout << "输入有误请重新输入：";
							cin >> inContestChoice;
						}
						if (inContestChoice == '1')//选择查看选手信息
						{
							system("cls");
							currentSingerList->printList();//输出歌手列表
							while (1)
							{
								cout << "#############################" << endl;
								cout << "#                           #" << endl;
								cout << "#  操作：                   #" << endl;
								cout << "#     1.排序查看            #" << endl;
								cout << "#     2.搜索歌手            #" << endl;
								cout << "#     3.返回上一级          #" << endl;
								cout << "#                           #" << endl;
								cout << "#############################" << endl;
								char singerListChoice;
								cout << "请输入您的选择：";
								cin >> singerListChoice;
								while (singerListChoice < '1' || singerListChoice > '3')
								{
									cout << "输入错误，请重新输入：";
									cin >> singerListChoice;
								}
								if (singerListChoice == '1')
								{
									currentUser.showSingers(currentContest);//排序输出歌手列表
								}
								else if(singerListChoice=='2')
								{
									currentUser.search(currentContest);//进行搜索
								}
								else if (singerListChoice == '3')
								{
									system("cls");
									break;
								}
							}
						}
						else if (inContestChoice == '2')//为选手投票
						{
							system("cls");
							for (int i = 1;i <= singerNum;i++)
							{
								singer* tmp = currentSingerList->getNode(i);
								cout << "->" << i << endl;
								cout << "\t编号：" <<tmp->getNumber()<< "\t姓名：" <<tmp->getName()<< endl;
								cout << "\t\t当前得票数：" << tmp->getVotes() << endl;
								cout << endl;
							}
							int voteChoose;
							cout << "请输入您想要投票的选手前的序号（非选手编号！）:";
							cin >> voteChoose;
							while (voteChoose<1 || voteChoose>singerNum)
							{
								cout << "输入错误，请重新输入：";
								cin >> voteChoose;
							}
							currentUser.voteSinger(contestChoice, currentSingerList->getNode(voteChoose));
						}
						else if (inContestChoice == '3')//返回上一级
						{
							system("cls");
							break;
						}
					}
				}
		}
		

		}
	}
	else if (choice == '2')//管理员
	{
		system("cls");
		const string adminPassword = "123456";
		cout << "请输入密码:";
		string pwd;
		cin >> pwd;
		while (pwd != adminPassword)
		{
			system("cls");
			cout << "密码错误，请重新输入：";
			cin >> pwd;
		}
		admin op;
		system("cls");
		cout << "欢迎来搞黑幕，管理员！"<<endl;
		while (1)
		{
			if (contestCount == 0)
			{
				cout << "当前没有比赛哦~"<<endl;
			}
			else
			{
				contestList.printList();
			}
			cout << "###########################################################" << endl;
			cout << "->" << contestCount + 1 << endl;
			cout << "\t\t新增/修改/删除比赛"<<endl;
			cout << endl;
			cout << "###########################################################" << endl;
			cout << "请输入您要进行操作的场次前的数字（1-" << contestCount+1 << ")" << endl;
			cout << "输入0表示退出系统\n\t(注意！不正常退出系统的话，您的任何操作不会被记录！)" << endl;
			cout << "您的选择是：";
			int opContestChoice;
			cin >> opContestChoice;
			while (opContestChoice < 0 || opContestChoice>contestCount + 1)
			{
				cout << "输入错误。请重新输入：";
				cin >> opContestChoice;
			}
			system("cls");
			if (opContestChoice == 0)
			{
				system("cls");
				break;
			}
			else if (opContestChoice >= 1 && opContestChoice <= contestCount)//对某场比赛进行操作
			{
				while (1)
				{
					contest* currentContest = contestList.getNode(opContestChoice);
					cout << "当前选中的比赛为： " << currentContest->getContestName() << endl;
					cout << "#############################" << endl;
					cout << "#                           #" << endl;
					cout << "#  操作：                   #" << endl;
					cout << "#     1.排序查看            #" << endl;
					cout << "#     2.搜索歌手            #" << endl;
					cout << "#     3.新增歌手            #" << endl;
					cout << "#     4.修改歌手数据        #" << endl;
					cout << "#     5.删除歌手            #" << endl;
					cout << "#     6.返回上一级          #" << endl;
					cout << "#                           #" << endl;
					cout << "#############################" << endl;
					int oop;
					cout << "请输入您的操作：";
					cin >> oop;
					while (oop < 1 || oop > 6)
					{
						cout << "输入错误，请重新输入：";
						cin >> oop;
					}
					if (oop == 1)//排序查看
					{
						op.showSingers(currentContest);
					}
					else if (oop == 2)//搜索
					{
						op.search(currentContest);
					}
					else if (oop == 3)//追加歌手数据
					{
						op.addSingerData(currentContest);
					}
					else if (oop == 4)//修改歌手数据
					{
						op.modifySingerData(currentContest);
					}
					else if (oop == 5)//删除歌手
					{
						op.deleteSingerData(currentContest);
					}
					else if (oop == 6)//返回上一级
					{
						system("cls");
						break;
					}
				}

			}
			else if (opContestChoice == contestCount + 1)//增删比赛
			{
				while (1)
				{
					cout << "#############################" << endl;
					cout << "#                           #" << endl;
					cout << "#  操作：                   #" << endl;
					cout << "#     1.增加比赛            #" << endl;
					cout << "#     2.修改比赛            #" << endl;
					cout << "#     3.删除比赛            #" << endl;
					cout << "#     4.返回上一级          #" << endl;
					cout << "#                           #" << endl;
					cout << "#############################" << endl;
					cout << "您的选择是：";
					int opSelect;
					cin >> opSelect;
					while (opSelect < 1 || opSelect>4)
					{
						cout << "输入错误，请重新输入：";
						cin >> opSelect;
					}
					if (opSelect == 1)
					{
						op.addContest(contestList,contestCount);
					}
					else if (opSelect == 2)
					{
						op.modifyContestData(contestList, contestCount);
					}
					else if (opSelect == 3)
					{
						op.deleteContest(contestList, contestCount);
					}
					else if(opSelect == 4)
					{
						system("cls");
						break;
					}
				}
			}
		}
	}

	system("cls");
	cout << "#####################################" << endl;
	cout << "#                                   #" << endl;
	cout << "#\t已退出，期待下次再见~       #" << endl;
	cout << "#                                   #" << endl;
	cout << "#####################################" << endl;

	writeData(contestCount, contestList);//数据写入文件
	system("pause");
	return 0;
}

void readData(int& contestCount,myList<contest>& contestList)
{
	ifstream Input;
	Input.open("Data/contestData.dat");
	Input >> contestCount;
	for (int i = 0;i < contestCount;i++)
	{
		string cName;
		int singerCnt;
		Input >> cName >> singerCnt;		//读入每场比赛的信息（比赛名称，歌手数量）
		contest* contestObj = new contest(cName, singerCnt);
		contestObj->readContestantList(cName);		//读入该场次的参赛选手信息
		contestList.addNode(*contestObj);
	}
	Input.close();
	return;
}

void writeData(int& contestCount, myList<contest>& contestList)
{
	ofstream Output;					//将数据写入文件保存
	Output.open("Data/contestData.dat");
	Output << contestCount << endl;
	for (int i = 1;i <= contestCount;i++)
	{
		contest* pc = contestList.getNode(i);
		Output << (*pc) << endl;
		ofstream singerOutput;
		singerOutput.open("Data/SingerLists/"+pc->getContestName() + ".dat");
		for (int j = 1;j <= pc->getContestantCount();j++)
		{
			singer* ps = (pc->contestantList).getNode(j);
			singerOutput << (*ps);
		}
		singerOutput.close();
	}
	Output.close();
	return;
}
