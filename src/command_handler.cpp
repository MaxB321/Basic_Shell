#include "command_handler.h"
#include "constants.h"
#include "enums.h"
#include "flags.h"
#include "utility.h"


char* currentPath{std::getenv("USERPROFILE")};


void catExec(){} 
void cdExec(std::istringstream& argsString)
{
    std::string argPath{};
    std::getline(argsString, argPath);
    utility::trimString(argPath);

    if (!validatePath(argPath))
        std::cerr << RED_TEXT << "Error: " << argPath << " is not a valid path" << NORMAL_TEXT << std::endl;
        return;
    
    
}

void commandHandler(uint32_t commandIndex, std::vector<std::string>& inputArgs, std::istringstream& argsString)
{
    if (!validateArgs())
        return;

    switch (commandIndex)
    {
        case static_cast<uint32_t>(commandsEnum::Exit):
            PROGRAM_RUNNING = false;
            break;
        case static_cast<uint32_t>(commandsEnum::Echo):
            echoExec(argsString);
            break;
        case static_cast<uint32_t>(commandsEnum::Pwd):
            std::cout << "Path: " << currentPath << '\n';
            break;
        case static_cast<uint32_t>(commandsEnum::Cd):
            cdExec(argsString);
            break;
        case static_cast<uint32_t>(commandsEnum::Ls):
            break;
        case static_cast<uint32_t>(commandsEnum::Clear):
            system("CLS");
            break;
        case static_cast<uint32_t>(commandsEnum::Touch):
            break;
        case static_cast<uint32_t>(commandsEnum::Mkdir):
            break;
        case static_cast<uint32_t>(commandsEnum::Rm):
            break;
        case static_cast<uint32_t>(commandsEnum::Cat):
            break;
        case static_cast<uint32_t>(commandsEnum::Grep):
            break;
        case static_cast<uint32_t>(commandsEnum::Cp):
            break;
        case static_cast<uint32_t>(commandsEnum::Mv):
            break;
    }
}

void cpExec(){}

void echoExec(std::istringstream& argsString)
{
    std::string echoOutput{};
	std::getline(argsString, echoOutput);
    utility::trimString(echoOutput);

    std::cout << echoOutput << '\n';
}

void grepExec(){}
void lsExec(){}
void mkdirExec(){}
void mvExec(){}

void rmExec(){}

void setArgVec(std::vector<std::string>& inputArgs, std::istringstream& argsString)
{
    std::string arg{};
    while (argsString >> arg)
    {
        inputArgs.push_back(arg);
    }
}

void touchExec()
{
    
}

bool validateArgs()
{
    return true;
}

bool validatePath(std::string& path)
{

    return false;
}
