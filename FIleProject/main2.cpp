#include <iostream>
#include <vector>
#include "Monster.h"

// 파일 헤더 - POD
struct Header
{
	int version{ 1 };
	int itemCount{};
};

using Monsters = std::vector<Monster>;

bool SaveToFile(const char* filename, Monsters& monsters)
{
	std::ofstream ofs;
	ofs.exceptions(std::ofstream::badbit | std::ofstream::failbit);

	try
	{
		ofs.open(filename, std::ofstream::binary);

		// 헤더 파일
		Header header{ 1, monsters.size() };
		ofs.write(reinterpret_cast<char*>(&header), sizeof(Header));

		for (auto e : monsters)
		{
			ofs << e;
		}

		ofs.close();
	}
	catch (std::exception e)
	{
		std::cout << "파일 저장 중에 에러가 발생했습니다." << std::endl;
		std::cout << e.what() << std::endl;

		ofs.close();
		return false;
	}

	return true;
}

bool LoadFromFile(const char* filename, Monsters& monsters)
{
	std::ifstream ifs;
	ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		ifs.open(filename, std::ifstream::binary);

		// 헤더
		Header header;
		ifs.read(reinterpret_cast<char*>(&header), sizeof(Header));

		for (int i = 0; i < header.itemCount; i++)
		{
			Monster monster;
			ifs >> monster;
			monsters.push_back(monster);
		}

		ifs.close();
	}
	catch (std::exception e)
	{
		std::cout << "파일을 읽는 도중 에러가 발생하였습니다." << std::endl;
		std::cout << e.what() << std::endl;

		ifs.close();
		return false;
	}

	return true;
}

int main()
{
	Monsters monsters
	{
		{"JELLY", 1, 1, 1},
		{"WOLF", 5, 5, 5},
		{"DEMON", 10, 10, 10}
	};

	SaveToFile("Data/SimpleData.dat", monsters);

	monsters.clear();
	LoadFromFile("Data/SimpleData.dat", monsters);
}