#pragma once
#include <fstream>
#include <string>

class Monster
{
private:
	std::string mName;
	int mLevel;
	int mHP;
	int mMP;

public:
	Monster() 
		: mName{}, mLevel{}, mHP{}, mMP{}
	{}

	Monster(std::string name, int level, int hp, int mp)
		: mName{ name }, mLevel{ level }, mHP{ hp }, mMP{ mp }
	{
	}

	std::ifstream& ReadBinary(std::ifstream& ifs);
	std::ofstream& WriteBinary(std::ofstream& ofs);
};

std::ifstream& Monster::ReadBinary(std::ifstream& ifs)
{
	int strLen{};
	ifs.read(reinterpret_cast<char*>(&strLen), sizeof(int));
	mName.resize(strLen);
	ifs.read(&mName[0], strLen);

	ifs.read(reinterpret_cast<char*>(&mLevel), sizeof(int));
	ifs.read(reinterpret_cast<char*>(&mHP), sizeof(int));
	ifs.read(reinterpret_cast<char*>(&mMP), sizeof(int));

	return ifs;
}

std::ofstream& Monster::WriteBinary(std::ofstream& ofs)
{
	// name, level, hp, mp
	int strLen{ static_cast<int>(mName.size()) };
	ofs.write(reinterpret_cast<char*>(&strLen), sizeof(int));
	ofs.write(mName.c_str(), strLen);

	ofs.write(reinterpret_cast<char*>(&mLevel), sizeof(int));
	ofs.write(reinterpret_cast<char*>(&mHP), sizeof(int));
	ofs.write(reinterpret_cast<char*>(&mMP), sizeof(int));

	return ofs;
}

std::ifstream& operator >> (std::ifstream& ifs, Monster& monster)
{
	return monster.ReadBinary(ifs);
}

std::ofstream& operator << (std::ofstream& ofs, Monster& monster)
{
	return monster.WriteBinary(ofs);
}