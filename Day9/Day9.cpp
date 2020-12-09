#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

int FindBadNumber(const std::vector<long long>& nbList, int preambleSize)
{
	int result = 0;

	for (int i = preambleSize; i < nbList.size(); i++)
	{
		bool found = false;

		for (int j = i - preambleSize; j < i; j++)
		{
			if (found) break;
			
			for (int k = i - preambleSize; k < i; k++)
			{
				if (nbList[k] == nbList[j]) continue;

				if (nbList[i] == nbList[j] + nbList[k])
				{
					//std::cout << "found : " << nbList[i] << " = " << nbList[j] << " + " << nbList[k] << std::endl;
					found = true;
					break;
				}
			}
		}

		if (!found)
		{
			//std::cout << "result : " << nbList[i] << std::endl;
			result = nbList[i];
			break;
		}
	}

	return result;
}

int FindSum(const std::vector<long long>& nbList, long long target)
{
	std::vector<long long> tmpVect;
	long long sum = 0, current = 0;

	auto itr = std::find(nbList.begin(), nbList.end(), target);
	int targetIndex = std::distance(nbList.begin(), itr);

	for (int i = 0; i < targetIndex; i++)
	{
		int j = i;

		while (sum < target)
		{
			current = nbList[j];
			sum += current;
			//std::cout << j << " "<< sum << std::endl;
			tmpVect.push_back(current);
			j++;
		}

		if (sum == target)
		{
			return tmpVect[0] + tmpVect[tmpVect.size() - 1];
		}
		else
		{
			sum = 0;
			tmpVect.clear();
		}
	}

	return -1;
}

int main(int argc, char* argv[])
{
	std::vector<long long> nbList;
	int nb;

	std::ifstream inputFile("../Day9/input.txt");

	while (inputFile >> nb)
	{
		nbList.push_back(nb);
	}

	long long res = FindBadNumber(nbList, 25);
	std::cout << "Part 1 : Encoding Error : " << res << std::endl;
	std::cout << "Part 2 : Encoding Error : " << FindSum(nbList, res) << std::endl;

	std::cin.get();
	return 0;
}