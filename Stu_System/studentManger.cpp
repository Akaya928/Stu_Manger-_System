#include"studentManger.h"

StuManger::StuManger() //初始化文件
{
	std::ifstream ifs;
	ifs.open(FILENAME, std::ios::in);

	//文件创建可能出现的两种错误
	//1.文件打开失败
	if (!ifs.is_open())
	{
		std::cout << "File failed to open!" << std::endl;
		this->isFileEmpty = true; //文件为空
		ifs.close();
		return;
	}

	//2.文件为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		std::cout << "文件为空!" << std::endl;
		this->isFileEmpty = true; //文件为空
		ifs.close();
		return;
	}

	int num = this->getNum();
	std::cout << "职工人数为：" << num << std::endl;
	this->stu_num = num;
	this->initStudent();//初始化stu_vec容器
}

void StuManger::initStudent()
{
	std::ifstream ifs(FILENAME, std::ios::in);

	std::string name;
	int age;
	std::string gender;
	std::string ID;
	std::vector<Score> score_vec;
	std::string flag1;
	std::string course;
	int score;
	std::string flag2;

	while (ifs >> name && ifs >> age && ifs >> gender && ifs >> ID)
	{
		std::streampos pos = ifs.tellg(); //记录位置
		ifs >> flag1;
		if (flag1 == "[")
		{
			while (ifs >> course && ifs >> score)
			{
				score_vec.push_back(Score(course, score));
				std::streampos pos2 = ifs.tellg(); //记录位置
				ifs >> flag2;
				if (flag2 == "]")
					break;
				ifs.seekg(pos2); //回到之前的位置。
			}
		}
		else
			ifs.seekg(pos);//回退
		if(gender == "男")
			stu_vec.push_back(Student(name, age, 1, ID, score_vec));
		else
			stu_vec.push_back(Student(name, age, 2, ID, score_vec));
	}

	ifs.close();
}

int StuManger::getNum()
{
	std::ifstream ifs(FILENAME, std::ios::in);

	int num = 0;
	std::string name;
	int age;
	std::string gender;
	std::string ID;
	std::string flag1;
	std::string flag2;

	while (ifs >> name && ifs >> age && ifs >> gender && ifs >> ID)
	{
		std::streampos pos = ifs.tellg(); //记录位置
		ifs >> flag1;
		if (flag1 == "[")
		{
			while (ifs >> flag2)
			{
				if (flag2 == "]")
					break;
			}
		}
		++num;
	}

	ifs.close();

	return num;
}


void StuManger::showMenu()
{
	std::cout << "欢迎使用学生信息管理系统！\n"
		<< "1. 增加\t2. 显示\n"
		<< "3. 查询\t4. 更改\n"
		<< "5. 删除\t6. 排序\n"
		<< "7. 删库\t8. 退出\n";
}

void StuManger::cleanFile()
{
	std::cout << "是否确认清空？\n"
		<< "1. 确定"
		<< "2. 返回" << std::endl;

	int select = 0;
	std::cin >> select;

	if (1 == select)
	{
		//文件清空
		std::ofstream ofs(FILENAME, std::ios::trunc);
		ofs.close();
		std::cout << "删库跑路喽！" << std::endl;

		//容器置零
		stu_vec.clear();
		stu_num = 0;
		this->isFileEmpty = true;
	}

	system("pause");
	system("cls");
}

void StuManger::exitSystem()
{
	std::cout << "欢迎下次使用！" << std::endl;
}

void StuManger::addInfo()
{

	//Stu对象的基本属性
	std::string name;
	int age;
	int gender;
	std::string ID;
	std::vector<Score> score_vec;

	int add_num; //一次存入的对象数量
	std::cout << "存入系统的学生数量：__\b\b";
	std::cin >> add_num;

	if (add_num > 0)
	{
		stu_num += add_num;
		for (int n = 1; n <= add_num; ++n)
		{
			//输入学生的基本信息
			std::cout << "请输入第" << n << "个学生的姓名：" << std::endl;
			std::cin >> name;

			std::cout << "请输入第" << n << "个学生的年龄：" << std::endl;
			std::cin >> age;

			std::cout << "请输入第" << n << "个学生的性别：" << std::endl;
			std::cin >> gender;

			std::cout << "请输入第" << n << "个学生的学号：" << std::endl;
			std::cin >> ID;

			//输入学生的成绩信息
			setScore(score_vec);

			stu_vec.push_back(Student(name, age, gender, ID, score_vec));
		}

		this->save(); //保存到文件
		this->isFileEmpty = false;
		std::cout << "成功添加" << add_num << "个学生信息" << std::endl;
	}
	else
		std::cout << "输入有误！" << std::endl;
	return;
	
	system("pause");
	system("cls");
}

