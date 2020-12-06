#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>

int main(int argc, char* argv[])
{
	std::ifstream inputFile("../Day6/input.txt");
	std::string line, uniqueCustoms, groupCustoms;
	int anyoneSum = 0, everyoneSum = 0, nbOfPeopleInGroup = 0;

	while (getline(inputFile, line))
	{
		if(!line.empty())
		{
			groupCustoms += line;
			nbOfPeopleInGroup++;
		}

		if (line.empty() || inputFile.eof())
		{
			std::sort(groupCustoms.begin(), groupCustoms.end());
			std::unique_copy(groupCustoms.begin(), groupCustoms.end(), std::back_inserter(uniqueCustoms));
			for (char c : uniqueCustoms)
			{
				if (std::count(groupCustoms.begin(), groupCustoms.end(), c) == nbOfPeopleInGroup)
				{
					everyoneSum++;
				}
			}

			anyoneSum += uniqueCustoms.size();
			groupCustoms.clear();
			uniqueCustoms.clear();
			nbOfPeopleInGroup = 0;
		}
	}

	std::cout << "Part 1 : Custom Customs : " << anyoneSum << std::endl;
	std::cout << "Part 2 : Custom Customs : " << everyoneSum << std::endl;

	std::cin.get();
	return 0;
}