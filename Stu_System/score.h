#pragma once
#include<iostream>

class Score
{
public:

	Score(); // д╛хон╙0

	Score(std::string course, int score);

//protected:

	std::string course;
	int score;
};