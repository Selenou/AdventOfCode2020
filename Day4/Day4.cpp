#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <sstream>
#include <algorithm>
#include <cctype>


///////////////////////////////////////////////////////////
///////////////////////PASSPORT CLASS//////////////////////
///////////////////////////////////////////////////////////

class Passport
{
public:
	Passport(const std::map<std::string, std::string>& data)
	{
		auto it = data.find("byr");
		m_Byr = it != data.end() ? it->second : "";

		it = data.find("iyr");
		m_Iyr = it != data.end() ? it->second : "";

		it = data.find("eyr");
		m_Eyr = it != data.end() ? it->second : "";

		it = data.find("hgt");
		m_Hgt = it != data.end() ? it->second : "";

		it = data.find("hcl");
		m_Hcl = it != data.end() ? it->second : "";

		it = data.find("ecl");
		m_Ecl = it != data.end() ? it->second : "";

		it = data.find("pid");
		m_Pid = it != data.end() ? it->second : "";

		it = data.find("cid");
		m_Cid = it != data.end() ? it->second : "";
	}

	bool IsValid()
	{
		return !m_Byr.empty() && !m_Iyr.empty() && !m_Eyr.empty() && !m_Hgt.empty() && !m_Hcl.empty() && !m_Ecl.empty() && !m_Pid.empty();
	}

	bool IsValidStrict()
	{
		if (!IsValid()) 
			return false;

		if (std::stoi(m_Byr) < 1920 || std::stoi(m_Byr) > 2002) 
			return false;

		if (std::stoi(m_Iyr) < 2010 || std::stoi(m_Iyr) > 2020)
			return false;

		if (std::stoi(m_Eyr) < 2020 || std::stoi(m_Eyr) > 2030)
			return false;

		std::string heightUnit = m_Hgt.substr(m_Hgt.size() - 2);
		int height = std::stoi(m_Hgt);

		if (heightUnit == "cm")
		{
			if (height < 150 || height > 193)
			{
				return false;
			}
		}	
		else if (heightUnit == "in")
		{
			if (height < 59 || height > 76)
			{
				return false;
			}
		}
		else
		{
			return false;
		}

		char color[7];
		if (sscanf_s(m_Hcl.c_str(), "#%6[a-f0-9]", &color, sizeof(color)) == 0)
		{
			return false;
		}
		
		std::vector<std::string> eyeColor = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
		if (std::find(eyeColor.begin(), eyeColor.end(), m_Ecl) == eyeColor.end())
			return false;

		if (m_Pid.size() != 9 || !std::all_of(m_Pid.begin(), m_Pid.end(), std::isdigit))
			return false;

		return true;
	}

private:
	std::string m_Byr; //Birth Year
	std::string m_Iyr; //Issue Year
	std::string m_Eyr; //Expiration Year
	std::string m_Hgt; //Height
	std::string m_Hcl; //Hair Color
	std::string m_Ecl; //Eye Color
	std::string m_Pid; //Passport ID
	std::string m_Cid; //Country ID
};

///////////////////////////////////////////////////////////
////////////////////////////MAIN///////////////////////////
///////////////////////////////////////////////////////////


std::vector<std::unique_ptr<Passport>> ParseInput(const std::string& path)
{
	std::vector<std::unique_ptr<Passport>> passports;
	std::ifstream inputFile(path);
	std::string bufferStr;
	std::map<std::string, std::string> passwordTokens;
	std::string passportData;

	passportData.reserve(1000);

	while (getline(inputFile, bufferStr))
	{
		if (bufferStr.size() > 0)
		{
			passportData += bufferStr;
			passportData += " ";
		}

		if (bufferStr.size() == 0 || inputFile.eof())
		{
			std::stringstream ss(passportData);
			std::string token;

			while (ss >> token)
			{
				int delimiterPosition = token.find(':');
				passwordTokens.emplace(token.substr(0, delimiterPosition), token.substr(delimiterPosition + 1, token.length()));
			}
			
			passports.emplace_back(std::make_unique<Passport>(passwordTokens));

			passportData.clear();
			passwordTokens.clear();
		}
	}

	return passports;
}

int main(int argc, char* argv[])
{
	std::vector<std::unique_ptr<Passport>> passports = ParseInput("../Day4/input.txt");

	int validCpt = 0;
	int validStrictCpt = 0;
	for (auto& passport : passports)
	{
		validCpt += (*passport).IsValid();
		validStrictCpt += (*passport).IsValidStrict();
	}

	std::cout << "Part 1 : Valid Passports : " << std::to_string(validCpt) << std::endl;
	std::cout << "Part 2 : Valid Passports : " << std::to_string(validStrictCpt) << std::endl;

	std::cin.get();
	return 0;
}