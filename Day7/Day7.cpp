#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <functional>
#include <regex>
#include <unordered_map>

std::vector<std::string> consumedBags;

int GetBagsNbContainingTarget(std::unordered_map<std::string, std::vector<std::string>>& bagTable, const std::string& key)
{
	int res = 0;
	for (auto bag : bagTable)
	{
		for (auto const& vecValue : bag.second)
		{
			if(vecValue.find(key) != std::string::npos)
			{
				std::cout << "Found " << key << " in " << bag.first << std::endl;

				bool isAvailable = std::find(consumedBags.begin(), consumedBags.end(), bag.first) == consumedBags.end();
				consumedBags.emplace_back(bag.first);

				if (isAvailable)
				{
					res++;
					std::cout << "Looking for " << bag.first << std::endl;
					res += GetBagsNbContainingTarget(bagTable, bag.first);
				}
			}
		}
	}

	return res;
}

int GetBagsNbInsideTarget(std::unordered_map<std::string, std::vector<std::string>>& bagTable, const std::string& key, int size)
{
	int res = size;

	for (auto bag : bagTable[key])
	{
		auto& bagStr = bag;
		res += size * GetBagsNbInsideTarget(bagTable, bagStr.substr(2, bagStr.size() - 1), std::stoi(bagStr.substr(0,1)));
		//std::cout << "Nb of bag returned for " << bagStr.substr(2, bagStr.size() - 1) << " : " << res << std::endl;
	}
	
	return res;
}

int main(int argc, char* argv[])
{
	std::ifstream inputFile("../Day7/input.txt");
	std::string line;

	std::unordered_map<std::string, std::vector<std::string>> bagTable;

	while (getline(inputFile, line))
	{
		std::smatch colorMatch;
		std::regex_search(line, colorMatch, std::regex("(.+?) bag"));

		std::string bagContentStr = colorMatch.suffix().str();
		std::regex contentMatch = std::regex("(\\d+) ([a-z]+ [a-z]+ bag)");
		std::sregex_iterator bagRgxIteratorBegin(bagContentStr.begin(), bagContentStr.end(), contentMatch), bagRgxIteratorEnd;
		std::vector<std::string> bagContent {};

		for (; bagRgxIteratorBegin != bagRgxIteratorEnd; bagRgxIteratorBegin++)
		{
			bagContent.push_back((*bagRgxIteratorBegin)[0]);
		}

		bagTable[colorMatch[0]] = bagContent;
	}
	
	std::cout << "Part 1 : Handy Haversacks : " << GetBagsNbContainingTarget(bagTable, "shiny gold bag") << std::endl;
	std::cout << "Part 2 : Handy Haversacks : " << GetBagsNbInsideTarget(bagTable, "shiny gold bag", 1) - 1 << std::endl;

	std::cin.get();
	return 0;
}