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

    if (!isValidPath(argPath))
        return;

    currentPath = argPath;
    std::replace(currentPath.begin(), currentPath.end(), '\\', '/');
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
            lsExec();
            break;
        case static_cast<uint32_t>(commandsEnum::Clear):
            system("CLS");
            break;
        case static_cast<uint32_t>(commandsEnum::Touch):
            touchExec(argsString);
            break;
        case static_cast<uint32_t>(commandsEnum::Mkdir):
            mkdirExec(argsString);
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

bool isValidArgs(std::istringstream& argsString)
{
    return true;
}

bool isValidPath(std::string& path)
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

void lsExec()
{
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(currentPath))
    {
        if (std::filesystem::is_directory(entry.status()))
        {
            std::cout << BLUE_TEXT << "[DIR]\t" << entry.path().filename().string() << '/' <<  NORMAL_TEXT << '\n';
        }
        else
        {
            std::cout << "[FILE]\t" << entry.path().filename().string() << '\n';
        }
    }
    std::cout << std::endl;
}

void mkdirExec(std::istringstream& argsString)
{
    std::filesystem::path dirPath{currentPath};
    std::string dirName{};
    argsString >> dirName;
    dirPath /= dirName;

    if (std::filesystem::exists(dirPath))
    {
        std::cerr << RED_TEXT << "Error: Directory [" << dirName << "] already exists" << NORMAL_TEXT << std::endl;
        return;
        
    }

    std::filesystem::create_directory(dirPath);
}

void mvExec(){}

void rmExec(){}

void setArgVec(std::vector<std::string>& inputArgs, std::istringstream& argsString)
{
    if (!isValidArgs(argsString))
    {
        std::string args{};
        std::getline(argsString, args);
        utility::trimString(args);
        std::cerr << RED_TEXT << "Error: " << args << " is not a valid arg" << NORMAL_TEXT << std::endl;
        return;
    }
    std::string arg{};
    while (argsString >> arg)
    {
        inputArgs.push_back(arg);
    }
}

void touchExec(std::istringstream& argsString)
{
    std::filesystem::path filePath{currentPath};
    std::string fileName{};
    argsString >> fileName;
    filePath /= fileName;

    if (std::filesystem::exists(filePath))
    {
        std::cerr << RED_TEXT << "Error: File [" << fileName << "] already exists" << NORMAL_TEXT << std::endl;
        return;
    }
   
    std::ofstream file(filePath, std::fstream::app);
}


