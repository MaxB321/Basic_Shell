#include "command_handler.h"
#include "constants.h"
#include "enums.h"
#include "flags.h"
#include "utility.h"


std::string currentPath{std::getenv("USERPROFILE")};


void catExec(){} 
void cdExec(std::istringstream& argsString)
{
    std::string argPath{};
    std::getline(argsString, argPath);
    utility::trimString(argPath);

    if (!validatePath(argPath))
        return;

    currentPath = argPath;
}

void commandHandler(uint32_t commandIndex, std::vector<std::string>& inputArgs, std::istringstream& argsString)
{
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
    if (!validateArgs(argsString))
    {
        std::string args{};
        std::getline(argsString, args);
        utility::trimString(args);
        std::cerr << RED_TEXT << "Error: " << args << " is not a valid path" << NORMAL_TEXT << std::endl;
        return;
    }
    std::string arg{};
    while (argsString >> arg)
    {
        inputArgs.push_back(arg);
    }
}

void touchExec()
{
    
}

bool validateArgs(std::istringstream& argsString)
{
    return true;
}

bool validatePath(std::string& path)
{
    try
    {
        std::filesystem::current_path(path);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }

    return true;
}
