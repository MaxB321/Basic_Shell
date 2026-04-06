#include "command_handler.h"
#include "constants.h"
#include "enums.h"
#include "flags.h"
#include "utility.h"


std::string currentPath{std::getenv("USERPROFILE")};


void catExec(std::istringstream& argsStringStream)
{
    std::filesystem::path filePath{currentPath};
    std::string fileName{};
    argsStringStream >> fileName;
    filePath /= fileName;

    if (!std::filesystem::exists(filePath))
    {
        std::cerr << RED_TEXT << "Error: File [" << fileName << "] does not exist" << NORMAL_TEXT << std::endl;
        return;
    }
    std::ifstream fileStream(filePath, std::ios::in);
    if (!fileStream)
    {
        std::cerr << RED_TEXT << "Error: Failed to Open File [" << fileName << "]" << NORMAL_TEXT << std::endl;
        return;
    }
    
    std::string line{};
    while (std::getline(fileStream, line))
    {
        std::cout << line << '\n';
    }
    std::cout << std::endl;
}

void cdExec(uint32_t& commandIndex, std::istringstream& argsStringStream)
{
    std::string arg{};
    std::getline(argsStringStream, arg);
    utility::trimString(arg);

    if (isValidArgs(commandIndex, arg))
    {
        std::filesystem::path curPath{currentPath};
        if ((arg == "..") && curPath.has_parent_path())
        {
            std::filesystem::path parentPath{curPath.parent_path()};
            currentPath = parentPath.string();
        }
        else if (arg == "/" && curPath.has_root_path())
        {
            std::filesystem::path rootPath{curPath.root_path()};
            currentPath = rootPath.string();
        }

        return;
    }

    std::string& argPath{arg};

    if (!isValidPath(argPath))
    {
        if ((argPath[0] == '.') && (argPath[1] == '/'))
        {
            handleRelativePathing(argPath);
            return;
        }

        std::string tempPath{currentPath + '/' + argPath};
        if (isValidPath(tempPath))
        {
            handleRelativePathing(tempPath);
            return;
        }

        std::cerr << RED_TEXT << "Error: " << argPath << " is not a valid path." << NORMAL_TEXT << std::endl;
        return;
    }    

    currentPath = argPath;
    std::replace(currentPath.begin(), currentPath.end(), '\\', '/');
    
    std::filesystem::path pathObj{currentPath};
    if (pathObj.parent_path() == pathObj.root_path())
    {
        if (currentPath.substr(2, 2) == "//")
            currentPath.erase(3, 1);
    }
    
    if (currentPath.back() == '/')
        currentPath.pop_back();
    
}

void commandHandler(uint32_t commandIndex, std::vector<std::string>& inputArgs, std::istringstream& argsStringStream)
{
    switch (commandIndex)
    {
        case static_cast<uint32_t>(commandsEnum::Exit):
            PROGRAM_RUNNING = false;
            break;
        case static_cast<uint32_t>(commandsEnum::Echo):
            echoExec(argsStringStream);
            break;
        case static_cast<uint32_t>(commandsEnum::Pwd):
            std::cout << "Path: " << currentPath << '\n';
            break;
        case static_cast<uint32_t>(commandsEnum::Cd):
            cdExec(commandIndex, argsStringStream);
            break;
        case static_cast<uint32_t>(commandsEnum::Ls):
            lsExec();
            break;
        case static_cast<uint32_t>(commandsEnum::Clear):
            system("CLS");
            break;
        case static_cast<uint32_t>(commandsEnum::Touch):
            touchExec(argsStringStream);
            break;
        case static_cast<uint32_t>(commandsEnum::Mkdir):
            mkdirExec(argsStringStream);
            break;
        case static_cast<uint32_t>(commandsEnum::Rm):
            break;
        case static_cast<uint32_t>(commandsEnum::Cat):
            catExec(argsStringStream);
            break;
        case static_cast<uint32_t>(commandsEnum::Grep):
            grepExec(commandIndex, inputArgs, argsStringStream);
            break;
        case static_cast<uint32_t>(commandsEnum::Cp):
            break;
        case static_cast<uint32_t>(commandsEnum::Mv):
            break;
    }
}

void cpExec(){}

void echoExec(std::istringstream& argsStringStream)
{
    std::string echoOutput{};
	std::getline(argsStringStream, echoOutput);
    utility::trimString(echoOutput);

    std::cout << echoOutput << '\n';
}

void grepExec(uint32_t& commandIndex, std::vector<std::string>& inputArgs, std::istringstream& argsStringStream)
{
    std::string args{};
    std::getline(argsStringStream, args);
    setArgVec(commandIndex, inputArgs, args);

}

void handleRelativePathing(std::string& path)
{
    std::string tempPath{currentPath};

    if ((path[0] == '.') && (path[1] == '/'))
    {
        path.erase(0, 2);
        tempPath.append("/");
        tempPath.append(path);

        if (!isValidPath(tempPath))
        {
            std::cerr << RED_TEXT << "Error: " << tempPath << " is not a valid path." << NORMAL_TEXT << std::endl;
            return;
        }

        currentPath = tempPath;
        if (currentPath.back() == '/')
            currentPath.pop_back();
    }

    if (isValidPath(path))
    {
        currentPath = path;

        if (currentPath.back() == '/')
            currentPath.pop_back();
    }

    std::filesystem::path pathObj{currentPath};
    if (pathObj.parent_path() == pathObj.root_path())
    {
        if (currentPath.substr(2, 2) == "//")
            currentPath.erase(3, 1);
    }
}

bool isValidArgs(uint32_t& commandIndex, std::string& argsString)
{

    if (commandIndex == static_cast<uint32_t>(commandsEnum::Cd))
    {
        auto arr_it{std::find(std::begin(cdArgs), std::end(cdArgs), static_cast<std::string_view>(argsString))};
        if (arr_it == std::end(cdArgs))
            return false;

        return true;
    }
    else if (commandIndex == static_cast<uint32_t>(commandsEnum::Rm))
    {
        if (static_cast<std::string_view>(argsString) != rmRecFlag)
            return false;

        return true;
    }
    else if (commandIndex == static_cast<uint32_t>(commandsEnum::Grep))
    {
        auto arr_it{std::find(std::begin(grepArgs), std::end(grepArgs), static_cast<std::string_view>(argsString))};
        if (arr_it == std::end(grepArgs))
            return false;

        return true;
    }

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

void mkdirExec(std::istringstream& argsStringStream)
{
    std::filesystem::path dirPath{currentPath};
    std::string dirName{};
    argsStringStream >> dirName;
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

void setArgVec(uint32_t commandIndex, std::vector<std::string>& inputArgs, std::string& argsString)
{    
    std::istringstream args{argsString};
    std::string arg{};
    while (args >> arg)
    {
        inputArgs.push_back(arg);
    }
}

void touchExec(std::istringstream& argsStringStream)
{
    std::filesystem::path filePath{currentPath};
    std::string fileName{};
    argsStringStream >> fileName;
    filePath /= fileName;

    if (std::filesystem::exists(filePath))
    {
        std::cerr << RED_TEXT << "Error: File [" << fileName << "] already exists" << NORMAL_TEXT << std::endl;
        return;
    }
   
    std::ofstream file(filePath, std::ios::app);
}
