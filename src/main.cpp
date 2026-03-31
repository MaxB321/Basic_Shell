#include "pch.h"
#include "constants.h"


int main()
{
	std::cout << defaultPath;
	std::string userInput{};

	while (true)
	{
		std::cin >> userInput;
		if (userInput == "exit")
		{
			break;
		}
	}
	

	return 0;
}
