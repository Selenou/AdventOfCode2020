#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

#define PI std::atan(1.0)*4

enum Direction
{
	East,
	South,
	West,
	North
};

int GetManhattanDistance(const std::vector<std::pair<char, int>>& instructions)
{
	int x = 0, y = 0;
	Direction currentDir = Direction::East;

	for (auto instruction : instructions)
	{
		switch (instruction.first)
		{
			case 'N': y += instruction.second; break;
			case 'S': y -= instruction.second; break;
			case 'E': x += instruction.second; break;
			case 'W': x -= instruction.second; break;
			case 'L': currentDir = static_cast<Direction>((4 + currentDir - instruction.second / 90) % 4); break;
			case 'R': currentDir = static_cast<Direction>((4 + currentDir + instruction.second / 90) % 4); break;
			case 'F': 
				switch (currentDir)
				{
					case Direction::North:	y += instruction.second; break;
					case Direction::South :	y -= instruction.second; break;
					case Direction::East :	x += instruction.second; break;
					case Direction::West :	x -= instruction.second; break;
				};
				break;
		}
		//std::cout << x << " " << y << std::endl;
	}

	return abs(x) + abs(y);
}

int GetWaypointManhattanDistance(const std::vector<std::pair<char, int>>& instructions)
{
	int x = 0, y = 0;
	int wpx = 10, wpy = 1;
	int deltaX = 0, deltaY = 0;

	for (auto instruction : instructions)
	{
		switch (instruction.first)
		{
			case 'N': wpy += instruction.second; break;
			case 'S': wpy -= instruction.second; break;
			case 'E': wpx += instruction.second; break;
			case 'W': wpx -= instruction.second; break;
			case 'L':
			case 'R':
			{
				int multiplier = instruction.first == 'R' ? -1 : 1; // if turn right, inverse angle
				float angleDeg = multiplier * instruction.second * PI / 180.0;
				int c = cos(angleDeg);
				int s = sin(angleDeg);
				int px = wpx * c - wpy * s;
				int py = wpx * s + wpy * c;
				wpx = px;
				wpy = py;
				break;
			}
			case 'F': 
				deltaX = instruction.second * wpx;
				deltaY = instruction.second * wpy;
				x += deltaX;
				y += deltaY;
				break;
		}
		//std::cout << x << " " << y << std::endl;
	}

	return abs(x) + abs(y);
}

int main(int argc, char* argv[])
{
	std::vector<std::pair<char, int>> instructions;
	
	std::ifstream inputFile("../Day12/input.txt");
	char action;
	int value;

	while (inputFile >> action >> value)
	{
		instructions.emplace_back(std::make_pair(action , value));
	}

	std::cout << "Part 1 : Rain Risk : " << GetManhattanDistance(instructions) << std::endl;
	std::cout << "Part 2 : Rain Risk : " << GetWaypointManhattanDistance(instructions) << std::endl;

	std::cin.get();
	return 0;
}