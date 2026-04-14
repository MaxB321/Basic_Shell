#include "command_handler.h"
#include "constants.h"
#include "enums.h"
#include "flags.h"
#include "utility.h"


std::string currentPath{std::getenv("USERPROFILE")};


void catExec(std::vector<std::string>& inputArgs, std::istringstream& argsStringStream)
{
    std::filesystem::path filePath{currentPath};
    std::string argsString{};
    std::getline(argsStringStream, argsString);
    setArgVec(argsString, inputArgs);
    if (inputArgs.size() < 1)
    {
        std::cerr << RED_TEXT << "Error: Add file argument." << NORMAL_TEXT << std::endl;
        return;
    }

    std::string& fileName{inputArgs[0]};
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

void cdExec(const uint32_t& commandIndex, std::istringstream& argsStringStream)
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

    if (currentPath == pathObj.root_path())
    {
        if (currentPath.back() != '/')
            currentPath.push_back('/');

        return;
    }
    
    if (pathObj.parent_path() == pathObj.root_path())
    {
        if (currentPath.substr(2, 2) == "//")
            currentPath.erase(3, 1);
    }
    
    if (currentPath.back() == '/')
        currentPath.pop_back();
    
}

void commandHandler(const uint32_t& commandIndex, std::vector<std::string>& inputArgs, std::istringstream& argsStringStream)
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
            touchExec(inputArgs, argsStringStream);
            break;
        case static_cast<uint32_t>(commandsEnum::Mkdir):
            mkdirExec(argsStringStream);
            break;
        case static_cast<uint32_t>(commandsEnum::Rm):
            rmExec(commandIndex, inputArgs, argsStringStream);
            break;
        case static_cast<uint32_t>(commandsEnum::Cat):
            catExec(inputArgs, argsStringStream);
            break;
        case static_cast<uint32_t>(commandsEnum::Grep):
            grepExec(commandIndex, inputArgs, argsStringStream);
            break;
        case static_cast<uint32_t>(commandsEnum::Cp):
            cpExec(inputArgs, argsStringStream);
            break;
        case static_cast<uint32_t>(commandsEnum::Mv):
            mvExec(inputArgs, argsStringStream);
            break;
    }
}

void cpExec(std::vector<std::string>& inputArgs, std::istringstream& argsStringStream)
{
    std::string argsString{};
    std::getline(argsStringStream, argsString);
    utility::trimString(argsString);
    setArgVec(argsString, inputArgs);

    if (inputArgs.size() < 2)
    {
        std::cerr << RED_TEXT << "Error: Copy Command Needs an input & output file" << NORMAL_TEXT << std::endl;
        return;
    }
    std::string& iFile{inputArgs[0]};
    std::string& oFile{inputArgs[1]};
    std::string commandString{};

    if (!std::filesystem::exists(iFile) && !std::filesystem::exists(oFile))
    {
        std::string iFilePath{'"' + currentPath + '/' + iFile + '"'};
        std::string oFilePath{'"' + currentPath + '/' + oFile + '"'};
        std::replace(iFilePath.begin(), iFilePath.end(), '/', '\\'); 
        commandString = "cmd.exe /C copy " + iFilePath + ' ' + oFilePath;
    }
    else if (!std::filesystem::exists(iFile) && std::filesystem::exists(oFile))
    {
        std::string iFilePath{currentPath + '/' + iFile};
        std::replace(iFilePath.begin(), iFilePath.end(), '/', '\\');
        commandString = "cmd.exe /C copy " + iFilePath + ' ' + oFile;
    }
    else if (std::filesystem::exists(iFile) && !std::filesystem::exists(oFile))
    {
        std::string oFilePath{currentPath + '/' + oFile};
        std::replace(oFilePath.begin(), oFilePath.end(), '/', '\\');
        commandString = "cmd.exe /C copy " + iFile + ' ' + oFilePath;
    }
    else
        commandString = "cmd.exe /C copy " + iFile + ' ' + oFile;

    STARTUPINFOA si_struct{};
    si_struct.cb = sizeof(si_struct);
    PROCESS_INFORMATION pi_struct{};
    

    if (!CreateProcessA(
        nullptr,
        commandString.data(),
        nullptr,
        nullptr,
        false,
        static_cast<DWORD>(0),
        nullptr,
        nullptr,
        &si_struct,
        &pi_struct
    ))
    {
        std::cerr << RED_TEXT << "Error: Process Could Not Be Created for Copy Command. (code: " << GetLastError() << ")" << NORMAL_TEXT << std::endl;
        return;
    }

    WaitForSingleObject(pi_struct.hProcess, INFINITE);
    CloseHandle(pi_struct.hProcess);
    CloseHandle(pi_struct.hThread);

}

