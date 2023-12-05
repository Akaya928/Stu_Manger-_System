#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
#include<fstream>
#include"score.h"
#include"student.h"
#define FILENAME "StuInfo.txt"

class MycompareGreater;

class MycompareLess;

class StuManger
{
public:

	StuManger();

	void initStudent();

	int getNum(); //获取存入文件的对象数目 done

	void showMenu(); //展示菜单 done

	void cleanFile(); //删除文件 done
	
	void exitSystem(); //退出系统 done

	void addInfo(); //添加 done 

	void showInfo(); //显示 done

	void save(); //将数据存入本地文件 done

	void findInfo(); //查询 done

	void modInfo(); //更改 done

	void delInfo(); //删除 done

	void sortInfo(); //排序 可再分为1.按姓名，2.按学号，3.按成绩... done 1.

	void setScore(std::vector<Score> &s_v); //设置学生的 n 门课成绩信息 done

	bool isFileEmpty = false;

	~StuManger();

	int stu_num = 0; //学生数量

	std::vector<Student> stu_vec; //用来存放学生信息
};

//自定义二元谓词 作为sort的标准
class MyCompareLess
{
public:

	bool operator()(Student& s1, Student& s2)
	{
		return s1.showID() > s2.showID();
	}
};

class MyCompareGreater
{
public:

	bool operator()(Student &s1, Student &s2)
	{
		return s1.showID() < s2.showID();
	}
};