void StuManger::showInfo()
{
	if (this->isFileEmpty)
	{
		std::cout << "文件不存在或记录为空" << std::endl;
	}
	else
	{
		for (Student val : stu_vec)
		{
			val.getPersonIfo();
			if (val.isScoreExsit())
			{
				val.getScore();
			}
		}
	}

	system("pause");
	system("cls");
}

void StuManger::save()
{
	std::ofstream ofs;
	ofs.open(FILENAME, std::ios::out); //?以ascill码写入，可改为以二进制写入确保信息安全

	for (auto it = this->stu_vec.begin(); it != this->stu_vec.end(); ++it)
	{
		ofs << it->showName() << " "
			<< it->showAge() << " "
			<< it->showGender() << " "
			<< it->showID() << std::endl;
		if (it->isScoreExsit())
		{
			ofs << "[ ";
			for (auto s_it = it->score_vec.begin(); s_it != it->score_vec.end(); ++s_it)
			{
				ofs << s_it->course << " " << s_it->score << " ";
			}
			ofs << "]" << std::endl;
		}
	}

	ofs.close();
}

void StuManger::findInfo()
{
	if (this->isFileEmpty)
	{
		std::cout << "文件不存在或文件打开失败！" << std::endl;
	}
	else
	{
		std::cout << "请选择查找方式：1.按学号查，2.按姓名查询" << std::endl;
		int choice = 0;
		std::cin >> choice;

		if (1 == choice)
		{
			std::cout << "请输入要查询学生的学号：__________\b\b\b\b\b\b\b\b\b\b" << std::endl;
			std::string ID;
			std::cin >> ID;

			bool flag = false; //判断是否查询到
			for (auto it = stu_vec.begin(); it != stu_vec.end(); ++it)
			{
				if (ID == it->showID())
				{
					std::cout << "成功查询到学号为" << ID << "学生的信息！\n"
						<< "具体信息如下：\n"
						<< "Name: " << it->showName()
						<< "\tID: " << it->showID()
						<< "\tGender: " << it->showGender()
						<< "\tAge: " << it->showAge() << std::endl;
					if (it->isScoreExsit())
					{
						std::cout << it->showName() << "同学成绩已录入，如下: " << std::endl;
						it->getScore();
					}
					else
					{
						std::cout << it->showName() << "同学成绩未录入！" << std::endl;
					}

					flag = true; //查询到了
					break;
				}
			}

			if (!flag)
			{
				std::cout << "查询失败！" << std::endl;
			}
		}
		else if (2 == choice)
		{
			std::cout << "请输入要查询学生的姓名：__________\b\b\b\b\b\b\b\b\b\b";
			std::string name;
			std::cin >> name;

			bool flag = false;
			for (auto it = stu_vec.begin(); it != stu_vec.end(); ++it)
			{
				if (name == it->showName())
				{
					std::cout << "成功查询到姓名为" << name << "学生的信息！\n"
						<< "具体信息如下：\n"
						<< "Name: " << it->showName()
						<< "\tID: " << it->showID()
						<< "\tGender: " << it->showGender()
						<< "\tAge: " << it->showAge() << std::endl;
					if (it->isScoreExsit())
					{
						std::cout << it->showName() << "同学成绩已录入，如下: " << std::endl;
						it->getScore();
					}
					else
					{
						std::cout << it->showName() << "同学成绩未录入！" << std::endl;
					}

					flag = true; //查询到了
					break;
				}
			}

			if (!flag)
			{
				std::cout << "查询失败！" << std::endl;
			}
		}
	}

	system("pause");
	system("cls");
}

