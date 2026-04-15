#include "threading.h"


namespace
{
    std::mutex queueMutex{};
    std::mutex outputMutex{};
}


std::queue<std::filesystem::directory_entry> threadingFuncs::mkEntryQueue(std::string& directory)
{
    std::queue<std::filesystem::directory_entry> dirEntries{};
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(directory))
    {
        dirEntries.push(entry);
    }
    return dirEntries;
}

void threadingFuncs::mtParseDirStringRec(std::queue<std::filesystem::directory_entry>& dirEntries, std::string& target, bool caseSensitive)
{
    ThreadData* data1 = new ThreadData{
        &dirEntries,
        target
    };

    ThreadData* data2 = new ThreadData{
        &dirEntries,
        target
    };

    HANDLE thread1{};
    HANDLE thread2{};

    if (caseSensitive)
    {
        HANDLE thread1 = CreateThread(
            nullptr,
            0,
            mtParseFuncCs,
            data1,
            0,
            nullptr
        );

        HANDLE thread2 = CreateThread(
            nullptr,
            0,
            mtParseFuncCs,
            data2,
            0,
            nullptr
        );
    }
    else
    {
        HANDLE thread1 = CreateThread(
            nullptr,
            0,
            mtParseFuncCi,
            data1,
            0,
            nullptr
        );

        HANDLE thread2 = CreateThread(
            nullptr,
            0,
            mtParseFuncCi,
            data2,
            0,
            nullptr
        );
    }
    

    WaitForSingleObject(thread1, INFINITE);
    WaitForSingleObject(thread2, INFINITE);
    CloseHandle(thread1);
    CloseHandle(thread2);
}

// case insensitive
DWORD WINAPI threadingFuncs::mtParseFuncCi(LPVOID lpParam)
{
    ThreadData* data = static_cast<ThreadData*>(lpParam);
    std::queue<std::filesystem::directory_entry>& dirEntries = *data->dirEntries;
    std::string& target = data->target;

    delete data;
    return 0;
}

// case sensitive
DWORD WINAPI threadingFuncs::mtParseFuncCs(LPVOID lpParam)
{
    ThreadData* data = static_cast<ThreadData*>(lpParam);
    std::queue<std::filesystem::directory_entry>& dirEntries = *data->dirEntries;
    std::string& target = data->target;
    uint32_t lineNumber{0};
    bool targetFound{};
    std::ifstream file{};
    std::string line{};

    while (true)
    {
        std::filesystem::directory_entry entry{};

        {
            std::lock_guard<std::mutex> lock(queueMutex);

            if (dirEntries.empty())
                break;
            
            entry = dirEntries.front();
            dirEntries.pop(); 
        }

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
            break;
        }
    }

    delete data;
    return 0;
}
