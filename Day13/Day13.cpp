#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

int main(int argc, char* argv[])
{
	// Read input
	std::ifstream inputFile("../Day13/input.txt");
	std::string strBuffer;

	std::getline(inputFile, strBuffer);
	int timestamp = std::stoi(strBuffer);

	std::getline(inputFile, strBuffer);
	std::stringstream busesLine(strBuffer);
	std::vector<std::pair<int, int>> buses;
	int delta = -1;

	while (std::getline(busesLine, strBuffer, ','))
	{
		delta++;
		if (strBuffer == "x") continue;
		buses.push_back(std::make_pair(std::stoi(strBuffer), delta));
	}

	// Part1

	int waitingTime = INT_MAX, earlierBusId = 0;

	for (auto bus : buses)
	{
		int wait = bus.first - timestamp % bus.first;

		if (wait < waitingTime)
		{
			waitingTime = wait;
			earlierBusId = bus.first;
		}
	}

	std::cout << "Part 1 : Shuttle Search : " << waitingTime * earlierBusId << std::endl;

	// Part2

	long long time = 0;
	long long stride = 1;

	for (auto bus : buses)
	{
		while ((time + bus.second) % bus.first != 0)
		{
			time += stride;
		}
		stride *= bus.first;
	}

	std::cout << "Part 2 : Shuttle Search : " << time << std::endl;

	std::cin.get();
	return 0;
}