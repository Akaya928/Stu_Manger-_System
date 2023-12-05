#pragma once
#include<iostream>
#include<vector>
#include"Score.h"

class Student : public Score
{
public:

	Student(std::string name, int age, int gender, std::string ID, std::vector<Score> &score_vec);

	void getPersonIfo(); //学生基本信息

	void getScore(); //学生相关成绩

	std::string showName();

	int showAge();

	std::string showGender();

	int showGenderNumber();

	std::string showID();

	bool isScoreExsit();

	std::vector<Score> score_vec; //对应 N 组成绩

protected:

	std::string name;

	int age;

	int gender; //gender = 1 为男生  gender = 0 为女生

	std::string ID;
};