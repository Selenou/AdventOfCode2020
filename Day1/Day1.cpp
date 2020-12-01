#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

void ReadFile(std::vector<int>& values)
{
	std::ifstream inputFile;
	inputFile.open("../Day1/input.txt");

	std::string line;

	if (inputFile.is_open())
	{
		while (getline(inputFile, line))
		{
			values.push_back(atoi(line.c_str()));
		}
	}
	else
	{
		std::cerr << "Cannot open input file" << std::endl;
	}

	inputFile.close();
}

int TwoSum(std::vector<int>& values, int sumTarget)
{
	int siblingTarget;
	bool siblingFound = false;

	for(int value : values)
	{
		siblingTarget = sumTarget - value;
		siblingFound = std::binary_search(values.begin(), values.end(), siblingTarget);

		if(siblingFound)
		{
			return value * siblingTarget;
		}
	}

	return -1;
}

int ThreeSum(std::vector<int>& values, int sumTarget)
{
	int siblingTarget;
	bool siblingFound = false;

	for (auto i = values.begin(); i != values.end(); i++)
	{
		for (auto j = i + 1; j != values.end(); j++)
		{
			siblingTarget = sumTarget - *i - *j;
			siblingFound = std::binary_search(values.begin(), values.end(), siblingTarget);

			if (siblingFound)
			{
				return (*i) * (*j) * siblingTarget;
			}
		}
	}

	return -1;
}

int main(int argc, char* argv[])
{
	// Fetch data
	std::vector<int> values;
	ReadFile(values);
	std::sort(values.begin(), values.end());

	int solution = TwoSum(values, 2020);
	std::cout << "TwoSum Solution : " << std::to_string(solution) << std::endl;
	
	solution = ThreeSum(values, 2020);
	std::cout << "ThreeSum Solution : " << std::to_string(solution) << std::endl;

	std::cin.get();
	return 0;
}