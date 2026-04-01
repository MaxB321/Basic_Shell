#include "pch.h"
#include "constants.h"


int main()
{
	std::string userInput{};

	while (true)
	{
		std::cout << GREEN_TEXT << defaultPath << "> " << NORMAL_TEXT;
		std::cin >> userInput;
		if (std::find(commands_start, commands_end, userInput) == commands_end)
		{
			std::cerr << RED_TEXT << "Error: " << userInput << " is not a valid command" << NORMAL_TEXT << std::endl;
		}
		else
		{
			std::cout << "valid" << std::endl; // replace with a command handler
		}

		if (userInput == "exit")
		{
			break;
		}
	}
	

	return 0;
}
