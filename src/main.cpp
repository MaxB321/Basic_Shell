#include "pch.h"
#include "constants.h"
#include "command_handler.h"
#include "flags.h"


int main()
{
	std::string userInput{};

	while (PROGRAM_RUNNING)
	{
		std::cout << GREEN_TEXT << defaultPath << "> " << NORMAL_TEXT;
		std::cin >> userInput;
		auto arr_it{std::find(commands_start, commands_end, userInput)};
		if (arr_it == commands_end)
		{
			std::cerr << RED_TEXT << "Error: " << userInput << " is not a valid command" << NORMAL_TEXT << std::endl;
		}
		else
		{
			uint32_t element_index = static_cast<uint32_t>(arr_it - commands_start);
			commandHandler(element_index, userInput);
		}
	}

	return 0;
}
