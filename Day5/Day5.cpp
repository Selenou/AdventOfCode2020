#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

void GetAllSeatId(const std::string& path, std::vector<int>& seatIds)
{
	std::ifstream inputFile(path);
	std::string seatData;

	while (inputFile >> seatData)
	{
		for (int i = 0; i < seatData.size(); i++)
		{
			seatData.at(i) = (seatData.at(i) == 'B' || seatData.at(i) == 'R') ? '1' : '0';
		}

		seatIds.push_back(std::stoi(seatData, nullptr, 2));
	}
}

int main(int argc, char* argv[])
{
	std::vector<int> seatIds;
	GetAllSeatId("../Day5/input.txt", seatIds);
	std::sort(seatIds.begin(), seatIds.end());

	auto ourSeatId = std::adjacent_find(seatIds.begin(), seatIds.end(), [](int l, int r) 
	{
		return l + 1 < r; 
	});

	std::cout << "Part 1 : Max seat ID : " << std::to_string(seatIds[seatIds.size() - 1]) << std::endl;
	std::cout << "Part 2 : Our seat ID : " << std::to_string(1+*ourSeatId) << std::endl;

	std::cin.get();
	return 0;
}