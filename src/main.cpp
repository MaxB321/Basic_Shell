#include "pch.h"
#include "constants.h"
#include "command_handler.h"
#include "flags.h"


void handleSigInt(int)
{
	std::signal(SIGINT, handleSigInt); // re-register signal to suppress default termination

	if (cmdHandlerFlags::commandExecuting)
	{
		cmdHandlerFlags::commandInterrupted = true;
	}
}


int main()
{
	std::signal(SIGINT, handleSigInt);

	std::string userInput{};
	std::string command{};
	std::vector<std::string> inputArgs{};
	inputArgs.reserve(5);
	std::replace(currentPath.begin(), currentPath.end(), '\\', '/');

	while (PROGRAM_RUNNING)
	{
		std::cout << GREEN_TEXT << currentPath << "> " << NORMAL_TEXT;

		std::getline(std::cin, userInput);

		if (std::cin.fail())
        {
            std::cin.clear();
            std::cout << std::endl;
            continue;
        }

		if (userInput.empty())
			continue;

		std::istringstream inputStream(userInput);
		inputStream >> command;
		std::istringstream& argsString{inputStream};

		auto arr_it{std::find(std::begin(commands), std::end(commands), command)};

		if (arr_it == std::end(commands))
		{
			std::cerr << RED_TEXT << "Error: " << userInput << " is not a valid command" << NORMAL_TEXT << std::endl;
		}
		else
		{
			uint32_t command_index = static_cast<uint32_t>(arr_it - std::begin(commands));
			cmdHandlerFlags::commandExecuting = true;
			commandHandler(command_index, inputArgs, argsString);
		}
		cmdHandlerFlags::commandInterrupted = false;
		cmdHandlerFlags::commandExecuting = false;
		inputArgs.clear();
	}

	return 0;
}
