#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
	int min = 0, max = 0;
	int oldPolicyCounter = 0, newPolicyCounter = 0;
	char discriminant;
	std::string password;
	int discriminantCount = 0;

	std::ifstream inputFile("../Day2/input.txt");

	// first discriminant contains/skips the '-'
	// password is here twice in order to skip the whitespace between ':' and the current password
	while (inputFile >> min >> discriminant >> max >> discriminant >> password >> password)
	{
		// Old policy
		discriminantCount = std::count(password.begin(), password.end(), discriminant);
		if ((discriminantCount - max) * (discriminantCount - min) <= 0) // is in range ?
		{
			oldPolicyCounter++;
		}

		// New policy
		if ((password.at(min-1) == discriminant) != (password.at(max-1) == discriminant)) // XOR
		{
			newPolicyCounter++;
		}
	}

	std::cout << "Old Password Policy Solution : " << std::to_string(oldPolicyCounter) << std::endl;
	std::cout << "New Password Policy Solution : " << std::to_string(newPolicyCounter) << std::endl;

	// Dont need to close inputFile since its destructor will handle it (RAII)

	std::cin.get();
	return 0;
}