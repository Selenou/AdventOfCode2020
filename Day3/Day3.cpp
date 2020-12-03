#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int GetTreeNb(int rightShift, int downShift, const std::vector<std::string>& biome)
{
	int x = 0, y = 0;
	int totalTrees = 0;
	int biomeWidth = biome.at(0).length();
	int biomeHeight = biome.size();

	for (auto& biomeLine : biome)
	{
		x += rightShift;
		y += downShift;

		if (y >= biomeHeight) {
			break;
		}

		if (biome.at(y).at(x % biomeWidth) == '#')
		{
			totalTrees++;
		}
	}

	return totalTrees;
}

int main(int argc, char* argv[])
{
	std::vector<std::string> biome;
	std::string biomeLine;
	std::ifstream inputFile("../Day3/input.txt");

	while (inputFile >> biomeLine)
	{
		biome.emplace_back(biomeLine);
	}

	unsigned int r1d1 = GetTreeNb(1, 1, biome);
	unsigned int r3d1 = GetTreeNb(3, 1, biome);
	unsigned int r5d1 = GetTreeNb(5, 1, biome);
	unsigned int r7d1 = GetTreeNb(7, 1, biome);
	unsigned int r1d2 = GetTreeNb(1, 2, biome);

	unsigned int totalTrees = r1d1 * r3d1 * r5d1 * r7d1 * r1d2;

	std::cout << "Part 1 : Encountered trees : " << std::to_string(r3d1) << std::endl;
	std::cout << "Part 2 : Encountered trees : " << std::to_string(totalTrees) << std::endl;

	std::cin.get();
	return 0;
}