void echoExec(std::istringstream& argsStringStream)
{
    std::string echoOutput{};
	std::getline(argsStringStream, echoOutput);
    utility::trimString(echoOutput);

    std::cout << echoOutput << '\n';
}

void grepExec(const uint32_t& commandIndex, std::vector<std::string>& inputArgs, std::istringstream& argsStringStream)
{
    std::string argsString{};
    std::getline(argsStringStream, argsString);
    setArgVec(argsString, inputArgs);
    if (inputArgs.size() < 2)
    {
        utility::trimString(argsString);
        std::cerr << RED_TEXT << "(" << argsString << ") is not a valid argument" << NORMAL_TEXT << std::endl;
        return;
    }

    if (isValidArgs(commandIndex, inputArgs[0]))
    {
        // both flags passed 
        if (isValidArgs(commandIndex, inputArgs[1]))
        {
            if (inputArgs.size() < 4)
            {
                utility::trimString(argsString);
                std::cerr << RED_TEXT << "(" << argsString << ") is not a valid argument" << NORMAL_TEXT << std::endl;
                return;
            }
            std::string& targetString{inputArgs[2]};
            std::string& fileName{inputArgs[3]};
            grepWithArgs(targetString, fileName);

            return;
        }

        // one flag passed 
        if (inputArgs.size() < 3)
        {
            utility::trimString(argsString);
            std::cerr << RED_TEXT << "(" << argsString << ") is not a valid argument" << NORMAL_TEXT << std::endl;
            return;
        }
        std::string& flag1{inputArgs[0]};
        std::string& targetString{inputArgs[1]};
        std::string& fileName{inputArgs[2]};
        grepWithArgs(flag1, targetString, fileName);      

        return;
    }

    std::string& targetString{inputArgs[0]};
    std::string& fileName{inputArgs[1]};
    std::string filePath{currentPath + '/' + fileName};

    if (!std::filesystem::exists(filePath))
    {
        std::cerr << RED_TEXT << "Error: [" << fileName << "] does not exist." << NORMAL_TEXT << std::endl;
        return;
    }

    if (std::filesystem::is_regular_file(filePath))
    {
        parseFileString(fileName, targetString, false);
        return;
    }
    if (std::filesystem::is_directory(filePath))
    {
        std::cerr << RED_TEXT << "Error: [" << fileName << "] is a directory." << NORMAL_TEXT << std::endl;
        return;
    }
}

void grepWithArgs(const std::string& flag, std::string& targetString, const std::string& fileName)
{
    std::string filePath{currentPath + '/' + fileName};

    if (flag == "-i")
    {
        if (!std::filesystem::exists(filePath))
        {
            std::cerr << RED_TEXT << "Error: [" << fileName << "] does not exist." << NORMAL_TEXT << std::endl;
            return;
        }

        if (std::filesystem::is_regular_file(filePath))
        {
            parseFileString(fileName, targetString, true);
            return;
        }
        if (std::filesystem::is_directory(filePath))
        {
            std::cerr << RED_TEXT << "Error: [" << fileName << "] is a directory." << NORMAL_TEXT << std::endl;
            return;
        }

        return;   
    }

    // recursive flag solution
    if (!std::filesystem::exists(filePath))
    {
        std::cerr << RED_TEXT << "Error: [" << fileName << "] does not exist." << NORMAL_TEXT << std::endl;
        return;
    }  

    if (std::filesystem::is_regular_file(filePath))
    {
        parseFileStringRec(fileName, targetString, false);
        return;
    }
    if (std::filesystem::is_directory(filePath))
    {
        parseDirStringRec(fileName, targetString, false);
        return;
    }
    std::cerr << RED_TEXT << "Error: [" << fileName << "] is not a file or directory." << NORMAL_TEXT << std::endl;
    

}

