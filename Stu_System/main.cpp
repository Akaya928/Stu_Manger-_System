#include<iostream>
#include"score.h"
#include"student.h"
#include"studentManger.h"

using namespace std;

int main()
{
	StuManger stu_manger;

	while (true)
	{
		stu_manger.showMenu();
		char select;
		std::cin >> select;

		switch (select)
		{
		case '1':
			system("cls");
			stu_manger.addInfo();
			break;
		case '2':
			system("cls");
			stu_manger.showInfo();
			break;
		case '3':
			system("cls");
			stu_manger.findInfo();
			break;
		case '4':
			system("cls");
			stu_manger.modInfo();
			break;
		case '5':
			system("cls");
			stu_manger.delInfo();
			break;
		case '6':
			system("cls");
			stu_manger.sortInfo();
			break;
		case '7':
			system("cls");
			stu_manger.cleanFile();
			break;
		case '8':
			system("cls");
			stu_manger.exitSystem();
			return 0;
		default:
			system("cls");
		}
	}
}