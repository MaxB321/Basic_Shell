#include "pch.h"
#include "constants.h"


int main()
{
	std::string userInput{};

	while (true)
	{
		std::cout << defaultPath << "> ";
		std::cin >> userInput;
		if (std::find(commands_start, commands_end, userInput) == commands_end)
		{
			std::cerr << "Error: " << userInput << " is not a valid command" << std::endl;
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
