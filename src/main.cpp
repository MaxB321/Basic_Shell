#include "pch.h"
#include "constants.h"
#include "command_handler.h"
#include "flags.h"


int main()
{
	std::string userInput{};
	std::string command{};
	std::vector<std::string> inputArgs{};
	inputArgs.reserve(5);

	while (PROGRAM_RUNNING)
	{
		std::cout << GREEN_TEXT << defaultPath << "> " << NORMAL_TEXT;
		std::getline(std::cin, userInput);
		std::istringstream inputStream(userInput);
		std::string arg{};
		inputStream >> command;
		while (inputStream >> arg)
		{
			inputArgs.push_back(arg);
		}

		auto arr_it{std::find(commands_start, commands_end, command)};

		if (arr_it == commands_end)
		{
			std::cerr << RED_TEXT << "Error: " << userInput << " is not a valid command" << NORMAL_TEXT << std::endl;
		}
		else
		{
			uint32_t command_index = static_cast<uint32_t>(arr_it - commands_start);
			commandHandler(command_index, inputArgs);
		}
		inputArgs.clear();
	}

	return 0;
}