// Case Insensitive and Recursive Solution
void grepWithArgs(std::string& targetString, const std::string& fileName)
{
    std::string filePath{currentPath + '/' + fileName};
    if (!std::filesystem::exists(filePath))
    {
        std::cerr << RED_TEXT << "Error: [" << fileName << "] does not exist." << NORMAL_TEXT << std::endl;
        return;
    }

    if (std::filesystem::is_regular_file(filePath))
    {
        parseFileStringRec(fileName, targetString, true);
        return;
    }
    if (std::filesystem::is_directory(filePath))
    {
        parseDirStringRec(fileName, targetString, true);
        return;
    }
    std::cerr << RED_TEXT << "Error: [" << fileName << "] is not a file or directory." << NORMAL_TEXT << std::endl;
}

void handleRelativePathing(std::string& path)
{
    std::string tempPath{currentPath};
    bool isRoot{false};

    if (std::filesystem::path {tempPath}.root_path().string() == tempPath)
        isRoot = true;

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

    if (isRoot)
    {
        if (currentPath.substr(2, 2) == "//")
            currentPath.erase(3, 1);
    }
}

bool isValidArgs(const uint32_t& commandIndex, std::string& argsString)
{
    if (commandIndex == static_cast<uint32_t>(commandsEnum::Cd))
    {
        auto arr_it{std::find(std::begin(cdArgs), std::end(cdArgs), static_cast<std::string_view>(argsString))};
        if (arr_it == std::end(cdArgs))
            return false;
    }
    else if (commandIndex == static_cast<uint32_t>(commandsEnum::Rm))
    {
        if (static_cast<std::string_view>(argsString) != rmRecFlag)
            return false;
    }
    else if (commandIndex == static_cast<uint32_t>(commandsEnum::Grep))
    {
        auto arr_it{std::find(std::begin(grepArgs), std::end(grepArgs), static_cast<std::string_view>(argsString))};
        if (arr_it == std::end(grepArgs))
            return false;
    }

    return true;
}

bool isValidArgs(const uint32_t& commandIndex, std::vector<std::string>& inputArgs)
{
    if (commandIndex == static_cast<uint32_t>(commandsEnum::Cd))
    {
        for (std::string_view element : inputArgs)
        {
            auto arr_it{std::find(std::begin(cdArgs), std::end(cdArgs), static_cast<std::string_view>(element))};
            if (arr_it == std::end(cdArgs))
                return false;
        }  
    }
    else if (commandIndex == static_cast<uint32_t>(commandsEnum::Rm))
    {
        if (static_cast<std::string_view>(inputArgs[0]) != rmRecFlag)
            return false;
    }
    else if (commandIndex == static_cast<uint32_t>(commandsEnum::Grep))
    {
        for (std::string_view element : inputArgs)
        {
            auto arr_it{std::find(std::begin(grepArgs), std::end(grepArgs), static_cast<std::string_view>(element))};
            if (arr_it == std::end(grepArgs))
                return false;
        }
    }

    return true;
}

