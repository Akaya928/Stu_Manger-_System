#include"Score.h"

Score::Score(std::string course, int score)
{
	this->course = course;
	this->score = score;
}

Score::Score()
{
	course = "NULL";
	score = 0;
}