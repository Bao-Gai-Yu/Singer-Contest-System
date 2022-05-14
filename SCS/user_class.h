#pragma once
#include<string>
#include<iostream>
#include"singer.h"
#include"contest.h"
using namespace std;
//基础操作类
class basic {
public:
	basic();
	void showSingers(contest*);//显示歌手信息，参数表示比赛场次
	void search(contest*);//搜索功能,支持模糊搜索
};

//普通用户类
class user :public basic {
public:
	user(string,int);
	~user();
	void voteSinger(int, singer*);//给歌手投票
private:
	string id;//用户的ID
	bool* voted;//记录当前用户各场次的投票情况
};

//管理员用户类
class admin :public basic {
public:
	void addContest(myList<contest>&, int&);//追加比赛信息
	void modifyContestData(myList<contest>&, int&);//修改比赛数据
	void deleteContest(myList<contest>&, int&);//删除比赛信息
	void addSingerData(contest*);//追加歌手数据
	void modifySingerData(contest*);//修改歌手数据
	void deleteSingerData(contest*);//删除歌手数据
};