bool isValidPath(std::string& path)
{
    std::filesystem::path tempPath{path};
    if (!std::filesystem::exists(tempPath))
        return false;

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

void mvExec(std::vector<std::string>& inputArgs, std::istringstream& argsStringStream)
{
    std::string argsString{};
    std::getline(argsStringStream, argsString);
    utility::trimString(argsString);
    setArgVec(argsString, inputArgs);

    if (inputArgs.size() < 2)
    {
        std::cerr << RED_TEXT << "Error: Move Command Needs an input & output file" << NORMAL_TEXT << std::endl;
        return;
    }
    std::string& srcFile{inputArgs[0]};
    std::string& dstFile{inputArgs[1]};
    std::string commandString{};

    if (!std::filesystem::exists(srcFile) && !std::filesystem::exists(dstFile))
    {
        std::string srcFilePath{'"' + currentPath + '/' + srcFile + '"'};
        std::string dstFilePath{'"' + currentPath + '/' + dstFile + '"'};
        std::replace(srcFilePath.begin(), srcFilePath.end(), '/', '\\'); 
        commandString = "cmd.exe /C move " + srcFilePath + ' ' + dstFilePath;
    }
    else if (!std::filesystem::exists(srcFile) && std::filesystem::exists(dstFile))
    {
        std::string srcFilePath{currentPath + '/' + srcFile};
        std::replace(srcFilePath.begin(), srcFilePath.end(), '/', '\\');
        commandString = "cmd.exe /C move " + srcFilePath + ' ' + dstFile;
    }
    else if (std::filesystem::exists(srcFile) && !std::filesystem::exists(dstFile))
    {
        std::string dstFilePath{currentPath + '/' + dstFile};
        std::replace(dstFilePath.begin(), dstFilePath.end(), '/', '\\');
        commandString = "cmd.exe /C move " + srcFile + ' ' + dstFilePath;
    }
    else
        commandString = "cmd.exe /C move " + srcFile + ' ' + dstFile;

    STARTUPINFOA si_struct{};
    si_struct.cb = sizeof(si_struct);
    PROCESS_INFORMATION pi_struct{};
    

    if (!CreateProcessA(
        nullptr,
        commandString.data(),
        nullptr,
        nullptr,
        false,
        static_cast<DWORD>(0),
        nullptr,
        nullptr,
        &si_struct,
        &pi_struct
    ))
    {
        std::cerr << RED_TEXT << "Error: Process Could Not Be Created for Copy Command. (code: " << GetLastError() << ")" << NORMAL_TEXT << std::endl;
        return;
    }

    WaitForSingleObject(pi_struct.hProcess, INFINITE);
    CloseHandle(pi_struct.hProcess);
    CloseHandle(pi_struct.hThread);
}

void parseFileString(const std::string& fileName, std::string& target, const bool caseSensitive)
{
    uint32_t lineNumber{0};
    std::ifstream file(currentPath + '/' + fileName);
    std::string line{};

    if (!caseSensitive)
    {
        while (std::getline(file, line))
        {
            ++lineNumber;

            if (line.find(target) != std::string::npos) 
            {
                utility::trimString(line);
                std::cout << line << "\tline: " << lineNumber <<  "; File: [" << fileName << "]" << '\n';
                return;
            }
        }

        std::cout << target << " not found.\n";
        return;
    }

    utility::toLowerString(target);
    while (std::getline(file, line))
    {
        ++lineNumber;
        utility::toLowerString(line);
        if (line.find(target) != std::string::npos) 
        {
            utility::trimString(line);
            std::cout << line << "\tline: " << lineNumber <<  "; File: [" << fileName << "]" << '\n';
            return;
        }
    }

    std::cout << target << " not found.\n";
    return;
}

void parseFileStringRec(const std::string& fileName, std::string& target, const bool caseSensitive)
{
    uint32_t lineNumber{0};
    uint32_t prevLineNumber{0};
    std::ifstream file(currentPath + '/' + fileName);
    std::string line{};

    if (!caseSensitive)
    {
        while (std::getline(file, line))
        {
            ++lineNumber;

            if (line.find(target) != std::string::npos) 
            {
                prevLineNumber = lineNumber;
                utility::trimString(line);
                std::cout << line << "\tline: " << lineNumber <<  "; File: [" << fileName << "]" << '\n';
            }
        }
        if (prevLineNumber > 0)
            return;

        std::cout << target << " not found.\n";
        return;
    }

    utility::toLowerString(target);
    while (std::getline(file, line))
    {
        ++lineNumber;
        utility::toLowerString(line);
        if (line.find(target) != std::string::npos) 
        {
            prevLineNumber = lineNumber;
            utility::trimString(line);
            std::cout << line << "\tline: " << lineNumber <<  "; File: [" << fileName << "]" << '\n';
        }
    }
    if (prevLineNumber > 0)
        return;

    std::cout << target << " not found.\n";
    return;
}

void parseDirStringRec(const std::string& dirName, std::string& target, const bool caseSensitive)
{
    uint32_t lineNumber{0};
    bool targetFound{};
    std::string directory{currentPath + '/' + dirName};
    std::ifstream file{};
    std::string line{};

    if (!caseSensitive)
    {
        for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(directory))
        {
            lineNumber = 0;
            file.open(entry.path());
            while (std::getline(file, line))
            {
                ++lineNumber;

                if (line.find(target) != std::string::npos) 
                {
                    targetFound = true;
                    utility::trimString(line);
                    std::cout << line << "\tline: " << lineNumber <<  "; File: [" << entry.path().filename().string() << "]" << '\n';
                }
            }
            file.close();
            file.clear();

            if (COMMAND_INTERRUPTED)
            {
                std::cout << "^C\n" << std::endl;
                return;
            }
                
        }
        if (targetFound)
            return;

        std::cout << target << " not found.\n";
        return;
    }

    utility::toLowerString(target);
    for (const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(directory))
    {
        if (!entry.is_regular_file())
            continue;

        lineNumber = 0;
        file.open(entry.path());
        while (std::getline(file, line))
        {
            ++lineNumber;
            utility::toLowerString(line);
            if (line.find(target) != std::string::npos) 
            {
                targetFound = true;
                utility::trimString(line);
                std::cout << line << "\tline: " << lineNumber <<  "; File: [" << entry.path().filename().string() << "]" << '\n';
            }
        }
        file.close();
        file.clear();

        if (COMMAND_INTERRUPTED)
        {
            std::cout << "^C\n" << std::endl;
            return;
        }
    }
    if (targetFound)
        return;

    std::cout << target << " not found.\n";
    return;
}

