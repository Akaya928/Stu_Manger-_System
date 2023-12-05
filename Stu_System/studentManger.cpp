#include"studentManger.h"

StuManger::StuManger() //��ʼ���ļ�
{
	std::ifstream ifs;
	ifs.open(FILENAME, std::ios::in);

	//�ļ��������ܳ��ֵ����ִ���
	//1.�ļ���ʧ��
	if (!ifs.is_open())
	{
		std::cout << "File failed to open!" << std::endl;
		this->isFileEmpty = true; //�ļ�Ϊ��
		ifs.close();
		return;
	}

	//2.�ļ�Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		std::cout << "�ļ�Ϊ��!" << std::endl;
		this->isFileEmpty = true; //�ļ�Ϊ��
		ifs.close();
		return;
	}

	int num = this->getNum();
	std::cout << "ְ������Ϊ��" << num << std::endl;
	this->stu_num = num;
	this->initStudent();//��ʼ��stu_vec����
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
		std::streampos pos = ifs.tellg(); //��¼λ��
		ifs >> flag1;
		if (flag1 == "[")
		{
			while (ifs >> course && ifs >> score)
			{
				score_vec.push_back(Score(course, score));
				std::streampos pos2 = ifs.tellg(); //��¼λ��
				ifs >> flag2;
				if (flag2 == "]")
					break;
				ifs.seekg(pos2); //�ص�֮ǰ��λ�á�
			}
		}
		else
			ifs.seekg(pos);//����
		if(gender == "��")
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
		std::streampos pos = ifs.tellg(); //��¼λ��
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
	std::cout << "��ӭʹ��ѧ����Ϣ����ϵͳ��\n"
		<< "1. ����\t2. ��ʾ\n"
		<< "3. ��ѯ\t4. ����\n"
		<< "5. ɾ��\t6. ����\n"
		<< "7. ɾ��\t8. �˳�\n";
}

void StuManger::cleanFile()
{
	std::cout << "�Ƿ�ȷ����գ�\n"
		<< "1. ȷ��"
		<< "2. ����" << std::endl;

	int select = 0;
	std::cin >> select;

	if (1 == select)
	{
		//�ļ����
		std::ofstream ofs(FILENAME, std::ios::trunc);
		ofs.close();
		std::cout << "ɾ����·ඣ�" << std::endl;

		//��������
		stu_vec.clear();
		stu_num = 0;
		this->isFileEmpty = true;
	}

	system("pause");
	system("cls");
}

void StuManger::exitSystem()
{
	std::cout << "��ӭ�´�ʹ�ã�" << std::endl;
}

void StuManger::addInfo()
{

	//Stu����Ļ�������
	std::string name;
	int age;
	int gender;
	std::string ID;
	std::vector<Score> score_vec;

	int add_num; //һ�δ���Ķ�������
	std::cout << "����ϵͳ��ѧ��������__\b\b";
	std::cin >> add_num;

	if (add_num > 0)
	{
		stu_num += add_num;
		for (int n = 1; n <= add_num; ++n)
		{
			//����ѧ���Ļ�����Ϣ
			std::cout << "�������" << n << "��ѧ����������" << std::endl;
			std::cin >> name;

			std::cout << "�������" << n << "��ѧ�������䣺" << std::endl;
			std::cin >> age;

			std::cout << "�������" << n << "��ѧ�����Ա�" << std::endl;
			std::cin >> gender;

			std::cout << "�������" << n << "��ѧ����ѧ�ţ�" << std::endl;
			std::cin >> ID;

			//����ѧ���ĳɼ���Ϣ
			setScore(score_vec);

			stu_vec.push_back(Student(name, age, gender, ID, score_vec));
		}

		this->save(); //���浽�ļ�
		this->isFileEmpty = false;
		std::cout << "�ɹ����" << add_num << "��ѧ����Ϣ" << std::endl;
	}
	else
		std::cout << "��������" << std::endl;
	return;
	
	system("pause");
	system("cls");
}