void StuManger::modInfo()
{
	if (this->isFileEmpty)
	{
		std::cout << "文件不存在或文件打开失败！" << std::endl;
	}
	else
	{
		std::cout << "请输入要更改信息的学生的学号：__________\b\b\b\b\b\b\b\b\b\b";
		std::string ID;
		std::cin >> ID;
		
		for (auto it = stu_vec.begin(); it != stu_vec.end(); ++it)
		{
			if (ID == it->showID())
			{
				std::string new_name = it->showName();
				std::string new_ID = it->showID();
				int new_age = it->showAge();
				int new_gender = it->showGenderNumber();

				bool flag = true;
				int choice = 0;
				while (flag)
				{
					std::cout << "成功查询到学号为" << ID << "的学生！请选择要更改的部分：\n"
						<< "1.学号 2.姓名 3.年龄 4.性别 5.成绩 0.确认修改" << std::endl;


					std::cin >> choice;
					switch (choice)
					{
					case 1:
						std::cout << "请输入新的学号：" << std::endl;
						std::cin >> new_ID;
						std::cout << "修改成功！" << std::endl;
						system("pause");
						system("cls");
						break;
					case 2:
						std::cout << "请输入新的姓名：" << std::endl;
						std::cin >> new_name;
						system("pause");
						system("cls");
						break;
					case 3:
						std::cout << "请输入新的年龄：" << std::endl;
						std::cin >> new_age;
						system("pause");
						system("cls");
						break;
					case 4:
						std::cout << "请输入新的性别：" << std::endl;
						std::cin >> new_gender;
						system("pause");
						system("cls");
						break;
					case 5:
						std::cout << "请输入新的成绩：" << std::endl;
						setScore(it->score_vec);
						system("pause");
						system("cls");
					case 0:
						flag = false;
						break;

					}
				}

				*it = Student(new_name, new_age, new_gender, new_ID, it->score_vec);
				std::cout << "修改成功！" << std::endl;
				this->save();
				break;
			}
			else
			{
				std::cout << "查询失败，查无此人！" << std::endl;
			}
		}
	}

	system("pause");
	system("cls");
}

void StuManger::setScore(std::vector<Score> &s_v)
{
	if (s_v.size() > 0)
	{
		s_v.resize(0); //若存在成绩，重置成绩
	}
	std::string course;
	int score;

	int score_num = 0;
	std::cout << "请输入要添加的科目数：" << std::endl;
	std::cin >> score_num;

	for (int i = 0; i < score_num; ++i)
	{
		std::cout << "科目：_____\b\b\b\b\b";
		std::cin >> course;

		std::cout << "成绩：__\b\b";
		std::cin >> score;

		s_v.push_back(Score(course, score));
	}

	system("pause");
	system("cls");
}

void StuManger::delInfo()
{
	if (this->isFileEmpty)
	{
		std::cout << "文件不存在或文件打开失败！" << std::endl;
	}
	else
	{
		bool flag = false;
		std::cout << "请输入要删除信息的学生的学号：__________\b\b\b\b\b\b\b\b\b\b";
		std::string ID;
		std::cin >> ID;

		for (auto it = stu_vec.begin(); it != stu_vec.end(); ++it)
		{
			if (ID == it->showID())
			{
				for (auto it = stu_vec.begin(); ++it != stu_vec.end(); ++it)
				{
					*it = *(++it);
				}

				flag = true;
				--stu_num;
				this->save();
				std::cout << "删除成功！" << std::endl;
				break;
			}
		}
		if (!flag)
		{
			std::cout << "删除失败，未找到该学生！" << std::endl;
		}
	}

	system("pause");
	system("cls");
}

void StuManger::sortInfo()
{
	if (this->isFileEmpty)
	{
		std::cout << "文件不存在或记录为空！" << std::endl;
		system("pause");
		system("clear");
	}
	else
	{
		std::cout << "请选择排序方式：" << std::endl
			<< "1.按学号升序排序" << std::endl
			<< "2.按学号降序排序" << std::endl;

		int select;
		std::cin >> select;

		if (1 == select)
		{
			std::sort(stu_vec.begin(), stu_vec.end(), MyCompareGreater());
		}
		if (2 == select)
		{
			std::sort(stu_vec.begin(), stu_vec.end(), MyCompareLess());
		}

		std::cout << "排序成功！排序后的结果为：" << std::endl;
		this->save();
		this->showInfo();
	}
}

StuManger::~StuManger()
{
	stu_vec.clear();
	stu_num = 0;
	this->isFileEmpty = true;
}