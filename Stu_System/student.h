#pragma once
#include<iostream>
#include<vector>
#include"Score.h"

class Student : public Score
{
public:

	Student(std::string name, int age, int gender, std::string ID, std::vector<Score> &score_vec);

	void getPersonIfo(); //ѧ��������Ϣ

	void getScore(); //ѧ����سɼ�

	std::string showName();

	int showAge();

	std::string showGender();

	int showGenderNumber();

	std::string showID();

	bool isScoreExsit();

	std::vector<Score> score_vec; //��Ӧ N ��ɼ�

protected:

	std::string name;

	int age;

	int gender; //gender = 1 Ϊ����  gender = 0 ΪŮ��

	std::string ID;
};