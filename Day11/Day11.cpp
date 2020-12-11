#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

enum SeatStatus
{
	Floor,
	Empty,
	Occupied
};

std::vector<std::vector<SeatStatus>> GetSeatLayout()
{
	std::vector<std::vector<SeatStatus>> seatLayout;

	std::ifstream inputFile("../Day11/input.txt");
	std::string line;

	while (std::getline(inputFile, line))
	{
		std::vector<SeatStatus> seatRow;

		for (const char& c : line)
		{
			switch (c)
			{
				case '.':
					seatRow.emplace_back(SeatStatus::Floor);
					break;
				case 'L':
					seatRow.emplace_back(SeatStatus::Empty);
					break;
				case '#':
					seatRow.emplace_back(SeatStatus::Occupied);
					break;
			}
		}
		seatLayout.emplace_back(std::move(seatRow));
	}

	return seatLayout;
}

int StabilizeChaos(std::vector<std::vector<SeatStatus>> seatLayout, bool (*seatRules) (int, int, const std::vector<std::vector<SeatStatus>>&))
{
	int changes = 0;
	std::vector<std::vector<SeatStatus>> oldSeatLayout{};

	// Apply Changes until no chaos
	do
	{
		oldSeatLayout = seatLayout;
		changes = 0;

		for (int i = 0; i < seatLayout.size(); i++)
		{
			for (int j = 0; j < seatLayout[i].size(); j++)
			{
				if (seatRules(i, j, oldSeatLayout))
				{
					changes++;

					switch (seatLayout[i][j]) 
					{
						case SeatStatus::Occupied:
							seatLayout[i][j] = SeatStatus::Empty;
							break;
						case SeatStatus::Empty:
							seatLayout[i][j] = SeatStatus::Occupied;
							break;
					}
				}
			}
		}
		std::cout << "Changes : " << changes << std::endl;
	} 
	while (changes != 0);

	// Compute occupied seat nb
	int occupiedSeatCpt = 0;
	for (int i = 0; i < seatLayout.size(); i++) 
	{
		for (int j = 0; j < seatLayout[i].size(); j++) 
		{
			if (seatLayout[i][j] == SeatStatus::Occupied)
			{
				occupiedSeatCpt++;
			}
		}
	}

	return occupiedSeatCpt;
}

bool FirstRule(int row, int col, const std::vector<std::vector<SeatStatus>>& layout)
{
	if (layout[row][col] == SeatStatus::Floor) 
		return false;

	int adjacent = 0;

	for (int i = row - 1; i <= row + 1; i++) 
	{
		for (int j = col - 1; j <= col + 1; j++) 
		{
			// I could have fill my vector with floor as trim to avoid some checks
			if ((i != -1 && j != -1) &&
				(i < layout.size() && j < layout[i].size()) &&
				(i != row || j != col) && 
				layout[i][j] == SeatStatus::Occupied)
			{
				adjacent++;
			}
		}
	}

	switch (layout[row][col]) 
	{
		case SeatStatus::Occupied :	return adjacent >= 4;
		case SeatStatus::Empty :	return adjacent == 0;
	}

	return false;
}

bool FoundOccupiedSeat(int row, int col, int rowOffset, int colOffset, const std::vector<std::vector<SeatStatus>>& layout)
{
	if ((row <= 0 && rowOffset < 0) || (row >= layout.size()-1 && rowOffset > 0))
		return false;

	if ((col <= 0 && colOffset < 0) || (col >= layout[0].size()-1 && colOffset > 0))
		return false;

	row += rowOffset;
	col += colOffset;

	int rowMax = layout.size() - 1;
	int colMax = layout[0].size() - 1;

	while (((row < rowMax && rowOffset > 0) || (row > 0 && rowOffset < 0) || rowOffset == 0) &&
		((col < colMax && colOffset > 0) || (col > 0 && colOffset < 0) || colOffset == 0) &&
		layout[row][col] == SeatStatus::Floor)
	{
		row += rowOffset;
		col += colOffset;
	}

	return layout[row][col] == SeatStatus::Occupied;
}

bool SecondRule(int row, int col, const std::vector<std::vector<SeatStatus>>& layout)
{
	if (layout[row][col] == SeatStatus::Floor)
		return false;

	int adjacent = 0;

	for (int i : {-1, 0, 1})
	{
		for (int j : {-1, 0, 1})
		{
			if (i == 0 && j == 0) 
				continue;
			if(FoundOccupiedSeat(row, col, i, j, layout))
				adjacent++;
		}
	}

	switch (layout[row][col]) 
	{
		case SeatStatus::Occupied:	return adjacent >= 5;
		case SeatStatus::Empty:		return adjacent == 0;
	}

	return false;
}

int main(int argc, char* argv[])
{
	auto layout = GetSeatLayout();

	std::cout << "Part 1 : Seating System : " << StabilizeChaos(layout, FirstRule) << std::endl;
	std::cout << "Part 2 : Seating System : " << StabilizeChaos(layout, SecondRule) << std::endl;

	std::cin.get();
	return 0;
}