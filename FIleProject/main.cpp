#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

// fstream
// good()
// fail()
// eof() -> end of file
// bad() 
// rdstate()
// Comma Sepereated Values => CSV

class Monster
{
private:
	std::string mName;
	int mLevel;
	int mHP;
	int mMP;

public:
	Monster()
	{
	}

	Monster(std::string name, int level, int hp, int mp)
		: mName{ name }, mLevel{ level }, mHP{ hp }, mMP{ mp }
	{
	}

	void SetName(std::string name) { mName = name; }
	void SetLevel(int level) { mLevel = level; }
	void SetHP(int hp) { mHP = hp; }
	void SetMP(int mp) { mMP = mp; }

	void Print()
	{
		std::cout << mName << ", " << mLevel << ", " << mHP << ", "
			<< mHP << ", " << mMP << std::endl;
	}

	friend std::istream& operator >>(std::istream& is, Monster& monster);
	friend std::ostream& operator <<(std::ostream& os, Monster& monster);
};

std::istream& operator >>(std::istream& is, Monster& monster)
{
	std::string buffer;

	try
	{
		std::getline(is, buffer, ',');
		monster.mName = buffer;

		std::getline(is, buffer, ',');
		monster.mLevel =std::stoi(buffer);

		std::getline(is, buffer, ',');
		monster.mHP = std::stoi(buffer);

		std::getline(is, buffer);
		monster.mMP = std::stoi(buffer);
	}
	catch(std::exception e)
	{
		std::cout << "������ ������ �߸��Ǿ����ϴ�." << std::endl;
		std::cout << e.what() << std::endl;
	}

	return is;
}

std::ostream& operator <<(std::ostream& os, Monster& monster)
{
	try
	{
		os << monster.mName << ", " << monster.mLevel << ", " << monster.mHP << ", "
			<< monster.mHP << ", " << monster.mMP << std::endl;
	}
	catch (std::exception e)
	{
		std::cout << "��Ʈ�� ���忡 ������ �߻��Ͽ����ϴ�." << std::endl;
		std::cout << e.what() << std::endl;
	}

	return os;
}

bool LoadFile(const char* filename, std::vector<Monster>& vector)
{
	// 1. ���� ��Ʈ�� ��ü ����(�Է�)
	std::ifstream ifs;
	ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		ifs.open(filename);

		std::string buffer;

		std::getline(ifs, buffer);
		while (!ifs.eof())
		{
			Monster monster;

			ifs >> monster;

			vector.push_back(monster);
		}

		// 3. ���� ��Ʈ�� ��ü ����(���� �ݱ�)
		ifs.close();
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;

		ifs.close();
		return false;
	}

	return true;
}

bool SaveFile(const char* filename, std::vector<Monster>& monsters)
{
	std::ofstream ofs;
	ofs.exceptions(std::ofstream::badbit);

	try
	{
		ofs.open(filename);
		ofs << "--- MONSTER DATA ---" << std::endl;
		for (auto& e : monsters)
		{
			ofs << e;
		}
		ofs.close();
	}
	catch (std::exception e)
	{
		std::cout << "���� ���� ������ �߻��Ͽ����ϴ�." << std::endl;
		std::cout << e.what() << std::endl;
		ofs.close();
		return false;
	}

	return true;
}


int main()
{
	std::vector<Monster> monsters;

	// Windows ǥ���
	// LoadFile("C:\\Programming\\01\.Cpp\\FileProject\\Data\\SimpleData.txt");

	// Unix ǥ���
	// LoadFile("C:/Users/catal/OneDrive/FileProject/SimpleData.txt", monsters);

	// ���� ���丮 - Current Directory
	LoadFile("Data/SimpleData.txt", monsters);

	for (auto& e : monsters)
	{
		e.Print();
	}

	monsters.push_back({ "ORC", 20, 20, 20 });

	SaveFile("Data/SimpleData.txt", monsters);
}