void rmExec(const uint32_t& commandIndex, std::vector<std::string>& inputArgs, std::istringstream& argsStringStream)
{
    std::string argsString{};
    std::getline(argsStringStream, argsString);
    setArgVec(argsString, inputArgs);
    
    if (inputArgs.size() < 1)
    {
        std::cerr << RED_TEXT << "Error: Invalid Arguments." << NORMAL_TEXT << std::endl;
        return;
    }

    // recursive rm
    if (isValidArgs(commandIndex, inputArgs))
    {
        if (inputArgs.size() < 2)
        {
            std::cerr << RED_TEXT << "Error: Missing Argument." << NORMAL_TEXT << std::endl;
            return;
        }

        std::filesystem::directory_entry recEntry{currentPath + '/' + inputArgs[1]};
        
        if (std::filesystem::exists(recEntry))
        {
            std::filesystem::remove_all(recEntry);
            return;
        }

        std::cerr << RED_TEXT << "Error: File/Dir [" << recEntry << "] does not exist." << NORMAL_TEXT << std::endl;
        return;
    }

    std::filesystem::directory_entry entry{currentPath + '/' + inputArgs[0]};
    if (std::filesystem::exists(entry))
    {
        if (std::filesystem::is_regular_file(entry))
        {
            std::filesystem::remove(entry);
            return;
        }
        if (std::filesystem::is_directory(entry) && std::filesystem::is_empty(entry))
        {
            std::filesystem::remove(entry);
            return;
        }
        else if (std::filesystem::is_directory(entry) && !std::filesystem::is_empty(entry))
        {
            std::cerr << RED_TEXT << "Error: Dir [" << entry << "] is not empty. Use -r flag." << NORMAL_TEXT << std::endl;
            return;
        }
    }
    std::cerr << RED_TEXT << "Error: File/Dir [" << entry << "] does not exist." << NORMAL_TEXT << std::endl;
}

void setArgVec(std::string& argsString, std::vector<std::string>& inputArgs)
{    
    std::istringstream argsStream{argsString};
    std::string arg{};
    char ch{};

    while (argsStream >> ch)
    {
        if (ch == '"')
        {
            arg.clear();
            while (argsStream.get(ch) && ch != '"')
                arg += ch;

            inputArgs.push_back(arg);
        }
        else
        {
            arg = ch;
            while (argsStream.get(ch) && ch != ' ' && ch != '\t')
                arg += ch;

            inputArgs.push_back(arg);
        }
        
    }
}

void touchExec(std::vector<std::string>& inputArgs, std::istringstream& argsStringStream)
{
    std::filesystem::path filePath{currentPath};
    std::string argsString{};
    std::getline(argsStringStream, argsString);
    setArgVec(argsString, inputArgs);
    if (inputArgs.size() < 1)
    {
        std::cerr << RED_TEXT << "Error: Add file argument." << NORMAL_TEXT << std::endl;
        return;
    }

    std::string& fileName{inputArgs[0]};
    filePath /= fileName;

    if (std::filesystem::exists(filePath))
    {
        std::cerr << RED_TEXT << "Error: File [" << fileName << "] already exists" << NORMAL_TEXT << std::endl;
        return;
    }
   
    std::ofstream file(filePath, std::ios::app);
}
