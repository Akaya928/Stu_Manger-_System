#pragma once
#include<iostream>

class Score
{
public:

	Score(); // Ĭ��Ϊ0

	Score(std::string course, int score);

//protected:

	std::string course;
	int score;
};