void StuManger::showInfo()
{
	if (this->isFileEmpty)
	{
		std::cout << "�ļ������ڻ��¼Ϊ��" << std::endl;
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
	ofs.open(FILENAME, std::ios::out); //?��ascill��д�룬�ɸ�Ϊ�Զ�����д��ȷ����Ϣ��ȫ

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
		std::cout << "�ļ������ڻ��ļ���ʧ�ܣ�" << std::endl;
	}
	else
	{
		std::cout << "��ѡ����ҷ�ʽ��1.��ѧ�Ų飬2.��������ѯ" << std::endl;
		int choice = 0;
		std::cin >> choice;

		if (1 == choice)
		{
			std::cout << "������Ҫ��ѯѧ����ѧ�ţ�__________\b\b\b\b\b\b\b\b\b\b" << std::endl;
			std::string ID;
			std::cin >> ID;

			bool flag = false; //�ж��Ƿ��ѯ��
			for (auto it = stu_vec.begin(); it != stu_vec.end(); ++it)
			{
				if (ID == it->showID())
				{
					std::cout << "�ɹ���ѯ��ѧ��Ϊ" << ID << "ѧ������Ϣ��\n"
						<< "������Ϣ���£�\n"
						<< "Name: " << it->showName()
						<< "\tID: " << it->showID()
						<< "\tGender: " << it->showGender()
						<< "\tAge: " << it->showAge() << std::endl;
					if (it->isScoreExsit())
					{
						std::cout << it->showName() << "ͬѧ�ɼ���¼�룬����: " << std::endl;
						it->getScore();
					}
					else
					{
						std::cout << it->showName() << "ͬѧ�ɼ�δ¼�룡" << std::endl;
					}

					flag = true; //��ѯ����
					break;
				}
			}

			if (!flag)
			{
				std::cout << "��ѯʧ�ܣ�" << std::endl;
			}
		}
		else if (2 == choice)
		{
			std::cout << "������Ҫ��ѯѧ����������__________\b\b\b\b\b\b\b\b\b\b";
			std::string name;
			std::cin >> name;

			bool flag = false;
			for (auto it = stu_vec.begin(); it != stu_vec.end(); ++it)
			{
				if (name == it->showName())
				{
					std::cout << "�ɹ���ѯ������Ϊ" << name << "ѧ������Ϣ��\n"
						<< "������Ϣ���£�\n"
						<< "Name: " << it->showName()
						<< "\tID: " << it->showID()
						<< "\tGender: " << it->showGender()
						<< "\tAge: " << it->showAge() << std::endl;
					if (it->isScoreExsit())
					{
						std::cout << it->showName() << "ͬѧ�ɼ���¼�룬����: " << std::endl;
						it->getScore();
					}
					else
					{
						std::cout << it->showName() << "ͬѧ�ɼ�δ¼�룡" << std::endl;
					}

					flag = true; //��ѯ����
					break;
				}
			}

			if (!flag)
			{
				std::cout << "��ѯʧ�ܣ�" << std::endl;
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
		std::cout << "�ļ������ڻ��ļ���ʧ�ܣ�" << std::endl;
	}
	else
	{
		std::cout << "������Ҫ������Ϣ��ѧ����ѧ�ţ�__________\b\b\b\b\b\b\b\b\b\b";
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
					std::cout << "�ɹ���ѯ��ѧ��Ϊ" << ID << "��ѧ������ѡ��Ҫ���ĵĲ��֣�\n"
						<< "1.ѧ�� 2.���� 3.���� 4.�Ա� 5.�ɼ� 0.ȷ���޸�" << std::endl;


					std::cin >> choice;
					switch (choice)
					{
					case 1:
						std::cout << "�������µ�ѧ�ţ�" << std::endl;
						std::cin >> new_ID;
						std::cout << "�޸ĳɹ���" << std::endl;
						system("pause");
						system("cls");
						break;
					case 2:
						std::cout << "�������µ�������" << std::endl;
						std::cin >> new_name;
						system("pause");
						system("cls");
						break;
					case 3:
						std::cout << "�������µ����䣺" << std::endl;
						std::cin >> new_age;
						system("pause");
						system("cls");
						break;
					case 4:
						std::cout << "�������µ��Ա�" << std::endl;
						std::cin >> new_gender;
						system("pause");
						system("cls");
						break;
					case 5:
						std::cout << "�������µĳɼ���" << std::endl;
						setScore(it->score_vec);
						system("pause");
						system("cls");
					case 0:
						flag = false;
						break;

					}
				}

				*it = Student(new_name, new_age, new_gender, new_ID, it->score_vec);
				std::cout << "�޸ĳɹ���" << std::endl;
				this->save();
				break;
			}
			else
			{
				std::cout << "��ѯʧ�ܣ����޴��ˣ�" << std::endl;
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
		s_v.resize(0); //�����ڳɼ������óɼ�
	}
	std::string course;
	int score;

	int score_num = 0;
	std::cout << "������Ҫ��ӵĿ�Ŀ����" << std::endl;
	std::cin >> score_num;

	for (int i = 0; i < score_num; ++i)
	{
		std::cout << "��Ŀ��_____\b\b\b\b\b";
		std::cin >> course;

		std::cout << "�ɼ���__\b\b";
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
		std::cout << "�ļ������ڻ��ļ���ʧ�ܣ�" << std::endl;
	}
	else
	{
		bool flag = false;
		std::cout << "������Ҫɾ����Ϣ��ѧ����ѧ�ţ�__________\b\b\b\b\b\b\b\b\b\b";
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
				std::cout << "ɾ���ɹ���" << std::endl;
				break;
			}
		}
		if (!flag)
		{
			std::cout << "ɾ��ʧ�ܣ�δ�ҵ���ѧ����" << std::endl;
		}
	}

	system("pause");
	system("cls");
}

void StuManger::sortInfo()
{
	if (this->isFileEmpty)
	{
		std::cout << "�ļ������ڻ��¼Ϊ�գ�" << std::endl;
		system("pause");
		system("clear");
	}
	else
	{
		std::cout << "��ѡ������ʽ��" << std::endl
			<< "1.��ѧ����������" << std::endl
			<< "2.��ѧ�Ž�������" << std::endl;

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

		std::cout << "����ɹ��������Ľ��Ϊ��" << std::endl;
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