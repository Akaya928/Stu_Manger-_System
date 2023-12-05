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

	int getNum(); //��ȡ�����ļ��Ķ�����Ŀ done

	void showMenu(); //չʾ�˵� done

	void cleanFile(); //ɾ���ļ� done
	
	void exitSystem(); //�˳�ϵͳ done

	void addInfo(); //��� done 

	void showInfo(); //��ʾ done

	void save(); //�����ݴ��뱾���ļ� done

	void findInfo(); //��ѯ done

	void modInfo(); //���� done

	void delInfo(); //ɾ�� done

	void sortInfo(); //���� ���ٷ�Ϊ1.��������2.��ѧ�ţ�3.���ɼ�... done 1.

	void setScore(std::vector<Score> &s_v); //����ѧ���� n �ſγɼ���Ϣ done

	bool isFileEmpty = false;

	~StuManger();

	int stu_num = 0; //ѧ������

	std::vector<Student> stu_vec; //�������ѧ����Ϣ
};

//�Զ����Ԫν�� ��Ϊsort�ı�׼
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