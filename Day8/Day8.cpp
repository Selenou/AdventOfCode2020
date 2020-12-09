#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <functional>

int ComputeAccumulator(const std::vector<std::tuple<std::string, int>>& instructions, bool expectTerminate)
{
	int idx = 0, accumulator = 0;
	auto[op, arg] = instructions.at(idx); // C++ 17, could have used std::tie too
	std::vector<int> visited;

	while (std::find(visited.begin(), visited.end(), idx) == visited.end())
	{
		if (idx >= instructions.size())
		{
			return accumulator;
		}

		visited.push_back(idx);
		auto[op, arg] = instructions.at(idx);

		// Could have used a switch with an enum too but for only 3 opcodes it is fine I guess
		if (op == "acc")
		{
			accumulator += arg;
			idx++;
		}
		else if (op == "jmp")
		{
			idx += arg;
		}
		else
		{
			idx++;
		}

		//std::cout << "Op : " << op << ", Arg : " << arg << ", Idx : " << idx << std::endl;
	}

	return expectTerminate ? -1 : accumulator;
}

int TerminateProgram(const std::vector<std::tuple<std::string, int>>& instructions)
{
	std::vector<std::tuple<std::string, int>> instructionsCopy;
	int accumulator = 0, idx = 0;

	for (auto& instruction : instructions) 
	{
		instructionsCopy = instructions;
		std::string& op = std::get<0>(instructionsCopy[idx]);

		if (op == "jmp")
		{
			op = "nop";
		}
		else if (op == "nop")
		{
			op = "jmp";
		}
		else
		{
			idx++;
			continue;
		}

		accumulator = ComputeAccumulator(instructionsCopy, true);

		if (accumulator != -1)
		{
			return accumulator;
		}

		idx++;
	}

	return -1;
}

int main(int argc, char* argv[])
{
	std::vector<std::tuple<std::string, int>> instructions;
	std::string operation;
	char sign;
	int argument;

	std::ifstream inputFile("../Day8/input.txt");

	while (inputFile >> operation >> sign >> argument)
	{
		instructions.emplace_back(operation, sign == '+' ? argument : -argument);
	}

	std::cout << "Part 1 : Handheld Halting : " << ComputeAccumulator(instructions, false) << std::endl;
	std::cout << "Part 2 : Handheld Halting : " << TerminateProgram(instructions) << std::endl;

	std::cin.get();
	return 0;
}