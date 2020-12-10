#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_map>

// Global 
std::unordered_map<int, long long> memory;
std::vector<int> adaptersVector;

int FindSum()
{
	int oneJoltCpt = 0, threeJoltCpt = 1; // device's built-in adapter is always 3
	int mem = 0;

	for (auto adapter : adaptersVector)
	{
		if (adapter - mem == 1) oneJoltCpt++;
		else threeJoltCpt++;

		mem = adapter;
	}

	return oneJoltCpt * threeJoltCpt;
}

// Not the fastest solution, it can be better
long long FindDistinctWays(int n)
{
	if (n < 0) return 0;
	if (n == 0) return 1;
	if (std::find(adaptersVector.begin(), adaptersVector.end(), n) == adaptersVector.end()) return 0; // if n is not in adaptersVector, dont compute

	auto itr = memory.find(n);
	if (itr != memory.end()) return itr->second; // if we have already computed the result, return it

	long long res = FindDistinctWays(n - 1) + FindDistinctWays(n - 2) + FindDistinctWays(n - 3); // delta can only be 1, 2 or 3 in this puzzle
	memory[n] = res; // add result in memory
	//std::cout << "Adding m[" << n << "] = " << res << " in memory" << std::endl;

	return res;
}

int main(int argc, char* argv[])
{
	std::ifstream inputFile("../Day10/input.txt");
	int adapters;

	while (inputFile >> adapters)
	{
		adaptersVector.push_back(adapters);
	}

	std::sort(adaptersVector.begin(), adaptersVector.end());

	std::cout << "Part 1 : Adapter Array : " << FindSum() << std::endl;
	std::cout << "Part 2 : Adapter Array : " << FindDistinctWays(adaptersVector[adaptersVector.size()-1]) << std::endl;

	std::cin.get();
	return 0;
}