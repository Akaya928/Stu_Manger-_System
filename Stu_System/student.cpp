#include"student.h"

Student::Student(std::string name, int age, int gender, std::string ID, std::vector<Score> &score_vec)
{
	this->name = name;
	this->age = age;
	this->gender = gender;
	this->ID = ID;
	this->score_vec = score_vec;
}

void Student::getPersonIfo()
{
	std::cout << "Name: " << name
		<< "\tID: " << ID
		<< "\tGender: " << showGender() //?
		<< "\tAge: " << age << std::endl;
}

void Student::getScore()
{
	std::cout << "[ ";
	for (auto it = score_vec.begin(); it != score_vec.end(); ++it)
	{
		std::cout << "course: " << it->course
			<< " score: " << it->score << "¡¢";
	}
	std::cout << " ]" << std::endl;
}

std::string Student::showName()
{
	return name;
}

std::string Student::showID()
{
	return ID;
}

std::string Student::showGender()
{
	if (gender == 1)
		return "ÄÐ";

	return "Å®";
}

int Student::showGenderNumber()
{
	return gender;
}

int Student::showAge()
{
	return age;
}

bool Student::isScoreExsit()
{
	if (score_vec.size() == 0)
		return false;

	return true;
}